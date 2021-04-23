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

        static IsNullObjectChecked(context, o)
        {
            let result = this.IsNullObject(o);
            console.assert(result, context + ": o: " + o + " is NOT NULL.");
            return result;
        }

        static IsValidObject(o)
        {
            return o != null && typeof o === "object";
        }

        static IsValidObjectChecked(context, o)
        {
            let result = this.IsValidObject(o);
            console.assert(result, context + ": o: " + o + " is NOT a Valid Object.");
            return result;
        }

        static IsFunction(func)
        {
            let getType = {};
            return func && getType.toString.call(func) === '[object Function]';
        }

        static IsFunctionChecked(context, func)
        {
            let result = this.IsFunction(func);
            console.assert(result, context + ": func: " + func + " is NOT a function.");
            return result;
        }

        static IsGenerator(gen)
        {
            return this.IsValidObject(gen) && ("" + gen) === '[object Generator]';
        }

        static IsGeneratorChecked(context, gen)
        {
            let result = this.IsGenerator(gen);
            console.assert(result, context + ": gen: " + gen + " is NOT a function.");
            return result;
        }

        static IsClassOf(a, c) { return a instanceof c; }

        static IsClassOfChecked(context, a, c)
        {
            let result = this.IsClassOf(a, c);
            console.assert(result, context + ": a: " + a + " is NOT an instance of c: " + c);
            return result;
        }

        static IsInt(a) { return Number.isSafeInteger(a); }

        static IsIntChecked(context, a)
        {
            let result = this.IsInt(a);
            console.assert(result, context + ": a: " + a + " is NOT an integer.");
            return result;
        }

        static IsFloat(a) { return Number.isFinite(a) && !Number.isSafeInteger(a); }

        static IsFloatChecked(context, a)
        {
            let result = this.IsFloat(a);
            console.assert(result, context + ": a: " + a + " is NOT a float.");
            return result;
        }

        static IsStringChecked(context, s)
        {
            let result = typeof s === 'string';
            console.assert(result, context + ": s: " + s + " is NOT a string.");
            return result;
        }
    };
};