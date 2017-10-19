/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me;

module.exports = class JsCsUI
{
    constructor()
    {
        me = this;

        this.ptr = null;
        this.root = null;

        this.Widgets = [];
        this.ActiveWidgets = [];
    }

    Init(inPtr, inRoot)
    {
        this.ptr = CsUI.C(inPtr);
        this.root = inRoot;

        /*
        // Update
        this.ptr.OnUpdate_ScriptEvent.Add(this.OnUpdate);
        // PostProcessInput
        this.ptr.OnPostProcessInput_ScriptEvent.Add(this.OnPostProcessInput);
        // LastTick
        this.ptr.OnLastTick_ScriptEvent.Add(this.OnLastTick);
        // Open
        this.ptr.OnOpen_ScriptEvent.Add(this.OnOpen);
        // Close
        this.ptr.OnClose_ScriptEvent.Add(this.OnClose);
        */
    }
    /*
    OnUpdate(deltaSeconds){ me.OnUpdate_Internal(deltaSeconds); }
    OnUpdate_Internal(deltaSeconds){}

    OnPostProcessInput(deltaTime){ me.OnPostProcessInput_Internal(deltaTime); }
    OnPostProcessInput_Internal(deltaTime){}

    OnOpen(widgetType){ me.OnOpen_Internal(widgetType); }
    OnOpen_Internal(widgetType){}

    OnClose(widgetType){ me.OnClose_Internal(widgetType); }
    OnClose_Internal(widgetType){}
    */
};