/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class FJsProperty
{
    constructor()
    {
        this.Value = null;
    }

    Get() { return this.Value; }

    IsBoolean() { return typeof Value === "boolean"; }
    IsNumber() { return typeof Value === "number"; }
    IsInt() { return Number.isSafeInteger(Value); }
    IsFloat() { return Number.isFinite(Value) && !Number.isSafeInteger(Value); }
    IsString() { return typeof Value === "string"; }
    IsObject() { return typeof Value === "object"; }
    IsNonNullObject() { return Value != null && Value === "object"; }
};