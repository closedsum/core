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

module.exports = class NJsArray
{
    static FLibrary = class Library
    {
        static IsEmpty(a)
        {
            if (!Array.isArray(a))
                return true;
            return a.length === 0;
        }

        static IsNotEmptyChecked(context, a)
        {
            // Check is array
            checkf(Array.isArray(a), context + ": a is type: " + typeof a + " and NOT an array.");
            // Check array.length is NOT 0
            checkf(a.length !== 0, context + ": a is EMPTY");
            return true;
        }

        static IsNotEmpty(a)
        {
            // Check is array
            if (!Array.isArray(a))
                return false;
            // Check array.length is NOT 0
            if (a.length === 0)
                return false;
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