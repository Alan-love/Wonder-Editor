

import * as Curry from "../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as AppStore$WonderEditor from "../../../../../../../../../ui/store/AppStore.js";
import * as EventHandler$WonderEditor from "../../../../../../../../../ui/eventHandler/EventHandler.js";
import * as OptionService$WonderEditor from "../../../../../../../../../../service/primitive/OptionService.js";
import * as AssetNodeUtils$WonderEditor from "../utils/AssetNodeUtils.js";
import * as AssetTreeUtils$WonderEditor from "../composable_component/utils/AssetTreeUtils.js";
import * as EmptyEventHandler$WonderEditor from "../../../../../../../../../ui/eventHandler/EmptyEventHandler.js";
import * as StateEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/StateEditorService.js";
import * as SparseMapService$WonderCommonlib from "../../../../../../../../../../../../../node_modules/wonder-commonlib/lib/es6_global/src/SparseMapService.js";
import * as TreeAssetEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/asset/TreeAssetEditorService.js";
import * as TreeRootAssetEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/asset/TreeRootAssetEditorService.js";
import * as WDBNodeMapAssetEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/asset/WDBNodeMapAssetEditorService.js";
import * as FolderNodeMapAssetEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/asset/FolderNodeMapAssetEditorService.js";
import * as TextureNodeMapAssetEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/asset/TextureNodeMapAssetEditorService.js";
import * as MaterialNodeMapAssetEditorService$WonderEditor from "../../../../../../../../../../service/state/editor/asset/MaterialNodeMapAssetEditorService.js";
import * as RemoveAssetTreeNodeAssetLogicService$WonderEditor from "../../../../../../../../../../service/stateTuple/logic/asset/RemoveAssetTreeNodeAssetLogicService.js";

var setUndoValueToCopiedEngineState = EmptyEventHandler$WonderEditor.EmptyEventHandler[1];

function _setFolderNodeParent(folderId, parentFolderNodeId, editorState, folderNodeMap) {
  var __x = FolderNodeMapAssetEditorService$WonderEditor.setFolderNodeResultParent(parentFolderNodeId, SparseMapService$WonderCommonlib.unsafeGet(folderId, folderNodeMap));
  StateEditorService$WonderEditor.setState(FolderNodeMapAssetEditorService$WonderEditor.setResult(folderId, __x, editorState));
  return /* () */0;
}

function _setTextureNodeParent(textureComponent, parentFolderNodeId, editorState, textureNodeMap) {
  var __x = TextureNodeMapAssetEditorService$WonderEditor.setTextureNodeResultParent(parentFolderNodeId, SparseMapService$WonderCommonlib.unsafeGet(textureComponent, textureNodeMap));
  StateEditorService$WonderEditor.setState(TextureNodeMapAssetEditorService$WonderEditor.setResult(textureComponent, __x, editorState));
  return /* () */0;
}

function _setMaterialNodeParent(nodeId, parentFolderNodeId, editorState, materialNodeMap) {
  var __x = MaterialNodeMapAssetEditorService$WonderEditor.setMaterialNodeResultParent(parentFolderNodeId, SparseMapService$WonderCommonlib.unsafeGet(nodeId, materialNodeMap));
  StateEditorService$WonderEditor.setState(MaterialNodeMapAssetEditorService$WonderEditor.setResult(nodeId, __x, editorState));
  return /* () */0;
}

function _setWDBNodeParent(nodeId, parentFolderNodeId, editorState, wdbNodeMap) {
  var __x = WDBNodeMapAssetEditorService$WonderEditor.setWDBNodeResultParent(parentFolderNodeId, SparseMapService$WonderCommonlib.unsafeGet(nodeId, wdbNodeMap));
  StateEditorService$WonderEditor.setState(WDBNodeMapAssetEditorService$WonderEditor.setResult(nodeId, __x, editorState));
  return /* () */0;
}

function handleSelfLogic(param, _, param$1) {
  var sourceNodeId = param$1[1];
  var targetNodeId = param$1[0];
  var dispatchFunc = param[1];
  var editorState = StateEditorService$WonderEditor.getState(/* () */0);
  var match = TreeAssetEditorService$WonderEditor.isIdEqual(targetNodeId, sourceNodeId);
  if (match) {
    Curry._1(dispatchFunc, [
          AppStore$WonderEditor.UpdateAction,
          /* Update */[/* array */[/* Project */4]]
        ]);
    return /* () */0;
  } else {
    var editorState$1 = AssetTreeUtils$WonderEditor.setSpecificAssetTreeNodeIsShowChildrenFromEditorState(targetNodeId, true, editorState);
    var match$1 = OptionService$WonderEditor.unsafeGet(TreeAssetEditorService$WonderEditor.getSpecificTreeNodeById(sourceNodeId, OptionService$WonderEditor.unsafeGet(TreeRootAssetEditorService$WonderEditor.getAssetTreeRoot(editorState$1))));
    var match$2 = RemoveAssetTreeNodeAssetLogicService$WonderEditor.removeSpecificTreeNode(sourceNodeId, TreeRootAssetEditorService$WonderEditor.unsafeGetAssetTreeRoot(editorState$1));
    var editorState$2 = TreeRootAssetEditorService$WonderEditor.setAssetTreeRoot(AssetTreeUtils$WonderEditor.insertSourceTreeNodeToTargetTreeNodeChildren(targetNodeId, match$2[1], match$2[0]), editorState$1);
    var partial_arg = targetNodeId;
    var partial_arg$1 = targetNodeId;
    var partial_arg$2 = targetNodeId;
    var partial_arg$3 = targetNodeId;
    AssetNodeUtils$WonderEditor.handleSpeficFuncByAssetNodeType(match$1[/* type_ */2], /* tuple */[
          (function (param) {
              return _setFolderNodeParent(sourceNodeId, partial_arg, editorState$2, param);
            }),
          (function (param) {
              return _setTextureNodeParent(sourceNodeId, partial_arg$1, editorState$2, param);
            }),
          (function (param) {
              return _setMaterialNodeParent(sourceNodeId, partial_arg$2, editorState$2, param);
            }),
          (function (param) {
              return _setWDBNodeParent(sourceNodeId, partial_arg$3, editorState$2, param);
            })
        ], editorState$2);
    Curry._1(dispatchFunc, [
          AppStore$WonderEditor.UpdateAction,
          /* Update */[/* array */[/* Project */4]]
        ]);
    return /* () */0;
  }
}

var CustomEventHandler = /* module */[
  /* setUndoValueToCopiedEngineState */setUndoValueToCopiedEngineState,
  /* _setFolderNodeParent */_setFolderNodeParent,
  /* _setTextureNodeParent */_setTextureNodeParent,
  /* _setMaterialNodeParent */_setMaterialNodeParent,
  /* _setWDBNodeParent */_setWDBNodeParent,
  /* handleSelfLogic */handleSelfLogic
];

var MakeEventHandler = EventHandler$WonderEditor.MakeEventHandler([
      handleSelfLogic,
      setUndoValueToCopiedEngineState
    ]);

export {
  CustomEventHandler ,
  MakeEventHandler ,
  
}
/* MakeEventHandler Not a pure module */