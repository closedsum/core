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

module.exports = class NJsTypes
{
    static FTArrayMaterialInterface = class TArrayMaterialInterface
    {
        constructor()
        {  
            /** @type {string[]} */     this.Paths = [];
            /** @type {MaterialInterface[]} */ this.Materials_Internal = null;
        }

        /**
        * @returns {MaterialInterface[]}
        */
        /*MaterialInterface[]*/ Get() { return this.Materials_Internal; }

        /**
        * @param {MaterialInterface[]} mats 
        */
        Set(mats /*MaterialInterface[]*/) { this.Materials_Internal = mats; }
    }
};