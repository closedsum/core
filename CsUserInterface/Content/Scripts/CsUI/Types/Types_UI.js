// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - library (c++)
var PropertyLibrary = CsScriptLibrary_Property;
var WidgetLibrary   = CsScriptLibrary_Widget;

// "typedefs" - functions
var check                = CommonLibrary.check;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;
var IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked;

module.exports = class NJsTypes
{
    static FUserWidget = class UserWidgetClass
    {
        constructor()
        {  
            /** @type {string[]} */           this.Path = "";
            /** @type {UnrealEngineClass} */  this.Widget_Class = null;
        }

        /*string*/ GetName() { return " NJsTypes.FUserWidget" }

        /**
        * @returns {UnrealEngineClass}
        */
        /*UnrealEngineClass*/ GetClass() { return this.Widget_Class; }

        /**
        * @param {UnrealEngineClass} widgetClass 
        */
        SetClass(widgetClass /*UnrealEngineClass*/) { this.Widget_Class = widgetClass; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsNotEmptyChecked(context, this.Path);
           // IsValidObjectChecked(context, this.Widget_Class);
            return true;
        }

        /**
        * @param {string} context 
        * @param {object} o 
        * @param {string} memberPath 
        */
        OverrideByUObject(context /*string*/, o /*object*/, memberPath /*string*/)
        {
            let result = WidgetLibrary.GetSoftClassAsStringByPath(context, o, memberPath + ".Widget");
            check(result.OutSuccess);
            IsStringNotEmptyChecked(context, result.OutPathAsString);
            this.Path = result.OutPathAsString;
            result = PropertyLibrary.GetClassByPath(context, o, memberPath + ".Widget_Class");
            //IsValidObjectChecked(context, result.$);
            this.Widget_Class = result.$;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            let widgetClass = WidgetLibrary.LoadByStringPath(context, this.Path);
            //IsValidObjectChecked(context, widgetClass);
            this.Widget_Class = widgetClass;
        }

        Unload()
        {
            this.Widget_Class = null;
        }
    }
};