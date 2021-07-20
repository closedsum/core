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

module.exports = class IData_GetProjectileType
{
    static IsImplementedByChecked(context, o)
    {
        let self = IData_GetProjectileType;

        check(CommonLibrary.IsValidObjectChecked(context, o));

        // GetProjectileType()
        check(self.Implements_GetProjectileTypeChecked(context, o));
        return true;
    }

    static IsImplementedBy(o)
    {
        let self = IData_GetProjectileType;

        if (!CommonLibrary.IsValidObject(o))
            return false;
        // GetProjectileType()
        if (!self.Implements_GetProjectileType(o))
            return false;
        return true;
    }

    static Implements_GetProjectileTypeChecked(context, o)
    {
        return FunctionLibrary.IsArgCountAndReturn_Instance_Checked(context, o.GetProjectileType, 0, o, ECsProjectile);
    }

    static Implements_GetProjectileType(o)
    {
        return FunctionLibrary.IsArgCountAndReturn_Instance(o.GetProjectileType, 0, o, ECsProjectile);
    }
};