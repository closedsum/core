/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class FJsCore
{
    constructor()
    {
        this.CoroutineScheduler = null;
    }

    GetCoroutineScheduler() { return this.CoroutineScheduler; }
};