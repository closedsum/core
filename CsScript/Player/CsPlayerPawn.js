/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me = [];

var INDEX_NONE = -1;

module.exports = class JsCsPlayerPawn
{
    constructor()
    {
        me.push(this);
        
        this.ptr = null;
        this.root = null;
        this.ps = null;
        this.pc = null;
    }

    Init(inPtr, inRoot)
    {
        this.ptr  = CsPlayerPawn.C(inPtr);
        this.root = inRoot;

        //this.ptr.OnTick_ScriptEvent.Add(this.OnTick);
    }

    CleanUp() {}
    /*
    static GetMeIndex(mappingId)
    {
        const len = me.length;

        for (let i = 0; i < len; i++)
        {
            if (me[i].ptr.mappingId == mappingId)
            {
                return i;
            }
        }
        return INDEX_NONE;
    }

    OnTick(mappingId, deltaSeconds) { me[JsCsPlayerState.GetMeIndex(mappingId)].OnTick_Internal(deltaSeconds); }
    OnTick_Internal(deltaSeconds){}
    */
};