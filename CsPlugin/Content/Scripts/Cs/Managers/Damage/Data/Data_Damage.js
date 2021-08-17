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

module.exports = class NJsDamage
{
    static NData = class Data
    {
        static IData = class InterfaceData
        {
            // ValueType GetValue()
            // ECsDamageType GetType()

            static IsImplementedByChecked(context, o)
            {
                let self = NJsDamage.NData.IData;

                check(CommonLibrary.IsValidObjectChecked(context, o));

                // GetValue()
                check(self.Implements_GetValueChecked(context, o));
                // GetType()
                check(self.Implements_GetTypeChecked(context, o));
                return true;
            }

            static IsImplementedBy(o)
            {
                let self = NJsDamage.NData.IData;

                if (!CommonLibrary.IsValidObject(o))
                    return false;
                // GetValue()
                if (!self.Implements_GetValue(o))
                    return false;
                // GetType()
                if (!self.Implements_GetType(o))
                    return false;
                return true;
            }

            // GetValue()
            static Implements_GetValueChecked(context, o)
            {
                return FunctionLibrary.IsArgCountChecked(context, o.GetValue, 0, o);
            }

            static Implements_GetValue(o)
            {
                return FunctionLibrary.IsArgCount(o.GetValue, 0, o);
            }

            // GetType()
            static Implements_GetTypeChecked(context, o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Instance_Checked(context, o.GetType, 0, o, ECsDamageType);
            }

            static Implements_GetType(o)
            {
                return FunctionLibrary.IsArgCountAndReturn_Instance(o.GetType, 0, o, ECsDamageType);
            }
        }
    }
};