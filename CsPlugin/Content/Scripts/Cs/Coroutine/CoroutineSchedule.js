// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Types
/// <reference path="../Coroutine/Types_Coroutine.ts">/>
// Coroutine
/// <reference path="../Coroutine/Routine.ts">/>
// Library
/// <reference path="../Library/Library_Common.ts">/>
// Managers
/// <reference path="../Managers/Resource/Manager_Resource_Fixed.ts">/>

"use strict"

// Type
var FJsProperty = require('Cs/Types/Property/Property.js');
// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsMath = require('Cs/Library/Library_Math.js');
// Managers
/** @type {FJsManager_Resource_Fixed} */
var FJsManager_Resource_Fixed = require('Cs/Managers/Resource/Manager_Resource_Fixed.js');
// Coroutine
var NJsCoroutine = require('Cs/Coroutine/Types_Coroutine.js');
/** @type {FJsRoutine} */
var FJsRoutine = require('Cs/Coroutine/Routine.js');

const ROUTINE_POOL_SIZE = 2048;
const COROUTINE_PAYLOAD_SIZE = 64;
const INDEX_NONE = -1;

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;
/** @type {JsMathLibrary} */ var JsMathLibrary = NJsMath.FLibrary;

// "typedefs" - library (c++)
var RoutineLibrary = CsScriptLibrary_Routine;
var UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;

// "typedefs" - class
/** @type {NJsCoroutine_NPayload_FImpl} */ var PayloadType = NJsCoroutine.NPayload.FImpl;

// "typedefs" - functions
var checkf              = CommonLibrary.checkf;
var check               = CommonLibrary.check;
var IsValidObject       = CommonLibrary.IsValidObject;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;
var IsInstanceOfChecked = CommonLibrary.IsInstanceOfChecked;
var IsInt               = CommonLibrary.IsInt;
var IsIntChecked        = CommonLibrary.IsIntChecked;
var IsEqual_UpdateGroup = UpdateGroupLibrary.EqualEqual;

// "typedefs" - enums
var StateType = NJsCoroutine.EState;
var EndReasonType = NJsCoroutine.EEndReason;

// Globals
/** @type {FJsCore} */                          var Core = null;
    // Default
/** @type {NJsCoroutine.NSchedule.FDefault} */              var DefaultClassType = null;
/** @type {NJsCoroutine.NSchedule.FDefault.NCached.NStr} */ var Default_Str = null;
    // Custom
/** @type {NJsCoroutine.NSchedule.FCustom} */              var CustomClassType = null;
/** @type {NJsCoroutine.NSchedule.FCustom.NCached.NStr} */ var Custom_Str = null;

var DefaultClassName = "NJsCoroutine.NSchedule.FDefault";
var CustomClassName = "NJsCoroutine.NSchedule.FCustom";

