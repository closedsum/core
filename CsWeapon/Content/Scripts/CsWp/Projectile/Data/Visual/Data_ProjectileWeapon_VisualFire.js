/// <reference path="../../../../typings/ue.d.ts">/>
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
            static NVisual = class Visual
            {
                static NFire = class Fire
                {
                    static IFire = class InterfaceFire
                    {
                        static IsImplementedByChecked(context, o)
                        {
                            let self = NJsWeapon.NProjectile.NData.NVisual.NFire.IFire;

                            check(CommonLibrary.IsValidObjectChecked(context, o));

                            // GetFireFXParams()
                            check(self.Implements_GetFireFXParamsChecked(context, o));
                            return true;
                        }

                        static IsImplementedBy(o)
                        {
                            let self = NJsWeapon.NProjectile.NData.NVisual.NFire.IFire;

                            if (!CommonLibrary.IsValidObject(o))
                                return false;

                            // GetFireFXParams()
                            if (!self.Implements_GetFireFXParams(o))
                                return false;
                            return true;
                        }

                        static Implements_GetFireFXParamsChecked(context, o)
                        {
                            let classType = CsProjectileWeapon_VisualFire_Params;
                            return FunctionLibrary.IsArgCountAndReturn_Class_Checked(context, o.GetFireFXParams, 0, o, classType);
                        }

                        static Implements_GetFireFXParams(o)
                        {
                            let classType = CsProjectileWeapon_VisualFire_Params;
                            return FunctionLibrary.IsArgCountAndReturn_Class(o.GetFireFXParams, 0, o, classType);
                        }
                    }
                }
            }
        }
    }
};