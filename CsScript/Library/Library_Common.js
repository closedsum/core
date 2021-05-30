/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class NJsCommon
{
    static FLibrary = class Library
    {
        static checkf(condition, message)
        {
            if (!condition)
            {   
                // NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
                throw Error(message);
            }
        }

        static check(condition)
        {
            if (!condition)
            {
                // NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
                throw Error();  
            }
        }

        static IsNullObject(o)
        {
            return o == null || typeof o !== "object";
        }

        static IsNullObjectChecked(context, o)
        {
            let result = this.IsNullObject(o);
            this.checkf(result, context + ": o: " + o + " is NOT NULL.");
            return result;
        }

        static IsValidObject(o)
        {
            return o != null && typeof o === "object";
        }

        static IsValidObjectChecked(context, o)
        {
            let result = this.IsValidObject(o);
            this.checkf(result, context + ": o: " + o + " is NOT a Valid Object.");
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
            this.checkf(result, context + ": func: " + func + " is NOT a function.");
            return result;
        }

        static IsGenerator(gen)
        {
            return this.IsValidObject(gen) && ("" + gen) === '[object Generator]';
        }

        static IsGeneratorChecked(context, gen)
        {
            let result = this.IsGenerator(gen);
            this.checkf(result, context + ": gen: " + gen + " is NOT a function.");
            return result;
        }

        static IsClassOf(a, c) { return a instanceof c; }

        static IsClassOfChecked(context, a, c)
        {
            let result = this.IsClassOf(a, c);
            this.checkf(result, context + ": a: " + a + " is NOT an instance of c: " + c);
            return result;
        }

        static IsInt(a) { return Number.isSafeInteger(a); }

        static IsIntChecked(context, a)
        {
            let result = this.IsInt(a);
            this.checkf(result, context + ": a: " + a + " is NOT an integer.");
            return result;
        }

        static IsFloat(a) { return Number.isFinite(a) && !Number.isSafeInteger(a); }

        static IsFloatChecked(context, a)
        {
            let result = this.IsFloat(a);
            this.checkf(result, context + ": a: " + a + " is NOT a float.");
            return result;
        }

        static IsNumberChecked(context, a)
        {
            let result = this.IsNumber(a);
            this.checkf(result, context + ": a " + a + " is NOT a Number.");
            return result;
        }

        static IsNumber(a) { return Number.isFinite(a); }

        static IsStringChecked(context, s)
        {
            let result = typeof s === 'string';
            this.checkf(result, context + ": s: " + s + " is NOT a string.");
            return result;
        }
    };
};