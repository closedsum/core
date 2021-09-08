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
        static NCollision = class Collision
        {
            static ICollision= class InterfaceCollision
            {
                // CsCollisionPreset GetCollisionPreset()
                // float GetCollisionRadius()

                static IsImplementedByChecked(context, o)
                {
                    let self = NJsProjectile.NData.NCollision.ICollision;

                    check(CommonLibrary.IsValidObjectChecked(context, o));

                    // GetCollisionPreset()
                    check(self.Implements_GetCollisionPresetChecked(context, o));
                    // GetCollisionRadius()
                    check(self.Implements_GetCollisionRadiusChecked(context, o));
                    return true;
                }

                static IsImplementedBy(o)
                {
                    let self = NJsProjectile.NData.NVisual.NStaticMesh.IStaticMesh;

                    if (!CommonLibrary.IsValidObject(o))
                        return false;
                    // GetCollisionPreset()
                    if (!self.Implements_GetCollisionPreset(o))
                        return false;
                    // GetCollisionRadius()
                    if (!self.Implements_GetCollisionRadius(o))
                        return false;
                    return true;
                }

                // GetCollisionPreset()
                
                static Implements_GetCollisionPresetChecked(context, o)
                {
                    let classType = CsCollisionPreset;
                    return FunctionLibrary.IsArgCountAndReturn_Instance_Checked(context, o.GetCollisionPreset, 0, o, classType);
                }

                static Implements_GetCollisionPreset(o)
                {
                    let classType = CsCollisionPreset;
                    return FunctionLibrary.IsArgCountAndReturn_Instance(o.GetCollisionPreset, 0, o, classType);
                }

                // GetCollisionRadius()
                
                static Implements_GetCollisionRadiusChecked(context, o)
                {
                    return FunctionLibrary.IsArgCountAndReturn_Number_Checked(context, o.GetCollisionRadius, 0, o);
                }

                static Implements_GetCollisionRadius(o)
                {
                    return FunctionLibrary.IsArgCountAndReturn_Number(o.GetCollisionRadius, 0, o);
                }
            }
        }
    }
};