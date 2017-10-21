/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"


var JsCsRoutine;

const INDEX_NONE = -1;

const ROUTINE_POOL_SIZE = 256;
const ROUTINE_END = -1;
const ROUTINE_FREE = -2;

module.exports = class JsCsCoroutineScheduler
{
    constructor()
    {
        JsCsRoutine = require('CsScript/Coroutine/Routine.js');

        this.RoutinePool      = new Array(ROUTINE_POOL_SIZE);
        this.RoutinePoolIndex = 2;//INDEX_NONE;
        this.RoutinesToInit   = [];
        this.RoutinesToRun    = [];

        for (let i = 0; i < ROUTINE_POOL_SIZE; i++)
        {
            this.RoutinePool[i] = new JsCsRoutine();
            this.RoutinePool[i].Init(this.RoutinePool[i], this, i);
        }

        this.CalcCamera_RoutinePool = new Array(ROUTINE_POOL_SIZE);

        for (let i = 0; i < ROUTINE_POOL_SIZE; i++)
        {
            this.CalcCamera_RoutinePool[i] = new JsCsRoutine();
            this.CalcCamera_RoutinePool[i].Init(this.CalcCamera_RoutinePool[i], this, i);
        }
    };

    CleanUp()
    {
        EndAll();
    }

    Allocate(inCoroutine, inStopCondition, inActor, inObject, doInit, performFirstRun)
    {
        let lastIndex = Math.min(this.RoutinePoolIndex, ROUTINE_POOL_SIZE);

        if (this.RoutinePoolIndex >= ROUTINE_POOL_SIZE)
            this.RoutinePoolIndex = 0;

        // Last to End
        for (let i = lastIndex; i < ROUTINE_POOL_SIZE; i++)
        {
            this.RoutinePoolIndex = i + 1;

            let r = this.RoutinePool[i];

            if (r.index == ROUTINE_FREE)
            {
                r.Start(inCoroutine, inStopCondition, inActor, inObject, GWorld.TimeSeconds);

                if (doInit)
                {
                    r.index = this.RoutinesToRun.length;
                    this.RoutinesToRun.push(r);

                    if (performFirstRun)
                    {
                        r.Run(0.0);
                    }
                }
                else
                {
                    this.RoutinesToInit.push(r);
                }
                return r;
            }
        }
        // 0 to Last
        for (let i = 0; i < lastIndex; i++)
        {
            this.RoutinePoolIndex = i + 1;

            let r = this.RoutinePool[i];

            if (r.index == ROUTINE_FREE)
            {
                r.Start(inCoroutine, inStopCondition, inActor, inObject, GWorld.TimeSeconds);

                if (doInit)
                {
                    r.index = this.RoutinesToRun.length;
                    this.RoutinesToRun.push(r);

                    if (performFirstRun)
                    {
                        r.Run(0.0);
                    }
                }
                else
                {
                    this.RoutinesToInit.push(r);
                }
                return r;
            }
        }
        console.log("CoroutineScheduler::Allocate: No free Routines. Look for Runaway Coroutines or consider raising the pool size.");
        return null;
    };

    Start(inCoroutine, inStopCondition, inActor, inObject)
    {
        return this.Allocate(inCoroutine, inStopCondition, inActor, inObject, true, true);
    }

    StartChild(parent, inCoroutine, inStopCondition, inActor, inObject)
    {
        let lastIndex = Math.min(this.RoutinePoolIndex, ROUTINE_POOL_SIZE);

        if (this.RoutinePoolIndex >= ROUTINE_POOL_SIZE)
            this.RoutinePoolIndex = 0;

        // Last to End
        for (let i = lastIndex; i < ROUTINE_POOL_SIZE; i++)
        {
            this.RoutinePoolIndex = i + 1;

            let r = this.RoutinePool[i];

            if (r.index == ROUTINE_FREE)
            {
                parent.AddChild(r);
                r.Start(inCoroutine, inStopCondition, inActor, inObject, GWorld.TimeSeconds);

                let lastChild = null;
                let len       =  parent.children.length;

                if (len > 0)
                { 
                    lastChild = parent.children[len - 1] === "object" && paret.children[len - 1] != r ? parent.children[len - 1] : null;
                }

                let insertedAtLastChild = lastChild != null;
                let element		        = insertedAtLastChild ? lastChild : parent;
                r.index				    = this.RoutinesToRun.indexOf(element);
                this.RoutinesToRun.splice(r, 0, r.index);

                let parentIndex = parent.index;

                for (let j = r.index + 1; j <= parentIndex; j++)
                {
                    r.index++;
                }
                
                r.Run(0.0);
                return r;
            }
        }
        // 0 to Last
        for (let i = 0; i < lastIndex; i++)
        {
            this.RoutinePoolIndex = i + 1;

            let r = this.RoutinePool[i];

            if (r.index == ROUTINE_FREE)
            {
                parent.AddChild(r);
                r.Start(inCoroutine, inStopCondition, inActor, inObject, GWorld.TimeSeconds);

                let lastChild = null;
                let len       =  parent.children.length;

                if (len > 0)
                { 
                    lastChild = parent.children[len - 1] === "object" && paret.children[len - 1] != r ? parent.children[len - 1] : null;
                }

                let insertedAtLastChild = lastChild != null;
                let element		        = insertedAtLastChild ? lastChild : parent;
                r.index				    = this.RoutinesToRun.indexOf(element);
                this.RoutinesToRun.splice(r, 0, r.index);

                let parentIndex = parent.index;

                for (let j = r.index + 1; j <= parentIndex; j++)
                {
                    r.index++;
                }
                
                r.Run(0.0);
                return r;
            }
        }
        console.log("CoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size.");
        return null;
    }

    StartRoutine(r)
    {
        this.RoutinesToRun[r.index].Run(0.0);
        return r;
    }

    OnTick_Update(deltaSeconds)
    {
        // Init
        let count = this.RoutinesToInit.length;

        for (let i = 0; i < count; i++)
        {
            let r = this.RoutinesToInit[i];

            r.index = this.RoutinesToRun.length;
            this.RoutinesToRun.push(r);
        }

        this.RoutinesToInit = [];

        // Remove any Routines executed previous to tick
        count = this.RoutinesToRun.length;

        for (let i = count - 1; i >= 0; i--)
        {
            let r = this.RoutinesToRun[i];

            if (r.index == ROUTINE_END)
            {
                r.Reset();
                this.RoutinesToRun.splice(i, 1);
            }
        }
        // Execute
        count = this.RoutinesToRun.length;

        for (let i = 0; i < count; i++)
        {
            this.RoutinesToRun[i].Run(deltaSeconds);
        }
        // Remove any Routines executed end of tick
        for (let i = count - 1; i >= 0; i--)
        {
            let r = this.RoutinesToRun[i];

            if (r.index == ROUTINE_END)
            {
                r.Reset();
                this.RoutinesToRun.splice(i, 1);
            }
        }
    }

    EndAll()
    {
        let count = this.RoutinesToInit.length;

        for (let i = 0; i < count; i++)
        {
            let r = this.RoutinesToInit[i];

            r.End();
            r.Reset();
        }

        this.RoutinesToInit = [];

        count = this.RoutinesToRun.length;

        for (let i = 0; i < count; i++)
        {
            r = this.RoutinesToRun[i];

            r.End();
            r.Reset();
        }
        this.RoutinesToRun = [];
    }

    BroadcastMessage(messageType, message, inOwner)
    {
        let count = this.RoutinesToInit.length;

        for (let i = 0; i < count; i++)
        {
            if (inOwner != null && inOwner === "object" && inOwner != this.RoutinesToInit[i].GetOwner())
                continue;

            if (messageType == ECoroutineMessage.Stop)
                this.RoutinesToInit[i].ReceiveMessage(messageType, message);
        }

        count = this.RoutinesToRun.length;

        for (let i = 0; i < count; i++)
        {
            if (inOwner != null && inOwner === "object" && inOwner != this.RoutinesToInit[i].GetOwner())
                continue;

            if (messageType == ECoroutineMessage.Stop)
                this.RoutinesToRun[i].ReceiveMessage(messageType, message);
        }
    }
};
