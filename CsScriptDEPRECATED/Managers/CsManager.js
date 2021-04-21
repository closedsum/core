/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me;

module.exports = class JsCsManager
{
    constructor()
    {
        me = this;
        
        this.ptr = null;
        this.root = null;

        this.Pool = [];
        this.Pools = [];
    }

    Init(inPtr, inRoot)
    {
        this.ptr = CsManager.C(inPtr);
        this.root = inRoot;

        // OnAllocate
        //this.ptr.OnAllocate_ScriptEvent.Add(this.OnAllocate);
        // OnDeAllocate
        //this.ptr.OnDeAllocate_ScriptEvent.Add(this.OnDeAllocate);
        // OnDeAllocateEX
        //this.ptr.OnDeAllocateEX_ScriptEvent.Add(this.OnDeAllocateEX);
    }

    CleanUp()
    {
        // OnAllocate
        this.ptr.OnAllocate_ScriptEvent.Remove(this.OnAllocate);
        // OnDeAllocate
        this.ptr.OnDeAllocate_ScriptEvent.Remove(this.OnDeAllocate);
        // OnDeAllocateEX
        this.ptr.OnDeAllocateEX_ScriptEvent.Remove(this.OnDeAllocateEX);
    }

    OnAllocate(poolIndex) { me.OnAllocate_Internal(poolIndex); }
    OnAllocate_Internal(poolIndex) { }

    OnDeAllocate(poolIndex) { me.OnDeAllocate_Internal(poolIndex); }
    OnDeAllocate_Internal(poolIndex) { }

    OnDeAllocateEX(poolIndex, activeIndex, type) { me.OnDeAllocateEX_Internal(poolIndex, activeIndex, type); }
    OnDeAllocateEX_Internal(poolIndex, activeIndex, type) { }
};