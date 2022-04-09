/// <reference path="../../Cs/Library/Library_Common.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - classes
/** @type {CommonLibrary} */
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var checkf = CommonLibrary.checkf;
var check = CommonLibrary.check;

module.exports = class NJsArray
{
    static FLibrary = class Library
    {
        /**
         * @param {Array} a 
         * @returns {boolean}
         */
        static /*bool*/ IsEmpty(a /*Array*/)
        {
            if (!Array.isArray(a))
                return true;
            return a.length === 0;
        }

        /**
         * @param {string} context 
         * @param {Array} a 
         * @returns {boolean}
         */
        static /*bool*/ IsNotEmptyChecked(context /*string*/, a /*Array*/)
        {
            // Check is array
            checkf(Array.isArray(a), context + ": a is type: " + typeof a + " and NOT an array.");
            // Check array.length is NOT 0
            checkf(a.length !== 0, context + ": a is EMPTY");
            return true;
        }

        /**
         * @param {Array} a 
         * @returns {boolean}
         */
        static /*bool*/ IsNotEmpty(a /*Array*/)
        {
            // Check is array
            if (!Array.isArray(a))
                return false;
            // Check array.length is NOT 0
            if (a.length === 0)
                return false;
            return true;
        }

        /**
         * @param {Array}   a 
         * @param {number}  size    int
         * @returns {boolean} 
         */
        /*bool*/ static IsSize(a /*Array*/, size /*int*/)
        {
            let self = NJsArray.FLibrary;

            if (!self.IsNotEmpty(a))
                return false;

            if (!CommonLibrary.IsInt(size))
                return false;

            return a.length === size;
        }

        /**
         * @param {string}  context
         * @param {Array}   a 
         * @param {number}  size    int
         * @returns {boolean} 
         */
        /*bool*/ static IsSizeChecked(context /*string*/, a /*Array*/, size /*int*/)
        {
            let self = NJsArray.FLibrary;

            check(self.IsNotEmptyChecked(context, a));

            check(CommonLibrary.IsIntChecked(context, size));

            checkf(a.length === size, context + ": a is NOT of length: " + size);

            return true;
        }

        static AreAllElements_Class_Checked(context, a, classType)
        {
            let self = NJsArray.FLibrary;

            // Check is array
            checkf(Array.isArray(a), context + ": a is type: " + typeof a + " and NOT an array.");

            for (let item of a)
            {
                check(CommonLibrary.IsClassOfChecked(context, item, classType));
            }
            return true;
        }

        static AreAllElements_Class(a, classType)
        {
            // Check is array
            if (!Array.isArray(a))
                return false;

            for (let item of a)
            {
                if (!CommonLibrary.IsClassOf(item, classType))
                    return false;
            }
            return true;
        }

        static AreAllElements2d_Class_Checked(context, a, classType)
        {
            // Check is array
            checkf(Array.isArray(a), context + ": a is type: " + typeof a + " and NOT an array.");

            for (let a2 of a)
            {
                checkf(Array.isArray(a2), context + ": a2 is type: " + typeof a + " and NOT an array.");

                for (let item of a2)
                {
                    check(CommonLibrary.IsClassOfChecked(context, item, classType));
                }
            }
            return true;
        }

        static AreAllElements2d_Class(a, classType)
        {
            // Check is array
            checkf(Array.isArray(a), context + ": a is type: " + typeof a + " and NOT an array.");

            for (let a2 of a)
            {
                checkf(Array.isArray(a2), context + ": a2 is type: " + typeof a + " and NOT an array.");

                for (let item of a2)
                {
                    check(CommonLibrary.IsClassOfChecked(context, item, classType));
                }
            }
            return true;
        }

        static IsNotEmptyAndAllElements_Class_Checked(context, a, classType)
        {
            let self = NJsArray.FLibrary;

            check(self.IsNotEmptyChecked(context, a));

            for (let item of a)
            {
                check(CommonLibrary.IsClassOfChecked(context, item, classType));
            }
            return true;
        }

        static IsNotEmptyAndAllElements_Class(a, classType)
        {
            let self = NJsArray.FLibrary;

            if (self.IsEmpty(a))
                return false;

            for (let item of a)
            {
                if (!CommonLibrary.IsClassOf(item, classType))
                    return false;
            }
            return true;
        }

        static IsNotEmptyAndAllElements2d_Class_Checked(context, a, classType)
        {
            let self = NJsArray.FLibrary;

            check(self.IsNotEmptyChecked(context, a));

            for (let a2 of a)
            {
                check(self.IsNotEmptyChecked(context, a2));

                for (let item of a2)
                {
                    check(CommonLibrary.IsClassOfChecked(context, item, classType));
                }
            }
            return true;
        }

        static IsNotEmptyAndAllElements2d_Class(a, classType)
        {
            let self = NJsArray.FLibrary;

            if (self.IsEmpty(a))
                return false;

            for (let a2 of a)
            {
                if (self.IsEmpty(a2))
                    return false;

                for (let item of a2)
                {
                    if (!CommonLibrary.IsClassOf(item, classType))
                        return false;
                }
            }
            return true;
        }
    };
};