/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsMath = require('Cs/Library/Library_Math.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var MathLibrary = NJsMath.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var IsNonNegativeInt = MathLibrary.IsNonNegativeInt;

module.exports = class FJsMask
{
    constructor()
    {
        this.Value = 0;
    }

    Equal(val /*number*/)
    {
        check(IsNonNegativeInt(val));

        this.Value = val;
    }

    Reset()
    {
        this.Value = 0;
    }

    Set(bit /*number*/)
    {
        check(IsNonNegativeInt(this.Value));
        check(IsNonNegativeInt(bit))

        this.Value |= bit;
    }

    Clear(bit /*number*/)
    {
        check(IsNonNegativeInt(this.Value));
        check(IsNonNegativeInt(bit))

        this.Value &= ~bit;
    }

    /*boolean*/ Test(bit /*number*/)
    {
        check(IsNonNegativeInt(this.Value));
        check(IsNonNegativeInt(bit))

        return ((this.Value & bit) === bit);
    }
};