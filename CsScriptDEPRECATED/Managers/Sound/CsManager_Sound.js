/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsManager = require('CsScript/Managers/CsManager.js');
var JsCsSound = require('CsScript/Managers/Sound/CsSound.js')

var me;

module.exports = class JsCsManager_Sound extends JsCsManager
{
    constructor() {
        super();

        me = this;

        this.ActiveSounds = [];
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsManager_Sound.C(inPtr);

        // OnAllocate
        //this.ptr.OnAllocate_ScriptEvent.Add(this.OnAllocate);
        // OnDeAllocate
        //this.ptr.OnDeAllocate_ScriptEvent.Add(this.OnDeAllocate);

        const len = this.ptr.Pool.length;

        for (let i = 0; i < len; i++) {
            let sound = new JsCsSound();
            sound.Init(this.ptr.Pool[i], inRoot);

            this.Pool.push(sound);
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

    OnAllocate(poolIndex) { me.OnAllocate_Internal(poolIndex); }
    OnAllocate_Internal(poolIndex)
    {
        const len = this.Pool.length;

        for (let i = 0; i < len; i++)
        {
            if (poolIndex === this.Pool[i].ptr.poolIndex)
            {
                this.ActiveSounds.push(this.Pool[i]);
            }
        }
    }

    OnDeAllocate(poolIndex) { me.OnDeAllocate_Internal(poolIndex); }
    OnDeAllocate_Internal(poolIndex)
    {
        const len = this.ActiveSounds.length;

        for (let i = len - 1; i >= 0; i++)
        {
            if (poolIndex === this.ActiveSounds[i].ptr.poolIndex)
            {
                this.ActiveSounds.splice(i, 0);
                break;
            }
        }
    }
};