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

module.exports = class NJsProjectile
{
    static NData = class Data
    {
        static NDamage = class Damage
        {
            static IDamage = class InterfaceDamage
            {
                // DamageDataType GetDamageData()

                static IsImplementedByChecked(context, o)
                {
                    let self = NJsProjectile.NData.NDamage.IDamage;

                    check(CommonLibrary.IsValidObjectChecked(context, o));

                    // GetDamageData()
                    check(self.Implements_GetDamageDataChecked(context, o));
                    return true;
                }

                static IsImplementedBy(o)
                {
                    let self = NJsProjectile.NData.NDamage.IDamage;

                    if (!CommonLibrary.IsValidObject(o))
                        return false;
                    // GetDamageData()
                    if (!self.Implements_GetDamageData(o))
                        return false;

                    return true;
                }

                // GetDamageData()
                
                static Implements_GetDamageDataChecked(context, o)
                {
                    return FunctionLibrary.IsArgCountChecked(context, o.GetDamageData, 0, o);
                }

                static Implements_GetDamageData(o)
                {
                    return FunctionLibrary.IsArgCount(o.GetDamageData, 0, o);
                }
            }
        }
    }
};