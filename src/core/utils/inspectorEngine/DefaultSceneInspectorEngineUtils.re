let getAmbientLightArr = () => [|0.2, 0.2, 0.2|];

let _initCameraAddToSceneGameObject = (camera, inspectorEngineState) =>
  inspectorEngineState
  |> TransformEngineService.setLocalPosition(
       (0., 0., 1.1),
       GameObjectComponentEngineService.unsafeGetTransformComponent(
         camera,
         inspectorEngineState,
       ),
     )
  |> BasicCameraViewEngineService.activeBasicCameraView(
       inspectorEngineState
       |> GameObjectComponentEngineService.unsafeGetBasicCameraViewComponent(
            camera,
          ),
     )
  |> SceneEngineService.addSceneChild(camera);
let _initDirectionLightAddToSceneGameObject =
    (directionLight, inspectorEngineState) =>
  inspectorEngineState
  |> TransformEngineService.setTransformLocalEulerAngles(
       (145., 15., 0.),
       GameObjectComponentEngineService.unsafeGetTransformComponent(
         directionLight,
         inspectorEngineState,
       ),
     )
  |> SceneEngineService.addSceneChild(directionLight);

let _initEmptyGameObjectAddToSceneGameObject =
    (emptyGameObject, inspectorEngineState) =>
  inspectorEngineState |> SceneEngineService.addSceneChild(emptyGameObject);

let _initAmbientLight = inspectorEngineState =>
  inspectorEngineState
  |> SceneEngineService.setAmbientLightColor(getAmbientLightArr());

let createDefaultScene = inspectorEngineState => {
  let (inspectorEngineState, camera) =
    PrimitiveEngineService.createCamera(inspectorEngineState);
  let (inspectorEngineState, directionLight) =
    PrimitiveEngineService.createDirectionLight(inspectorEngineState);
  let (inspectorEngineState, emptyGameObject) =
    GameObjectEngineService.create(inspectorEngineState);

  let inspectorEngineState =
    inspectorEngineState
    |> _initCameraAddToSceneGameObject(camera)
    |> _initDirectionLightAddToSceneGameObject(directionLight)
    |> _initEmptyGameObjectAddToSceneGameObject(emptyGameObject)
    |> _initAmbientLight;

  (emptyGameObject, inspectorEngineState);
};