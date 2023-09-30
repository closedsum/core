// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Types
/// <reference path="../../Types/Enum/Enum.ts">/>
// Library
/// <reference path="../../Library/Library_Common.ts">/>

"use strict"

// Types
/** @type {FJsEnum} */
var FJsEnum = require('Cs/Types/Enum/Enum.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - library
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check  = CommonLibrary.check;
var checkf = CommonLibrary.checkf;

module.exports = class NJsYield
{
    static FEnum = class EnumYield
    {
        constructor()
        {
            /** @type {FJsEnum_FValue} */    this.Enum = null;
            /** @type {FJsEnum} */          this.Type = null;
            /** @type {FJsEnum_FValue} */   this.Value = null;
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
                /** @type {FJsEnum} */  
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