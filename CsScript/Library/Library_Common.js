/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class NJsCommon
{
    static FLibrary = class Library
    {
        static IsNullObject(o)
        {
            return o == null || typeof o !== "object";
        }

        static IsValidObject(o)
        {
            return o != null && typeof o === "object";
        }

        static IsFunction(func)
        {
            let getType = {};
            return func && getType.toString.call(func) === '[object Function]';
        }

        static IsGenerator(o)
        {
            return this.IsValidObject(o) && ("" + o) === '[object Generator]';
        }

        static IsClassOf(a, c) { return a instanceof c; }

        static IsInt(a) { return Number.isSafeInteger(a); }
        static IsFloat(a) { return Number.isFinite(a) && !Number.isSafeInteger(a); }
    };
};