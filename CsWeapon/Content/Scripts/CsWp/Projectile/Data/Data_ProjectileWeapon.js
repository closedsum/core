/// <reference path="../../../typings/ue.d.ts">/>
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

module.exports = class NJsWeapon
{
    static NProjectile = class NJsProjectile
    {
        static NData = class Data
        {
            static IData = class InterfaceData
            {
                static IsImplementedByChecked(context, o)
                {
                    let self = NJsWeapon.NProjectile.NData.IData;

                    check(CommonLibrary.IsValidObjectChecked(context, o));
                    return true;
                }

                static IsImplementedBy(o)
                {
                    let self = NJsWeapon.NProjectile.NData.IData;

                    if (!CommonLibrary.IsValidObject(o))
                        return false;
                    return true;
                }

                static Implements_DoFireOnReleaseChecked(context, o)
                {
                    return FunctionLibrary.IsArgCountAndReturn_Bool_Checked(context, o.DoFireOnRelease, 0, o);
                }

                static Implements_DoFireOnRelease(o)
                {
                    return FunctionLibrary.IsArgCountAndReturn_Bool(o.DoFireOnRelease, 0, o);
                }
            }
        }
    }
};