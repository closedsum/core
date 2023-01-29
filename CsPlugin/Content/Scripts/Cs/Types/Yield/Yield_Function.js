/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');
var NJsArray = require('Cs/Library/Library_Array.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;
var ArrayLibrary = NJsArray.FLibrary;

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
            this.Args = [];/*array*/
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
                let argCount = 0;

                if (CommonLibrary.DoesKeyExist(yieldCommand, 'Caller'))
                {
                    this.Caller = yieldCommand['Caller'];
                }

                if (CommonLibrary.DoesKeyOfArrayExist(yieldCommand, 'Args'))
                {
                    check(ArrayLibrary.IsNotEmptyChecked(context, yieldCommand['Args']));

                    for (let element of yieldCommand['Args'])
                    {
                        this.Args.push(element);
                    }
                    argCount = this.Args.length;
                }

                // Check yieldCommand.WaitForFunction is of type: function
                check(FunctionLibrary.IsArgCountAndReturn_Bool_Checked(context, yieldCommand.WaitForFunction, argCount, this.Caller, this.Args))

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
            {
                if (this.Args.length > 0)
                    return this.Fn.apply(this.Caller, this.Args);
                return this.Fn.call(this.Caller);
            }

            if (this.Args.length > 0)
                return this.Fn.apply(null, this.Args);
            return this.Fn();
        }

        Reset()
        {
            this.Fn = null;
            this.Caller = null;
            this.Args = [];
        }
    }
};