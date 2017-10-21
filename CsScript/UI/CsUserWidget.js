/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me = [];

module.exports = class JsCsUserWidget
{
    constructor()
    {
        me.push(this);

        this.ptr = null;
        this.root = null;
    }

    Init(inPtr, inRoot)
    {
        this.ptr = CsUserWidget.C(inPtr);
        this.root = inRoot;

        //this.ptr.OnNativeTick_ScriptEvent.Add(this.OnNativeTick);
        //this.ptr.OnOpenChild_ScriptEvent.Add(this.OnOpenChild);
        //this.ptr.OnCloseChild.ScriptEvent.Add(this.OnCloseChild);
        //this.ptr.Override_ProcessGameEvent_ScriptEvent.Add(this.ProcessGameEvent);
    }

    CleanUp()
    {
    }
};