module.exports = class NJsCoroutine
{
    static NSchedule = class NamespaceSchedule
    {
        static FDefault = class Default
        {
            static NCached = class Cached
            {
                static NStr = class Str
                {
                    static GetRoutineContainer   = DefaultClassName + ".GetRoutineContainer";
                    static StartByContainer      = DefaultClassName + ".StartByContainer";
                    static StartChildByContainer = DefaultClassName + ".Start";
                }
            }

            constructor(core)
            {
                DefaultClassType = NJsCoroutine.NSchedule.FDefault;
                Default_Str      = DefaultClassType.NCached.NStr;

                Core = core;

                /** @type {ECsUpdateGroup} */ this.Group = new ECsUpdateGroup();

                /** @type {FJsManager_Resource_Fixed} */
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

                /** @type {FJsManager_Resource_Fixed} */
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

                this.QueueEndHandles = [];
            }

            // Schedule
            // #region Schedule
            // public:

            SetGroup(group /*ECsUpdateGroup*/)
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
            * @param {CsRoutineHandle}          handle
            * @returns {FJsResourceContainer}
            */
            /*FJsResourceContainer*/ GetRoutineContainer(handle /*CsRoutineHandle*/)
            {
                let context = Default_Str.GetRoutineContainer;
                
                check(IsInstanceOfChecked(context, handle, CsRoutineHandle));

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
            /*boolean*/ IsHandleValid(handle /*CsRoutineHandle*/)
            {
                return this.GetRoutineContainer(handle) != null;
            }

            /**
             * @param {CsRoutineHandle} handle 
             * @returns {boolean}
             */
            /*boolean*/ IsRunning(handle /*CsRoutineHandle*/)
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
            * @returns {CsRoutineHandle}
            */
            /*CsRoutineHandle*/ StartByContainer(payloadContainer /*FJsResourceContainer*/)
            {
                let context = Default_Str.StartByContainer;

                /** @type {NJsCoroutine_NPayload_FImpl}*/
                let payload = payloadContainer.Get();

                checkf(IsValidObject(payload), context + ": payloadContainer does NOT contain a reference to a payload.");
                check(payload.IsValidChecked(context));
                checkf(IsEqual_UpdateGroup(this.Group, payload.Group), context + ": Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, this.Group.Name_Internal);

                /** @type {FJsRoutine} */
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
            * @param {NJsCoroutine_NPayload_FImpl} payload
            * @returns {FJsRoutine}
            */
            /*CsRoutineHandle*/ Start(payload /*NJsCoroutine_NPayload_FImpl*/)
            {
                return this.StartByContainer(this.GetPayloadContainer(payload));
            }

            /**
            * @param {FJsResourceContainer} payloadContainer
            * @returns {FJsRoutine}
            */
            /*CsRoutineHandle*/ StartChildByContainer(payloadContainer /*FJsResourceContainer*/)
            {
                let context = Default_Str.StartChildByContainer;

                let payload = payloadContainer.Get();

                checkf(IsValidObject(payload), context + ": payloadContainer does NOT contain a reference to a payload.");
                checkf(payload.IsValidChecked(context));
                checkf(IsEqual_UpdateGroup(Group, payload.Group), context + ": Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, Group.Name_Internal);

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
            * @param {NJsCoroutine_NPayload_FImpl} payload
            * @returns {FJsRoutine}
            */
            /*CsRoutineHandle*/ StartChild(payload /*NJsCoroutine_NPayload_FImpl*/)
            {
                return this.StartChildByContainer(this.GetPayloadContainer(payload));
            }

            // #endregion Start

            // End
            // #region End
            // public:

            /**
            * End all coroutines.
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
            /*boolean*/ End(handle /*CsRoutineHandle*/)
            {
                let container = this.GetRoutineContainer(handle);

                if (IsValidObject(container))
                {
                    let r = container.Get();

                    // If the Routine has already Ended, exit
                    if (r.HasEnded() ||
                        r.HasJustEnded())
                    {
                        return false;
                    }

                    // If the Routine is currently being Updated, queue the End for either the
                    // beginning of the next Update or the end of the current Update.
                    if (!r.IsUpdateComplete())
                    {
                        this.QueueEndHandles.push(handle);
                        return false;
                    }

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
            /*boolean*/ HasEnded(handle /*CsRoutineHandle*/)
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
            /*boolean*/ HasJustEnded(handle /*CsRoutineHandle*/)
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
            * @param {CsDeltaTime} deltaTime
            */
            Update(deltaTime /*CsDeltaTime*/)
            {
                // End any pending Handles requested for End from the previous Update
                for (let handle of this.QueueEndHandles)
                {
                    this.End(handle);
                }

                this.QueueEndHandles = [];

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

                // End any Handles requested for End on the current Update
                for (let handle of this.QueueEndHandles)
                {
                    this.End(handle);
                }

                this.QueueEndHandles = [];
            }

            // #endregion Update

            // Payload
            // #region Payload
            // public:

            /**
            *
            *
            * @returns {FJsResourceContainer}
            */
            /*FJsResourceContainer*/ AllocatePayloadContainer() { return this.Manager_Payload.Allocate(); }

            /**
            *
            *
            * @returns {NJsCoroutine_NPayload_FImpl}
            */
            /*NJsCoroutine_NPayload_FImpl*/ AllocatePayload() { return this.Manager_Payload.AllocateResource(); }

            // protected:

            /**
            *
            *
            * @param {NJsCoroutine_NPayload_FImpl} payload
            * @returns {FJsResourceContainer}               FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
            */
            /*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/ GetPayloadContainer(payload /*NJsCoroutine_NPayload_FImpl*/)
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
            // #region Message
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
        }

        static FCustom = class Custom
        {
            static NCached = class Cached
            {
                static NStr = class Str
                {
                    // Owner
                    static GetOwnerID            = CustomClassName + ".GetOwnerID";
                    // Routine
                    static GetRoutineContainer   = CustomClassName + ".GetRoutineContainer";
                    // Start
                    static StartByContainer      = CustomClassName + ".StartByContainer";
                    static StartChildByContainer = CustomClassName + ".Start";
                    // End
                    static End                   = CustomClassName + ".End";
                    // Update
                    static Update                = CustomClassName + ".Update";
                }
            }

            constructor(core)
            {
                CustomClassType = NJsCoroutine.NSchedule.FCustom;
                Custom_Str      = CustomClassType.NCached.NStr;

                Core = core;

                /** @type {ECsUpdateGroup} */ this.Group = new ECsUpdateGroup();

                // Owmer
                /** @type {FJsManager_Resource_Fixed} */
                this.Manager_OwnerID = new FJsManager_Resource_Fixed();
                this.Manager_OwnerID.CreatePool(ROUTINE_POOL_SIZE, FJsProperty);

                {
                    let pool = this.Manager_OwnerID.GetPool();

                    for (let i = 0; i < pool.length; ++i)
                    {
                        let container = pool[i];
                        let p         = container.Get();
                        p.Value       = container.GetIndex();
                    }
                }

                // TODO: Get from settings
                this.MaxOwners = 128;
                this.MaxRoutinesPerOwner = 16;
                // Max Owners * Max Allocated Routines (Stride)
                this.OwnerRoutineIDs = [];
                this.RoutineStrideByOwnerID = [];
                this.OwnerQueueEndHandles = [];
                this.QueueEndHandleStrideByOwnerID = [];

                for (let i = 0; i < ROUTINE_POOL_SIZE; ++i)
                {
                    this.OwnerRoutineIDs[i] = INDEX_NONE;
                    this.OwnerQueueEndHandles[i] = null;
                }

                for (let i = 0; i < this.MaxOwners; ++i)
                {
                    this.RoutineStrideByOwnerID[i] = 0;
                    this.QueueEndHandleStrideByOwnerID[i] = 0;
                }

                /** @type {FJsManager_Resource_Fixed} */
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

                /** @type {FJsManager_Resource_Fixed} */
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

                /** Handles to End either beginning of the next Update or the end of the
                    current Update.
                    NOTE: This list is populated when a Routine is currently being Executed and
                        requested to End. */
                this.OwnerQueueEndHandles = [];
                this.QueueEndHandleStrideByOwnerID = [];
            }

            // Owner
            // #region Owner

            /*number*/ AllocateOwnerID()
            {
                return this.Manager_OwnerID.AllocateResource().Get();
            }

            DeallocateOwnerID(ownerID /*number*/)
            {
                this.End(ownerID);
                this.Manager_OwnerID.DeallocateAtByIndex(ownerID);
            }
        
            /*boolean*/ HasFreeOwnerID()
            {
                return !this.Manager_OwnerID.IsExhausted(); 
            }
        
            /*number*/ GetOwnerID(routineIndex /*number*/)
            {
                let context = Custom_Str.GetOwnerID;

                check(IsIntChecked(context, routineIndex));
                check(JsMathLibrary.IsIntInRangeInclusiveChecked(context, routineIndex, 0, this.Manager_Routine.GetPoolSize()));

                let current = this.Manager_OwnerID.GetAllocatedHead();
                let next	= current;

                while (IsValidObject(next))
                {
                    current				 = next;
                    let routineContainer = current.GetElement();
                    next				 = current.GetNextLink();

                    let id = routineContainer.Get().Get();

                    let start  = id * this.MaxRoutinesPerOwner;
                    let stride = this.RoutineStrideByOwnerID[id];
                        
                    for (let i = 0; i < stride; ++i)
                    {
                        let index = start + i;

                        if (this.OwnerRoutineIDs[index] === routineIndex)
                        {
                            return id;
                        }
                    }
                }
                checkf(0, context + ": Failed to find OwnerID associated with RoutineIndex: " + routineIndex + ".");
                return INDEX_NONE;
            }

            /*number*/ GetOwnerIDByRoutine(r /*FJsRoutine*/)
            {
                check(IsValidObjectChecked(context, r));
                return GetOwnerID(r.GetIndex());
            }

            /*number*/ GetOwnerIDByHandle(handle /*CsRoutineHandle*/)
            {
                let container = this.GetRoutineContainer(handle);

                if (IsValidObject(container))
                    return this.GetOwnerIDByRoutine(container.Get());
                return INDEX_NONE;
            }

            // #endregion Owner

            // Schedule
            // #region Schedule
            // public:

            SetGroup(group /*ECsUpdateGroup*/)
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
            * @param {CsRoutineHandle}          handle
            * @returns {FJsResourceContainer}
            */
            /*FJsResourceContainer*/ GetRoutineContainer(handle /*CsRoutineHandle*/)
            {
                let context = Custom_Str.GetRoutineContainer;
                
                check(IsInstanceOfChecked(context, handle, CsRoutineHandle));

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
            /*boolean*/ IsHandleValid(handle /*CsRoutineHandle*/)
            {
                return this.GetRoutineContainer(handle) != null;
            }

            /**
             * @param {CsRoutineHandle} handle 
             * @returns {boolean}
             */
            /*boolean*/ IsRunning(handle /*CsRoutineHandle*/)
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
            * @param {number}               ownerID             int 
            * @param {FJsResourceContainer} payloadContainer
            * @returns {CsRoutineHandle}
            */
            /*CsRoutineHandle*/ StartByContainer(ownerID /*number*/, payloadContainer /*FJsResourceContainer*/)
            {
                let context = Custom_Str.StartByContainer;
                
                check(this.Manager_OwnerID.IsAllocatedChecked(context, ownerID));
                
                /** @type {NJsCoroutine_NPayload_FImpl}*/
                let payload = payloadContainer.Get();

                checkf(IsValidObject(payload), context + ": payloadContainer does NOT contain a reference to a payload.");
                check(payload.IsValidChecked(context));
                checkf(IsEqual_UpdateGroup(this.Group, payload.Group), context + ": Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, this.Group.Name_Internal);

                /** @type {FJsRoutine} */
                let r = this.Manager_Routine.AllocateResource();

                checkf(this.RoutineStrideByOwnerID[ownerID] < this.MaxRoutinesPerOwner, context + ": Owner ID: " +  ownerID + " has ALREADY allocated " + this.RoutineStrideByOwnerID[ownerID] + " Max Routines Per Owner: " + this.MaxRoutinesPerOwner + ".");
    
                let routineIdIndex		             = (ownerID * this.MaxRoutinesPerOwner) + this.RoutineStrideByOwnerID[ownerID];
                this.OwnerRoutineIDs[routineIdIndex] = r.GetIndex();

                ++this.RoutineStrideByOwnerID[ownerID];

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
            * @param {number}                       ownerID             int 
            * @param {NJsCoroutine_NPayload_FImpl}  payload
            * @returns {FJsRoutine}
            */
            /*CsRoutineHandle*/ Start(ownerID /*number*/, payload /*NJsCoroutine_NPayload_FImpl*/)
            {
                return this.StartByContainer(ownerID, this.GetPayloadContainer(payload));
            }

            /**
            * @param {number}               ownerID             int 
            * @param {FJsResourceContainer} payloadContainer
            * @returns {FJsRoutine}
            */
            /*CsRoutineHandle*/ StartChildByContainer(ownerID /*number*/, payloadContainer /*FJsResourceContainer*/)
            {
                let context = Custom_Str.StartChildByContainer;
                
                check(this.Manager_OwnerID.IsAllocatedChecked(context, ownerID));

                let payload = payloadContainer.Get();

                checkf(IsValidObject(payload), context + ": payloadContainer does NOT contain a reference to a payload.");
                checkf(payload.IsValidChecked(context));
                checkf(IsEqual_UpdateGroup(Group, payload.Group), context + ": Mismatch between payload.Group: %s and Group: %s", payload.Group.Name_Internal, Group.Name_Internal);

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

                checkf(this.RoutineStrideByOwnerID[ownerID] < this.MaxRoutinesPerOwner, context + ": Owner ID: " +  ownerID + " has ALREADY allocated " + this.RoutineStrideByOwnerID[ownerID] + " Max Routines Per Owner: " + this.MaxRoutinesPerOwner + ".");
    
                let routineIdIndex		             = (ownerID * this.MaxRoutinesPerOwner) + this.RoutineStrideByOwnerID[ownerID];
                this.OwnerRoutineIDs[routineIdIndex] = r.GetIndex();

                ++this.RoutineStrideByOwnerID[ownerID];

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
            * @param {number}                       ownerID         int
            * @param {NJsCoroutine_NPayload_FImpl}  payload
            * @returns {FJsRoutine}
            */
            /*CsRoutineHandle*/ StartChild(ownerID /*number*/, payload /*NJsCoroutine_NPayload_FImpl*/)
            {
                return this.StartChildByContainer(this.GetPayloadContainer(payload));
            }

            // #endregion Start

            // End
            // #region End
            // public:

            /**
            * End all coroutines.
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
            * End all routines associated with the ownerID.
            *
            * @param {number}           ownerID     int
            * @returns {boolean}			            Whether the routine has successful ended.
            *					                        NOTE: If the routine has already ended, this will return false.
            */
            /*boolean*/ End(ownerID /*number*/)
            {
                let context = Custom_Str.End;

                let result = false;

                if (!this.Manager_OwnerID.IsAllocated(ownerID))
                    return false;

                let start   = ownerID * this.MaxRoutinesPerOwner;
                let stride	= this.RoutineStrideByOwnerID[ownerID];
                        
                for (let i = 0; i < stride; ++i)
                {
                    let index        = start + i;
                    let routineIndex = this.OwnerRoutineIDs[index];

                    let routineContainer = this.Manager_Routine.GetAt(routineIndex);	
                    let r				 = routineContainer.Get();

                    // If the Routine is currently being Updated, queue the End for either the
                    // beginning of the next Update or the end of the current Update.
                    if (!r.IsUpdateComplete())
                    {
                        let handleStride = this.QueueEndHandleStrideByOwnerID[ownerID];
                        let handleIndex  = (ownerID * this.MaxRoutinesPerOwner) + handleStride;

                        this.OwnerQueueEndHandles[handleIndex] = r.GetHandle();

                        ++this.QueueEndHandleStrideByOwnerID[ownerID];
                        continue;
                    }
                    
                    if (!r.HasEnded())
                    {
                        r.End(EndReasonType.Shutdown);
                    }
                    //LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

                    r.Reset();
                    this.Manager_Routine.Deallocate(routineContainer);

                    result = true;
                }

                // Clear out routine information for ownerID
                this.RoutineStrideByOwnerID[ownerID] = 0;

                for (let i = 0; i < this.MaxRoutinesPerOwner; ++i)
                {
                    let index                   = start + i;
                    this.OwnerRoutineIDs[index] = INDEX_NONE;
                }
                return result;
            }

            /**
            * End the routine associated with the Handle.
            *
            * @param {number}           ownerID     int
            * @param {CsRoutineHandle}  handle          Handle to a routine.
            * @returns {boolean}			            Whether the routine has successful ended.
            *					                        NOTE: If the routine has already ended, this will return false.
            */
            /*boolean*/ EndHandle(ownerID /*number*/, handle /*CsRoutineHandle*/)
            {
                let context = Custom_Str.End;

                let container = this.GetRoutineContainer(handle);

                if (IsValidObject(container))
                {
                    let r = container.Get();

                    // If the Routine has already Ended, exit
                    if (r.HasEnded() ||
                        r.HasJustEnded())
                    {
                        return false;
                    }

                    check(this.Manager_OwnerID.IsAllocatedChecked(context, ownerID));

                    // If the Routine is currently being Updated, queue the End for either the
                    // beginning of the next Update or the end of the current Update.
                    if (!r.IsUpdateComplete())
                    {
                        let stride = this.QueueEndHandleStrideByOwnerID[ownerID];
                        let index  = (ownerID * this.MaxRoutinesPerOwner) + stride;

                        this.OwnerQueueEndHandles[index] = handle;

                        ++this.QueueEndHandleStrideByOwnerID[ownerID];
                        return false;
                    }

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
            /*boolean*/ HasEnded(handle /*CsRoutineHandle*/)
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
            /*boolean*/ HasJustEnded(handle /*CsRoutineHandle*/)
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
            * @param {number}       ownerID     int 
            * @param {CsDeltaTime}  deltaTime
            */
            Update(ownerID /*number*/, deltaTime /*CsDeltaTime*/)
            {
                let context = Custom_Str.Update;
                
                check(this.Manager_OwnerID.IsAllocatedChecked(context, ownerID));

                // End any pending Handles requested for End from the previous Update
                {
                    let stride = this.QueueEndHandleStrideByOwnerID[ownerID];
                    let start  = ownerID * this.MaxRoutinesPerOwner;
                    
                    for (let i = 0; i < stride; ++i)
                    {
                        let index   = start + i;
                        let handle  = this.OwnerQueueEndHandles[index];

                        this.End(ownerID, handle);

                        this.OwnerQueueEndHandles[index] = null;
                    }

                    this.QueueEndHandleStrideByOwnerID[ownerID] = 0;
                }

                {
                    let start  = ownerID * this.MaxRoutinesPerOwner;
                    let stride = this.RoutineStrideByOwnerID[ownerID];
                            
                    // Indices "with in" the Stride (local to the Stride, so in the Range [0, Stride - 1])
                    let indicesToDeallocate = [];

                    for (let i = 0; i < stride; ++i)
                    {
                        let index        = start + i;
                        let routineIndex = this.OwnerRoutineIDs[index];

                        let routineContainer = this.Manager_Routine.GetAt(routineIndex);
                        let r                = routineContainer.Get();

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

                            indicesToDeallocate.push(i);
                        }
                    }
                    
                    // "Bubble" the Routines that have Ended to the End of the Stride
                    for (let i = stride - 1; i >= 0; --i)
                    {
                        if (indicesToDeallocate.includes(i))
                            continue;
                    
                        for (let j = i; j < stride - 1; ++j)
                        {
                            let index                       = start + j;
                            let temp			            = this.OwnerRoutineIDs[index + 1];
                            this.OwnerRoutineIDs[index + 1] = this.OwnerRoutineIDs[index];
                            this.OwnerRoutineIDs[index]	    = temp;
                        }
                    }
                    
                    this.RoutineStrideByOwnerID[ownerID] -= indicesToDeallocate.length;
                }

                // End any Handles requested for End on the current Update
                {
                    let stride = this.QueueEndHandleStrideByOwnerID[ownerID];
                    let start  = ownerID * this.MaxRoutinesPerOwner;
                    
                    for (let i = 0; i < stride; ++i)
                    {
                        let index   = start + i;
                        let handle  = this.OwnerQueueEndHandles[index];

                        this.End(ownerID, handle);

                        this.OwnerQueueEndHandles[index] = null;
                    }

                    this.QueueEndHandleStrideByOwnerID[ownerID] = 0;
                }
            }

            // #endregion Update

            // Payload
            // #region Payload
            // public:

            /**
            *
            *
            * @returns {FJsResourceContainer}
            */
            /*FJsResourceContainer*/ AllocatePayloadContainer() { return this.Manager_Payload.Allocate(); }

            /**
            *
            *
            * @returns {NJsCoroutine_NPayload_FImpl}
            */
            /*NJsCoroutine_NPayload_FImpl*/ AllocatePayload() { return this.Manager_Payload.AllocateResource(); }

            // protected:

            /**
            *
            *
            * @param {NJsCoroutine_NPayload_FImpl} payload
            * @returns {FJsResourceContainer}               FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
            */
            /*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/ GetPayloadContainer(payload /*NJsCoroutine_NPayload_FImpl*/)
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
            // #region Message
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
        }
    }
};