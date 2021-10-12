/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Coroutine
var FJsCoroutineSchedule = require('Cs/Coroutine/CoroutineSchedule.js');

var Core;

module.exports = class FJCoroutineScheduler
{
    constructor(core)
    {
		Core = core;
		
		this.Schedules = [];

		let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
		let count			   = UpdateGroupLibrary.GetCount();

		for (let i = 0; i < count; ++i)
		{
			let schedule = new FJsCoroutineSchedule(Core);

			schedule.SetGroup(UpdateGroupLibrary.GetByIndex(i));

			this.Schedules.push(schedule);
        }
    }

	CleanUp()
	{
		for (let i = 0; i < this.Schedules.length; ++i)
		{
			this.Schedules[i].EndAll();
		}
		this.Schedules = [];
	}

    // Start
	// #region Start
	// public:

	/**
	*
	*
	* @param {FJsResourceContainer} payloadContainer	FJsResourceContainer <PayloadType>
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartByContainer(payloadContainer /*FJsResourceContainer<PayloadType>*/)
	{
		let payload = payloadContainer.Get();

		return this.Schedules[payload.Group.Value].StartByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param {NJsCoroutine.NPayload.FImpl} payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ Start(payload /*PayloadType*/) { return this.Schedules[payload.Group.Value].Start(payload); }

	/**
	*
	*
	* @param {FJsResourceContainer} payloadContainer	FJsResourceContainer <PayloadType>
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartChildByContainer(payloadContainer /*FJsResourceContainer<PayloadType>*/)
	{
		let payload = payloadContainer.Get();

		return this.Schedules[payload.Group.Value].StartChildByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param {NJsCoroutine.NPayload.FImpl} payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartChild(payload /*PayloadType*/) { return this.Schedules[payload.Group.Value].StartChild(payload); }

	// #endregion Start

	// Update
	// #region Update
	// public:

	/**
	*
	*
	* @param {ECsUpdateGroup} 	group
	* @param {CsDeltaTime}		deltaTime
	*/
	Update(group /*ECsUpdateGroup*/, deltaTime /*CsDeltaTime*/) { this.Schedules[group.Value].Update(deltaTime); }

	// #endregion Update

	// End
	// #region End
	// public:

	/**
	*
	*
	* @param {ECsUpdateGroup} 	group
	* @returns {boolean}
	*/
	/*bool*/ EndByGroup(group /*ECsUpdateGroup*/) { return this.Schedules[group.Value].End(); }

	/**
	*
	*
	* @param {ECsUpdateGroup} 	group
	* @param {CsRoutineHandle}	handle	Handle to a routine.
	* @returns {boolean}
	*/
	/*bool*/ EndByHandle(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/) { return this.Schedules[group.Value].End(handle); }

	/**
	*
	*/
	EndAll()
	{
		for (let i = 0; i < this.Schedules.length; ++i)
		{
			this.Schedules[i].EndAll();
		}
	}

	/**
	* Check if a routine associated with the Group and Handle has already ended.
	* NOTE: This returns True if Handle is NOT Valid.
	* 
	* @param {ECsUpdateGroup} 	group
	* @param {CsRoutineHandle}	handle		Handle to a routine.
	* @returns {boolean}					Whether the routine has already ended.
	*/
	/*bool*/ HasEnded(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/) { return this.Schedules[group.Value].HasEnded(handle); }

	/**
	* Check if a routine associated with the Group and Handle has just ended.
	*
	* @param {ECsUpdateGroup} 	group
	* @param {CsRoutineHandle}	handle		Handle to a routine.
	* @returns {boolean}					Whether the routine has just ended.
	*/
	/*bool*/ HasJustEnded(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/) { return this.Schedules[group.Value].HasJustEnded(handle); }

	// #endregion End

	// Payload
	// #region Payload
	// public:

	/**
	*
	*
	* @param {ECsUpdateGroup} group
	* @returns {FJsResourceContainer} FJsResourceContainer < PayloadType >
	*/
	/*FJsResourceContainer<PayloadType>*/ AllocatePayloadContainer(group /*ECsUpdateGroup*/) { return this.Schedules[group.Value].AllocatePayloadContainer(); }

	/**
	*
	*
	* @param {ECsUpdateGroup} group
	* @returns {NJsCoroutine.NPayload.FImpl} PayloadType
	*/
	/*PayloadType*/ AllocatePayload(group /*ECsUpdateGroup*/) { return this.Schedules[group.Value].AllocatePayload(); }

	// #endregion Payload

	// Handle
	// #region
	// public:

	/**
	* 
	* 
	* @param {ECsUpdateGroup} group
	* @param {CsRoutineHandle} handle
	* @returns {boolean}
	*/
	/*bool*/ IsHandleValid(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/)
	{
		return this.Schedules[group.Value].GetRoutineContainer(handle) != null;
	}

	/**
	* 
	* 
	* @param {ECsUpdateGroup} group
	* @param {CsRoutineHandle} handle
	* @returns {boolean}
	*/
	/*bool*/ IsRunning(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/)
	{
		return this.Schedules[group.Value].IsRunning(handle);
	}

	// #endregion Handle
};