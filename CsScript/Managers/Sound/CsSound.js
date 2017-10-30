/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsPooledActor = require('CsScript/Managers/CsPooledActor.js');

var me;

module.exports = class JsCsSound extends JsCsPooledActor
{
    constructor()
    {
        super();

        me = this;
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsSound.C(inPtr);
    }

    CleanUp(){}
};