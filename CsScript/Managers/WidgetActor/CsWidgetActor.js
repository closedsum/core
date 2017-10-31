/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsPooledActor = require('CsScript/Managers/CsPooledActor.js');

var me = [];

const INDEX_NONE = -1;

module.exports = class JsCsWidgetActor extends JsCsPooledActor
{
    constructor()
    {
        super();

        me.push(this);
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsWidgetActor.C(inPtr);

        //this.ptr.Override_OnCalcCamera_ScriptEvent.Add(this.OnCalcCamera);
    }

    CleanUp()
    {
        this.ptr.Override_OnCalcCamera_ScriptEvent.Remove(this.OnCalcCamera);
    }

    GetMeIndex(index)
    {
        const len = me.length;

        for (let i = 0; i < len; i++)
        {
            if (me[i].ptr.PoolIndex == index)
            {
                return i;
            }
        }
        return INDEX_NONE;
    }

    OnCalcCamera(index, mappingId, deltaTime, viewInfo)
    {
        me[this.GetMeIndex(index)].OnCalcCamera_Internal(mappingId, deltaTime, viewInfo);
    }

    OnCalcCamera_Internal(mappingId, deltaTime, viewInfo)
    {
    }
}