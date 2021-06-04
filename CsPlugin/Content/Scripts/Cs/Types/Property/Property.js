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

    IsBoolean() { return typeof this.Value === "boolean"; }
    IsNumber() { return typeof this.Value === "number"; }
    IsInt() { return Number.isSafeInteger(this.Value); }
    IsFloat() { return Number.isFinite(this.Value) && !Number.isSafeInteger(this.Value); }
    IsString() { return typeof this.Value === "string"; }
    IsObject() { return typeof this.Value === "object"; }
    IsNonNullObject() { return this.Value != null && this.Value === "object"; }
};