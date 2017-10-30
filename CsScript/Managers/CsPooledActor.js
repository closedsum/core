/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me;

module.exports = class JsCsPooledActor
{
    constructor()
    {
        me = this;
        
        this.ptr = null;
        this.root = null;
    }

    Init(inPtr, inRoot)
    {
        this.ptr = CsPooledActor.C(inPtr);
        this.root = inRoot;
    }

    CleanUp(){}
};