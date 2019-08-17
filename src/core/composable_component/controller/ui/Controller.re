open LanguageType;

open ColorType;

open Color;

open UserDataType;

type retainedProps = {updateTypeArr: UpdateStore.updateComponentTypeArr};

type state = {isShowRepoList: bool};

type action =
  | ShowRepoList
  | HideRepoList;

module Method = {
  /* let buildOperateExtensionComponent = () =>
     <div className="header-item">
       <div className="component-item">
         <FileInput
           buttonText="show Input"
           onSubmit=(value => addExtension(value))
         />
       </div>
     </div>; */
  let changeLanguage = languageType =>
    switch (languageType) {
    | EN =>
      LocalStorage.setValue("language", "ZH");
      DomHelper.reloadLocationFromCacheFirst(.);
    | ZH =>
      LocalStorage.setValue("language", "EN");
      DomHelper.reloadLocationFromCacheFirst(.);
    };

  let handleChangeCurrentTransformGizmoType = (dispatchFunc, type_) => {
    open SceneViewType;

    StateEditorService.getState()
    |> CurrentTransformGizmoSceneViewEditorService.mark(type_)
    |> SelectTransformGizmoSceneViewEditorService.markNotSelectAnyTransformGizmo
    |> StateEditorService.setState
    |> ignore;

    StateLogicService.getAndRefreshEngineState();

    dispatchFunc(AppStore.UpdateAction(Update([|UpdateStore.Controller|])))
    |> ignore;
  };

  let _handleChangeCurrentTransformGizmoCoordinateSystem = coordinateSystem => {
    StateEditorService.getState()
    |> CoordinateSystemTransformGizmoSceneViewEditorService.setCoordinateSystem(
         coordinateSystem,
       )
    |> StateEditorService.setState
    |> ignore;

    StateLogicService.getAndRefreshEngineState();

    ();
  };

  let _getCurrentTransformGizmoType = () =>
    CurrentTransformGizmoSceneViewEditorService.getCurrentGizmoType
    |> StateLogicService.getEditorState;

  let _getCurrentTransformGizmoCoordinateSystem = () =>
    CoordinateSystemTransformGizmoSceneViewEditorService.getCoordinateSystem
    |> StateLogicService.getEditorState;

  let _isTransformGizmoCoordinateSystemSwitchDisable = () =>
    switch (_getCurrentTransformGizmoType()) {
    | Scale => true
    | _ => false
    };

  let buildTransformComponent = (uiState, dispatchFunc, languageType) =>
    <div className="header-item">
      <div className="component-item">
        <TransformGizmoSwitch
          key={DomHelper.getRandomKey()}
          data=[|
            {
              type_: SceneViewType.Translation,
              onChangeFunc:
                handleChangeCurrentTransformGizmoType(dispatchFunc),
            },
            {
              type_: SceneViewType.Rotation,
              onChangeFunc:
                handleChangeCurrentTransformGizmoType(dispatchFunc),
            },
            {
              type_: SceneViewType.Scale,
              onChangeFunc:
                handleChangeCurrentTransformGizmoType(dispatchFunc),
            },
          |]
          defaultType={_getCurrentTransformGizmoType()}
        />
        <TransformGizmoCoordinateSystemSwitch
          key={DomHelper.getRandomKey()}
          onChange=_handleChangeCurrentTransformGizmoCoordinateSystem
          defaultCoordinateSystem={_getCurrentTransformGizmoCoordinateSystem()}
          isDisable={_isTransformGizmoCoordinateSystemSwitchDisable()}
        />
      </div>
    </div>;

  let renderRunAndStop = (uiState, dispatchFunc, languageType) =>
    <div
      className="controller-runAndStop"
      title={
        LanguageUtils.getControllerLanguageDataByType(
          "run-describe",
          languageType,
        )
      }
      onClick={
        _e => {
          StateEditorService.getIsRun() ?
            ControllerUtils.stop(dispatchFunc) : ControllerUtils.run(uiState);

          dispatchFunc(AppStore.UpdateAction(Update([|UpdateStore.All|])))
          |> ignore;
        }
      }>
      {
        StateEditorService.getIsRun() ?
          <img src="./public/img/stop.png" /> :
          <img src="./public/img/run.png" />
      }
    </div>;

  let _isCurrentRepo = (currentId, targetId) => currentId === targetId;

