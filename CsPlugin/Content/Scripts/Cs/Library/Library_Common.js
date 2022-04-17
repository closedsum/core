/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class NJsCommon
{
    static FLibrary = class Library
    {

        /**
         * @param {boolean} condition 
         * @param {string} message 
         */
        static checkf(condition /*bool*/, message /*string*/)
        {
            if (!condition)
            {   
                // NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
                throw Error(message);
            }
        }

        /**
         * @param {boolean} condition 
         */
        static check(condition /*bool*/)
        {
            if (!condition)
            {
                // NOTE: Future add different "level" of errors. Maybe even a native / c++ checkf.
                throw Error();  
            }
        }

        /**
         * @param {any} o 
         * @returns {boolean}
         */
        static /*bool*/ IsDefined(o /*any*/)
        {
            return typeof o !== "undefined";    
        }

        /**
         * @param {object} o 
         * @returns {boolean}
         */
        static /*bool*/ IsNullObject(o /*object*/)
        {
            return o == null || typeof o !== "object";
        }

        /**
         * @param {string} context 
         * @param {object} o 
         * @returns {boolean}
         */
        static /*bool*/ IsNullObjectChecked(context /*string*/, o /*object*/)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsNullObject(o);
            self.checkf(result, context + ": o: " + o + " is NOT NULL.");
            return result;
        }

        /**
         * @param {object} o 
         * @returns {boolean}
         */
        static /*bool*/ IsValidObject(o /*string*/)
        {
            return o != null && typeof o === "object";
        }

        /**
         * @param {string} context
         * @param {object} o
         * @returns {boolean}
         */
        static /*bool*/ IsValidObjectChecked(context /*string*/, o /*object*/)
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

        static IsClass(c) 
        { 
            let self = NJsCommon.FLibrary;

            return self.IsFunction(c); 
        }

        static IsClassChecked(context, c)
        {
            let self = NJsCommon.FLibrary;

            let result = self.IsFunction(c);
            self.checkf(result, context + ": class: " + c + " is NOT a class.");
            return true;
        }

        static IsClassOf(a, c) 
        { 
            let self = NJsCommon.FLibrary;

            if (!self.IsFunction(a))
                return false;
            if (!self.IsFunction(c))
                return false;
            return a instanceof c; 
        }

        static IsClassOfChecked(context, a, c)
        {
            let self = NJsCommon.FLibrary;

            self.check(self.IsFunctionChecked(context, a));
            self.check(self.IsFunctionChecked(context, c));

            let result = a.prototype instanceof c;
            self.checkf(result, context + ": a: " + a + " is NOT an instance of c: " + c);
            return result;
        }

        static IsInstanceOf(a, c) 
        { 
            let self = NJsCommon.FLibrary;

            if (!self.IsValidObject(a))
                return false;
            if (!self.IsFunction(c))
                return false;
            return a instanceof c; 
        }

        static IsInstanceOfChecked(context, a, c)
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