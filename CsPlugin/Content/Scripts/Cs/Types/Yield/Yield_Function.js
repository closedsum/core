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
var checkf = CommonLibrary.checkf;

var Core;

module.exports = class NJsYield
{
    static FFunction = class FunctionYield
    {
        constructor()
        {
            this.Fn = null;/*function*/
            this.Caller = null;/*object*/
        }

        SetCore(core)
        {
            Core = core;
        }

        /**
         * @param {object} yieldCommand 
         * @returns {boolean}
         */
        /*bool*/ CopyFromYield(yieldCommand /*object*/)
        {
            let context = "NJsYield.FFunction.CopyFromYield";

            check(CommonLibrary.IsValidObjectChecked(context, yieldCommand));

            // Check 'WaitForFunction' key exists for yieldCommand
            if ('WaitForFunction' in yieldCommand)
			{
                if (CommonLibrary.DoesKeyExist(yieldCommand, 'Caller'))
                {
                    this.Caller = yieldCommand['Caller'];
                }

                // Check yieldCommand.WaitForFunction is of type: function
                check(FunctionLibrary.IsArgCountAndReturn_Bool_Checked(context, yieldCommand.WaitForFunction, 0, this.Caller))

                this.Fn = yieldCommand.WaitForFunction;
                return true;
            }
            return false;
        }

        /**
         * @returns {boolean}
         */
        /*bool*/ Execute()
        {
            if (CommonLibrary.IsValidObject(this.Caller))
                return this.Fn.call(this.Caller);
            return this.Fn();
        }

        Reset()
        {
            this.Fn = null;
            this.Caller = null;
        }
    }
};