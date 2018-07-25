/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsManager_PooledObjects_TMap = require('CsScript/Managers/CsManager_PooledObjects_TMap.js');

var me;

module.exports = class JsCsManager_AI extends JsCsManager_PooledObjects_TMap
{
    constructor()
    {
        super();

        me = this;
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);
        
        this.ptr = ICsManager_AI.C(inPtr);


    }
}