/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;

var Core;

module.exports = class NJsYield
{
    static FRoutineHandle = class RoutineHandleYield
    {
        constructor()
        {
            this.Handle = null;/*CsRoutineHandle*/
            this.Group = null;/*ECsUpdateGroup*/
            this.bNative = false;/*bool*/
        }

        SetCore(core)
        {
            Core = core;
        }

        /**
         * @param {object} yieldCommand 
         * @returns {boolean}
         */
        /*bool*/ CopyFromYield(yieldCommand /*object*/)
        {
            let context = "NJsYield.FRoutineHandle.CopyFromYield";

            check(CommonLibrary.IsValidObjectChecked(context, yieldCommand));

            // Check 'WaitForRoutineHandle' key exists for yieldCommand
            if ('WaitForRoutineHandle' in yieldCommand)
			{
                // Check yieldCommand.WaitForRoutineHandle is of type: CsRoutineHandle
                check(CommonLibrary.IsInstanceOfChecked(context, yieldCommand.WaitForRoutineHandle, CsRoutineHandle));
                // Check 'Group' key of type: ECsUpdateGroup exists for yieldCommand
                check(CommonLibrary.DoesKeyOfInstanceExistChecked(context, yieldCommand, 'Group', ECsUpdateGroup));
                // Check 'bNative' key of type: boolean exists for yieldCommand
                check(CommonLibrary.DoesKeyOfBoolExistChecked(context, yieldCommand, 'bNative'));

                this.Handle = yieldCommand.WaitForRoutineHandle;
                this.Group = yieldCommand.Group;
                this.bNative = yieldCommand.bNative;

                // Check coroutine associated with handle is running
                let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
                let groupName = UpdateGroupLibrary.ToString(this.Group);

                if (this.bNative)
                {
                    let SchedulerLibrary = CsScriptLibrary_CoroutineScheduler;
                    let result = SchedulerLibrary.IsRunning(context, Core.GetWorld(), this.Group, this.Handle);

                    checkf(result, context + ": coroutine assocated with NATIVE Handle for Group: " + groupName + " is NOT running.");
                }
                else
                {
                    let result = Core.GetCoroutineScheduler().IsRunning(this.Group, this.Handle);

                    checkf(result, context + ": coroutine assocated with SCRIPT Handle for Group: " + groupName + " is NOT running.");
                }
                return true;
            }
            return false;
        }

        /**
         * @returns {boolean}
         */
        /*bool*/ IsRunning()
        {
            if (this.bNative)
            {
                let SchedulerLibrary = CsScriptLibrary_CoroutineScheduler;
                return SchedulerLibrary.IsRunning(context, Core.GetWorld(), this.Group, this.Handle);
            }
            return Core.GetCoroutineScheduler().IsRunning(this.Group, this.Handle);
        }

        /**
         * @returns {boolean}
         */
        /*bool*/ Execute()
        {
            return IsRunning();
        }

        Reset()
        {
            this.Handle = null;
            this.Group = null;
            this.bNative = null;
        }
    }
};