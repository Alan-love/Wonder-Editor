import {setDefaultScene} from "../adaptorOperator/SceneOper";
import { init as initMain } from "../adaptorOperator/MainOper";
import {
    init as initDirector, loopBody as loopDirectorBody
    // setClearColor as setDirectorClearColor
} from "../adaptorOperator/DirectorOper";
import { Map } from "immutable";
import { containerConfig } from "../../config/containerConfig";
import { createState as createStateEdit, getState as getStateEdit, setState as setStateEdit } from "../editor/StateManagerEdit";
import { saveLoop as saveLoopEdit } from "../editor/LoopEdit";
import {setClearColor, setViewport as setDeviceViewport} from "../adaptorOperator/DeviceOper";
import {init as initComponentManager, prepare as prepareComponentManager} from "./ComponentManagerBuss";

export const getState = getStateEdit;

export const setState = setStateEdit;

export const createState = createStateEdit;

export const saveLoop = saveLoopEdit;

export const setViewport = setDeviceViewport;

export const initEditor = (state: Map<any, any>) => {
    var resultState: Map<any, any> = state;

    setDefaultScene();

    initDirector();

    resultState = prepareComponentManager(resultState);

    resultState = initComponentManager(resultState);

    return resultState;
};

export const initContainer = () => {
    var {
        canvasId,
        clearColor
    } = containerConfig;

    initMain(canvasId);

    setClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
};

export const loopBody = (state: Map<any, any>, time: number) => {
    loopDirectorBody(time);

    return state;
};
