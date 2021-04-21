/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me = [];

var INDEX_NONE = -1;

module.exports = class JsCsPlayerController
{
    constructor()
    {
        me.push(this);
        
        this.ptr = null;
        this.root = null;
        this.ps = null;
        this.pawn = null;
    }

    Init(inPtr, inRoot)
    {
        this.ptr = CsPlayerController.C(inPtr);
        this.root = inRoot;

        //this.ptr.OnTickAcor_ScriptEvent.Add(this.OnTickActor);
        //this.ptr.OnCalcCamera_ScriptEvent.Add(this.OnCalcCamera);
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

    OnTickActor(mappingId, deltaSeconds) { me[JsCsPlayerController.GetMeIndex(mappingId)].OnTickActor_Internal(deltaSeconds); }
    OnTickActor_Internal(deltaSeconds){}

    OnCalcCamera(mappingId, deltaTime, viewInfo) { me[JsCsPlayerController.GetMeIndex(mappingId)].OnCalcCamera_Internal(deltaTime, viewInfo); }
    OnCalcCamera_Internal(deltaTime, viewInfo){}
    */
};