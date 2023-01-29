/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - classes
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var checkf = CommonLibrary.checkf;
var check = CommonLibrary.check;

module.exports = class NJsFunction 
{
    static FLibrary = class Library 
    {
        static NCached = class Cached 
        {
            static NStr = class Str 
            {
                static IsArgFormatValidChecked = "NJsFunction::FLibrary::IsFormateValidChecked";
            }
        }

        /**
         * @param {string}                  context 
         * @param {{type: any, value: any}} param 
         * @param {number}                  index       int 
         * @returns {boolean}
         */
        static /*bool*/ IsArgFormatValidChecked(context /*string*/, param /*{type: any, value: any}*/, index /*int*/) 
        {
            let Str = NJsFunction.FLibrary.NCached.NStr;

            checkf(typeof context === 'string', Str.IsArgFormatValidChecked + ": context is NOT a string.");

            CommonLibrary.IsValidObjectChecked(context, param);

            CommonLibrary.IsIntChecked(context, index);

            // Check 'key'.type exists
            if (param['type'] === undefined) 
            {
                checkf(false, context + ": params[" + index + "].type is NOT defined.");
                return false;
            }
            // check 'key'.value exists
            if (param['value'] === undefined) 
            {
                checkf(false, context + ": params[" + index + "].value is NOT defined.");
                return false;
            }

            // String
            if (param['type'] === "string")
                checkf(typeof param['value'] === "string", context + ": params[" + index + "].value: " + param['value'] + " NOT type 'string'.");
            // Class
            if (CommonLibrary.IsClass(param['type']))
                checkf(CommonLibrary.IsInstanceOf(param['value'], param['type']), context + ": params[" + index + "].value: " + param['value'] + " NOT type: params[type].");

            return true;
        }

        /**
         * @param {string}                      context 
         * @param {{type: any, value: any}[]}   args 
         * @returns {boolean}
         */
        static /*bool*/ IsArgsValidChecked(context /*string*/, args /*{type: any, value: any}[]*/) 
        {
            let self = NJsFunction.FLibrary;

            for (let i = 0; i < args.length; ++i) 
            {
                const arg = args[i];

                CommonLibrary.IsValidObjectChecked(context, arg);

                self.IsArgFormatValidChecked(context, arg, i);
            }
            return true;
        }

        /**
         * @param {string}      context 
         * @param {function}    fn 
         * @param {object}      caller
         * @param {any[]}       args
         * @returns {boolean}
         */
        static /*bool*/ IsReturn_Bool_Checked(context /*string*/, fn /*function*/, caller /*object*/, args /*any[]*/) 
        {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, use caller to call fn
            if (CommonLibrary.IsValidObject(caller))
            {
                // if args is valid, use caller + args to apply fn
                if (Array.isArray(args))
                    return CommonLibrary.IsBoolChecked(context, fn.apply(caller, args));
                return CommonLibrary.IsBoolChecked(context, fn.call(caller));
            }
            // if args is valid, use args to apply fn
            if (Array.isArray(args))
               return CommonLibrary.IsBoolChecked(context, fn.apply(null, args));
            return CommonLibrary.IsBoolChecked(context, fn());
        }

        /**
         * @param {function}    fn 
         * @param {object}      caller
         * @param {any[]}       args
         * @returns {boolean}
         */
        static /*bool*/ IsReturn_Bool(fn /*function*/, caller /*object*/, args /*any[]*/) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, use caller to call fn
            if (CommonLibrary.IsValidObject(caller))
            {
                // if args is valid, use caller + args to apply fn
                if (Array.isArray(args))
                    return CommonLibrary.IsBool(fn.apply(caller, args));
                return CommonLibrary.IsBool(fn.call(caller));
            }
            // if args is valid, use args to apply fn
            if (Array.isArray(args))
                return CommonLibrary.IsBool(fn.apply(null, args));
            return CommonLibrary.IsBool(fn());
        }

        static IsReturn_Int_Checked(context, fn, caller) 
        {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsIntChecked(context, fn.call(caller));
            return CommonLibrary.IsIntChecked(context, fn());
        }

        static IsReturn_Int(fn, caller) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsInt(fn.call(caller));
            return CommonLibrary.IsInt(fn());
        }

        static IsReturn_Number_Checked(context, fn, caller) 
        {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsNumberChecked(context, fn.call(caller));
            return CommonLibrary.IsNumberChecked(context, fn());
        }

        static IsReturn_Number(fn, caller) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsNumber(fn.call(caller));
            return CommonLibrary.IsNumber(fn());
        }

        static IsReturn_Array_Checked(context, fn, caller) 
        {
            // Check fn is a function
            check(CommonLibrary.IsFunctionChecked(context, fn));

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
            {
                let ret = fn.call(caller);
                checkf(Array.isArray(ret), context + ": fn: " + fn.name + " returns type: " + typeof ret + " NOT an array.");
                return true
            }
            let ret = fn();
            checkf(Array.isArray(ret), context + ": fn: " + fn.name + " returns type: " + typeof ret + " NOT an array.");
            return true;
        }

        static IsReturn_Array(fn, caller) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return Array.isArray(fn.call(caller));
            return Array.isArray(fn());
        }

        static IsReturn_ArrayAndNotEmpty_Checked(context, fn, caller) 
        {
            // Check fn is a function
            check(CommonLibrary.IsFunctionChecked(context, fn));

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
            {
                let ret = fn.call(caller);
                checkf(ret, context + ": fn: " + fn.name + " returns type: " + typeof ret + " NOT an array.");
                checkf(ret.length !== 0, context + ": fn: " + fn.name + " returns an EMPTY array.");
                return true
            }
            let ret = fn();
            checkf(ret, context + ": fn: " + fn.name + " returns type: " + typeof ret + " NOT an array.");
            checkf(ret.length !== 0, context + ": fn: " + fn.name + " returns an EMPTY array.");
            return true;
        }

        static IsReturn_ArrayAndNotEmpty(fn, caller) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
            {
                let ret = fn.call(caller);

                if (Array.isArray(ret))
                    return ret.length !== 0;
                return false;
            }
            let ret = fn();
            
            if (Array.isArray(ret))
                return ret.length !== 0;
            return false;
        }

        static IsReturn_Instance_Checked(context, fn, caller, classType) 
        {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsInstanceOfChecked(context, fn.call(caller), classType);
            return CommonLibrary.IsInstanceOfChecked(context, fn(), classType);
        }

        static IsReturn_Instance(fn, caller, classType) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsInstaceOf(fn.call(caller), classType);
            return CommonLibrary.IsInstaceOf(fn(), classType);
        }

        static IsReturn_Class_Checked(context, fn, caller, classType) 
        {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsClassOfChecked(context, fn.call(caller), classType);
            return CommonLibrary.IsClassOfChecked(context, fn(), classType);
        }

        static IsReturn_Class(fn, caller, classType) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsClassOf(fn.call(caller), classType);
            return CommonLibrary.IsClassOf(fn(), classType);
        }

        static IsReturn_Function_Checked(context, fn, caller) 
        {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsFunctionChecked(context, fn.call(caller));
            return CommonLibrary.IsFunctionChecked(context, fn());
        }

        static IsReturn_Function(fn, caller) 
        {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsFunction(fn.call(caller));
            return CommonLibrary.IsFunction(fn());
        }

        /**
         * @param {string}      context 
         * @param {function}    fn 
         * @param {number}      argCount    int 
         * @returns {boolean} 
         */
        static /*bool*/ IsArgCountChecked(context /*string*/, fn /*function*/, argCount /*int*/)
        {
            check(CommonLibrary.IsFunctionChecked(context, fn));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        /**
         * @param {function}    fn 
         * @param {number}      argCount    int
         * @returns {boolean} 
         */
        static /*bool*/ IsArgCount(fn /*function*/, argCount /*int*/)
        {
            if (!CommonLibrary.IsFunction(fn))
                return false;

            if (fn.length !== argCount)
                return false;
            return true;
        }

        /**
         * @param {string}      context
         * @param {function}    fn 
         * @param {number}      argCount    int
         * @param {object}      caller
         * @returns {boolean} 
         */
        static /*bool*/ IsArgCountAndReturn_Bool_Checked(context /*string*/, fn /*function*/, argCount /*int*/, caller /*object*/, args /*any[]*/) 
        {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Bool_Checked(context, fn, caller, args));

            // Check argCount is an int
            check(CommonLibrary.IsIntChecked(context, argCount));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Bool(fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            if (!self.IsReturn_Bool(fn, caller))
                return false;
            // Check argCount is an int
            if (!CommonLibrary.IsBool(argCount))
                return false;
            if (fn.length !== argCount)
                return false;
            return true;
        }

        static IsArgCountAndReturn_Int_Checked(context, fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Int_Checked(context, fn, caller));

            // Check argCount is an int
            check(CommonLibrary.IsIntChecked(context, argCount));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Int(fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            if (!self.IsReturn_Int(fn, caller))
                return false;
            // Check argCount is an int
            if (!CommonLibrary.IsInt(argCount))
                return false;
            if (fn.length !== argCount)
                return false;
            return true;
        }

        static IsArgCountAndReturn_Number_Checked(context, fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Number_Checked(context, fn, caller));

            // Check argCount is an int
            check(CommonLibrary.IsIntChecked(context, argCount));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Number(fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            if (!self.IsReturn_Number(fn, caller))
                return false;
            // Check argCount is an int
            if (!CommonLibrary.IsInt(argCount))
                return false;
            if (fn.length !== argCount)
                return false;
            return true;
        }

        static IsArgCountAndReturn_ArrayAndNotEmpty_Checked(context, fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_ArrayAndNotEmpty_Checked(context, fn, caller));

            // Check argCount is an int
            check(CommonLibrary.IsIntChecked(context, argCount));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_ArrayAndNotEmpty(fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            if (!self.IsReturn_ArrayAndNotEmpty(fn, caller))
                return false;
            // Check argCount is an int
            if (!CommonLibrary.IsInt(argCount))
                return false;
            if (fn.length !== argCount)
                return false;
            return true;
        }

        static IsArgCountAndReturn_Instance_Checked(context, fn, argCount, caller, classType) 
        {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Instance_Checked(context, fn, caller, classType));

            // Check argCount is an int
            check(CommonLibrary.IsIntChecked(context, argCount));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Instance(fn, argCount, caller, classType) 
        {
            let self = NJsFunction.FLibrary;

            if (!self.IsReturn_Instance(fn, caller, classType))
                return false;
            // Check argCount is an int
            if (!CommonLibrary.IsInt(argCount))
                return false;
            if (fn.length !== argCount)
                return false;
            return true;
        }

        static IsArgCountAndReturn_Class_Checked(context, fn, argCount, caller, classType) 
        {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Class_Checked(context, fn, caller, classType));

            // Check argCount is an int
            check(CommonLibrary.IsIntChecked(context, argCount));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Class(fn, argCount, caller, classType) 
        {
            let self = NJsFunction.FLibrary;

            if (!self.IsReturn_Class(fn, caller, classType))
                return false;
            // Check argCount is an int
            if (!CommonLibrary.IsInt(argCount))
                return false;
            if (fn.length !== argCount)
                return false;
            return true;
        }

        static IsArgCountAndReturn_Function_Checked(context, fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Function_Checked(context, fn, caller));

            // Check argCount is an int
            check(CommonLibrary.IsIntChecked(context, argCount));

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Function(fn, argCount, caller) 
        {
            let self = NJsFunction.FLibrary;

            if (!self.IsReturn_Function(fn, caller))
                return false;
            // Check argCount is an int
            if (!CommonLibrary.IsInt(argCount))
                return false;
            if (fn.length !== argCount)
                return false;
            return true;
        }
    };
};