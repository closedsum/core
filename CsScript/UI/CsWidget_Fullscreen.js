/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me = [];

module.exports = class JsCsWidget_Fullscreen
{
    constructor()
    {
        me.push(this);

        this.ptr = null;
        this.root = null;
    }

    Init(inPtr, inRoot)
    {
        this.ptr = CsWidget_Fullscreen.C(inPtr);
        this.root = inRoot;
    }
};