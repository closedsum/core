// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// require('CsCoreLibrary/Library_SceneComponent.js');

declare namespace NJsSceneComponent {
    class FLibrary {

        /**
        * @param {SceneComponent}   child 
        * @param {SceneComponent}   parent
        * @param {string}           socket
        * @returns {boolean}
        */
        AttachToComponent_KeepRelativeTransform(child: SceneComponent, parent: SceneComponent, socket: string): boolean;

        /**
        * @param {string}           context 
        * @param {SceneComponent}   child 
        * @param {SceneComponent}   parent
        * @param {string}           socket
        */
        AttachToComponentChecked_KeepRelativeTransform(context: string, child: SceneComponent, parent: SceneComponent, socket: string): void;

        /**
        * @param {SceneComponent}   child 
        * @param {SceneComponent}   parent
        * @param {string}           socket
        */
        AttachToComponentChecked2_KeepRelativeTransform(child: SceneComponent, parent: SceneComponent, socket: string): void;
    }
}

declare type JsSceneComponentLibrary = NJsSceneComponent.FLibrary;