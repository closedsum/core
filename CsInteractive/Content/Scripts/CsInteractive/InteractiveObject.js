/// <reference path="../typings/ue.d.ts">/>
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

module.exports = class NJsInteractive
{
    static NObject = class Object
    {
        static IObject = class InterfaceObject
        {
            static IsImplementedByChecked(context, o)
            {
                let self = NJsInteractive.NObject.IObject;

                check(CommonLibrary.IsValidObjectChecked(context, o));

                return true;
            }

            static IsImplementedBy(o)
            {
                let self = NJsInteractive.NObject.IObject;

                if (!CommonLibrary.IsValidObject(o))
                    return false;
                return true;
            }
        }
    }
};