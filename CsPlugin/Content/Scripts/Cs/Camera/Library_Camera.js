// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Core
/// <reference path="../../Cs/Core.ts">/>
// Library
/// <reference path="../../Cs/Library/Library_Common.ts">/>
/// <reference path="../../Cs/Library/Library_Math.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsMath = require('Cs/Library/Library_Math.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;
/** @type {JsMathLibrary} */ var JsMathLibrary = NJsMath.FLibrary;

// "typedefs" - library (c++)
var MathLibrary         = CsScriptLibrary_Math;
var TimeManagerLibrary  = CsScriptLibrary_Manager_Time;

// "typedefs" - functions
var checkf              = CommonLibrary.checkf;
var check               = CommonLibrary.check;
var IsInstanceOfChecked = CommonLibrary.IsInstanceOfChecked;
var IsBoolChecked       = CommonLibrary.IsBoolChecked;
    //  Math
var IsGreaterThanChecked             = JsMathLibrary.IsGreaterThanChecked;
var IsGreaterThanOrEqualChecked      = JsMathLibrary.IsGreaterThanOrEqualChecked;
var IsLessThanOrEqualChecked         = JsMathLibrary.IsLessThanOrEqualChecked;
var IsFloatGreaterThanOrEqualChecked = JsMathLibrary.IsFloatGreaterThanOrEqualChecked;
var IsFloatLessThanOrEqualChecked    = JsMathLibrary.IsFloatLessThanOrEqualChecked;

// Globals
var ClassName = "NJsCamera.FLibrary";

module.exports = class NJsCamera
{
    static FLibrary = class Library
    {
        static NCached = class NamespaceCached
        {
            static NStr = class NamespaceStr
            {
                static Animate_FOV          = ClassName + ".Animate_FOV";
                static Animate_FOV_Internal = ClassName + ".Animate_FOV_Internal";
            }
        }

        static FAnimate_FOV = class _Animate_FOV
        {
            static FParams = class Params
            {
                constructor()
                {
                    /** @type {CameraComponent} */  this.Component = null;
                    /** @type {ECsUpdateGroup} */   this.UpdateGroup = null;
                    /** @type {number} */           this.Start = 0.0;
                    /** @type {number} */           this.End = 0.0;
                    /** @type {number} */           this.Time = 0.0;
                    /** @type {ECsEasingType} */    this.EasingType = ECsEasingType.Linear;
                    /** @type {boolean} */          this.bLog = false;
                }

                /*boolean*/ IsValidChecked(context /*string*/)
                {
                    IsInstanceOfChecked(context, this.Component, CameraComponent);
                    IsGreaterThanOrEqualChecked(context, this.Start, 0.0);
                    IsLessThanOrEqualChecked(context, this.End, 360.0);
                    IsGreaterThanChecked(context, this.Time, 0.0);
                    checkf(this.EasingType !== ECsEasingType.ECsEasingType_MAX, context + ": EasingType == ECsEasingType_MAX is NOT Valid.");
                    IsBoolChecked(context, this.bLog);
                    return true;
                }
            }
        }
    
        /**
        * @param {FJsCore}                                  core 
        * @param {NJsCamera.FLibrary.FAnimate_FOV.FParams} params 
        * @returns {CsRoutineHandle}
        */
        static /*CsRoutineHandle*/ Animate_FOV(core /*FJsCore*/, params /*NJsCamera.FLibrary.FAnimate_FOV.FParams*/)
        {
            let self    = NJsCamera.FLibrary;
            let context = self.NCached.NStr.Animate_FOV;

            params.IsValidChecked(context);

            /** @type {FJCoroutineScheduler} */
            let scheduler = core.GetCoroutineScheduler();
    
            /** @type {ECsUpdateGroup} */               let group   = params.UpdateGroup;
            /** @type {NJsCoroutine_NPayload_FImpl} */  let payload = scheduler.AllocatePayload(group);
        
            let func                = self.Animate_FOV_Internal();
            payload.CoroutineImpl   = func;
            payload.StartTime.Time  = TimeManagerLibrary.GetTime(context, core.GetWorld(), group);
            payload.Owner.SetObject(core.GetWorld());
    
            const COMPONENT = 0;
            payload.SetValue(COMPONENT, params.Component);
            const START = 1;
            payload.SetValue(START, params.Start);
            const END = 2;
            payload.SetValue(END, params.End);
            const TIME = 3;
            payload.SetValue(TIME, params.Time);
            const EASING = 4;
            payload.SetValue(EASING, params.EasingType);
            const LOG = 5;
            payload.SetValue(LOG, params.bLog);

            /** @type {CsRoutineHandle} */ let handle = scheduler.Start(payload);
            return handle
        }
    
        static * Animate_FOV_Internal()
        {
            let self    = NJsCamera.FLibrary;
            let context = self.NCached.NStr.Animate_FOV_Internal;
    
            /** @type {FJsRoutine} */
            let r;

            // COROUTINE BEGIN
            r = yield;
    
            const COMPONENT = 0;
            /** @type {CameraComponent} */  let component = r.GetValue(COMPONENT);
            const START = 1;
            /** @type {number} */           let start = r.GetValue(START);
            const END = 2;
            /** @type {number} */           let end = r.GetValue(END);
            const TIME = 3;
            /** @type {number} */           let time = r.GetValue(TIME);
            const EASING = 4;
            /** @type {ECsEasingType} */    let easing = r.GetValue(EASING);
            const LOG = 5;
            /** @type {boolean} */          let bLog = r.GetValue(LOG);
           
            do 
            {
                let timeAsPercent = r.ElapsedTime.Time / time;
                let fov           = MathLibrary.EasePercent(context, easing, timeAsPercent, start, end);
                
                if (bLog)
                {
                    console.log(context + ": Time: " + r.ElapsedTime.Time + " (" + timeAsPercent + ")" + " Start: " + start + " End: " + end + " Current: " + fov);
                }

                component.SetFieldOfView(fov);

                r = yield;
            } while (r.ElapsedTime.Time < time)

            if (bLog)
            {
                console.log(context + ": Time: " + r.ElapsedTime.Time + " (1.0)" + " Start: " + start + " End: " + end + " Current: " + end);
            }

            component.SetFieldOfView(end);

            // COROUTINE END
            r.EndOfExecution();
            return;
        }
    };
};