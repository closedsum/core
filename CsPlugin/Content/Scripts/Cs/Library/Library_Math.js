/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

module.exports = class NJsMath
{
    static FLibrary = class Library
    {
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
            self.checkf(result, context + ": a: " + a + " is NOT BOTH an integer AND > 0.");
            return result;
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
            self.checkf(result, context + ": a: " + a + " is NOT BOTH an integer AND >= 0.");
            return result;
        }
    };
};