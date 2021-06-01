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
            let self = NJsCommon.FLibrary;

            let result = self.IsNullObject(o);
            self.checkf(result, context + ": o: " + o + " is NOT NULL.");
            return result;
        }

        static IsValidObject(o)
        {
            return o != null && typeof o === "object";
        }

        static IsValidObjectChecked(context, o)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsValidObject(o);
            self.checkf(result, context + ": o: " + o + " is NOT a Valid Object.");
            return result;
        }

        static IsFunction(func)
        {
            let getType = {};
            return func && getType.toString.call(func) === '[object Function]';
        }

        static IsFunctionChecked(context, func)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsFunction(func);
            self.checkf(result, context + ": func: " + func + " is NOT a function.");
            return result;
        }

        static IsGenerator(gen)
        {
            let self = NJsCommon.FLibrary;
            
            return self.IsValidObject(gen) && ("" + gen) === '[object Generator]';
        }

        static IsGeneratorChecked(context, gen)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsGenerator(gen);
            self.checkf(result, context + ": gen: " + gen + " is NOT a function.");
            return result;
        }

        static IsClassOf(a, c) 
        { 
            let self = NJsCommon.FLibrary;

            if (!self.IsValidObject(a))
                return false;
            if (!self.IsFunction(c))
                return false;
            return a instanceof c; 
        }

        static IsClassOfChecked(context, a, c)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.IsValidObjectChecked(context, a));
            self.check(self.IsFunctionChecked(context, c));

            let result = a instanceof c;
            self.checkf(result, context + ": a: " + a + " is NOT an instance of c: " + c);
            return result;
        }

        static IsBool(a) { return typeof a === "boolean"; }

        static IsBoolChecked(context, a)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsBool(a);
            self.checkf(result, context + ": a: " + a + " is NOT a boolean.");
            return result;
        }

        static IsInt(a) { return Number.isSafeInteger(a); }

        static IsIntChecked(context, a)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsInt(a);
            self.checkf(result, context + ": a: " + a + " is NOT an integer.");
            return result;
        }

        static IsFloat(a) { return Number.isFinite(a) && !Number.isSafeInteger(a); }

        static IsFloatChecked(context, a)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsFloat(a);
            self.checkf(result, context + ": a: " + a + " is NOT a float.");
            return result;
        }

        static IsNumberChecked(context, a)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsNumber(a);
            self.checkf(result, context + ": a " + a + " is NOT a Number.");
            return result;
        }

        static IsNumber(a) { return Number.isFinite(a); }

        static IsStringChecked(context, s)
        {
            let self = NJsCommon.FLibrary;

            let result = typeof s === 'string';
            self.checkf(result, context + ": s: " + s + " is NOT a string.");
            return result;
        }
    };
};