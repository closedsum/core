// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Core
/// <reference path="../../Cs/Core.ts">/>

// require('Cs/Camera/Library_Camera.js');

declare namespace NJsCamera.FLibrary.FAnimate_FOV {
    class FParams {
        Component: CameraComponent;
        UpdateGroup: ECsUpdateGroup;
        Start: number;
        End: number;
        Time: number;
        EasingType: ECsEasingType;
    }
}

declare type NJsCamera_FLibrary_FAnimate_FOV_FParams = NJsCamera.FLibrary.FAnimate_FOV.FParams;

declare namespace NJsCamera {
    class FLibrary {
        Animate_FOV(core: FJsCore, inPayload: NJsCamera.FLibrary.FAnimate_FOV.FParams): CsRoutineHandle;
    }
}

declare type CameraLibrary = NJsCamera.FLibrary;