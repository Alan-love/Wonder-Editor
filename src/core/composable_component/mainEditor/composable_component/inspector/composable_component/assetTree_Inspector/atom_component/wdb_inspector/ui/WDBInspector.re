module Method = {};

let component = ReasonReact.statelessComponent("WDBInspector");

let render = (name, (onChangeFunc, onBlurFunc), _self) =>
  <div className="inspector-asset-wdb">
    <h1> {DomHelper.textEl("Model")} </h1>
    <hr />
    <div className="inspector-item">
      <div className="item-header">
        <span className=""> {DomHelper.textEl("Name:")} </span>
      </div>
      <div className="item-content">
        <input
          className="input-component float-input"
          type_="text"
          value=name
          onChange=onChangeFunc
          onBlur=onBlurFunc
        />
      </div>
    </div>
  </div>;

let make = (~name, ~onChangeFunc, ~onBlurFunc, _children) => {
  ...component,
  render: _self => render(name, (onChangeFunc, onBlurFunc), _self),
  /* didMount: _self =>
     MaterialInspectorEngineUtils.createMaterialSphereInToInspectorCanvas(
       type_,
       materialComponent,
     ), */
  didMount: _self => Js.log("fdccck"),
  willUnmount: _self =>
    (
      StateEditorService.getState(),
      StateInspectorEngineService.unsafeGetState(),
    )
    |> InspectorEngineGameObjectLogicService.disposeInspectorEngineParentGameObjectAllChild,
};