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

module.exports = class NJsProjectile
{
    static NData = class Data
    {
        static IData = class InterfaceData
        {
            static IsImplementedByChecked(context, o)
            {
                let self = NJsProjectile.NData.IData;

                check(CommonLibrary.IsValidObjectChecked(context, o));

                // GetLifeTime()
                check(self.Implements_GetLifeTimeChecked(context, o));
                // GetInitialSpeed()
                check(self.Implements_GetInitialSpeedChecked(context, o));
                // GetMaxSpeed()
                check(self.Implements_GetMaxSpeedChecked(context, o));
                // GetGravityScale()
                check(self.Implements_GetGravityScaleChecked(context, o));
                return true;
            }

            static IsImplementedBy(o)
            {
                let self = NJsProjectile.NData.IData;

                if (!CommonLibrary.IsValidObject(o))
                    return false;
                // GetLifeTime()
                if (!self.Implements_GetLifeTime(o))
                    return false;
                // GetInitialSpeed()
                if (!self.Implements_GetInitialSpeed(o))
                    return false;
                // GetMaxSpeed()
                if (!self.Implements_GetMaxSpeed(o))
                    return false;
                // GetGravityScale()
                if (!self.Implements_GetGravityScale(o))
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