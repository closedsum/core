/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsPooledActor = require('CsScript/Managers/CsPooledActor.js');

var me = [];

module.exports = class JsCsInteractiveActor extends JsCsPooledActor
{
    constructor()
    {
        super();

        me.push(this);

        //this.ptr.Override_OnInteraction_ScriptEvent.Add(this.OnInteraction);
        //this.ptr.Override_OnFirstFreeze_ScriptEvent.Add(this.OnFirstFreeze);
        //this.ptr.Override_OnFreeze_ScriptEvent.Add(this.OnFreeze);
        //this.ptr.Override_OnFirstUnFreeze_ScriptEvent.Add(this.OnFirstUnFreeze);
        //this.ptr.Override_OnFirstHold_ScriptEvent.Add(this.OnFirstHold);
        //this.ptr.Override_OnHold_ScriptEvent.Add(this.OnHold);
        //this.ptr.Override_OnRelease_ScriptEvent.Add(this.OnRelease);
        //this.ptr.Override_OnFirstTouch_ScriptEvent.Add(this.OnFirstTouch);
        //this.ptr.Override_OnTouch_ScriptEvent.Add(this.OnTouch);
        //this.ptr.Override_OnFirstHover_ScriptEvent.Add(this.OnFirstHover);
        //this.ptr.Override_OnHover_ScriptEvent.Add(this.OnHover);
        //this.ptr.Override_OnFirstUnHover_ScriptEvent.Add(this.OnFirstUnHover);
        //this.ptr.Override_OnFirstCollide_ScriptEvent.Add(this.OnFirstCollide);
        //this.ptr.Override_OnCollide_ScriptEvent.Add(this.OnCollide);
        //this.ptr.Override_OnFirstUnCollide_ScriptEvent.Add(this.OnFirstUnCollide);
        //this.ptr.Override_OnRemove_ScriptEvent.Add(this.OnRemove);

        //this.ptr.Override_OnTickOverlap_ScriptEvent.Add(this.OnTickOverlap);
        //this.ptr.Override_OnBeginOverlap_ScriptEvent.Add(this.OnBeginOverlap);
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsInteractiveActor.C(inPtr);
    }

    CleanUp()
    {
        this.ptr.Override_OnInteraction_ScriptEvent.Remove(this.OnInteraction);
        this.ptr.Override_OnFirstFreeze_ScriptEvent.Remove(this.OnFirstFreeze);
        this.ptr.Override_OnFreeze_ScriptEvent.Remove(this.OnFreeze);
        this.ptr.Override_OnFirstUnFreeze_ScriptEvent.Remove(this.OnFirstUnFreeze);
        this.ptr.Override_OnFirstHold_ScriptEvent.Remove(this.OnFirstHold);
        this.ptr.Override_OnHold_ScriptEvent.Remove(this.OnHold);
        this.ptr.Override_OnRelease_ScriptEvent.Remove(this.OnRelease);
        this.ptr.Override_OnFirstTouch_ScriptEvent.Remove(this.OnFirstTouch);
        this.ptr.Override_OnTouch_ScriptEvent.Remove(this.OnTouch);
        this.ptr.Override_OnFirstHover_ScriptEvent.Remove(this.OnFirstHover);
        this.ptr.Override_OnHover_ScriptEvent.Remove(this.OnHover);
        this.ptr.Override_OnFirstUnHover_ScriptEvent.Remove(this.OnFirstUnHover);
        this.ptr.Override_OnFirstCollide_ScriptEvent.Remove(this.OnFirstCollide);
        this.ptr.Override_OnCollide_ScriptEvent.Remove(this.OnCollide);
        this.ptr.Override_OnFirstUnCollide_ScriptEvent.Remove(this.OnFirstUnCollide);
        this.ptr.Override_OnRemove_ScriptEvent.Remove(this.OnRemove);

        //this.ptr.Override_OnTickOverlap_ScriptEvent.Remove(this.OnTickOverlap);
        this.ptr.Override_OnBeginOverlap_ScriptEvent.Remove(this.OnBeginOverlap);
    }

    static GetMeIndex(index)
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

    OnInteraction(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnInteraction_Internal(instigator); }
    OnInteraction_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstFreeze; }

    OnFirstFreeze(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstFreeze_Internal(instigator); }
    OnFirstFreeze_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstFreeze; }

    OnFreeze(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFreeze_Internal(instigator); }
    OnFreeze_Internal(instigator){ this.ptr.State = ECsInteractiveState.Freeze; }

    OnFirstUnFreeze(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstUnFreeze_Internal(instigator); }
    OnFirstUnFreeze_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstUnFreeze; }

    OnFirstHold(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstHold_Internal(instigator); }
    OnFirstHold_Internal(instigator)
    {
        if (this.ptr.State !== ECsInteractiveState.FirstCollide && this.ptr.state !== ECsInteractiveState.Collide) 
            this.ptr.State = ECsInteractiveState.FirstHold; 
    }

    OnHold(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnHold_Internal(instigator); }
    OnHold_Internal(instigator)
    {
        if (this.ptr.State !== ECsInteractiveState.FirstCollide && this.ptr.state !== ECsInteractiveState.Collide) 
            this.ptr.State = ECsInteractiveState.Hold; 
    }

    OnRelease(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnRelease_Internal(instigator); }
    OnRelease_Internal(instigator){ this.ptr.State = ECsInteractiveState.Release; }

    OnFirstTouch(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstTouch_Internal(instigator); }
    OnFirstTouch_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstTouch; }

    OnTouch(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnTouch_Internal(instigator); }
    OnTouch_Internal(instigator){ this.ptr.State = ECsInteractiveState.Touch; }

    OnFirstHover(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstHover_Internal(instigator); }
    OnFirstHover_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstHover; }

    OnHover(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnHover_Internal(instigator); }
    OnHover_Internal(instigator){ this.ptr.State = ECsInteractiveState.Hover; }

    OnFirstUnHover(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstUnHover_Internal(instigator); }
    OnFirstUnHover_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstUnHover; }

    OnFirstCollide(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstCollide_Internal(instigator); }
    OnFirstCollide_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstCollide; }

    OnCollide(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnCollide_Internal(instigator); }
    OnCollide_Internal(instigator){ this.ptr.State = ECsInteractiveState.Collide; }

    OnFirstUnCollide(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnFirstUnCollide_Internal(instigator); }
    OnFirstUnCollide_Internal(instigator){ this.ptr.State = ECsInteractiveState.FirstUnCollide; }

    OnRemove(index, instigator){ me[JsCsInteractiveActor.GetMeIndex(index)].OnRemove_Internal(instigator); }
    OnRemove_Internal(instigator){ this.ptr.State = ECsInteractiveState.Remove; }

    OnBeginOverlap(index, overlappedComponent, otherActor, otherComp, otherBodyIndex, bFromSweep, sweepResult)
    {
        me[JsCsInteractiveActor.GetMeIndex(index)].OnBeginOverlap_Internal(overlappedComponent, otherActor, otherComp, otherBodyIndex, bFromSweep, sweepResult);
    }

    OnBeginOverlap_Internal(overlappedComponent, otherActor, otherComp, otherBodyIndex, bFromSweep, sweepResult){}
}