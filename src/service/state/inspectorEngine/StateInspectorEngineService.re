open Wonderjs;

let deepCopyForRestore = Wonderjs.StateAPI.deepCopyForRestore;

let createState = Wonderjs.StateAPI.createState;

let getStateFromData = Wonderjs.StateAPI.getStateFromData;

let setStateToData = Wonderjs.StateAPI.setStateToData;

let getState = () => StateDataInspectorEngineService.getStateData().state;

let unsafeGetState = () =>
  Wonderjs.StateDataMainService.unsafeGetState(
    StateDataInspectorEngineService.getStateData(),
  );

let setState = (state: Wonderjs.StateDataMainType.state) =>
  Wonderjs.StateDataMainService.setState(
    StateDataInspectorEngineService.getStateData(),
    state,
  );

let setIsDebug = isDebug =>
  IsDebugMainService.setIsDebug(
    StateDataInspectorEngineService.getStateData(),
    isDebug,
  );