/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

const ROUTINE_MAX_TYPE = 255;

module.exports = class JsCsCoroutinePayload
{
    constructor()
    {
        this.Reset();
    }

    Reset()
    {
        this.IsAllocated = false;
        this.Schedule = ECsCoroutineSchedule.ECsCoroutineSchedule_MAX;

        this.Parent = null;
        this.Function = null;
        this.Actor = null;
        this.Object = null;
        this.Stop = null;
        this.Add = null;
        this.Remove = null;
        this.Type = ROUTINE_MAX_TYPE;
        this.DoInit = false;
        this.PerformFirstRun = false;
        this.Name = "";
    }
};