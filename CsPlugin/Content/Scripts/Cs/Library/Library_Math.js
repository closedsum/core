// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Library
/// <reference path="Library_Common.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check           = CommonLibrary.check;
var checkf          = CommonLibrary.checkf;
var IsNumberChecked = CommonLibrary.IsNumberChecked;
var IsIntChecked    = CommonLibrary.IsIntChecked;
var IsFloatChecked  = CommonLibrary.IsFloatChecked;

var ClassName = "NJsMath.FLibrary";

module.exports = class NJsMath
{
    static FLibrary = class Library
    {
        static NCached = class NamespaceCached
        {
            static NStr = class NamespaceStr
            {   
                // Number
                static IsGreaterThanChecked          = ClassName = ".IsGreaterThanChecked";
                static IsGreaterThanOrEqualChecked   = ClassName = ".IsGreaterThanOrEqualChecked";
                static IsLessThanChecked             = ClassName = ".IsLessThanChecked";
                static IsLessThanOrEqualChecked      = ClassName = ".IsLessThanOrEqualChecked";
                // Int
                static IsPositiveIntChecked             = ClassName + ".IsPositiveIntChecked";
                static IsNonNegativeIntChecked          = ClassName + ".IsNonNegativeIntChecked";
                static IsIntGreaterThanChecked          = ClassName = ".IsIntGreaterThanChecked";
                static IsIntGreaterThanOrEqualChecked   = ClassName = ".IsIntGreaterThanOrEqualChecked";
                static IsIntLessThanChecked             = ClassName = ".IsIntLessThanChecked";
                static IsIntLessThanOrEqualChecked      = ClassName = ".IsIntLessThanOrEqualChecked";
                // Float
                static IsFloatGreaterThanChecked          = ClassName = ".IsFloatGreaterThanChecked";
                static IsFloatGreaterThanOrEqualChecked   = ClassName = ".IsFloatGreaterThanOrEqualChecked";
                static IsFloatLessThanChecked             = ClassName = ".IsFloatLessThanChecked";
                static IsFloatLessThanOrEqualChecked      = ClassName = ".IsFloatLessThanOrEqualChecked";
            }
        }

        static FDisableCheck = class DisableCheck
        {
            static Setup()
            {
                // Number
                NJsMath.FLibrary.IsGreaterThanChecked  = NJsMath.FLibrary.FDisableCheck.IsGreaterThanChecked;
                NJsMath.FLibrary.IsGreaterThanChecked2 = NJsMath.FLibrary.FDisableCheck.IsGreaterThanChecked2;
                NJsMath.FLibrary.IsGreaterThanOrEqualChecked  = NJsMath.FLibrary.FDisableCheck.IsGreaterThanOrEqualChecked;
                NJsMath.FLibrary.IsGreaterThanOrEqualChecked2 = NJsMath.FLibrary.FDisableCheck.IsGreaterThanOrEqualChecked2;
                NJsMath.FLibrary.IsLessThanChecked  = NJsMath.FLibrary.FDisableCheck.IsLessThanChecked;
                NJsMath.FLibrary.IsLessThanChecked2 = NJsMath.FLibrary.FDisableCheck.IsLessThanChecked2;
                NJsMath.FLibrary.IsLessThanOrEqualChecked  = NJsMath.FLibrary.FDisableCheck.IsLessThanOrEqualChecked;
                NJsMath.FLibrary.IsLessThanOrEqualChecked2 = NJsMath.FLibrary.FDisableCheck.IsLessThanOrEqualChecked2;
                // Int
                NJsMath.FLibrary.IsPositiveIntChecked     = NJsMath.FLibrary.FDisableCheck.IsPositiveIntChecked;
                NJsMath.FLibrary.IsPositiveIntChecked2    = NJsMath.FLibrary.FDisableCheck.IsPositiveIntChecked2;
                NJsMath.FLibrary.IsNonNegativeIntChecked  = NJsMath.FLibrary.FDisableCheck.IsNonNegativeIntChecked;
                NJsMath.FLibrary.IsNonNegativeIntChecked2 = NJsMath.FLibrary.FDisableCheck.IsNonNegativeIntChecked2;
                NJsMath.FLibrary.IsIntGreaterThanChecked  = NJsMath.FLibrary.FDisableCheck.IsIntGreaterThanChecked;
                NJsMath.FLibrary.IsIntGreaterThanChecked2 = NJsMath.FLibrary.FDisableCheck.IsIntGreaterThanChecked2;
                NJsMath.FLibrary.IsIntGreaterThanOrEqualChecked  = NJsMath.FLibrary.FDisableCheck.IsIntGreaterThanOrEqualChecked;
                NJsMath.FLibrary.IsIntGreaterThanOrEqualChecked2 = NJsMath.FLibrary.FDisableCheck.IsIntGreaterThanOrEqualChecked2;
                NJsMath.FLibrary.IsIntLessThanChecked  = NJsMath.FLibrary.FDisableCheck.IsIntLessThanChecked;
                NJsMath.FLibrary.IsIntLessThanChecked2 = NJsMath.FLibrary.FDisableCheck.IsIntLessThanChecked2;
                NJsMath.FLibrary.IsIntLessThanOrEqualChecked  = NJsMath.FLibrary.FDisableCheck.IsIntLessThanOrEqualChecked;
                NJsMath.FLibrary.IsIntLessThanOrEqualChecked2 = NJsMath.FLibrary.FDisableCheck.IsIntLessThanOrEqualChecked2;
                // Float
                NJsMath.FLibrary.IsFloatGreaterThanChecked  = NJsMath.FLibrary.FDisableCheck.IsFloatGreaterThanChecked;
                NJsMath.FLibrary.IsFloatGreaterThanChecked2 = NJsMath.FLibrary.FDisableCheck.IsFloatGreaterThanChecked2;
                NJsMath.FLibrary.IsFloatGreaterThanOrEqualChecked  = NJsMath.FLibrary.FDisableCheck.IsFloatGreaterThanOrEqualChecked;
                NJsMath.FLibrary.IsFloatGreaterThanOrEqualChecked2 = NJsMath.FLibrary.FDisableCheck.IsFloatGreaterThanOrEqualChecked2;
                NJsMath.FLibrary.IsFloatLessThanChecked  = NJsMath.FLibrary.FDisableCheck.IsFloatLessThanChecked;
                NJsMath.FLibrary.IsFloatLessThanChecked2 = NJsMath.FLibrary.FDisableCheck.IsFloatLessThanChecked2;
                NJsMath.FLibrary.IsFloatLessThanOrEqualChecked  = NJsMath.FLibrary.FDisableCheck.IsFloatLessThanOrEqualChecked;
                NJsMath.FLibrary.IsFloatLessThanOrEqualChecked2 = NJsMath.FLibrary.FDisableCheck.IsFloatLessThanOrEqualChecked2;
            }

            // Number
            static /*boolean*/ IsGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsGreaterThanChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsGreaterThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsGreaterThanOrEqualChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsLessThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsLessThanChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsLessThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsLessThanOrEqualChecked2(a /*number*/, b /*number*/) { return true; }
            // Int
            static /*boolean*/ IsPositiveIntChecked(context /*string*/, a /*number*/) { return true; }
            static /*boolean*/ IsPositiveIntChecked2(a /*number*/) { return true; }
            static /*boolean*/ IsNonNegativeIntChecked(context /*string*/, a /*number*/) { return true; }
            static /*boolean*/ IsNonNegativeIntChecked2(a /*number*/) { return true; }
            static /*boolean*/ IsIntGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsIntGreaterThanChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsIntGreaterThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsIntGreaterThanOrEqualChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsIntLessThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsIntLessThanChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsIntLessThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsIntLessThanOrEqualChecked2(a /*number*/, b /*number*/) { return true; }
            // Float
            static /*boolean*/ IsFloatGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsFloatGreaterThanChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsFloatGreaterThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsFloatGreaterThanOrEqualChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsFloatLessThanChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsFloatLessThanChecked2(a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsFloatLessThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/) { return true; }
            static /*boolean*/ IsFloatLessThanOrEqualChecked2(a /*number*/, b /*number*/) { return true; }
        }

        /**
        * @param {number}       bitmask 
        * @param {number}       bit
        * @returns {boolean}
        */
        static /*boolean*/ BitFlag_Test(bitmask /*number*/, bit /*number*/)
        {
            let self = NJsMath.FLibrary;

            check(self.IsNonNegativeInt(bitmask));
            check(self.IsNonNegativeInt(bit))

            return ((bitmask & bit) === bit);
        }

        /**
        * @param {number}       bitmask 
        * @param {number}       bit
        * @returns {number}
        */
        static /*number*/ BitFlag_Set(bitmask /*number*/, bit /*number*/)
        {
            let self = NJsMath.FLibrary;

            check(self.IsNonNegativeInt(bitmask));
            check(self.IsNonNegativeInt(bit))

            return (bitmask | bit);
        }

         /**
        * @param {number}       bitmask 
        * @param {number}       bit
        * @returns {number}
        */
        static /*number*/ BitFlag_Clear(bitmask /*number*/, bit /*number*/)
        {
            let self = NJsMath.FLibrary;

            check(self.IsNonNegativeInt(bitmask));
            check(self.IsNonNegativeInt(bit))
            
            return (bitmask & (~bit));
        }

    // #region Number

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsNumberChecked(context, a);
            IsNumberChecked(context, b);

            checkf(a > b, context + ": " + a + " is NOT > " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsGreaterThanChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsGreaterThanChecked;

            return self.IsGreaterThanChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsGreaterThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsNumberChecked(context, a);
            IsNumberChecked(context, b);

            checkf(a >= b, context + ": " + a + " is NOT >= " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsGreaterThanOrEqualChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsGreaterThanOrEqualChecked;

            return self.IsGreaterThanOrEqualChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsLessThanChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsNumberChecked(context, a);
            IsNumberChecked(context, b);

            checkf(a < b, context + ": " + a + " is NOT < " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsLessThanChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsLessThanChecked;

            return self.IsLessThanChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsLessThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsNumberChecked(context, a);
            IsNumberChecked(context, b);

            checkf(a <= b, context + ": " + a + " is NOT <= " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        static /*boolean*/ IsLessThanOrEqualChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsLessThanOrEqualChecked;

            return self.IsLessThanOrEqualChecked(context, a, b);
        }

    // #endregion Number

    // #region Int

        /**
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*boolean*/ IsPositiveInt(a /*number*/) { return Number.isSafeInteger(a) && (a > 0); }

        /**
        * Get whether or not 'a' is a positive integer (a > 0).
        *  Assert if NOT.  
        * 
        * @param {string}       context     The calling context.
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*boolean*/ IsPositiveIntChecked(context /*string*/, a /*number*/)
        {
            let self = NJsMath.FLibrary;

            let result = self.IsPositiveInt(a);
            checkf(result, context + ": a: " + a + " is NOT BOTH an integer AND > 0.");
            return result;
        }

        /**
        * Get whether or not 'a' is a positive integer (a > 0).
        *  Assert if NOT. 
        * 
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*boolean*/ IsPositiveIntChecked2(a /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsPositiveIntChecked;

            return self.IsPositiveIntChecked(context, a);
        }

        /**
        * Get whether or not 'a' is a non-negative integer (a >= 0).
        *  
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*boolean*/ IsNonNegativeInt(a /*number*/) { return Number.isSafeInteger(a) && (a >= 0); }

        /**
        * Get whether or not 'a' is a non-negative integer (a >= 0).
        *  Assert if NOT. 
        * 
        * @param {string}       context     The calling context.
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*boolean*/ IsNonNegativeIntChecked(context /*string*/, a /*number*/)
        {
            let self = NJsMath.FLibrary;

            let result = self.IsNonNegativeInt(a);
            checkf(result, context + ": a: " + a + " is NOT BOTH an integer AND >= 0.");
            return result;
        }

        /**
        * Get whether or not 'a' is a non-negative integer (a >= 0).
        *  Assert if NOT. 
        *  
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*boolean*/ IsNonNegativeIntChecked2(a /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsNonNegativeIntChecked;

            return self.IsNonNegativeIntChecked(context, a);
        }

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsIntChecked(context, a);
            IsIntChecked(context, b);

            checkf(a > b, context + ": " + a + " is NOT > " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntGreaterThanChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsIntGreaterThanChecked;

            return self.IsIntGreaterThanChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntGreaterThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsIntChecked(context, a);
            IsIntChecked(context, b);

            checkf(a >= b, context + ": " + a + " is NOT >= " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntGreaterThanOrEqualChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsIntGreaterThanOrEqualChecked;

            return self.IsIntGreaterThanOrEqualChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntLessThanChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsIntChecked(context, a);
            IsIntChecked(context, b);

            checkf(a < b, context + ": " + a + " is NOT < " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntLessThanChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsIntLessThanChecked;

            return self.IsIntLessThanChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntLessThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsIntChecked(context, a);
            IsIntChecked(context, b);

            checkf(a <= b, context + ": " + a + " is NOT <= " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        static /*boolean*/ IsIntLessThanOrEqualChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsIntLessThanOrEqualChecked;

            return self.IsIntLessThanOrEqualChecked(context, a, b);
        }

    // #endregion Int

    // #region Float

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatGreaterThanChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsFloatChecked(context, a);
            IsFloatChecked(context, b);

            checkf(a > b, context + ": " + a + " is NOT > " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatGreaterThanChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsFloatGreaterThanChecked;

            return self.IsFloatGreaterThanChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatGreaterThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsFloatChecked(context, a);
            IsFloatChecked(context, b);

            checkf(a >= b, context + ": " + a + " is NOT >= " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatGreaterThanOrEqualChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsFloatGreaterThanOrEqualChecked;

            return self.IsFloatGreaterThanOrEqualChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatLessThanChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsFloatChecked(context, a);
            IsFloatChecked(context, b);

            checkf(a < b, context + ": " + a + " is NOT < " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatLessThanChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsFloatLessThanChecked;

            return self.IsFloatLessThanChecked(context, a, b);
        }

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatLessThanOrEqualChecked(context /*string*/, a /*number*/, b /*number*/)
        {
            IsFloatChecked(context, a);
            IsFloatChecked(context, b);

            checkf(a <= b, context + ": " + a + " is NOT <= " + b + " .");
            return true;
        }

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.
        *  
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        static /*boolean*/ IsFloatLessThanOrEqualChecked2(a /*number*/, b /*number*/)
        {
            let self    = NJsMath.FLibrary;
            let context = self.NCached.NStr.IsFloatLessThanOrEqualChecked;

            return self.IsFloatLessThanOrEqualChecked(context, a, b);
        }

    // #endregion Float
    };
};