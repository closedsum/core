// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

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

    /**
    * @param {number} val 
    */
    Equal(val /*number*/)
    {
        check(IsNonNegativeInt(val));

        this.Value = val;
    }

    Reset()
    {
        this.Value = 0;
    }

    /**
    * @returns {boolean} 
    */
    /*boolean*/ AnySet() { return this.Value > 0; }
    
    /**
    * @param {bit} number 
    */
    Set(bit /*number*/)
    {
        check(IsNonNegativeInt(this.Value));
        check(IsNonNegativeInt(bit))

        this.Value |= bit;
    }

    /**
    * @param {bit} number 
    */
    Clear(bit /*number*/)
    {
        check(IsNonNegativeInt(this.Value));
        check(IsNonNegativeInt(bit))

        this.Value &= ~bit;
    }

    /**
    * @param {bit}          number 
    * @returns {boolean}
    */
    /*boolean*/ Test(bit /*number*/)
    {
        check(IsNonNegativeInt(this.Value));
        check(IsNonNegativeInt(bit))

        return ((this.Value & bit) === bit);
    }
};