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
var IsValidObject = CommonLibrary.IsValidObject;

// "typedefs" - enums
var StateType = NJsCoroutine.EState;
var EndReasonType = NJsCoroutine.EEndReason;

module.exports = class FJsCoroutineSchedule
{
    constructor()
    {
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
	* @param handle
	* return
	*/
    GetRoutineContainer(handle)
    {
        let RoutineLibrary = CsScriptLibrary_Routine;

        if (!RoutineLibrary.FCsRoutine_IsValid(handle))
            return null;

        let poolSize = this.Manager_Routine.GetPoolSize();
        
        if (handle.Index >= this.PoolSize)
        {
            console.log("FCsCoroutineSchedule::GetRoutineContainer: Handle's Index: %d is not associated with any Routine with Group: %s.", Handle.Index, Group.Name_Internal);
            return null;
        }

        let container = this.Manager_Routine.GetAt(handle.Index);
        let r		  = container.Get();

        let IsEqual = RoutineLibrary.EqualEqual_RoutineHandleRoutineHandle;

        if (IsEqual(r.GetHandle(), handle))
            return container;
        return null;
    }

    /**
    *
    *
    * @param handle
    * return
    */
    GetRoutine(handle)
    {
        let container = this.GetRoutineContainer(handle);

        return IsValidObject(container) ? container.Get() : null;
    }

    // #endregion Routine

    // Handle
    // #region Handle
    // public:

    IsHandleValid(handle)
	{
        return this.GetRoutineContainer(handle) != null;
    }

    IsRunning(handle)
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
	*
	*
	* @param payloadContainer
	* return
	*/
    StartByContainer(payloadContainer)
    {
	    let payload = payloadContainer.Get();

        console.assert(IsValidObject(payload), "FJsCoroutineSchedule.StartByContainer: payloadContainer does NOT contain a reference to a payload.");

        let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
        let IsEqual            = UpdateGroupLibrary.EqualEqual_UpdateGroupUpdateGroup;

        console.assert(IsEqual(this.Group, payload.Group), "FJsCoroutineSchedule.StartByContainer: Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, this.Group.Name_Internal);

        let r = this.Manager_Routine.AllocateResource();

        r.Init(payload);

        if (payload.bPerformFirstUpdate)
        {
            r.StartUpdate();
            r.Update(new CsDeltaTime());
        }

        //LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? TransactionType::Start : TransactionType::Allocate, R);

        payload.Reset();
        this.Manager_Payload.Deallocate(payloadContainer);
        return r.GetHandle();
    }

    /**
	*
	*
	* @param payload
	* return
	*/
    Start(payload)
    {
        return this.StartByContainer(this.GetPayloadContainer(payload));
    }

    /**
	*
	*
	* @param payloadContainer
	* return
	*/
    StartChildByContainer(payloadContainer)
    {
        let payload = payloadContainer.Get();

        console.assert(IsValidObject(payload), "FJsCoroutineSchedule.StartChildByContainer: payloadContainer does NOT contain a reference to a payload.");

        let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
        let IsEqual            = UpdateGroupLibrary.EqualEQual_UpdateGroupUpdateGroup;

        console.assert(IsEqual(Group, payload.Group), "FJsCoroutineSchedule.StartChildByContainer: Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, Group.Name_Internal);

	    let parentContainer = this.GetRoutineContainer(payload.ParentHandle);

        console.assert(IsValidObject(parentContainer), "FJsCoroutineSchedule.StartChildByContainer: Failed to find a container for payload.");

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
	    r.Update(new CsDeltaTime());

	    payload.Reset();
	    //UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
	    return r.GetHandle();
    }

    /**
	*
	*
	* @param payload
	* return
	*/
    StartChild(payload)
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
	* @param handle		Handle to a routine.
	* return			Whether the routine has successful ended.
	*					NOTE: If the routine has already ended, this will return false.
	*/
    End(handle)
    {
        let container = this.GetRoutine(handle);

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
	* @param handle		Handle to a routine.
	* return			Whether the routine has already ended.
	*/
	HasEnded(handle)
    {
        let r = this.GetRoutine(handle);

	    if (IsValidObject(r))
		    return r.HasEnded();
	    return true;
    }

	/**
	* Check if a routine associated with the Handle has just ended.
	*
	* @param handle		Handle to a routine.
	* return			Whether the routine has just ended.
	*/
	HasJustEnded(handle)
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
    *
    *
    * @param deltaTime
    */
    Update(deltaTime)
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
	* return
	*/
	AllocatePayload() { return this.Manager_Payload.AllocateResource(); }

    // protected:

	/**
	*
	*
	* @param payload
	* return
	*/
    GetPayloadContainer(payload)
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
    * @param message
    * @param owner
    */
    BroadcastMessage(type, message, owner)
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