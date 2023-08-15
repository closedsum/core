/// <reference path="../../Cs/Coroutine/Types_Coroutine.ts">/>
/// <reference path="../../Cs/Library/Library_Common.ts">/>
/// <reference path="../../Cs/Types/Property/Property.ts">/>
/// <reference path="../../Cs/Types/Yield/Yield_Enum.ts">/>
/// <reference path="../../Cs/Types/Yield/Yield_Function.ts">/>
/// <reference path="../../Cs/Types/Yield/Yield_RoutineHandle.ts">/>
/// <reference path="../../Cs/Core.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Types
var NJsCoroutine1 = require('Cs/Coroutine/Types_Coroutine.js');
/** @type {FJsProperty} */
var FJsProperty = require('Cs/Types/Property/Property.js');
var NJsYield1 = require('Cs/Types/Yield/Yield_Enum.js');
var NJsYield2 = require('Cs/Types/Yield/Yield_RoutineHandle.js');
var NJsYield3 = require('Cs/Types/Yield/Yield_Function.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

const INDEX_NONE = -1;

const EMPTY = 0;

const INVALID_LISTEN_MESSAGE = "";

const ROUTINE_END = -1;
const ROUTINE_FREE = -2;

// "typedefs" - class
/** @type {CommonLibrary} */
var CommonLibrary = NJsCommon.FLibrary;
var EnumYieldType = NJsYield1.FEnum;
var RoutineHandleYieldType = NJsYield2.FRoutineHandle;
var FunctionYieldType = NJsYield3.FFunction;

// "typedefs" - function
var checkf = CommonLibrary.checkf;
var IsValidObject = CommonLibrary.IsValidObject;
var IsInstanceOf = CommonLibrary.IsInstanceOf;

// "typedefs" - enums
/** @type {NJsCoroutine.EState} */ 		var StateType = NJsCoroutine1.EState;
/** @type {NJsCoroutine.EEndReason} */ 	var EndReasonType = NJsCoroutine1.EEndReason;
/** @type {NJsCoroutine.EMessage} */	var MessageType = NJsCoroutine1.EMessage;

/** @type {FJsCore} */	var Core;

module.exports = class FJsRoutine
{
    constructor()
    {
		/** @type {FJsRoutine} */	this.self = this;

		let UpdateGroupLibrary	= CsScriptLibrary_UpdateGroup;
		this.Group				= UpdateGroupLibrary.GetMax();

		// Time
		/** @type {CsTime} */ 		this.StartTime = new CsTime();
		/** @type {CsDeltaTime} */ 	this.ElapsedTime = new CsDeltaTime();
		/** @type {CsDeltaTime} */  this.DeltaTime = new CsDeltaTime();
		/** @type {number} int */ 	this.TickCount = 0;
		/** @type {number} float */	this.Delay = 0;

		/** @type {FJsRoutine} */	this.Handle = new CsRoutineHandle();
		
		this.AbortImpls = [];
		this.OnAborts = [];

		/** @type {NJsCoroutine.EState} */	this.State = StateType.Free;

		/** @type {number} int */	this.Index = INDEX_NONE;

		/** @type {string} */ this.Name = "";

		// End
		/** @type {NJsCoroutine.EEndReason} */	this.EndReason = EndReasonType.EEndReason_MAX;

		this.OnEnds = [];

		// Owner
		/** @type {NJsCoroutine.FOwner} */	let OwnerType = NJsCoroutine1.FOwner;
		/** @type {NJsCoroutine.FOwner} */	this.Owner    = new OwnerType();

		// Children

		/** @type {FJsRoutine} */   this.Parent = null;
		/** @type {FJsRoutine[]} */	this.Children = [];
		
		/** @type {NJsCoroutine.NRegister.FMap} */	let RegisterMapType = NJsCoroutine1.NRegister.FMap;
		/** @type {NJsCoroutine.NRegister.FMap} */	this.RegisterMap	= new RegisterMapType();

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

		/** @type {boolean} */		this.bWaitForFrame = false;
		/** @type {number} int */ 	this.WaitForFrameCounter = 0;
		/** @type {number} int */	this.WaitForFrame = 0;
		/** @type {FJsProperty} */	this.WaitForFrameType = null;
		/** @type {boolean} */		this.bWaitForTime = false;
		/** @type {number} float */	this.WaitForTime = 0.0;
		/** @type {number} float */	this.WaitForTimeTimer = 0.0;
		/** @type {FJsProperty} */	this.WaitForTimeType = null;
		/** @type {boolean} */		this.bWaitForFlag = false;
		/** @type {FJsProperty} */ 	this.WaitForFlagType = null;
		/** @type {boolean} */		this.bWaitForListenMessage = false;
		/** @type {string} */		this.WaitForListenMessage = null;
		/** @type {FJsProperty} */	this.WaitForListenMessageType = null;
		/** @type {boolean} */		this.bWaitForEnum = false;
		/** @type {NJsYield.FEnum} */	this.WaitForEnum = new EnumYieldType(); /*EnumYieldType (NJsYield.FEnum)*/
		/** @type {boolean} */		this.bWaitForRoutineHandle = false;
		/** @type {NJsYield.FRoutineHandle} */	this.WaitForRoutineHandle = new RoutineHandleYieldType(); /*RoutineHandleYieldType (NJsYield.FRoutineHandle)*/
		/** @type {boolean} */		this.bWaitForFunction = false;
		/** @type {NJsYield.FFunction} */	this.WaitForFunction = new FunctionYieldType(); /*FunctionYieldType (NJsYield.FFunction)*/
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
		this.Handle.index = index; 
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
		this.Handle		   = RoutineLibrary.New(this.Handle).$;
    }

	StartUpdate() { this.State = StateType.Update; }

	/**
	* @param {number} deltaTime		float
	*/
	Update(deltaTime /*float*/)
	{
		// Check for Abort Messages
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
		// WaitForRoutineHandle
		if (this.bWaitForRoutineHandle)
		{
			move = this.WaitForRoutineHandle.Execute();
			
			if (move)
			{
				this.bWaitForRoutineHandle = false;
				this.WaitForRoutineHandle.Reset();
			}
		}
		// WaitForFunction
		if (this.bWaitForFunction)
		{
			move = this.WaitForFunction.Execute();
			
			if (move)
			{
				this.bWaitForFunction = false;
				this.WaitForFunction.Reset();
			}
		}

		let TimeLibrary = CsScriptLibrary_Time;

		this.DeltaTime   = TimeLibrary.FCsDeltaTime_Copy(deltaTime);
		this.ElapsedTime = TimeLibrary.Add_DeltaTime(this.ElapsedTime, deltaTime);
		
		if (!move)
			return;

		++this.TickCount;

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
				// WaitForFunction
				else
				if (this.WaitForFunction.CopyFromYield(yieldCommand))
				{
					this.bWaitForFunction = true;
				}
				else
				{
					this.WaitForEnum.Reset();
					this.WaitForRoutineHandle.Reset();
					this.WaitForFunction.Reset();
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
			if (IsInstanceOf(yieldCommand, FJsProperty) &&
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
            if (IsInstanceOf(yieldCommand, FJsProperty) &&
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
            if (IsInstanceOf(yieldCommand, FJsProperty) &&
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
            if (IsInstanceOf(yieldCommand, FJsProperty) &&
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
			// WaitForFunction
			else
			if (this.bWaitForFunction)
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
            if (this.EndReason.Value === EndReasonType.EEndReason_MAX.Value &&
				this.TickCount > 0)
			{
				this.End(EndReasonType.EndOfExecution);
			}
		}
	}

	IsRunning() { return this.State.Value === StateType.Update.Value; }

	/**
	* @param {NJsCoroutine.EEndReason} endReason 
	*/
    End(endReason /*NJsCoroutine.EEndReason*/)
    {
		this.EndChildren();

		this.State = StateType.End;

		if (typeof endReason == "undefined")
			this.EndReason = EndReasonType.EndOfExecution;
		else
			this.EndReason = endReason;

		for (let i = 0; i < this.OnEnds.length; ++i)
		{
			this.OnEnds[i](this.self);
        }
    }

	EndOfExecution()
	{
		this.End(EndReasonType.EndOfExecution);
	}

	HasJustEnded() { return this.State.Value === StateType.End.Value; }
    HasEnded()
	{
		return this.State.Value === StateType.End.Value || this.State.Value === StateType.Free.Value;
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

		let RoutineLibrary = CsScriptLibrary_Routine;

		this.Handle = RoutineLibrary.Reset(this.Handle).$;
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
		this.bWaitForFunction = false;
		this.WaitForFunction.Reset();
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

	/**
	* @param {number} index 	int
	* @param {any} value 
	*/
	SetValue(index /*int*/, value /*any*/)
	{
		this.RegisterMap.SetValue(index, value);
	}

	/**
	* @param {number} index		int
	* @returns {any}
	*/
	GetValue(index /*int*/)
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