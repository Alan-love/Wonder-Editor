

import * as Curry from "../../../../../../../../../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../../../../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as Color$WonderEditor from "../../../../../../../../../../../../external/Color.js";
import * as ColorType$WonderEditor from "../../../../../../../../../../../../external/type/ColorType.js";
import * as ValueService$WonderEditor from "../../../../../../../../../../../../../service/atom/ValueService.js";
import * as LanguageUtils$WonderEditor from "../../../../../../../../../../../../utils/language/LanguageUtils.js";
import * as StateLogicService$WonderEditor from "../../../../../../../../../../../../../service/stateTuple/logic/StateLogicService.js";
import * as PickColorComponent$WonderEditor from "../../../../../../../../atom_component/PickColorComponent/ui/PickColorComponent.js";
import * as LanguageEditorService$WonderEditor from "../../../../../../../../../../../../../service/state/editor/LanguageEditorService.js";
import * as MainEditorMaterialMap$WonderEditor from "../../../atom_component/MainEditorMaterialMap.js";
import * as LightMaterialEngineService$WonderEditor from "../../../../../../../../../../../../../service/state/engine/LightMaterialEngineService.js";
import * as MainEditorFloatInputBaseComponent$WonderEditor from "../../../../../../atom_component/FloatInputBaseComponent/MainEditorFloatInputBaseComponent.js";
import * as LightMaterialDragTextureEventHandler$WonderEditor from "../eventHandler/LightMaterialDragTextureEventHandler.js";
import * as LightMaterialRemoveTextureEventHandler$WonderEditor from "../eventHandler/LightMaterialRemoveTextureEventHandler.js";
import * as LightMaterialShininessBlurEventHandler$WonderEditor from "../eventHandler/LightMaterialShininessBlurEventHandler.js";
import * as LightMaterialCloseColorPickEventHandler$WonderEditor from "../eventHandler/LightMaterialCloseColorPickEventHandler.js";

function getColor(materialComponent, param) {
  return Color$WonderEditor.getHexString(StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                    return LightMaterialEngineService$WonderEditor.getLightMaterialDiffuseColor(materialComponent, param);
                  })));
}

function changeColor(materialComponent, value) {
  var __x = Color$WonderEditor.getEngineColorRgbArr(ColorType$WonderEditor.convertColorObjToColorPickType(value));
  return StateLogicService$WonderEditor.getAndRefreshEngineStateWithFunc((function (param) {
                return LightMaterialEngineService$WonderEditor.setLightMaterialDiffuseColor(__x, materialComponent, param);
              }));
}

var closeColorPick = LightMaterialCloseColorPickEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithCopiedEngineState */1];

var onDrop = LightMaterialDragTextureEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithNoCopyEngineState */0];

function removeTexture(param, param$1, materialComponent) {
  var match = StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
          return LightMaterialEngineService$WonderEditor.getLightMaterialDiffuseMap(materialComponent, param);
        }));
  if (match !== undefined) {
    return Curry._3(LightMaterialRemoveTextureEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithNoCopyEngineState */0], /* tuple */[
                param[0],
                param[1]
              ], /* () */0, materialComponent);
  } else {
    return /* () */0;
  }
}

function blurShininessEvent(param, materialComponent, shininessValue) {
  var match = ValueService$WonderEditor.isValueEqual(/* Float */1, shininessValue, StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
              return LightMaterialEngineService$WonderEditor.getLightMaterialShininess(materialComponent, param);
            })));
  if (match) {
    return /* () */0;
  } else {
    return Curry._3(LightMaterialShininessBlurEventHandler$WonderEditor.MakeEventHandler[/* pushUndoStackWithCopiedEngineState */1], /* tuple */[
                param[0],
                param[1]
              ], materialComponent, shininessValue);
  }
}

function changeShininess(materialComponent, value) {
  return StateLogicService$WonderEditor.getAndRefreshEngineStateWithFunc((function (param) {
                return LightMaterialEngineService$WonderEditor.setLightMaterialShininess(value, materialComponent, param);
              }));
}

var Method = /* module */[
  /* getColor */getColor,
  /* changeColor */changeColor,
  /* closeColorPick */closeColorPick,
  /* onDrop */onDrop,
  /* removeTexture */removeTexture,
  /* blurShininessEvent */blurShininessEvent,
  /* changeShininess */changeShininess
];

var component = ReasonReact.statelessComponent("MainEditorLightMaterial");

function render(param, materialComponent, _self) {
  var dispatchFunc = param[1];
  var uiState = param[0];
  var languageType = StateLogicService$WonderEditor.getEditorState(LanguageEditorService$WonderEditor.unsafeGetType);
  var partial_arg = /* tuple */[
    uiState,
    dispatchFunc
  ];
  var partial_arg$1 = /* tuple */[
    uiState,
    dispatchFunc
  ];
  return React.createElement("article", {
              className: "wonder-light-material"
            }, ReasonReact.element(undefined, undefined, PickColorComponent$WonderEditor.make("Diffuse Color", LanguageUtils$WonderEditor.getInspectorLanguageDataByType("material-diffuseColor-describe", languageType), (function (param) {
                        return Color$WonderEditor.getHexString(StateLogicService$WonderEditor.getEngineStateToGetData((function (param) {
                                          return LightMaterialEngineService$WonderEditor.getLightMaterialDiffuseColor(materialComponent, param);
                                        })));
                      }), (function (param) {
                        return changeColor(materialComponent, param);
                      }), Curry._2(closeColorPick, /* tuple */[
                          uiState,
                          dispatchFunc
                        ], materialComponent), /* array */[])), ReasonReact.element(undefined, undefined, MainEditorMaterialMap$WonderEditor.make(uiState, dispatchFunc, materialComponent, "Diffuse Map", LightMaterialEngineService$WonderEditor.getLightMaterialDiffuseMap, onDrop, removeTexture, false, LanguageUtils$WonderEditor.getInspectorLanguageDataByType("material-diffuseMap-describe", languageType), /* array */[])), ReasonReact.element(undefined, undefined, MainEditorFloatInputBaseComponent$WonderEditor.make((function (param) {
                        return blurShininessEvent(partial_arg, materialComponent, param);
                      }), "Shininess", (function (param) {
                        return LightMaterialEngineService$WonderEditor.getLightMaterialShininess(materialComponent, param);
                      }), (function (param) {
                        return StateLogicService$WonderEditor.getAndRefreshEngineStateWithFunc((function (param$1) {
                                      return LightMaterialEngineService$WonderEditor.setLightMaterialShininess(param, materialComponent, param$1);
                                    }));
                      }), (function (param) {
                        return blurShininessEvent(partial_arg$1, materialComponent, param);
                      }), LanguageUtils$WonderEditor.getInspectorLanguageDataByType("material-shininess-describe", languageType), /* array */[])));
}

function make(uiState, dispatchFunc, materialComponent, _children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return render(/* tuple */[
                          uiState,
                          dispatchFunc
                        ], materialComponent, self);
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

export {
  Method ,
  component ,
  render ,
  make ,
  
}
/* component Not a pure module */
