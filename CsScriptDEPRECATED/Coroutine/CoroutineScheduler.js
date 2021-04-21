/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"


var JsCsRoutine = require('CsScript/Coroutine/Routine.js');
var JsCsCoroutinePayload = require('CsScript/Coroutine/CoroutinePayload.js');

var me;

const INDEX_NONE = -1;

const ROUTINE_POOL_SIZE = 256;
const ROUTINE_END = -1;
const ROUTINE_FREE = -2;

module.exports = class JsCsCoroutineScheduler
{
    constructor()
    {
        me = this;

        this.RoutinePools = [];
        this.RoutinePoolIndices = [];
        this.RoutinesToInit   = [];
        this.RoutinesToRun    = [];

        const count = CsJavascriptLibrary.GetCoroutineScheduleMax();

        for (let i = 0; i < count; ++i)
        {
            this.RoutinePoolIndices.push(0);
            this.RoutinesToInit[i] = [];
            this.RoutinesToRun[i] = [];
            this.RoutinePools[i] = new Array(ROUTINE_POOL_SIZE);

            for (let j = 0; j < ROUTINE_POOL_SIZE; ++j)
            {
                this.RoutinePools[i][j] = new JsCsRoutine();
                this.RoutinePools[i][j].Init(this.RoutinePools[i][j], this, j);
            }
        }

        this.Payloads = [];

        for (let i = 0; i < ROUTINE_POOL_SIZE; ++i)
        {
            this.Payloads.push(new JsCsCoroutinePayload());
        }
        this.PayloadIndex = 0;
    };

    CleanUp()
    {
        EndAll();
    }

    Allocate(payload /*JsCsCoroutinePayload*/)
    {
        const schedule = CsJavascriptLibrary.CoroutineScheduleToUint8(payload.Schedule);

        for (let i = 0; i < ROUTINE_POOL_SIZE; ++i)
        {
            this.RoutinePoolIndices[schedule] = (this.RoutinePoolIndices[schedule] + 1) % ROUTINE_POOL_SIZE;

            let r = this.RoutinePools[schedule][this.RoutinePoolIndices[schedule]];

            if (r.index == ROUTINE_FREE)
            {
                r.name = payload.Name;

                let currentTime = 0;
                
                if (inActor != null && typeof inActor === "object")
                    currentTime = CsJavascriptLibrary.GetTimeSeconds(inActor.root.MyWorld);
                if (inObject != null && typeof inObject === "object")
                    currentTime = CsJavascriptLibrary.GetTimeSeconds(inObject.root.MyWorld);

                r.Start(payload.Function, payload.Stop, payload.Actor, payload.Object, currentTime, payload.Add, payload.Remove, payload.Type);

                if (payload.DoInit)
                {
                    r.index = this.RoutinesToRun[schedule].length;
                    this.RoutinesToRun[schedule].push(r);

                    if (payload.PerformFirstRun)
                    {
                        r.Run(0.0);
                    }
                }
                else
                {
                    this.RoutinesToInit[schedule].push(r);
                }
                // LogTransaction
                payload.Reset();
                return r;
            }
        }
        payload.Reset();
        console.log("CoroutineScheduler::Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size.");
        return null;
    };

    Start(payload /*JsCsCoroutinePayload*/)
    {
        return this.Allocate(payload);
    }

    StartChild(payload /*JsCsCoroutinePayload*/)
    {
        const schedule = CsJavascriptLibrary.CoroutineScheduleToUint8(payload.Schedule);

        for (let i = 0; i < ROUTINE_POOL_SIZE; ++i)
        {
            this.RoutinePoolIndices[schedule] = (this.RoutinePoolIndices[schedule] + 1) % ROUTINE_POOL_SIZE;

            let r = this.RoutinePools[schedule][this.RoutinePoolIndices[schedule]];

            if (r.index == ROUTINE_FREE)
            {
                r.name = payload.Name;

                let currentTime = 0;

                if (inActor != null && typeof inActor === "object")
                    currentTime = CsJavascriptLibrary.GetTimeSeconds(inActor.root.MyWorld);
                if (inObject != null && typeof inObject === "object")
                    currentTime = CsJavascriptLibrary.GetTimeSeconds(inObject.root.MyWorld);

                let parent = Payload.Parent;

                parent.AddChild(r);

                r.Start(payload.Function, payload.Stop, payload.Actor, payload.Object, currentTime, payload.Add, payload.Remove, payload.Type);

                let lastChild = null;
                let len       =  parent.children.length;

                if (len > 0)
                { 
                    lastChild = parent.children[len - 1] === "object" && paret.children[len - 1] != r ? parent.children[len - 1] : null;
                }

                let insertedAtLastChild = lastChild != null;
                let element		        = insertedAtLastChild ? lastChild : parent;
                r.index				    = this.RoutinesToRun[schedule].indexOf(element);
                this.RoutinesToRun[schedule].splice(r, 0, r.index);

                let parentIndex = parent.index;

                for (let j = r.index + 1; j <= parentIndex; ++j)
                {
                    r.index++;
                }
                
                r.Run(0.0);
                payload.Reset();
                return r;
            }
        }
        payload.Reset();
        console.log("CoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size.");
        return null;
    }

    StartRoutine(scheduleType, r)
    {
        const schedule = CsJavascriptLibrary.CoroutineScheduleToUint8(scheduleType);

        this.RoutinesToRun[schedule][r.index].Run(0.0);
        return r;
    }

    Update(scheduleType, deltaSeconds)
    {
        const schedule = CsJavascriptLibrary.CoroutineScheduleToUint8(scheduleType);

        // Init
        let count = this.RoutinesToInit[schedule].length;

        for (let i = 0; i < count; i++)
        {
            let r = this.RoutinesToInit[schedule][i];

            r.index = this.RoutinesToRun[schedule].length;
            this.RoutinesToRun[schedule].push(r);
        }

        this.RoutinesToInit[schedule] = [];

        // Remove any Routines executed previous to tick
        count = this.RoutinesToRun[schedule].length;

        for (let i = count - 1; i >= 0; --i)
        {
            let r = this.RoutinesToRun[schedule][i];

            if (r.index === ROUTINE_END)
            {
                r.Reset();
                this.RoutinesToRun[schedule].splice(i, 1);
            }
        }
        // Execute

        // LogRunning(scheduleType)

        count = this.RoutinesToRun[schedule].length;

        for (let i = 0; i < count; i++)
        {
            this.RoutinesToRun[schedule][i].Run(deltaSeconds);
        }
        // Remove any Routines executed end of tick
        for (let i = count - 1; i >= 0; --i)
        {
            let r = this.RoutinesToRun[schedule][i];

            if (r.index === ROUTINE_END)
            {
                r.Reset();
                this.RoutinesToRun[schedule].splice(i, 1);
            }
        }
    }

    OnTick_Update(deltaSeconds) { me.OnTick_Update_Internal(deltaSeconds); }
    OnTick_Update_Internal(deltaSeconds)
    {
        this.Update(ECsCoroutineSchedule.Tick, deltaSeconds);
    }

    EndAll(schedule)
    {
        const max = CsJavascriptLibrary.GetCoroutineScheduleMax();
        const start = schedule === max ? 0 : schedule;
        const end = schedule === max ? max : start + 1;

        for (let i = 0; i < end; ++i)
        {
            let count = this.RoutinesToInit[i].length;

            for (let j = 0; j < count; j++)
            {
                let r = this.RoutinesToInit[i][j];

                r.End();
                r.Reset();
            }

            this.RoutinesToInit[i] = [];

            count = this.RoutinesToRun[i].length;

            for (let j = 0; j < count; ++j)
            {
                let r = this.RoutinesToRun[i][j];

                r.End();
                r.Reset();
            }
            this.RoutinesToRun[i] = [];
        }
    }

    BroadcastMessage(scheduleType, messageType, message, inOwner)
    {
        const schedule = CsJavascriptLibrary.CoroutineScheduleToUint8(scheduleType);

        let count = this.RoutinesToInit[schedule].length;

        for (let i = 0; i < count; ++i)
        {
            if (inOwner != null && inOwner === "object" && inOwner != this.RoutinesToInit[schedule][i].GetOwner())
                continue;

            if (messageType == ECoroutineMessage.Stop)
                this.RoutinesToInit[schedule][i].ReceiveMessage(messageType, message);
        }

        count = this.RoutinesToRun[schedule].length;

        for (let i = 0; i < count; ++i)
        {
            if (inOwner != null && inOwner === "object" && inOwner != this.RoutinesToInit[schedule][i].GetOwner())
                continue;

            if (messageType == ECoroutineMessage.Stop)
                this.RoutinesToRun[schedule][i].ReceiveMessage(messageType, message);
        }
    }

    // TODO

    // LogTransaction(functionName, transaction, r){}

    // LogRunning(scheduleType)

    // Payload
    // #region

    AllocatePayload()
    {
        for (let i = 0; i < ROUTINE_POOL_SIZE; ++I)
        {
            this.PayloadIndex = (this.PayloadIndex + 1) % ROUTINE_POOL_SIZE;

            if (!Payloads[PayloadIndex].IsAllocated)
            {
                return Payloads[PayloadIndex];
            }
        }
        console.log("JsCsCoroutineScheduler.AllocatePayload: No free Payloads. Look for Runaway Coroutines or consider raising the pool size.");
        return null;
    }

    // #endregion
};

// Example
/*

let func = RotateMesh();
MyScheduler.Start(func, null, null, null);

var RotateMesh = function*()
{
    class _Local
    {
        constructor()
        {
            this.a        = null;
            this.deltaSeconds = 0;
            this.rotation = new Rotator();
        }

        Set(r)
        {
            this.a        = r.GetActor();
            this.deltaSeconds = r.deltaSeconds;
            this.rotation = this.a.GetActorRotation();
        }
    }

    let local = new _Local();
    let r;

    // COROUTINE_BEGIN
    r = yield; local.Set(r);

    do
    {
        local.rotation = local.a.GetActorRotation();
        local.rotation.Yaw += local.deltaSeconds * 10;
        local.a.SetActorRotation(local.rotation);

        r = yield; local.Set(r);
    }
    while(1);

    r.End();
    // COROUTINE_END
}
*/