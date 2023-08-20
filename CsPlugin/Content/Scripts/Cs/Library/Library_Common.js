// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class NJsCommon
{
    static FLibrary = class Library
    {
        static FDisableCheck = class DisableCheck
        {
            static Setup()
            {
                NJsCommon.FLibrary.checkf               = NJsCommon.FLibrary.FDisableCheck.checkf;
                NJsCommon.FLibrary.check                = NJsCommon.FLibrary.FDisableCheck.check;
                NJsCommon.FLibrary.IsNullObjectChecked  = NJsCommon.FLibrary.FDisableCheck.IsNullObjectChecked;
                NJsCommon.FLibrary.IsValidObjectChecked = NJsCommon.FLibrary.FDisableCheck.IsValidObjectChecked;
                NJsCommon.FLibrary.IsFunctionChecked    = NJsCommon.FLibrary.FDisableCheck.IsFunctionChecked;
                NJsCommon.FLibrary.IsGeneratorChecked   = NJsCommon.FLibrary.FDisableCheck.IsGeneratorChecked;
                NJsCommon.FLibrary.IsClassChecked       = NJsCommon.FLibrary.FDisableCheck.IsClassChecked;
                NJsCommon.FLibrary.IsClassOfChecked     = NJsCommon.FLibrary.FDisableCheck.IsClassOfChecked;
                NJsCommon.FLibrary.IsInstanceOfChecked  = NJsCommon.FLibrary.FDisableCheck.IsInstanceOfChecked;
            }

            static checkf(condition /*boolean*/, message /*string*/) {}
            static check(condition /*boolean*/) {}
            static /*boolean*/ IsNullObjectChecked(context /*string*/, o /*object*/) { return true; }
            static /*boolean*/ IsValidObjectChecked(context /*string*/, o /*object*/) { return true; }
            static /*boolean*/ IsFunctionChecked(context /*context*/, func /*object*/) { return true; }
            static /*boolean*/ IsGeneratorChecked(context /*context*/, gen /*object*/) { return true; }
            static /*boolean*/ IsClassChecked(context /*context*/, c /*object*/) { return true; }
            static /*boolean*/ IsClassOfChecked(context /*string*/, a /*object*/, c /*object*/) { return true; }
            static /*boolean*/ IsInstanceOfChecked(context /*string*/, a /*object*/, c /*object*/) { return true; }
        }

        /**
        * Assert if condition is FALSE and display a message.
        *  
        * @param {boolean}  condition 
        * @param {string}   message 
        */
        static checkf(condition /*boolean*/, message /*string*/)
        {
            if (!condition)
            {   
                // NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
                throw Error(message);
            }
        }

        /**
        * Assert if condition is FALSE. 
        * 
        * @param {boolean} condition 
        */
        static check(condition /*boolean*/)
        {
            if (!condition)
            {
                // NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
                throw Error();  
            }
        }

        /**
        * Get whether or not 'o' is defined (NOT undefined).
        *  
        * @param {any}          o 
        * @returns {boolean}
        */
        static /*boolean*/ IsDefined(o /*any*/)
        {
            return typeof o !== "undefined";    
        }

        /**
        * Get whether or not 'o' is null.
        * 
        * @param {object}       o 
        * @returns {boolean}
        */
        static /*boolean*/ IsNullObject(o /*object*/)
        {
            return o == null || typeof o !== "object";
        }

        /**
        * Get whether or not 'o' is null. 
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {object}       o 
        * @returns {boolean}
        */
        static /*boolean*/ IsNullObjectChecked(context /*string*/, o /*object*/)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsNullObject(o);
            self.checkf(result, context + ": o: " + o + " is NOT NULL.");
            return result;
        }

        /**
        * Get whether or not 'o' is a valid object.
        * 
        * @param {object}       o 
        * @returns {boolean}
        */
        static /*boolean*/ IsValidObject(o /*string*/)
        {
            return o != null && typeof o === "object";
        }

        /**
        * Get whether or not 'o' is a valid object.
        *  Assert if NOT. 
        * 
        * @param {string}       context
        * @param {object}       o
        * @returns {boolean}
        */
        static /*boolean*/ IsValidObjectChecked(context /*string*/, o /*object*/)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsValidObject(o);
            self.checkf(result, context + ": o: " + o + " is NOT a Valid Object.");
            return result;
        }

        /**
        * Get whether or not 'func' is a function. 
        * 
        * @param {object}       func 
        * @returns {boolean} 
        */
        static /*boolean*/ IsFunction(func /*object*/)
        {
            let getType = {};
            return func && getType.toString.call(func) === '[object Function]';
        }

        /**
        * Get whether or not 'func' is a function.
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {object}       func 
        * @returns {boolean}
        */
        static /*boolean*/ IsFunctionChecked(context /*context*/, func /*object*/)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsFunction(func);
            self.checkf(result, context + ": func: " + func + " is NOT a function.");
            return result;
        }

        /**
        * @param {object}       gen 
        * @returns {boolean}
        */
        static /*boolean*/ IsGenerator(gen /*object*/)
        {
            let self = NJsCommon.FLibrary;
            
            return self.IsValidObject(gen) && ("" + gen) === '[object Generator]';
        }

        /**
        * @param {string}       context 
        * @param {object}       gen 
        * @returns {boolean}
        */
        static /*boolean*/ IsGeneratorChecked(context /*context*/, gen /*object*/)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsGenerator(gen);
            self.checkf(result, context + ": gen: " + gen + " is NOT a function.");
            return result;
        }

        /**
        * @param {object}       c 
        * @returns {boolean}
        */
        static /*boolean*/ IsClass(c /*object*/) 
        { 
            let self = NJsCommon.FLibrary;

            return self.IsFunction(c); 
        }

        /**
        * @param {string}  context
        * @param {object}  c
        * @returns {boolean}
        */
        static /*boolean*/ IsClassChecked(context /*context*/, c /*object*/)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsFunction(c);
            self.checkf(result, context + ": class: " + c + " is NOT a class.");
            return true;
        }

        /**
        * Get whether or not 'a' is a class of 'c'.
        * 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        static /*boolean*/ IsClassOf(a /*object*/, c /*object*/) 
        { 
            let self = NJsCommon.FLibrary;

            if (!self.IsFunction(a))
                return false;
            if (!self.IsFunction(c))
                return false;
            return a instanceof c; 
        }

        /**
        * Get whether or not 'a' is a class of 'c'.
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        static /*boolean*/ IsClassOfChecked(context /*string*/, a /*object*/, c /*object*/)
        {
            let self = NJsCommon.FLibrary;

            self.IsFunctionChecked(context, a);
            self.IsFunctionChecked(context, c);

            let result = a.prototype instanceof c;
            self.checkf(result, context + ": a: " + a + " is NOT an instance of c: " + c);
            return result;
        }

        /**
        * Get whether or not 'a' is an instance of 'c'.
        * 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        static /*boolean*/ IsInstanceOf(a /*object*/, c /*object*/) 
        { 
            let self = NJsCommon.FLibrary;

            if (!self.IsValidObject(a))
                return false;
            if (!self.IsFunction(c))
                return false;
            return a instanceof c; 
        }

        /**
        * Get whether or not 'a' is an instance of 'c'.
        *  Assert if NOT.
        * 
        * @param {string}       context 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        static /*boolean*/ IsInstanceOfChecked(context /*string*/, a /*object*/, c /*object*/)
        {
            let self = NJsCommon.FLibrary;

            self.IsValidObjectChecked(context, a);
            self.IsFunctionChecked(context, c);

            let result = a instanceof c;
            self.checkf(result, context + ": a: " + a + " is NOT an instance of c: " + c);
            return result;
        }
        
        /**
        * @param {boolean}  a 
        * @returns {boolean}
        */
        static /*boolean*/ IsBool(a /*boolean*/) { return typeof a === "boolean"; }

        /**
        * @param {string}   context
        * @param {boolean}  a 
        * @returns {boolean}
        */
        static /*boolean*/ IsBoolChecked(context /*string*/, a /*boolean*/)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsBool(a);
            self.checkf(result, context + ": a: " + a + " is NOT a boolean.");
            return result;
        }

        /**
        * @param {number}   a 
        * @returns {boolean}
        */
        static /*boolean*/ IsInt(a /*number*/) { return Number.isSafeInteger(a); }

        /**
        * @param {string}   context
        * @param {number}   a 
        * @returns {boolean}
        */
        static /*boolean*/ IsIntChecked(context /*string*/, a /*number*/)
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

        static IsStringNotEmptyChecked(context, s)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.IsStringChecked(context, s));
            self.checkf(s !== "", context + ": s: " + s + " is EMPTY.");
            return true;
        }

        /**
         * @param {object} o 
         * @param {string} key
         * @returns {boolean} 
         */
        static /*bool*/ DoesKeyExist(o /*object*/, key /*string*/)
        {
            let self = NJsCommon.FLibrary;

            if (!self.IsValidObject(o))
                return false;

            return key in o;
        }
 
         /**
          * @param {string} context
          * @param {object} o 
          * @param {string} key
          * @returns {boolean} 
          */
        static /*bool*/ DoesKeyExistChecked(context /*string*/, o /*object*/, key /*string*/)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.IsValidObjectChecked(context, o));

            self.checkf(key in o, context + ": o does NOT contain key: " + key);
            return true;
        }

        /**
         * @param {object} o 
         * @param {string} key
         * @returns {boolean} 
         */
        static /*bool*/ DoesKeyOfBoolExist(o /*object*/, key /*string*/)
        {
            let self = NJsCommon.FLibrary;

            if (!self.DoesKeyExist(o, key))
                return false;
            return self.IsBool(o[key]);
        }
  
        /**
         * @param {string} context
         * @param {object} o 
         * @param {string} key
         * @returns {boolean} 
         */
        static /*bool*/ DoesKeyOfBoolExistChecked(context /*string*/, o /*object*/, key /*string*/)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.DoesKeyExistChecked(context, o, key));
            self.check(self.IsBoolChecked(context, o[key]));
            return true;
        }

        /**
         * @param {object} o 
         * @param {string} key
         * @returns {boolean} 
         */
        static /*bool*/ DoesKeyOfArrayExist(o /*object*/, key /*string*/)
        {
            let self = NJsCommon.FLibrary;

            if (!self.DoesKeyExist(o, key))
                return false;
            return Array.isArray(o[key]);
        }

        /**
         * @param {string} context
         * @param {object} o 
         * @param {string} key
         * @returns {boolean} 
         */
        static /*bool*/ DoesKeyOfArrayExistChecked(context /*string*/, o /*object*/, key /*string*/)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.DoesKeyExistChecked(context, o, key));
            self.check(Array.isArray(o[key]), context + ": o[key] is type: " + typeof (o[key]) + " and NOT an array.");
            return true;
        }

        /**
         * @param {object} o 
         * @param {string} key
         * @param {function} classType
         * @returns {boolean} 
         */
         static /*bool*/ DoesKeyOfInstanceExist(o /*object*/, key /*string*/, classType /*class*/)
         {
             let self = NJsCommon.FLibrary;
 
             if (!self.DoesKeyExist(o, key))
                 return false;
             return self.IsInstanceOf(o[key], classType);
         }
  
          /**
           * @param {string} context
           * @param {object} o 
           * @param {string} key
           * @param {function} classType
           * @returns {boolean} 
           */
         static /*bool*/ DoesKeyOfInstanceExistChecked(context /*string*/, o /*object*/, key /*string*/, classType /*class*/)
         {
             let self = NJsCommon.FLibrary;
 
             self.check(self.DoesKeyExistChecked(context, o, key));
             self.check(self.IsInstanceOfChecked(context, o[key], classType));
             return true;
         }

        /**
         * @param {object} o 
         * @param {string} key
         * @param {function} classType
         * @returns {boolean} 
         */
        static /*bool*/ DoesKeyOfClassExist(o /*object*/, key /*string*/, classType /*class*/)
        {
            let self = NJsCommon.FLibrary;

            if (!self.DoesKeyExist(o, key))
                return false;
            return self.IsClassOf(o[key], classType);
        }
 
         /**
          * @param {string} context
          * @param {object} o 
          * @param {string} key
          * @param {function} classType
          * @returns {boolean} 
          */
        static /*bool*/ DoesKeyOfClassExistChecked(context /*string*/, o /*object*/, key /*string*/, classType /*class*/)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.DoesKeyExistChecked(context, o, key));
            self.check(self.IsClassOfChecked(context, o[key], classType));
            return true;
        }

        /**
         * @param {object} o 
         * @param {string} key
         * @param {function} fn
         * @returns {boolean} 
         */
        static /*bool*/ DoesKeyOfFunctionExist(o /*object*/, key /*string*/, fn /*function*/)
        {
            let self = NJsCommon.FLibrary;

            if (!self.DoesKeyExist(o, key))
                return false;
            return self.IsFunction(o[key], fn);
        }
 
         /**
          * @param {string} context
          * @param {object} o 
          * @param {string} key
          * @param {function} fn
          * @returns {boolean} 
          */
        static /*bool*/ DoesKeyOfFunctionExistChecked(context /*string*/, o /*object*/, key /*string*/, fn /*function*/)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.DoesKeyExistChecked(context, o, key));
            self.check(self.IsFunctionChecked(context, o[key], fn));
            return true;
        }
    };
};