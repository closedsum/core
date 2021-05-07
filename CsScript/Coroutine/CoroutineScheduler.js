/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var FJsCoroutineSchedule = require('Cs/Coroutine/CoroutineSchedule.js');

module.exports = class FJCoroutineScheduler
{
    constructor()
    {
		this.Schedules = [];

		let UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;
		let count			   = UpdateGroupLibrary.GetCount();

		for (let i = 0; i < count; ++i)
		{
			let schedule = new FJsCoroutineSchedule();

			schedule.SetGroup(UpdateGroupLibrary.GetByIndex(i));

			this.Schedules.push(schedule);
        }
    }

	CleanUp()
	{
		for (let i = 0; i < this.Schedules.length; ++i)
		{
			this.Schedules.EndAll();
		}
		this.Schedules = [];
	}

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

		return this.Schedules[payload.Group.Value].StartByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param payload
	* return
	*/
	Start(payload) { return this.Schedules[payload.Group.Value].Start(payload); }

	/**
	*
	*
	* @param payloadContainer
	* return
	*/
	StartChildByContainer(payloadContainer)
	{
		let payload = payloadContainer.Get();

		return this.Schedules[payload.Group.Value].StartChildByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param payload
	* return
	*/
	StartChild(payload) { return this.Schedules[payload.Group.Value].StartChild(payload); }

	// #endregion Start

	// Update
	// #region Update
	// public:

	/**
	*
	*
	* @param group
	* @param deltaTime
	*/
	Update(group, deltaTime) { this.Schedules[group.Value].Update(deltaTime); }

	// #endregion Update

	// End
	// #region End
	// public:

	/**
	*
	*
	* @param group
	* return
	*/
	EndByGroup(group) { return this.Schedules[group.Value].End(); }

	/**
	*
	*
	* @param group
	* @param handle
	* return
	*/
	EndByHandle(group, handle) { return this.Schedules[group.Value].End(handle); }

	/**
	*
	*/
	EndAll()
	{
		for (i = 0; i < Schedules.length; ++i)
		{
			this.Schedules[i].End();
		}
	}

	/**
	* Check if a routine associated with the Group and Handle has already ended.
	* NOTE: This returns True if Handle is NOT Valid.
	* 
	* @param group
	* @param handle		Handle to a routine.
	* return			Whether the routine has already ended.
	*/
	HasEnded(group, handle) { return this.Schedules[group.Value].HasEnded(handle); }

	/**
	* Check if a routine associated with the Group and Handle has just ended.
	*
	* @param group
	* @param handle		Handle to a routine.
	* return			Whether the routine has just ended.
	*/
	HasJustEnded(group, handle) { return this.Schedules[group.Value].HasJustEnded(handle); }

	// #endregion End

	// Payload
	// #region Payload
	// public:

	/**
	*
	*
	* @param group
	* return
	*/
	AllocatePayloadContainer(group) { return this.Schedules[group.Value].AllocatePayloadContainer(); }

	/**
	*
	*
	* @param group
	* return
	*/
	AllocatePayload(group) { return this.Schedules[group.Value].AllocatePayload(); }

	// #endregion Payload

	// Handle
	// #region
	// public:

	/**
	* 
	* 
	* @param group
	* @param handle
	* return
	*/
	IsHandleValid(group, handle)
	{
		return this.Schedules[group.Value].GetRoutineContainer(handle) != null;
	}

	/**
	* 
	* 
	* @param group
	* @param handle
	* return
	*/
	IsRunning(group, handle)
	{
		return this.Schedules[group.Value].IsRunning(handle);
	}

	// #endregion Handle
};