// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../Cs/custom_typings/Cs.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Coroutine
/// <reference path="../Coroutine/CoroutineSchedule.ts">/>

"use strict"

// Coroutine
/** @type {FJsCoroutineSchedule} */
var FJsCoroutineSchedule = require('Cs/Coroutine/CoroutineSchedule.js');

// "typedefs" - library
var UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;

// Globals
/** @type {FJsCore} */ var Core;

module.exports = class FJCoroutineScheduler
{
    constructor(core)
    {
		Core = core;
		
		/** @type {FJCoroutineSchedule}*/ this.Schedules = [];

		let count = UpdateGroupLibrary.GetCount();

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
	* @param {FJsResourceContainer} payloadContainer	FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartByContainer(payloadContainer /*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/)
	{
		let payload = payloadContainer.Get();

		return this.Schedules[payload.Group.Value].StartByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param {NJsCoroutine_NPayload_FImpl} payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ Start(payload /*NJsCoroutine_NPayload_FImpl*/) { return this.Schedules[payload.Group.Value].Start(payload); }

	/**
	*
	*
	* @param {FJsResourceContainer} payloadContainer	FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartChildByContainer(payloadContainer /*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/)
	{
		let payload = payloadContainer.Get();

		return this.Schedules[payload.Group.Value].StartChildByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param {NJsCoroutine_NPayload_FImpl} payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartChild(payload /*NJsCoroutine_NPayload_FImpl*/) { return this.Schedules[payload.Group.Value].StartChild(payload); }

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
	/*boolean*/ EndByGroup(group /*ECsUpdateGroup*/) { return this.Schedules[group.Value].End(); }

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
	* @returns {FJsResourceContainer} FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
	*/
	/*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/ AllocatePayloadContainer(group /*ECsUpdateGroup*/) { return this.Schedules[group.Value].AllocatePayloadContainer(); }

	/**
	*
	*
	* @param {ECsUpdateGroup} group
	* @returns {NJsCoroutine_NPayload_FImpl} PayloadType
	*/
	/*NJsCoroutine_NPayload_FImpl*/ AllocatePayload(group /*ECsUpdateGroup*/) { return this.Schedules[group.Value].AllocatePayload(); }

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
	/*boolean*/ IsHandleValid(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/)
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
	/*boolean*/ IsRunning(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/)
	{
		return this.Schedules[group.Value].IsRunning(handle);
	}

	// #endregion Handle
};