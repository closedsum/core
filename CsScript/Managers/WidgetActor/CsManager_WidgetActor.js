/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsManager = require('CsScript/Managers/CsManager.js');

var me;

module.exports = class JsCsManager_WidgetActor extends JsCsManager
{
    constructor()
    {
        super();

        me = this;

        this.ActiveWidgetActors = [];
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);
        
        this.ptr = CsManager_WidgetActor.C(inPtr);
    }
}