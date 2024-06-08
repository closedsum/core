// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../../Cs/custom_typings/Cs.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - library
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

module.exports = class FJsProperty
{
    constructor()
    {
        this.Value = null;
    }

    Get() { return this.Value; }

    IsBoolean() { return typeof this.Value === "boolean"; }
    IsNumber() { return typeof this.Value === "number"; }
    IsInt() { return Number.isSafeInteger(this.Value); }
    IsFloat() { return Number.isFinite(this.Value) && !Number.isSafeInteger(this.Value); }
    IsFloatChecked(context /*string*/) { return CommonLibrary.IsFloatChecked(context, this.Value); }
    IsFloatChecked2() { return CommonLibrary.IsFloatChecked2(this.Value); }
    IsString() { return typeof this.Value === "string"; }
    IsObject() { return typeof this.Value === "object"; }
    IsNonNullObject() { return this.Value != null && this.Value === "object"; }
};