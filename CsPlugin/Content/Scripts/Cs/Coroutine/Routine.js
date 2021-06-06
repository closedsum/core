/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var NJsCoroutine = require('Cs/Coroutine/Types_Coroutine.js');
var FJsProperty = require('Cs/Types/Property/Property.js');
var NJsYield1 = require('Cs/Types/Yield/Yield_Enum.js');
var NJsYield2 = require('Cs/Types/Yield/Yield_RoutineHandle.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

const INDEX_NONE = -1;

const EMPTY = 0;

const INVALID_LISTEN_MESSAGE = "";

const ROUTINE_END = -1;
const ROUTINE_FREE = -2;

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var EnumYieldType = NJsYield1.FEnum;
var RoutineHandleYieldType = NJsYield2.FRoutineHandle;

// "typedefs" - function
var checkf = CommonLibrary.checkf;
var IsValidObject = CommonLibrary.IsValidObject;
var IsClassOf = CommonLibrary.IsClassOf;

// "typedefs" - enums
var StateType = NJsCoroutine.EState;
var EndReasonType = NJsCoroutine.EEndReason;
var MessageType = NJsCoroutine.EMessage;

var Core;

module.exports = class JsRoutine
{
    constructor()
    {
		this.self = this;

		let UpdateGroupLibrary	= CsScriptLibrary_UpdateGroup;
		this.Group				= UpdateGroupLibrary.GetMax();

		// Time
		this.StartTime = new CsTime();
		this.ElapsedTime = new CsDeltaTime();
		this.DeltaTime = new CsDeltaTime();
		this.TickCount = 0;
		this.Delay = 0;

		this.Handle = new CsRoutineHandle();

		this.AbortImpls = [];
		this.OnAborts = [];

		this.State = StateType.Free;

		this.Index = INDEX_NONE;

		this.Name = "";

		// End
		this.EndReason = EndReasonType.EEndReason_MAX;

		this.OnEnds = [];

		// Owner
		let OwnerType = NJsCoroutine.FOwner;
		this.Owner    = new OwnerType();

		// Children

        this.Parent = null;
		this.Children = [];

		let RegisterMapType = NJsCoroutine.NRegister.FMap;
		this.RegisterMap	= new RegisterMapType();

		this.Messages = [[], []];
		this.Messages_Recieved = [[], []];
		{
			let count = MessageType.EMessage_MAX.Value;

			for (let i = 0; i < count; ++i)
			{
				this.Messages.push([]);
				this.Messages_Recieved.push([]);
			}
        }

		this.bWaitForFrame = false; /*bool*/
		this.WaitForFrameCounter = 0; /*int*/
		this.WaitForFrame = 0; /*int*/
		this.WaitForFrameType = null; /*FJsProperty*/
		this.bWaitForTime = false; /*bool*/
		this.WaitForTime = 0.0; /*float*/
		this.WaitForTimeTimer = 0.0; /*float*/
		this.WaitForTimeType = null; /*FJsProperty*/
		this.bWaitForFlag = false; /*bool*/
		this.WaitForFlagType = null; /*FJsProperty*/
		this.bWaitForListenMessage = false; /*bool*/
		this.WaitForListenMessage = null; /*string*/
		this.WaitForListenMessageType = null; /*FJsProperty*/
		this.bWaitForEnum = false; /*bool*/
		this.WaitForEnum = new EnumYieldType(); /*EnumYieldType (NJsYield.FEnum)*/
		this.bWaitForRoutineHandle = false; /*bool*/
		this.WaitForRoutineHandle = new RoutineHandleYieldType(); /*RoutineHandleYieldType (NJsYield.FRoutineHandle)*/
    }

	SetCore(core)
	{
		Core = core;
		this.WaitForRoutineHandle.SetCore(core);
	}

	IsValid()
	{
		if (this.self == null)
			return false;
		if (this != this.self)
			return false;
		return true;
	}

	SetGroup(group) { this.Group = group; }
	GetGroup() { return this.Group; }

	GetHandle() { return this.Handle; }

	SetIndex(index) 
	{ 
		this.Index = index;
		this.Handle.Index = index; 
	}
	GetIndex() { return this.Index; }

    Init(payload)
	{
		this.State = StateType.Init;

		this.CoroutineImpl = payload.CoroutineImpl;

		let TimeLibrary = CsScriptLibrary_Time;
		this.StartTime = TimeLibrary.FCsTime_Copy(payload.StartTime);

		this.Owner.Copy(payload.Owner);
		
		this.Messages[MessageType.Abort.Value] = Array.from(payload.AbortMessages);

		this.AbortImpls = Array.from(payload.AbortImpls);

		this.OnEnds = Array.from(payload.OnEnds);

		this.Name = payload.Name;

		for (const info of payload.RegisterMap.Infos)
		{
			let idx = info.Index;

			this.RegisterMap.Values[idx] = payload.RegisterMap.Values[idx];
			this.RegisterMap.SetUsedValue(idx);
		}

		let RoutineLibrary = CsScriptLibrary_Routine;
		this.Handle		   = RoutineLibrary.New(this.Handle);
    }

	StartUpdate() { this.State = NJsCoroutine.EState.Update; }

	Update(deltaTime)
	{
		// Check for Abort Messages
		let MessageType = NJsCoroutine.EMessage;

		let msgs		  = this.Messages[MessageType.Abort.Value];
		let msgs_recieved = this.Messages_Recieved[MessageType.Abort.Value];

		if (msgs.length > EMPTY)
		{
			let found = false;

			for (const recieved of msgs_recieved)
			{
				if (msgs.find(recieved) != null)
				{
					this.Messages[MessageType.Abort.Value] = [];

					this.End(EndReasonType.AbortMessage);

					found = true;
				}

				if (found)
					break;
            }
		}
		this.Messages_Recieved[MessageType.Abort.Value] = [];

		// If the Coroutine has been eneded by an Abort Message, EXIT
		if (this.State.Value === StateType.End.Value &&
			this.EndReason.Value === EndReasonType.AbortMessage.Value)
		{
			return;
		}
		// If the Owner of the Coroutine is a UObject, check if the object
		// is still valid
		if (!IsValidObject(this.Owner.Owner))
		{
			this.End(EndReasonType.OwnerIsInvalid);
		}
		// Check if Coroutine should be aborted
		for (let i = 0; i < this.AbortImpls.length; i++)
		{
			let impl = this.AbortImpls[i];

			if (impl(this.self))
			{
				for (let j = 0; j < this.OnAborts.length; j++)
				{
					this.OnAborts[i](this.self);
				}
				this.End(EndReasonType.AbortCondition);
				return;
			}
		}
		// Check if Coroutine has been ended
		if (this.State.Value === StateType.End.Value)
		{
			if (this.EndReason.Value === EndReasonType.EEndReason_MAX.Value)
				this.End(EndReasonType.EndOfExecution);
			return;
		}

		let move = true;
        // Check WaitForFrame
        if (this.bWaitForFrame)
        {
            if (this.WaitForFrameType != null)
			{
                this.WaitForFrame = this.WaitForFrameType.Get();

                if (this.WaitForFrame < 0)
                {
                    this.WaitForFrame	  = 0;
                    this.WaitForFrameType = null;

					checkf(false, "FJsRoutine.Update: yield return value of type 'FJsRoutine.FrameType' is used for WaitForFrame. yield return value must be >= 0.");
                }
            }

            ++this.WaitForFrameCounter;

            move = this.WaitForFrameCounter >= this.WaitForFrame;

            if (move)
            {
                this.WaitForFrame = 0;
                this.bWaitForFrame = false;
                this.WaitForFrameCounter = 0;
            }
        }
        // Check WaitForTime
        if (this.bWaitForTime)
        {
            if (this.WaitForTimeType != null)
            {
                this.WaitForTime = this.WaitForTimeType.Get();

                if (this.WaitForTime < 0.0)
                {
                    this.WaitForTime     = 0.0;
                    this.WaitForTimeType = null;

					checkf(false, "FJsRoutine.Update: yield return value of type 'FJsRoutine.TimeType' is used for WaitForTime. yield return value must be >= 0.0f.");
                }
            }

            this.WaitForTimeTimer += deltaTime.Time;

            move = this.WaitForTimeTimer >= this.WaitForTime;

            if (move)
            {
                this.WaitForTime	  = 0;
                this.bWaitForTime	  = false;
                this.WaitForTimeTimer = 0.0;
            }
        }
        // Check WaitingFor
		/*
        if (bWaitingFor)
        {
            move = WaitingFor.State != ECgRoutineState.Running;

            if (move)
            {
                WaitingFor.Blocking = null;
                WaitingFor  = null;
                bWaitingFor = false;
            }
        }
		*/
        // Check WaitForFlag
        if (this.bWaitForFlag)
        {
            move = (this.WaitForBoolType != null && this.WaitForBoolType.Get()) || (this.WaitForFlagType != null && this.WaitForFlagType.IsEqual());

            if (move)
            {
                this.WaitForBoolType = null;
                this.bWaitForFlag    = false;
            }
        }
        // WaitForListenMessage
        if (this.bWaitForListenMessage)
        {
            if (this.WaitForListenMessageType != null)
            {
                this.WaitForListenMessage = this.WaitForListenMessageType.Get();

                if (this.WaitForListenMessage === INVALID_LISTEN_MESSAGE)
                {
					checkf(false, "FJsRoutine.Update: yield return value of type 'FJsRoutine.ListenMessageType' is used for WaitForListenMessage. yield return value must NOT be empty.");
                }
            }

            move = this.WaitForListenMessage === INVALID_LISTEN_MESSAGE;

            if (move)
            {
                this.WaitForListenMessage  = INVALID_LISTEN_MESSAGE;
                this.bWaitForListenMessage = false;
            }
		}
		// WaitForEnum
		if (this.bWaitForEnum)
		{
			move = this.WaitForEnum.Execute();
			
			if (move)
			{
				this.bWaitForEnum = false;
				this.WaitForEnum.Reset();
			}
		}
		// WaitForEnum
		if (this.bWaitForRoutineHandle)
		{
			move = this.WaitForRoutineHandle.Execute();
			
			if (move)
			{
				this.bWaitForRoutineHandle = false;
				this.WaitForRoutineHandle.Reset();
			}
		}

		let TimeLibrary = CsScriptLibrary_Time;

		this.DeltaTime   = TimeLibrary.FCsDeltaTime_Copy(deltaTime);
		this.ElapsedTime = TimeLibrary.Add_DeltaTime(this.ElapsedTime, deltaTime);
		
		if (!move)
			return;

		let result		 = this.CoroutineImpl.next(this.self);
		let yieldCommand = result.value;
		let done		 = result.done;

		if (!done)
		{
			let waitForTimeByObject = false;

			// Check for alternatives ways for commands due to coercion or other caveats
			if (IsValidObject(yieldCommand))
			{
				// Objects that contain the 'WaitForTime' key are used
				// when floats (i.e. 1.0) get coerced to integers (i.e. 1.0 -> 1)
				// and the yieldCommand get interpretted as WaitForFrame
				if ('WaitForTime' in yieldCommand)
				{
					checkf(Number.isFinite(yieldCommand.WaitForTime), "FJsRoutine.Update: yieldCommand with key 'WaitForTime' does NOT have a numeric value.");

					waitForTimeByObject = true;
                }
				// WaitForEnum
				else
				if (this.WaitForEnum.CopyFromYield(yieldCommand))
				{
					this.bWaitForEnum = true;
				}
				// WaitForRoutineHandle
				else
				if (this.WaitForRoutineHandle.CopyFromYield(yieldCommand))
				{
					this.bWaitForRoutineHandle = true;
				}
				else
				{
					this.WaitForEnum.Reset();
					this.WaitForRoutineHandle.Reset();
				}
			}

			if (typeof yieldCommand === "undefined" || yieldCommand == null)
				yieldCommand = 1;

			// WaitForFrame
			if (CommonLibrary.IsInt(yieldCommand))
			{
				this.WaitForFrame = yieldCommand;

                if (this.WaitForFrame < 0)
                {
                    this.WaitForFrame = 0;

					checkf(false, "FJsRoutine.Update: yield return value of type 'int' is used for WaitForFrame. yield return value must be >= 0.");
                }
                else
                {
                    this.bWaitForFrame		 = true;
                    this.WaitForFrameCounter = 0;
                }
			}
			// WaitForFrameType
			else
			if (IsClassOf(yieldCommand, FJsProperty) &&
				yieldCommand.IsInt())
            {
                this.WaitForFrameType = yieldCommand;

                if (this.WaitForFrameType.Get() < 0)
                {
                    this.WaitForFrameType = null;

					checkf(false, "FJsRoutine.Update: yield return value of type 'FJsRoutine.FrameType' is used for WaitForFrame. yield return value must be >= 0.");
                }
                else
                {
                    this.bWaitForFrame		 = true;
                    this.WaitForFrameCounter = 0;
                }
            }
            // WaitForTime | 'waitForTimeByObject'
            else
            if (CommonLibrary.IsFloat(yieldCommand) ||
				waitForTimeByObject)
			{
				this.WaitForTime = waitForTimeByObject ? yieldCommand.WaitForTime : yieldCommand;

                if (this.WaitForTime < 0.0)
                {
                    this.WaitForTime = 0.0;

					checkf(false, "FCgRoutine.Run: yield return value of type 'float' is used for WaitForTime. yield return value must be >= 0.0f.");
                }
                else
                {
                    this.bWaitForTime	  = true;
                    this.WaitForTimeTimer = 0.0;
                }
			}
			// WaitForTimeType
            else
            if (IsClassOf(yieldCommand, FJsProperty) &&
				yieldCommand.IsFloat())
            {
                this.WaitForTimeType = yieldCommand;

                if (this.WaitForTimeType.Get() < 0.0)
                {
                    this.WaitForTimeType = null;

					checkf(false, "FCgRoutine.Run: yield return value of type 'FCgRoutine.FTimeType' is used for WaitForTime. yield return value must be >= 0.0f.");
                }
                else
                {
                    this.bWaitForTime	  = true;
                    this.WaitForTimeTimer = 0.0;
                }
            }
            // WaitingFor
			/*
            else
            if (type == typeof(FCgRoutine))
            {
                WaitingFor = (FCgRoutine)yieldCommand;
                WaitingFor.Blocking = this;
                bWaitingFor = true;

                // Fix linkage. Prev / Next
                InsertRoutine(Schedule, this, WaitingFor);
            }
			*/
            // WaitForFlag
            else
            if (IsClassOf(yieldCommand, FJsProperty) &&
				yieldCommand.IsBoolean())
            {
                this.WaitForBoolType = yieldCommand;

                if (!this.WaitForBoolType.Get())
                    this.bWaitForFlag = true;
            }
            // WaitForListenMessage
			else
			if (typeof yieldCommand === "string")
            {
                this.WaitForListenMessage = yieldCommand;

                if (this.WaitForListenMessage == INVALID_LISTEN_MESSAGE)
                {
					checkf(false, "FJsRoutine.Update: yield return value of type 'string' is used for WaitForListenMessage. yield return value must NOT be empty.");
                }
                else
                {
                    this.bWaitForListenMessage = true;
                }
			}
			// WaitForListenMessageType
            else
            if (IsClassOf(yieldCommand, FJsProperty) &&
				yieldCommand.IsString())
            {
                this.WaitForListenMessageType = yieldCommand;

                if (this.WaitForListenMessageType.Get() === INVALID_LISTEN_MESSAGE)
                {
					checkf(false, "FJsRoutine.Update: yield return value of type 'string' is used for WaitForListenMessage. yield return value must NOT be empty.");
                }
                else
                {
                    this.bWaitForListenMessage = true;
                }
            }
			// WaitForEnum
			else
			if (this.bWaitForEnum)
			{
				// Do Nothing, already set
			}
			// WaitForRoutineHandle
			else
			if (this.bWaitForRoutineHandle)
			{
				// Do Nothing, already set
			}
            // INVALID Type
            else
            {
				checkf(false, "FJsRoutine.Update: Invalid Type: %s for yield. yield return value must be of type: int, FJsRoutine.FrameType, float, FJsRoutine.TimeType, FJsRoutine, FJsRoutine.BoolType, string, or FJsRoutine.ListenMessageType.", typeof yieldCommand);
            }
        }
        // Finished
        else
        {
            this.End(EndReasonType.EndOfExecution);
		}
	}

	IsRunning() { return State.Value === NJsCoroutine.EState.Update.Value; }

    End(endReason)
    {
		this.EndChildren();

		this.State	   = StateType.End;
		this.EndReason = endReason;

		for (let i = 0; i < this.OnEnds.length; ++i)
		{
			this.OnEnds[i](this.self);
        }
    }

	HasJustEnded() { return State.Value === NJsCoroutine.EState.End.Value; }
    HasEnded()
	{
		return State.Value === StateType.End.Value || State.Value === StateType.Free.Value;
	}

    Reset()
	{
		if (IsValidObject(this.Parent))
		{
		    let i = this.Parent.Children.indexOf(this.self);

            if (i > INDEX_NONE)
                this.Parent.Children.splice(i, 1);
		}

		this.Parent = null;
		
		this.EndChildren();

		this.CoroutineImpl = null;

		// Time
		this.StartTime = new CsTime();
		this.ElapsedTime = new CsDeltaTime();
		this.DeltaTime = new CsDeltaTime();
		this.TickCount = 0;
		this.Delay = 0.0;

		this.Handle = new CsRoutineHandle();
		this.AbortImpls = [];
		this.OnAborts = [];

		this.State = StateType.Free;

		this.Name = "";

		this.EndReason = EndReasonType.EEndReason_MAX;
		this.OnEnds = [];

		this.Owner.Reset();

		this.RegisterMap.Reset();

        this.Messages = [[],[]];
		this.Messages_Recieved = [[],[]];
		{
			let count = MessageType.EMessage_MAX.Value;

			for (let i = 0; i < count; ++i)
			{
				this.Messages.push([]);
				this.Messages_Recieved.push([]);
			}
		}

		this.bWaitForFrame = false;
		this.WaitForFrameCounter = 0;
		this.WaitForFrame = 0;
		this.WaitForFrameType = null;
		this.bWaitForTime = false;
		this.WaitForTime = 0.0;
		this.WaitForTimeTimer = 0.0;
		this.WaitForTimeType = null;
		this.bWaitForFlag = false;
		this.WaitForFlagType = null;
		this.bWaitForListenMessage = false;
		this.WaitForListenMessage = null;
		this.WaitForListenMessageType = null;
		this.bWaitForEnum = false;
		this.WaitForEnum.Reset();
		this.bWaitForRoutineHandle = false;
		this.WaitForRoutineHandle.Reset();
	}

    AddChild(child)
	{
		child.Parent = this.self;
		this.Children.push(child);
	}

	EndChildren()
	{
		let count = this.Children.length;

		for (let i = 0; i < count; i++)
		{
			this.Children[i].End();
		}
        this.Children = [];
	}

	EndChild(child)
	{
		let count = this.Children.length;

		for (let i = count - 1; i >= 0; i--)
		{
			if (child == this.Children[i])
			{
				child.End();
				this.Children.splice(i,1);
				break;
			}
		}
	}

	SetValue(index, value)
	{
		this.RegisterMap.SetValue(index, value);
	}

	GetValue(index)
	{
		return this.RegisterMap.GetValue(index);
	}

	AddMessage(messageType, message)
	{
		this.Messages[messageType.Value].push(messsage);
	}

	ReceiveMessage(messageType, message)
	{
		this.Messages_Recieved[messageType.Value].push(message);
	}
};