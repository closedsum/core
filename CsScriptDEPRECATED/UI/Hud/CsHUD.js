/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsUI = require('CsScript/UI/CsUI.js');

var me;

module.exports = class JsCsHUD extends JsCsUI
{
    constructor()
    {
        super();
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsHUD.C(inPtr);
    }
};