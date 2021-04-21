/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me;

module.exports = class JsCsGameState
{
    constructor()
    {
        me = this;
        
        this.ptr = null;
        this.root = null;
    }

    Init(inPtr, inRoot)
    {
        this.ptr  = CsGameState.C(inPtr);
        this.root = inRoot;

        //this.ptr.OnTick_ScriptEvent.Add(this.OnTick);
    }

    CleanUp(){}
    /*
    OnTick(deltaSeconds) { me.OnTick_Internal(deltaSeconds); }
    OnTick_Internal(deltaSeconds){}
    */
};