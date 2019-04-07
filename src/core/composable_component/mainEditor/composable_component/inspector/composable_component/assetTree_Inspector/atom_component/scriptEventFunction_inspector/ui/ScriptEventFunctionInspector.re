module Method = {
  let _buildBodyStr = (eventFunctionName, eventFunction, str) =>
    switch (eventFunction) {
    | None => str
    | Some(func) =>
      let funcStr = SerializeService.serializeFunction(func);

      {j|$str,
  $(eventFunctionName): $funcStr|j};
    };

  let convertEventFunctionDataToJsObjStr =
      ({init, update, dispose}: Wonderjs.StateDataMainType.eventFunctionData) => {
    let bodyStr =
      ""
      |> _buildBodyStr("init", init)
      |> _buildBodyStr("update", update)
      |> _buildBodyStr("dispose", dispose)
      |> Js.String.sliceToEnd(~from=1);

    {j| (function() {
    return {
      $bodyStr
    };
  }())
  |j};
  };

  let _convertEventFunctionJsObjStrToData = jsObjStr =>
    jsObjStr
    |> SerializeService.deserializeFunction
    |> ScriptEventFunctionEngineService.createScriptEventFunctionData;

  let updateEventFunctionData = (nodeId, name, eventFunctionJsObjStr) =>
    /* TODO check eventFunctionJsObjStr: should be valid */
    /* TODO update script component->event function data of the name */
    ScriptEventFunctionNodeAssetEditorService.setNodeData(
      nodeId,
      ScriptEventFunctionNodeAssetService.buildNodeData(
        ~name,
        ~eventFunctionData=
          _convertEventFunctionJsObjStrToData(eventFunctionJsObjStr),
      ),
    )
    |> StateLogicService.getAndSetEditorState;
};

let component =
  ReasonReact.statelessComponent("ScriptEventFunctionInspector");

let render =
    (
      (uiState, dispatchFunc),
      (nodeId, name, eventFunctionData),
      renameFunc,
      {state, send}: ReasonReact.self('a, 'b, 'c),
    ) => {
  let languageType =
    LanguageEditorService.unsafeGetType |> StateLogicService.getEditorState;

  <article
    key="ScriptEventFunctionInspector"
    className="wonder-scriptEventFunction-inspector">
    <h1> {DomHelper.textEl("ScriptEventFunction")} </h1>
    <hr />
    <StringInput
      label="Name"
      title={
        LanguageUtils.getInspectorLanguageDataByType(
          "scriptEventFunction-name-describe",
          languageType,
        )
      }
      defaultValue=name
      onBlur=renameFunc
      canBeNull=false
    />
    <div className="scriptEventFunction-data">
      <FileInput
        buttonText="Set EventFunction Data"
        inputValue={
          Method.convertEventFunctionDataToJsObjStr(eventFunctionData)
        }
        onSubmit={
          value => Method.updateEventFunctionData(nodeId, name, value)
        }
      />
    </div>
  </article>;
};

let make =
    (
      ~uiState,
      ~dispatchFunc,
      ~currentNodeId,
      ~name,
      ~eventFunctionData,
      ~renameFunc,
      _children,
    ) => {
  ...component,
  render: self =>
    render(
      (uiState, dispatchFunc),
      (currentNodeId, name, eventFunctionData),
      renameFunc,
      self,
    ),
};