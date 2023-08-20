// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;

var ClassName = "NJsMath.FLibrary";

module.exports = class NJsMath
{
    static FLibrary = class Library
    {
        static FDisableCheck = class DisableCheck
        {
            static Setup()
            {
                NJsMath.FLibrary.IsPositiveIntChecked     = NJsMath.FLibrary.FDisableCheck.IsPositiveIntChecked;
                NJsMath.FLibrary.IsPositiveIntChecked2    = NJsMath.FLibrary.FDisableCheck.IsPositiveIntChecked2;
                NJsMath.FLibrary.IsNonNegativeIntChecked  = NJsMath.FLibrary.FDisableCheck.IsNonNegativeIntChecked;
                NJsMath.FLibrary.IsNonNegativeIntChecked2 = NJsMath.FLibrary.FDisableCheck.IsNonNegativeIntChecked2;
            }

            static /*bool*/ IsPositiveIntChecked(context /*string*/, a /*number*/) { return true; }
            static /*bool*/ IsPositiveIntChecked2(a /*number*/) { return true; }
            static /*bool*/ IsNonNegativeIntChecked(context /*string*/, a /*number*/) { return true; }
            static /*bool*/ IsNonNegativeIntChecked2(a /*number*/) { return true; }
        }

        /**
        * @param {number}       bitmask 
        * @param {number}       bit
        * @returns {boolean}
        */
        static /*bool*/ BitFlag_Test(bitmask /*number*/, bit /*number*/)
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

        /**
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*bool*/ IsPositiveInt(a /*number*/) { return Number.isSafeInteger(a) && (a > 0); }

        /**
        * @param {string}       context
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*bool*/ IsPositiveIntChecked(context /*string*/, a /*number*/)
        {
            let self = NJsMath.FLibrary;

            let result = self.IsPositiveInt(a);
            checkf(result, context + ": a: " + a + " is NOT BOTH an integer AND > 0.");
            return result;
        }

        /**
        * @param {string}       context
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*bool*/ IsPositiveIntChecked2(a /*number*/)
        {
            let context = ClassName + ".IsPositiveIntChecked";

            let self = NJsMath.FLibrary;

            return self.IsPositiveIntChecked(context, a);
        }

        /**
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*bool*/ IsNonNegativeInt(a /*number*/) { return Number.isSafeInteger(a) && (a >= 0); }

        /**
        * @param {string}       context
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*bool*/ IsNonNegativeIntChecked(context /*string*/, a /*number*/)
        {
            let self = NJsMath.FLibrary;

            let result = self.IsNonNegativeInt(a);
            checkf(result, context + ": a: " + a + " is NOT BOTH an integer AND >= 0.");
            return result;
        }

        /**
        * @param {number}       a 
        * @returns {boolean}
        */
        static /*bool*/ IsNonNegativeIntChecked2(a /*number*/)
        {
            let context = ClassName + ".IsNonNegativeIntChecked";

            let self = NJsMath.FLibrary;

            return self.IsNonNegativeIntChecked(context, a);
        }
    };
};