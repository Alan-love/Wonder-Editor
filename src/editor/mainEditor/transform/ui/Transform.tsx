import * as React from "react";
import Translation from "./component/Translation";
import { setCurrentGameObjectTranslation} from "../logic/view/TransformView";

interface IProps{
}

export default class Transform extends React.Component<IProps,any>{
    constructor(props:IProps){
        super(props);
    }

    render(){
        return(
            <div>
                <div className="root-btn">
                    <Translation translate={setCurrentGameObjectTranslation}></Translation>
                    {/*<Rotation rotate={setTriangleEulerAngle}></Rotation>*/}
                </div>
            </div>
        )
    }
}