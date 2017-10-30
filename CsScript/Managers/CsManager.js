/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me;

module.exports = class JsCsManager
{
    constructor()
    {
        me = this;
        
        this.ptr = null;
        this.root = null;
    }

    Init(inPtr, inRoot)
    {
        this.ptr = CsManager.C(inPtr);
        this.root = inRoot;
    }

    CleanUp(){}
};