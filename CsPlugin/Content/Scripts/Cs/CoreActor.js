/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

module.exports = class FJsCoreActor extends Actor
{
    ctor()
    {
        this.Core = null;
    }

    properties()
    {
    }

    /**
     * @param {FJsCore} core 
     */
    Init(core)
    {
        let context = "FJsCoreActor.Init";

        this.Core = core;

        this.Tags = ["FJsCoreActor"];
    }
};