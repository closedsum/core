/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

var Core;

module.exports = class NJsProjectile
{
    static NData = class Data
    {
        static IData = class InterfaceData
        {
            static IsImplementedByChecked(context, o)
            {
                check(CommonLibrary.IsValidObjectChecked(context, o));

                // GetLifeTime()
                check(this.Implements_GetLifeTimeChecked(context, o));
                // GetInitialSpeed()
                check(this.Implements_GetInitialSpeedChecked(context, o));
                // GetMaxSpeed()
                check(this.Implements_GetMaxSpeedChecked(context, o));
                // GetGravityScale()
                check(this.Implements_GetGravityScaleChecked(context, o));
                return true;
            }

            static IsImplementedBy(o)
            {
                if (!CommonLibrary.IsValidObject(o))
                    return false;
                // GetLifeTime()
                if (!this.Implements_GetLifeTime(o))
                    return false;
                // GetInitialSpeed()
                if (!this.Implements_GetInitialSpeed(o))
                    return false;
                // GetMaxSpeed()
                if (!this.Implements_GetMaxSpeed(o))
                    return false;
                // GetGravityScale()
                if (!this.Implements_GetGravityScale(o))
                    return false;
                return true;
            }

            static Implements_GetLifeTimeChecked(context, o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number_Checked(context, o.GetLifeTime, 0, o);
            }

            static Implements_GetLifeTime(o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number(o.GetLifeTime, 0, o);
            }

            static Implements_GetInitialSpeedChecked(context, o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number_Checked(context, o.GetInitialSpeed, 0, o);
            }

            static Implements_GetInitialSpeed(o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number(o.GetInitialSpeed, 0, o);
            }

            static Implements_GetMaxSpeedChecked(context, o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number_Checked(context, o.GetMaxSpeed, 0, o);
            }

            static Implements_GetMaxSpeed(o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number(o.GetMaxSpeed, 0, o);
            }

            static Implements_GetGravityScaleChecked(context, o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number_Checked(context, o.GetGravityScale, 0, o);
            }

            static Implements_GetGravityScale(o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Number(o.GetGravityScale, 0, o);
            }
        }
    }
};