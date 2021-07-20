/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var FJsEnum = require('Cs/Types/Enum/Enum.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;

module.exports = class NJsYield
{
    static FEnum = class EnumYield
    {
        constructor()
        {
            this.Enum = null;/*FJsEnum.FValue*/
            this.Type = null;/*FJsEnum*/
            this.Value = null;/*FJsEnum.FValue*/
        }

        /**
         * @param {object} yieldCommand 
         * @returns {boolean}
         */
        /*bool*/ CopyFromYield(yieldCommand /*object*/)
        {
            let context = "NJsYield.FEnum.CopyFromYield";

            check(CommonLibrary.IsValidObjectChecked(context, yieldCommand));

            // Check 'WaitForEnum' key exists for yieldCommand
            if ('WaitForEnum' in yieldCommand)
			{
                // Check yieldCommand.WaitForEnum is of type: FJsEnum.FValue
                check(CommonLibrary.IsInstanceOfChecked(context, yieldCommand.WaitForEnum, FJsEnum.FValue));
                let enumType = yieldCommand.WaitForEnum.GetOuter();
                // Check 'Value' key of type: yieldCommand.WaitForEnum.GetOuter() exists for yieldCommand
                check(CommonLibrary.DoesKeyOfInstanceExistChecked(context, yieldCommand, 'Value', FJsEnum.FValue));
                checkf(enumType.EqualEqualChecked(context, yieldCommand.Value.GetOuter(), enumType));
                
                this.Enum = yieldCommand.WaitForEnum;
                this.Type = enumType;
                this.Value = yieldCommand.Value;
                return true;
            }
            return false;
        }

        /**
         * @returns {boolean}
         */
        /*bool*/ Execute()
        {
            return this.Type.AreValuesEqual(this.Enum, this.Value);
        }

        Reset()
        {
            this.Enum = null;
            this.Type = null;
            this.Value = null;
        }
    }
};