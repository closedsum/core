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

module.exports = class IJsTeam
{
    // int GetTeam()
    // bool IsOnTeam(ECsTeam)

    static IsImplementedByChecked(context, o)
    {
        let self = NJsSkin.NData.NVisual.NMaterial.IMaterial;

        check(CommonLibrary.IsValidObjectChecked(context, o));

        // GetTeam()
        check(self.Implements_GeTeamChecked(context, o));
        return true;
    }

    static IsImplementedBy(o)
    {
        let self = IJsTeam;

        if (!CommonLibrary.IsValidObject(o))
            return false;
        // GetTeam()
        if (!self.Implements_GetTeam(o))
            return false;
        return true;
    }

    // GetTeam()
    static Implements_GetTeamChecked(context, o)
    {
        return FunctionLibrary.IsArgCountAndReturn_Int_Checked(context, o.GetTeam, 0, o);
    }

    static Implements_GetTeam(o)
    {
        return FunctionLibrary.IsArgCountAndReturn_Int(o.GetTeam, 0, o);
    }

    // IsOnTeam
    static Implements_IsOnTeamChecked(context, o)
    {
        // TODO: Get some Team type and check that it returns a bool
        return FunctionLibrary.IsArgCountChecked(context, o.IsOnTeam, 1);
    }

    static Implements_IsOnTeam(o)
    {
        // TODO: Get some Team type and check that it returns a bool
        return FunctionLibrary.IsArgCount(o.GetTeam, 1);
    }
}
};