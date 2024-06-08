/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var FJsEnum = require("Cs/Types/Enum/Enum.js");
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;

module.exports = class NJsEnum
{
    static NValue = class Value
    {
        static FLibrary = class Library
        {
            /**
             * @param {string}          context 
             * @param {FJsEnum.Value}   e 
             * @param {FJsEnum}         type 
             */
            /*bool*/ static IsTypeChecked(context /*string*/, e /*FJsEnum.FValue*/, type /*FJsEnum*/)
            {
                check(CommonLibrary.IsInstanceOfChecked(context, e, FJsEnum.FValue));
                check(e.IsTypeChecked(context, type));
                return true;
            }

            /**
             * @param {string}          context 
             * @param {FJsEnum.FValue}  e 
             * @param {string}          enumName 
             * @returns {boolean}
             */
            /*bool*/ static IsTypeByStringChecked(context /*string*/, e /*FJsEnum.FValue*/, enumName /*string*/)
            {
                check(CommonLibrary.IsInstanceOfChecked(context, e, FJsEnum.FValue));
                check(e.IsTypeByStringChecked(context, enumName));
                return true;
            }
        }
    }
};