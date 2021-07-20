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
            static NSound = class Sound
            {
                static NFire = class Fire
                {
                    static IFire = class InterfaceFire
                    {
                        static IsImplementedByChecked(context, o)
                        {
                            let self = NJsWeapon.NProjectile.NData.NSound.NFire.IFire;

                            check(CommonLibrary.IsValidObjectChecked(context, o));

                            // GetFireSoundParams()
                            check(self.Implements_GetFireSoundParamsChecked(context, o));
                            return true;
                        }

                        static IsImplementedBy(o)
                        {
                            let self = NJsWeapon.NProjectile.NData.NSound.NFire.IFire;

                            if (!CommonLibrary.IsValidObject(o))
                                return false;

                            // GetFireSoundParams()
                            if (!self.Implements_GetFireSoundParams(o))
                                return false;
                            return true;
                        }

                        static Implements_GetFireSoundParamsChecked(context, o)
                        {
                            let classType = CsProjectileWeapon_SoundFire_Params;
                            return FunctionLibrary.IsArgCountAndReturn_Instance_Checked(context, o.GetFireSoundParams, 0, o, classType);
                        }

                        static Implements_GetFireSoundParams(o)
                        {
                            let classType = CsProjectileWeapon_SoundFire_Params;
                            return FunctionLibrary.IsArgCountAndReturn_Instance(o.GetFireSoundParams, 0, o, classType);
                        }
                    }
                }
            }
        }
    }
};