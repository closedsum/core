/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
// Managers
var FJsManager_Resource_Fixed = require('Cs/Managers/Resource/Manager_Resource_Fixed.js');
// Coroutine
var NJsCoroutine = require('Cs/Coroutine/Types_Coroutine.js');
var FJsRoutine = require('Cs/Coroutine/Routine.js');

const ROUTINE_POOL_SIZE = 2048;
const COROUTINE_PAYLOAD_SIZE = 64;
const INDEX_NONE = -1;

// "typedefs" - classes
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var checkf = CommonLibrary.checkf;
var check = CommonLibrary.check;
var IsValidObject = CommonLibrary.IsValidObject;
var IsInstanceOfChecked = CommonLibrary.IsInstanceOfChecked;
var IsInt = CommonLibrary.IsInt;

// "typedefs" - enums
var StateType = NJsCoroutine.EState;
var EndReasonType = NJsCoroutine.EEndReason;

var Core;

module.exports = class FJsCoroutineSchedule
{
    static NCached = class Cached
    {
        static NStr = class Str
        {
            static StartByContainer = "FJsCoroutineSchedule::StartByContainer";
            static StartChildByContainer = "FJsCoroutineSchedule::Start";
        }
    }

    constructor(core)
    {
        Core = core;
        
        this.Group = new ECsUpdateGroup();

        this.Manager_Routine = new FJsManager_Resource_Fixed();
        this.Manager_Routine.CreatePool(ROUTINE_POOL_SIZE, FJsRoutine);

        // Set Index for fast look up

        // Routine
        {
            let pool = this.Manager_Routine.GetPool();

            for (let i = 0; i < pool.length; ++i)
            {
                let container = pool[i];
                let r         = container.Get();
                let index     = container.GetIndex();
                r.SetIndex(index);
            }
        }

        let PayloadType      = NJsCoroutine.NPayload.FImpl;
        this.Manager_Payload = new FJsManager_Resource_Fixed();
        this.Manager_Payload.CreatePool(COROUTINE_PAYLOAD_SIZE, PayloadType);

        // Set Index for fast look up

        // Payload
        {
            let pool = this.Manager_Payload.GetPool();

            for (let i = 0; i < pool.length; ++i)
            {
                let container = pool[i];
                let r         = container.Get();
                let index     = container.GetIndex();
                r.SetIndex(index);
            }
        }
    }

    // Schedule
    // #region Schedule
    // public:

    SetGroup(group)
    {
        this.Group = group;

        // Routine
        {
            let pool = this.Manager_Routine.GetPool();

            for (let i = 0; i < pool.length; ++i)
            {
                let container = pool[i];
                let r         = container.Get();
                r.SetGroup(group);
            }
        }
        // Payload
        {
            let pool = this.Manager_Payload.GetPool();

            for (let i = 0; i < pool.length; ++i)
            {
                let container = pool[i];
                let r         = container.Get();
                r.Group = group;
            }
        }
    }
    // #endregion Schedule

    // Routine
    // #region Routine
    // public:

    /**
	*
	*
	* @param {CsRoutineHandle} handle
	* @returns {FJsResourceContainer}
	*/
    /*FJsResourceContainer*/ GetRoutineContainer(handle /*CsRoutineHandle*/)
    {
        let context = "FJsCoroutineSchedule.GetRoutineContainer";
        
        check(IsInstanceOfChecked(context, handle, CsRoutineHandle));

        let RoutineLibrary = CsScriptLibrary_Routine;

        if (!RoutineLibrary.IsValid(handle))
        {
            //console.log("FCsCoroutineSchedule::GetRoutineContainer: Handle is NOT valid: " + handle.Index + " " + Guid.Conv_GuidToString(handle.Handle));
            return null;
        }

        let poolSize = this.Manager_Routine.GetPoolSize();
        
        let index = INDEX_NONE; 
        
        if (IsInt(handle.Index) &&
            handle.Index >= 0)
        {
            index = handle.Index
        }
        else
        if (IsInt(handle.index) &&
            handle.index >= 0)
        {
            index = handle.index;
        }

        if (index >= this.PoolSize)
        {
            console.log("FCsCoroutineSchedule::GetRoutineContainer: Handle's Index: " + index + " is not associated with any Routine with Group: " + Group.Name_Internal + ".");
            return null;
        }

        let container = this.Manager_Routine.GetAt(index);
        let r		  = container.Get();

        let IsEqual = RoutineLibrary.EqualEqual;
        
        if (IsEqual(r.GetHandle(), handle))
            return container;
        return null;
    }

    /**
    *
    *
    * @param {CsRoutineHandle} handle
    * @returns {FJsRoutine}
    */
    /*FJsRoutine*/ GetRoutine(handle /*CsRoutineHandle*/)
    {
        let container = this.GetRoutineContainer(handle);

        return IsValidObject(container) ? container.Get() : null;
    }

    // #endregion Routine

    // Handle
    // #region Handle
    // public:

    /**
     * @param {CsRoutineHandle} handle 
     * @returns {boolean}
     */
    /*bool*/ IsHandleValid(handle /*CsRoutineHandle*/)
	{
        return this.GetRoutineContainer(handle) != null;
    }

    /**
     * @param {CsRoutineHandle} handle 
     * @returns {boolean}
     */
    /*bool*/ IsRunning(handle /*CsRoutineHandle*/)
    {
        let r = this.GetRoutine(handle);

        if (IsValidObject(r))
            return r.IsRunning();
        return false;
    }
    // #endregion Handle

    // Start
    // #region Start
    // public:

    /**
	* @param {FJsResourceContainer} payloadContainer
	* @returns {boolean}
	*/
    StartByContainer(payloadContainer /*FJsResourceContainer*/)
    {
        let Str = FJsCoroutineSchedule.NCached.NStr;

        let context = Str.StartByContainer;

	    let payload = payloadContainer.Get();

        checkf(IsValidObject(payload), context + ": payloadContainer does NOT contain a reference to a payload.");

        check(payload.IsValidChecked(context));

        let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
        let IsEqual            = UpdateGroupLibrary.EqualEqual;

        checkf(IsEqual(this.Group, payload.Group), context + ": Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, this.Group.Name_Internal);

        let r = this.Manager_Routine.AllocateResource();

        r.Init(payload);

        if (payload.bPerformFirstUpdate)
        {
            r.StartUpdate();
            // NOTE: The double update since an initial yield is needed to set the Routine (r).
            //       Currently there doesn't seem to be a way to "seed" the Routine without doing this.
            r.Update(new CsDeltaTime());
            r.Update(new CsDeltaTime());
        }

        //LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? TransactionType::Start : TransactionType::Allocate, R);

        payload.Reset();
        this.Manager_Payload.Deallocate(payloadContainer);
        return r.GetHandle();
    }

    /**
	* @param {} payload
	* @returns {FJsRoutine}
	*/
    /*FJsRoutine*/ Start(payload)
    {
        return this.StartByContainer(this.GetPayloadContainer(payload));
    }

    /**
	* @param payloadContainer
	* @returns {FJsRoutine}
	*/
    /*FJsRoutine*/ StartChildByContainer(payloadContainer)
    {
        let Str = FJsCoroutineSchedule.NCached.NStr;

        let context = Str.StartChildByContainer;

        let payload = payloadContainer.Get();

        checkf(IsValidObject(payload), context + ": payloadContainer does NOT contain a reference to a payload.");

        checkf(payload.IsValidChecked(context));

        let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
        let IsEqual            = UpdateGroupLibrary.EqualEQual_UpdateGroupUpdateGroup;

        checkf(IsEqual(Group, payload.Group), context + ": Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, Group.Name_Internal);

	    let parentContainer = this.GetRoutineContainer(payload.ParentHandle);

        checkf(IsValidObject(parentContainer), context + ": Failed to find a container for payload.");

        let parent    = parentContainer.Get();
	    let lastChild = parent.GetLastChild();

	    let routineContainer = null;

	    // Add after Last Child
        if (lastChild)
	    {
		    let lastChildContainer = this.Manager_Routine.GetAt(lastChild.GetIndex());

            routineContainer = this.Manager_Routine.AllocateAfter(lastChildContainer);
	    }
	    // Add after Parent
	    else
	    {
            routineContainer = this.Manager_Routine.AllocateAfter(parentContainer);
	    }

        let r = routineContainer.Get();

	    parent.AddChild(r);

	    r.Init(payload);

	    r.StartUpdate();
        // NOTE: The double update since an initial yield is needed to set the Routine (r).
        //       Currently there doesn't seem to be a way to "seed" the Routine without doing this.
        r.Update(new CsDeltaTime());
	    r.Update(new CsDeltaTime());

	    payload.Reset();
	    //UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	    return r.GetHandle();
    }

    /**
	*
	*
	* @param {} payload
	* @returns {FJsRoutine}
	*/
    /*FJsRoutine*/ StartChild(payload)
    {
        return this.StartChildByContainer(this.GetPayloadContainer(payload));
    }

    // #endregion Start

    // End
    // #region End
    // public:

	/**
	*
	*/
    EndAll()
    {
	    let result = false;

	    let current = this.Manager_Routine.GetAllocatedHead();
	    let next	= current;

	    while (next != null)
	    {
		    current				 = next;
		    let routineContainer = current.Element;
		    next				 = current.GetNextLink();

            let r = routineContainer.Get();

		    r.End(EndReasonType.Shutdown);

		    //LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

		    r.Reset();
            this.Manager_Routine.Deallocate(routineContainer);

		    result = true;
	    }
        return result;
    }

	/**
	* End the routine associated with the Handle.
	*
	* @param {CsRoutineHandle}  handle  Handle to a routine.
	* @returns {boolean}			    Whether the routine has successful ended.
	*					                NOTE: If the routine has already ended, this will return false.
	*/
    /*bool*/ End(handle /*CsRoutineHandle*/)
    {
        let container = this.GetRoutineContainer(handle);

        if (IsValidObject(container))
        {
            let r = container.Get();

            r.End(EndReasonType.Manual);

            //LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

            r.Reset();
            this.Manager_Routine.Deallocate(container);
            return true;
        }
        return false;
    }

	/**
	* Check if a routine associated with the Handle has already ended.
	* NOTE: This returns True if Handle is NOT Valid.
	* 
	* @param {CsRoutineHandle} handle	Handle to a routine.
	* @returns {boolean}		        Whether the routine has already ended.
	*/
	/*bool*/ HasEnded(handle /*CsRoutineHandle*/)
    {
        let r = this.GetRoutine(handle);

	    if (IsValidObject(r))
		    return r.HasEnded();
	    return true;
    }

	/**
	* Check if a routine associated with the Handle has just ended.
	*
	* @param {CsRoutineHandle} handle	Handle to a routine.
	* @returns {boolean}			    Whether the routine has just ended.
	*/
	/*bool*/ HasJustEnded(handle /*CsRoutineHandle*/)
    {
        let r = this.GetRoutine(handle);

	    if (IsValidObject(r))
		    return r.HasJustEnded();
	    return true;
    }

    // #endregion End

    // Update
    // #region Update
    // public:

    /**
    * @params {CsDeltaTime} deltaTime
    */
    Update(deltaTime /*CsDeltaTime*/)
    {
	    let current = this.Manager_Routine.GetAllocatedHead();
	    let next    = current;

	    while (next != null)
	    {
		    current				 = next;
		    let routineContainer = current.Element;
		    next				 = current.GetNextLink();

		    let r = routineContainer.Get();

		    let state = r.State;

		    // Init -> Update
		    if (state.Value === StateType.Init.Value)
		    {
			    r.StartUpdate();
			    r.Update(deltaTime);
		    }
		    // Update
		    else
		    if (state.Value === StateType.Update.Value)
		    {
			    r.Update(deltaTime);
		    }

		    // End
		    if (state.Value === StateType.End.Value)
		    {
			    //LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);
                
			    r.Reset();
			    this.Manager_Routine.Deallocate(routineContainer);
		    }
	    }
    }

    // #endregion Update

    // Payload
    // #region Payload
    // public:

	/**
	*
	*
	* return
	*/
	AllocatePayloadContainer() { return this.Manager_Payload.Allocate(); }

	/**
	*
	*
	* @returns {NJsCoroutine.NPayload.FImpl}
	*/
	/*PayloadType*/ AllocatePayload() { return this.Manager_Payload.AllocateResource(); }

    // protected:

	/**
	*
	*
	* @param {NJsCoroutine.NPayload.FImpl} payload
	* @returns {FJsResourceContainer}               FJsResourceContainer < PayloadType >
	*/
    /*FJsResourceContainer<PayloadType>*/ GetPayloadContainer(payload /*PayloadType*/)
    {
        if (payload.GetIndex() === INDEX_NONE)
        {
            let container = this.Manager_Payload.Allocate();
            let p		  = this.container.Get();

            p.Copy(payload);

            return container;
	    }
	    return this.Manager_Payload.GetAt(payload.GetIndex());
    }

    // #endregion Payloads

    // Message
    // #region
    // public:

    /**
    *
    *
    * @param type
    * @param {string} message
    * @param {object} owner
    */
    BroadcastMessage(type, message /*string*/, owner /*object*/)
    {
	    let current = this.Manager_Routine.GetAllocatedHead();
	    let next    = current;

	    while (next != null)
	    {
		    current				 = next;
		    let routineContainer = current.Element;
		    next				 = current.GetNextLink();

		    let r = routineContainer.Get();

		    if (IsValidObject(owner))
		    {
			    if (r.Owner.Owner === owner)
				    r.ReceiveMessage(type, message);
		    }
		    else
		    {
			    r.ReceiveMessage(type, message);
		    }
	    }
    }
    // #endregion Message
};