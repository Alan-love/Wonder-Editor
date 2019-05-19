/* TODO add IntInput_test.re */
type state = {
  inputValue: option(string),
  isDragStart: bool,
};

type action =
  | DragStart
  | Change(option(string))
  | Blur
  | DragDrop;

/* TODO refactor(duplicate) extract from IntInput and FloatInput */

module Method = {
  let _change = event => {
    let inputVal =
      ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;

    switch (inputVal) {
    | "" => Change(Some(""))
    | "-" => Change(Some("-"))
    | value =>
      switch ([%re {|/^-?(0|[1-9][0-9]*)$/|}] |> Js.Re.test(value)) {
      | false => Change(None)
      | true => Change(Some(value))
      }
    };
  };

  let triggerOnChange = (value, onChangeFunc) =>
    switch (onChangeFunc) {
    | None => ()
    | Some(onChange) => onChange(int_of_string(value))
    };

  let triggerOnBlur = (value, onBlurFunc) =>
    switch (onBlurFunc) {
    | None => ()
    | Some(onBlur) => onBlur(int_of_string(value))
    };

  let handleChangeAction = (state, onChangeFunc, value) =>
    switch (value) {
    | None => ReasonReact.NoUpdate
    | Some("-") => ReasonReact.Update({...state, inputValue: Some("-")})
    | Some("") => ReasonReact.Update({...state, inputValue: None})
    | Some(value) =>
      ReasonReactUtils.updateWithSideEffects(
        {...state, inputValue: Some(value)}, _state =>
        triggerOnChange(value, onChangeFunc)
      )
    };

  let handleBlurAction = (state, (onChangeFunc, onBlurFunc), languageType) =>
    switch (state.inputValue) {
    | None
    | Some("-")
    | Some("") =>
      let value = "0";
      ReasonReactUtils.updateWithSideEffects(
        {...state, inputValue: Some(value)},
        _state => {
          triggerOnChange(value, onChangeFunc);
          triggerOnBlur(value, onBlurFunc);
        },
      );
    | Some("0") =>
      ReasonReactUtils.updateWithSideEffects(
        {...state, inputValue: Some("0")}, _state =>
        triggerOnBlur("0", onBlurFunc)
      )
    | Some(value) =>
      ReasonReactUtils.sideEffects(_state => triggerOnBlur(value, onBlurFunc))
    };

  let computeNewValue = (currentValue, (movementX, movementY)) => {
    let factor = 10;


     currentValue + movementX  - movementY ;
  };

  let isDragStart = ({isDragStart}) => isDragStart;

  let handleDragStart = (event, send) => {
    let e = ReactEventType.convertReactMouseEventToJsEvent(event);

    Wonderjs.DomExtend.requestPointerLock(e##target);

    send(DragStart);
  };

  let handleDragDrop = (event, (send, state), onDragDropFunc) =>
    isDragStart(state) ?
      {
        Wonderjs.DomExtend.exitPointerLock();

        onDragDropFunc(
          state.inputValue |> OptionService.unsafeGet |> int_of_string,
        );

        send(DragDrop);

        ();
      } :
      ();

  let handleDragOver = (event, (send, state)) =>
    isDragStart(state) ?
      {
        let e = ReactEventType.convertReactMouseEventToJsEvent(event);

        send(
          Change(
            Some(
              computeNewValue(
                state.inputValue |> OptionService.unsafeGet |> int_of_string,
                MouseEventService.getMovementDeltaWhenPointerLocked(e),
              )
              |> string_of_int,
            ),
          ),
        );

        ();
      } :
      ();

  let renderLabel = ((send, state), label, title, onDragDropFunc) =>
    switch (label) {
    | None => ReasonReact.null
    | Some(label) =>
      <div
        className="item-header component-label"
        onMouseDown=(event => handleDragStart(event, send))
        onMouseMove=(event => handleDragOver(event, (send, state)))
        onMouseUp=(
          event => handleDragDrop(event, (send, state), onDragDropFunc)
        )
        title={
          switch (title) {
          | None => ""
          | Some(title) => title
          }
        }>
        {DomHelper.textEl(label)}
      </div>
    };

  let renderContent = ((send, state)) =>
    <div className="item-content">
      <input
        className="input-component float-input"
        type_="text"
        value={
          switch (state.inputValue) {
          | None => ""
          | Some(value) => value
          }
        }
        onChange={_e => send(_change(_e))}
        onBlur={_e => send(Blur)}
      />
    </div>;
};

let component = ReasonReact.reducerComponent("FloatInput");

let reducer = ((onChangeFunc, onBlurFunc), action, state) => {
  let languageType =
    LanguageEditorService.unsafeGetType |> StateLogicService.getEditorState;

  switch (action) {
  | DragStart => ReasonReact.Update({...state, isDragStart: true})
  | DragDrop => ReasonReact.Update({...state, isDragStart: false})
  | Change(value) => Method.handleChangeAction(state, onChangeFunc, value)
  | Blur =>
    Method.handleBlurAction(state, (onChangeFunc, onBlurFunc), languageType)
  };
};

let render =
    (
      label,
      title,
      (onBlurFunc, onDragDropFunc),
      {state, handle, send}: ReasonReact.self('a, 'b, 'c),
    ) =>
  <article className="inspector-item wonder-float-input">
    {Method.renderLabel((send, state), label, title, onDragDropFunc)}
    {Method.renderContent((send, state))}
  </article>;

let make =
    (
      ~onDragDrop=_ => (),
      ~defaultValue: option(string)=?,
      ~label: option(string)=?,
      ~onChange: option(int => unit)=?,
      ~onBlur: option(int => unit)=?,
      ~title: option(string)=?,
      _children,
    ) => {
  ...component,
  initialState: () =>
    switch (defaultValue) {
    | None => {inputValue: Some("0"), isDragStart: false}
    | Some(value) => {inputValue: Some(value), isDragStart: false}
    },
  reducer: reducer((onChange, onBlur)),
  render: self => render(label, title, (onBlur, onDragDrop), self),
};