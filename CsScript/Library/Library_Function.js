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

module.exports = class NJsFunction {
    static FLibrary = class Library {
        static NCached = class Cached {
            static NStr = class Str {
                static IsArgFormatValidChecked = "NJsFunction::FLibrary::IsFormateValidChecked";
            }
        }

        static IsArgFormatValidChecked(context, param, index) {
            let Str = NJsFunction.FLibrary.NCached.NStr;

            checkf(typeof context === 'string', Str.IsArgFormatValidChecked + ": context is NOT a string.");

            CommonLibrary.IsValidObjectChecked(context, param);

            CommonLibrary.IsIntChecked(context, index);

            // Check 'key'.type exists
            if (param['type'] === undefined) {
                checkf(false, context + ": params[" + index + "].type is NOT defined.");
                return false;
            }
            // check 'key'.value exists
            if (param['value'] === undefined) {
                checkf(false, context + ": params[" + index + "].value is NOT defined.");
                return false;
            }
            return true;
        }

        static IsArgsValidChecked(context, args) {
            let self = NJsFunction.FLibrary;

            for (let i = 0; i < args.length; ++i) {
                const arg = args[i];

                CommonLibrary.IsValidObjectChecked(context, arg);

                self.IsArgFormatValidChecked(context, arg, i);
            }
            return true;
        }

        static IsReturn_Bool_Checked(context, fn, caller) {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsBoolChecked(context, fn.call(caller));
            return CommonLibrary.IsBoolChecked(context, fn());
        }

        static IsReturn_Bool(fn, caller) {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsBool(fn.call(caller));
            return CommonLibrary.IsBool(fn());
        }

        static IsReturn_Int_Checked(context, fn, caller) {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsIntChecked(context, fn.call(caller));
            return CommonLibrary.IsIntChecked(context, fn());
        }

        static IsReturn_Int(fn, caller) {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsInt(fn.call(caller));
            return CommonLibrary.IsInt(fn());
        }

        static IsReturn_Number_Checked(context, fn, caller) {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsNumberChecked(context, fn.call(caller));
            return CommonLibrary.IsNumberChecked(context, fn());
        }

        static IsReturn_Number(fn, caller) {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsNumber(fn.call(caller));
            return CommonLibrary.IsNumber(fn());
        }

        static IsReturn_Class_Checked(context, fn, caller, classType) {
            // Check fn is a function
            CommonLibrary.IsFunctionChecked(context, fn);

            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsClassOfChecked(context, fn.call(caller), classType);
            return CommonLibrary.IsClassOfChecked(context, fn(), classType);
        }

        static IsReturn_Class(fn, caller, classType) {
            // Check fn is a function
            if (!CommonLibrary.IsFunction(fn))
                return false;
            // If caller is valid, user caller to call fn
            if (CommonLibrary.IsValidObject(caller))
                return CommonLibrary.IsClassOf(fn.call(caller), classType);
            return CommonLibrary.IsClassOf(fn(), classType);
        }

        static IsArgCountAndReturn_Bool_Checked(context, fn, argCount, caller) {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Bool_Checked(context, fn, caller));

            // Check argCount is an int
            CommonLibrary.IsBoolChecked(context, argCount);

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Bool(fn, argCount, caller) {
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

        static IsArgCountAndReturn_Int_Checked(context, fn, argCount, caller) {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Int_Checked(context, fn, caller));

            // Check argCount is an int
            CommonLibrary.IsIntChecked(context, argCount);

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Int(fn, argCount, caller) {
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

        static IsArgCountAndReturn_Number_Checked(context, fn, argCount, caller) {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Number_Checked(context, fn, caller));

            // Check argCount is an int
            CommonLibrary.IsIntChecked(context, argCount);

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Number(fn, argCount, caller) {
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

        static IsArgCountAndReturn_Class_Checked(context, fn, argCount, caller, classType) {
            let self = NJsFunction.FLibrary;

            check(self.IsReturn_Class_Checked(context, fn, caller, classType));

            // Check argCount is an int
            CommonLibrary.IsIntChecked(context, argCount);

            checkf(fn.length === argCount, context + ": fn: " + fn.name + " argument count: " + fn.length + " != " + argCount);

            return true;
        }

        static IsArgCountAndReturn_Class(fn, argCount, caller, classType) {
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
    };
};