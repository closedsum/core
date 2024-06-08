// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Library
/// <reference path="../Cs/Library/Library_Common.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - library (c++)
var ObjectLibrary = CsScriptLibrary_Object;

// "typedefs" - functions
var check           = CommonLibrary.check;
var checkf          = CommonLibrary.checkf;

var ClassName = "NJsSceneComponent.FLibrary";

module.exports = class NJsSceneComponent
{
    static FLibrary = class Library
    {
        static NCached = class NamespaceCached
        {
            static NStr = class NamespaceStr
            {   
                // Number
                static AttachToComponent_KeepRelativeTransform          = ClassName + ".AttachToComponent_KeepRelativeTransform";
                static AttachToComponentChecked2_KeepRelativeTransform  = ClassName + ".AttachToComponentChecked2_KeepRelativeTransform";
            }
        }

        static FDisableCheck = class DisableCheck
        {
            static Setup()
            {
                // Number
                //NJsMath.FLibrary.IsGreaterThanChecked  = NJsMath.FLibrary.FDisableCheck.IsGreaterThanChecked;
                //NJsMath.FLibrary.IsGreaterThanChecked2 = NJsMath.FLibrary.FDisableCheck.IsGreaterThanChecked2;
            }

            // Number
            //static /*boolean*/ IsGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            //static /*boolean*/ IsGreaterThanChecked2(a /*number*/, b /*number*/) { return true; }
        }

        /**
        * @param {SceneComponent}   child 
        * @param {SceneComponent}   parent
        * @param {string}           socket
        * @returns {boolean}
        */
        static /*boolean*/ AttachToComponent_KeepRelativeTransform(child /*USceneComponent*/, parent /*USceneComponent*/, socket /*string*/)
        {
            let self    = NJsSceneComponent.FLibrary;
            let context = self.NCached.NStr.AttachToComponent_KeepRelativeTransform;

            if (!ObjectLibrary.SafeIsValid(context, child))
                return false;
            if (!ObjectLibrary.SafeIsValid(context, parent))
                return false;

            // TODO:
            // If socket is Valid, check socket Exists

            child.K2_AttachToComponent(parent, socket, EDetachmentRule.KeepRelative, EDetachmentRule.KeepRelative, EDetachmentRule.KeepRelative, false);
            return true;
        }

        /**
        * @param {string}           context
        * @param {SceneComponent}   child 
        * @param {SceneComponent}   parent
        * @param {string}           socket
        */
        static AttachToComponentChecked_KeepRelativeTransform(context /*string*/, child /*USceneComponent*/, parent /*USceneComponent*/, socket /*string*/)
        {
            let self  = NJsSceneComponent.FLibrary;

            check(ObjectLibrary.SafeIsValid(context, child));
            check(ObjectLibrary.SafeIsValid(context, parent));
            // TODO:
            // If socket is Valid, check socket Exists

            child.K2_AttachToComponent(parent, socket, EDetachmentRule.KeepRelative, EDetachmentRule.KeepRelative, EDetachmentRule.KeepRelative, false);
        }

        /**
        * @param {SceneComponent}   child 
        * @param {SceneComponent}   parent
        * @param {string}           socket
        */
        static AttachToComponentChecked2_KeepRelativeTransform(child /*USceneComponent*/, parent /*USceneComponent*/, socket /*string*/)
        {
            let self    = NJsSceneComponent.FLibrary;
            let context = self.NCached.NStr.AttachToComponentChecked2_KeepRelativeTransform;

            self.AttachToComponentChecked2_KeepRelativeTransform(context, child, parent, socket);
        }
    };
};