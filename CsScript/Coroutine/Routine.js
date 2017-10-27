/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

const INDEX_NONE = -1;

const ROUTINE_INDEXER_SIZE = 4;
const ROUTINE_COUNTER_SIZE = 4;
const ROUTINE_FLAG_SIZE = 16;
const ROUTINE_TIMER_SIZE = 4;
const ROUTINE_INT_SIZE = 4;
const ROUTINE_FLOAT_SIZE = 4;
const ROUTINE_VECTOR_SIZE = 4;
const ROUTINE_ROTATOR_SIZE = 4;
const ROUTINE_COLOR_SIZE = 4;
const ROUTINE_STRING_SIZE = 4;
const ROUTINE_OBJECT_SIZE = 4;
const ROUTINE_VOID_POINTER_SIZE = 4;
const ROUTINE_MAX_TYPE = 255;
const ROUTINE_END = -1;
const ROUTINE_FREE = -2;

module.exports = class JsCsRoutine
{
    constructor()
    {
        this.self = this;
        this.parent = null;
        this.children = [];
        this.scheduler = null;
        this.coroutine = null;
        this.stopCondition = null;
        this.poolIndex = -1;
        this.index = ROUTINE_FREE;
        this.name = "";
        this.type = ROUTINE_MAX_TYPE;
        this.a = null;
        this.o = null;
        this.owner = null;
        this.addRoutine = null;
        this.removeRoutine = null;
        this.startTime = 0.0;
        this.deltaSeconds = 0.0;
        this.tickCount = 0;
        this.delay = 0;

        this.stopMessages = [];
        this.stopMessages_recieved = [];

        this.indexers = new Array(ROUTINE_INDEXER_SIZE);
        this.counters = new Array(ROUTINE_COUNTER_SIZE);
        this.flags = new Array(ROUTINE_FLAG_SIZE);
        this.timers = new Array(ROUTINE_TIMER_SIZE);
        this.ints = new Array(ROUTINE_INT_SIZE);
        this.floats = new Array(ROUTINE_FLOAT_SIZE);
        this.vectors = new Array(ROUTINE_VECTOR_SIZE);

        for (let i = 0; i < ROUTINE_VECTOR_SIZE; i++)
		{
            this.vectors[i] = new Vector();
		}

        this.colors = new Array(ROUTINE_COLOR_SIZE);
        this.strings = new Array(ROUTINE_STRING_SIZE);
        this.objects = new Array(ROUTINE_OBJECT_SIZE);
        this.voidPointers = new Array(ROUTINE_VOID_POINTER_SIZE);
    }

    Init(inSelf, inScheduler, inPoolIndex)
    {
        this.self      = inSelf;
        this.scheduler = inScheduler;
        this.poolIndex = inPoolIndex;
    }

    IsValid()
    {
        if (this.self == null)
            return false;
        if (this != this.self)
            return false;
        return true;
    }

    IsFunction(func)
    {
        let getType = {};
        return func && getType.toString.call(func) === '[object Function]';
    }

    Start(inCoroutine, inStopCondition, inActor, inObject, inStartTime, inAddRoutine, inRemoveRoutine)
    {
        this.coroutine = inCoroutine;
        this.stopCondition = inStopCondition;
        this.a = inActor;
        this.o = inObject;
        this.startTime = inStartTime;
        this.addRoutine = inAddRoutine;
        this.removeRoutine = inRemoveRoutine;

        if (this.GetActor() != null && this.GetActor() === "object")
        {
            this.owner = this.a;
        }
        else
        if (this.GetRObject() != null && typeof this.GetRObject() === "object")
        {
            this.owner = this.o;
        }

        if (this.GetOwner() != null && typeof this.GetOwner() === "object" && IsFunction(this.addRoutine))
            this.addRoutine(GetOwner(), this.self, this.type)

        this.coroutine.next(this.self);
    }

    End()
    {
        if (this.GetOwner() != null && typeof this.GetOwner() === "object" && IsFunction(this.removeRoutine))
            this.removeRoutine(GetOwner(), this.self, this.type);
        this.index = ROUTINE_END;
    }

    HasEnded()
    {
        return this.index == ROUTINE_END || this.index == ROUTINE_FREE;
    }

    Reset()
	{
		if (this.parent != null && typeof this.parent === "object")
		{
		    let i = this.parent.children.indexOf(this.self);

            if (i > INDEX_NONE)
                this.parent.children.splice(i, 1);
		}

		this.parent = null;
		
		this.EndChildren();

		this.coroutine	  = null;
		this.stopCondition = null;
		this.index		  = ROUTINE_FREE;
	    this.name		  = "";
		this.type		  = ROUTINE_MAX_TYPE;
		this.a		      = null;
        this.o            = null;
        this.owner        = null;
        this.addRoutine   = null;
        this.removeRoutine = null;
		this.startTime    = 0.0;
		this.tickCount    = 0;
		this.delay	      = 0.0;

		for (let i = 0; i < ROUTINE_INDEXER_SIZE; i++)
		{
			this.indexers[i] = 0;
		}

		for (let i = 0; i < ROUTINE_COUNTER_SIZE; i++)
		{
			this.counters[i] = 0;
		}

		for (let i = 0; i < ROUTINE_FLAG_SIZE; i++)
		{
			this.flags[i] = false;
		}

		for (let i = 0; i < ROUTINE_TIMER_SIZE; i++)
		{
			this.timers[i] = 0.0;
		}

		for (let i = 0; i < ROUTINE_INT_SIZE; i++)
		{
			this.ints[i] = 0;
		}

		for (let i = 0; i < ROUTINE_FLOAT_SIZE; i++)
		{
			this.floats[i] = 0.0;
		}

		for (let i = 0; i < ROUTINE_VECTOR_SIZE; i++)
		{
			this.vectors[i].x = 0.0;
            this.vectors[i].y = 0.0;
            this.vectors[i].z = 0.0;
		}

		for (let i = 0; i < ROUTINE_COLOR_SIZE; i++)
        {
            this.colors[i] = CsJavascriptLibrary.GetLinearColor(ECsLinearColor.White);
		}

        for (let i = 0; i < ROUTINE_STRING_SIZE; i++)
        {
            this.strings[i] = "";
        }

		for (let i = 0; i < ROUTINE_OBJECT_SIZE; i++)
		{
			this.objects[i] = null;
		}

        this.stopMessages = [];
        this.stopMessages_recieved = [];
	}

    Run(inDeltaSeconds)
	{
		let iMax = this.stopMessages_recieved.length;

		for (let i = 0; i < iMax; i++)
		{
            let idx = this.stopMessages.indexOf(this.stopMessages_recieved[i]);

			if (idx != INDEX_NONE)
			{
                this.stopMessages = [];
				this.End();
				break;
			}
		}
        this.stopMessages_recieved = [];

        if (this.IsFunction(this.stopCondition))
			this.stopCondition(this.self);

		if (this.index == ROUTINE_END)
		{
            if (this.GetOwner() != null && typeof this.GetOwner() === "object" && IsFunction(this.removeRoutine))
                this.removeRoutine(GetOwner(), this.self, this.type);
			return;
		}
		this.deltaSeconds = inDeltaSeconds;
		this.tickCount++;
		this.coroutine.next(this.self);
	}

    GetActor()
	{
		return this.a;
	}

	GetRObject()
	{
		return this.o;
	}

	GetOwner()
	{
		return this.owner;
	}

    AddChild(child)
	{
		child.parent = this.self;
		this.children.push(child);
	}

	EndChildren()
	{
		let count = this.children.length;

		for (let i = 0; i < count; i++)
		{
			this.children[i].End();
		}
        this.children = [];
	}

	EndChild(child)
	{
		let count = this.children.length;

		for (let i = count - 1; i >= 0; i--)
		{
			if (child == this.children[i])
			{
				child.End();
				this.children.splice(i,1);
				break;
			}
		}
	}

	AddMessage(messageType, message)
	{
		if (messageType == ECoroutineMessage.Stop)
		{
            let idx = this.stopMessages.indexOf(message);

			if (idx == INDEX_NONE)
				this.stopMessages.push(message);
		}
	}

	ReceiveMessage(messageType, message)
	{
		if (messageType == ECoroutineMessage.Stop)
		{
            let idx = this.stopMessages_recieved.indexOf(message);

			if (idx == INDEX_NONE)
				this.stopMessages_recieved.push(message);
		}
	}
};