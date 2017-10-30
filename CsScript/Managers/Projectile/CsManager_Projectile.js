/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsManager = require('CsScript/Managers/CsManager.js');

var me;

module.exports = class JsCsManager_Projectile extends JsCsManager
{
    constructor()
    {
        super();

        me = this;
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsManager_Projectile.C(inPtr);
    }

    CleanUp(){}
};