  let renderRepoListComponent = send => {
    let editorState = StateEditorService.getState();

    let {id as currentId} =
      UserDataEditorService.getCurrentRepo(editorState);
    let userRepoArray = UserDataEditorService.getUserRepos(editorState);
    let userId = UserDataEditorService.getUserId(editorState);
    let hashCode = UserDataEditorService.getHashCode(editorState);

    <Modal
      title={j|项目列表|j}
      closeFunc={() => send(HideRepoList)}
      content={
        userRepoArray
        |> Js.Array.map(({id, name, description, filePath}) => {
             let url =
               ClientConfig.getEditorPath()
               ++ {j|/?userId=$userId&repoId=$id&code=$hashCode|j};

             <div
               className={
                 "content-repo "
                 ++ (_isCurrentRepo(currentId, id) ? "repo-notHover" : "")
               }
               key={id |> string_of_int}
               onClick={
                 _e =>
                   _isCurrentRepo(currentId, id) ?
                     () : DomHelper.setLocationHref(url)
               }>
               <div className="repo-name">
                 {DomHelper.textEl({j|项目名称: $name|j})}
               </div>
               <div className="repo-description">
                 {DomHelper.textEl({j|项目描述: $description|j})}
               </div>
               {
                 _isCurrentRepo(currentId, id) ?
                   <div className="repo-current">
                     {DomHelper.textEl("CURRENT")}
                   </div> :
                   ReasonReact.null
               }
             </div>;
           })
      }
    />;
  };

  let renderUserRepoComponent = send => {
    let editorState = StateEditorService.getState();

    DebugSettingEditorService.getIsTestLocal(editorState)
    |> WonderLog.Log.print ?
      {
        let {id, name, description, filePath} =
          UserDataEditorService.getCurrentRepo(editorState);
        <>
          <div className="other-currentRepo">
            <a href={ClientConfig.getHostPlatformPath()} target="view_window">
              <img src="./public/img/userHome.png" />
              <span className="currentRepo-name">
                {DomHelper.textEl({j|$name|j})}
              </span>
            </a>
          </div>
          <div className="other-repoList" onClick={_e => send(ShowRepoList)}>
            <img src="./public/img/repoList.png" />
            <span className="repoList-name">
              {DomHelper.textEl({j|项目列表|j})}
            </span>
          </div>
        </>;
      } :
      ReasonReact.null;
  };
};

let component = ReasonReact.reducerComponentWithRetainedProps("Controller");

let reducer = (dispatchFunc, action, state) =>
  switch (action) {
  | ShowRepoList =>
    ReasonReactUtils.updateWithSideEffects(
      {...state, isShowRepoList: true}, _state =>
      dispatchFunc(
        AppStore.UpdateAction(Update([|UpdateStore.Controller|])),
      )
      |> ignore
    )

  | HideRepoList =>
    ReasonReactUtils.updateWithSideEffects(
      {...state, isShowRepoList: false}, _state =>
      dispatchFunc(
        AppStore.UpdateAction(Update([|UpdateStore.Controller|])),
      )
      |> ignore
    )
  };

let render =
    (
      uiState: AppStore.appState,
      dispatchFunc,
      {state, send}: ReasonReact.self('a, 'b, 'c),
    ) => {
  let languageType =
    LanguageEditorService.unsafeGetType |> StateLogicService.getEditorState;

  <article key="controller" className="wonder-controller-component">
    <div className="header-controller">
      <div className="controller-transform">
        {Method.buildTransformComponent(uiState, dispatchFunc, languageType)}
      </div>
      {Method.renderRunAndStop(uiState, dispatchFunc, languageType)}
      <div className="controller-other">
        {Method.renderUserRepoComponent(send)}
        <div
          className="other-language"
          onClick={_e => Method.changeLanguage(languageType)}>
          {
            switch (languageType) {
            | EN => DomHelper.textEl({j|中文|j})
            | ZH => DomHelper.textEl({j|English|j})
            }
          }
        </div>
      </div>
    </div>
    {
      state.isShowRepoList ?
        Method.renderRepoListComponent(send) : ReasonReact.null
    }
  </article>;
};

let shouldUpdate =
    ({newSelf}: ReasonReact.oldNewSelf('a, retainedProps, 'c)) =>
  newSelf.retainedProps.updateTypeArr
  |> StoreUtils.shouldComponentUpdate(UpdateStore.Controller);

let make =
    (~uiState: AppStore.appState, ~dispatchFunc, ~isShowRepoList, _children) => {
  ...component,
  retainedProps: {
    updateTypeArr: StoreUtils.getUpdateComponentTypeArr(uiState),
  },
  initialState: () => {isShowRepoList: isShowRepoList},
  reducer: reducer(dispatchFunc),
  shouldUpdate,
  render: self => render(uiState, dispatchFunc, self),
};