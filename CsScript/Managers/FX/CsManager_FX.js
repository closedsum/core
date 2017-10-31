/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsManager = require('CsScript/Managers/CsManager.js');
var JsCsEmitter = require('CsScript/Managers/FX/CsEmitter.js')

var me;

module.exports = class JsCsManager_FX extends JsCsManager
{
    constructor()
    {
        super();

        me = this;
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsManager_FX.C(inPtr);

        const len = this.ptr.Pool.length;

        for (let i = 0; i < len; i++)
        {
            let emitter = new JsCsEmitter();
            emitter.Init(this.ptr.Pool[i], inRoot);

            this.Pool.push(emitter);
        }
    }

    CleanUp()
    {
        super.CleanUp();

        const len = this.Pool.length;

        for (let i = 0; i < len; i++)
        {
            this.Pool[i].CleanUp();
        }
    }

};