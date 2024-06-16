// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../Cs/custom_typings/Cs.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Coroutine
/// <reference path="../Coroutine/CoroutineSchedule.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsMath = require('Cs/Library/Library_Math.js');
// Coroutine
var NJsCoroutine = require('Cs/Coroutine/CoroutineSchedule.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;
/** @type {JsMathLibrary} */ var JsMathLibrary = NJsMath.FLibrary;

// "typedefs" - library (c++)
var UpdateGroupLibrary = CsScriptLibrary_UpdateGroup;

// "typedefs" - functions
var checkf	= CommonLibrary.checkf;
var check   = CommonLibrary.check;

// Globals
/** @type {FJsCore} */ var Core;
/** @type {FJCoroutineScheduler} */              var ClassType = null;
/** @type {FJCoroutineScheduler.NCached.NStr} */ var Str = null;

var ClassName = "FJCoroutineScheduler";

const INDEX_NONE = -1;

module.exports = class FJCoroutineScheduler
{
	static NCached = class Cached
	{
		static NStr = class Str
		{
			// Custom
			static GetCustomSchedule	= ClassName + ".GetCustomSchedule";
			static AllocateCustomGroupIndexAndOwnerID = ClassName + ".AllocateCustomGroupIndexAndOwnerID";
		}
	}

    constructor(core)
    {
		ClassType = FJCoroutineScheduler;
        Str       = ClassType.NCached.NStr;

		Core = core;
		
		/** @type {NJsCoroutine_NSchedule_FDefault} */ 	this.DefaultSchedules = [];
		/** @type {NJsCoroutine_NSchedule_FCustom} */ 	this.CustomSchedules = [];

		// Default
		{
			// NOTE: UpdateGroup: Custom = 0
			//		 This is skipped for DefaultSchedules

			let count = UpdateGroupLibrary.GetCount();

			for (let i = 1; i < count; ++i)
			{
				let schedule = new NJsCoroutine.NSchedule.FDefault(Core);

				schedule.SetGroup(UpdateGroupLibrary.GetByIndex(i));

				this.DefaultSchedules[i] = schedule;
			}
		}
		// Custom
		{
			// TODO: Get from settings
			let maxGroups = 4;

			for (let i = 0; i < maxGroups; ++i)
				{
					let schedule = new NJsCoroutine.NSchedule.FCustom(Core);

					schedule.SetGroup(UpdateGroupLibrary.Get("Custom"));
	
					this.CustomSchedules[i] = schedule;
				}
		}
    }

	CleanUp()
	{
		for (let i = 0; i < this.DefaultSchedules.length; ++i)
		{
			this.DefaultSchedules[i].EndAll();
		}
		this.DefaultSchedules = [];
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

		return this.DefaultSchedules[payload.Group.Value].StartByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param {NJsCoroutine_NPayload_FImpl} payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ Start(payload /*NJsCoroutine_NPayload_FImpl*/) { return this.DefaultSchedules[payload.Group.Value].Start(payload); }

	/**
	*
	*
	* @param {FJsResourceContainer} payloadContainer	FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartChildByContainer(payloadContainer /*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/)
	{
		let payload = payloadContainer.Get();

		return this.DefaultSchedules[payload.Group.Value].StartChildByContainer(payloadContainer);
	}

	/**
	*
	*
	* @param {NJsCoroutine_NPayload_FImpl} payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ StartChild(payload /*NJsCoroutine_NPayload_FImpl*/) { return this.DefaultSchedules[payload.Group.Value].StartChild(payload); }

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
	Update(group /*ECsUpdateGroup*/, deltaTime /*CsDeltaTime*/) { this.DefaultSchedules[group.Value].Update(deltaTime); }

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
	/*boolean*/ EndByGroup(group /*ECsUpdateGroup*/) { return this.DefaultSchedules[group.Value].End(); }

	/**
	*
	*
	* @param {ECsUpdateGroup} 	group
	* @param {CsRoutineHandle}	handle	Handle to a routine.
	* @returns {boolean}
	*/
	/*bool*/ EndByHandle(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/) { return this.DefaultSchedules[group.Value].End(handle); }

	/**
	*
	*/
	EndAll()
	{
		for (let i = 0; i < this.DefaultSchedules.length; ++i)
		{
			this.DefaultSchedules[i].EndAll();
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
	/*bool*/ HasEnded(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/) { return this.DefaultSchedules[group.Value].HasEnded(handle); }

	/**
	* Check if a routine associated with the Group and Handle has just ended.
	*
	* @param {ECsUpdateGroup} 	group
	* @param {CsRoutineHandle}	handle		Handle to a routine.
	* @returns {boolean}					Whether the routine has just ended.
	*/
	/*bool*/ HasJustEnded(group /*ECsUpdateGroup*/, handle /*CsRoutineHandle*/) { return this.DefaultSchedules[group.Value].HasJustEnded(handle); }

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
	/*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/ AllocatePayloadContainer(group /*ECsUpdateGroup*/) { return this.DefaultSchedules[group.Value].AllocatePayloadContainer(); }

	/**
	*
	*
	* @param {ECsUpdateGroup} group
	* @returns {NJsCoroutine_NPayload_FImpl} PayloadType
	*/
	/*NJsCoroutine_NPayload_FImpl*/ AllocatePayload(group /*ECsUpdateGroup*/) { return this.DefaultSchedules[group.Value].AllocatePayload(); }

	// #endregion Payload

	// Handle
	// #region Handle
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
		return this.DefaultSchedules[group.Value].GetRoutineContainer(handle) != null;
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
		return this.DefaultSchedules[group.Value].IsRunning(handle);
	}

	// #endregion Handle

	// Custom
	// #region Custom
	// public:

	/**
	* @param {string} 	context 
	* @param {number} 	groupIndex 	int
	* @returns {bolean}
	*/
	/*boolean*/ IsValidGroupIndexChecked(context /*string*/, groupIndex /*number*/)
	{
		check(JsMathLibrary.IsIntInRangeInclusiveChecked(context, groupIndex, 0, this.CustomSchedules.length));
		return true;
	}

	// private:

	/*NJsCoroutine.NSchedule.FCustom*/ GetCustomSchedule(groupIndex /*number*/)
	{
		let context = Str.GetCustomSchedule;
		
		check(this.IsValidGroupIndexChecked(context, groupIndex));
		
		return this.CustomSchedules[groupIndex];
	}

	// #endregion Custom

	// Owner
	// #region Owner
	// public:

	/**
	* @returns {{GroupIndex: number, OwnerID: number}}
	*/
	/*{GroupIndex: number, OwnerID: number}*/ AllocateCustomGroupIndexAndOwnerID()
	{
		let context = Str.AllocateCustomGroupIndexAndOwnerID;

		let count = this.CustomSchedules.length;

		let output = {GroupIndex: INDEX_NONE, OwnerID: INDEX_NONE};
		
		for (let i = 0; i < count; ++i)
		{
			let schedule = this.CustomSchedules[i];
			
			if (schedule.HasFreeOwnerID())
			{
				output.OwnerID	 = schedule.AllocateOwnerID();
				output.GroupIndex = i;
				return output;
			}
		}
		checkf(0, context + ": All Custom Schedules are Exhausted.");
		return output;
	}

	DeallocateOwnerID(groupIndex /*number*/, ownerID /*number*/)
	{
		this.GetCustomSchedule(groupIndex).DeallocateOwnerID(ownerID);
	}

	// #endregion Owner

	// Start
	// #region Start
	// public:

	/**
	* @param {number}				groupIndex			int
	* @param {number}				ownerID				int
	* @param {FJsResourceContainer} payloadContainer	FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ CustomStartByContainer(groupIndex /*number*/, ownerID /*number*/, payloadContainer /*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/)
	{
		return this.GetCustomSchedule(groupIndex).Start(ownerID, payloadContainer);
	}

	/**
	/**
	* @param {number}						groupIndex			int
	* @param {number}						ownerID				int
	* @param {NJsCoroutine_NPayload_FImpl} 	payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ CustomStart(groupIndex /*number*/, ownerID /*number*/, payload /*NJsCoroutine_NPayload_FImpl*/)
	{
		return this.GetCustomSchedule(groupIndex).Start(ownerID, payload);
	}

	/**
	* @param {number}				groupIndex			int
	* @param {number}				ownerID				int
	* @param {FJsResourceContainer} payloadContainer	FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ CustomStartChildByContainer(groupIndex /*number*/, ownerID /*number*/, payloadContainer /*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/)
	{
		return this.GetCustomSchedule(groupIndex).StartChild(ownerID, payloadContainer);
	}

	/**
	* @param {number}						groupIndex			int
	* @param {number}						ownerID				int
	* @param {NJsCoroutine_NPayload_FImpl} 	payload
	* @returns {CsRoutineHandle}
	*/
	/*CsRoutineHandle*/ CustomStartChild(groupIndex /*number*/, ownerID /*number*/, payload /*NJsCoroutine_NPayload_FImpl*/)
	{
		return this.GetCustomSchedule(groupIndex).StartChild(ownerID, payload);
	}

	// #endregion Start

	// Update
	// #region Update
	// public:

	/**
	* @param {number}		groupIndex			int
	* @param {number}		ownerID				int
	* @param {CsDeltaTime} 	deltaTime
	*/
	CustomUpdate(groupIndex /*number*/, ownerID /*number*/, deltaTime /*CsDeltaTime*/)
	{
		this.GetCustomSchedule(groupIndex).Update(ownerID, deltaTime);
	}

	// #endregion Update

	// End
	// #region End
	// public:

	/**
	* @param {number}			groupIndex	int
	* @param {CsRoutineHandle}	handle
	* @returns {boolean}
	*/
	/*boolean*/ CustomEnd(groupIndex /*number*/, handle /*CsRoutineHandle*/)
	{
		return this.GetCustomSchedule(groupIndex).End(groupIndex, handle);
	}

	/**
	* Check if a routine associated with the Group: Custom, GroupIndex and Handle has already ended.
	* NOTE: This returns True if Handle is NOT Valid.
	* 
	* @param {number}			groupIndex	int
	* @param {CsRoutineHandle}	handle
	* @returns {boolean}					Whether the routine has already ended.
	*/
	/*boolean*/ HasCustomEnded(groupIndex /*number*/, handle /*CsRoutineHandle*/)
	{
		return this.GetCustomSchedule(groupIndex).HasEnded(handle);
	}

	/**
	* Check if a routine associated with the Group: Custom, GroupIndex and Handle has just ended.
	*
	* @param {number}			groupIndex	int
	* @param {CsRoutineHandle}	handle	Handle to a routine.
	* @returns {boolean}				Whether the routine has just ended.
	*/
	/*boolean*/ HasCustomJustEnded(groupIndex /*number*/, handle /*CsRoutineHandle*/)
	{
		return this.GetCustomSchedule(groupIndex).HasJustEnded(handle);
	}

	// #endregion End

	// Payload
	// #region Payload
	// public:

	/**
	* @param {number} 					groupIndex	int
	* @returns {FJsResourceContainer} 				FJsResourceContainer<NJsCoroutine_NPayload_FImpl>
	*/
	/*FJsResourceContainer<NJsCoroutine_NPayload_FImpl>*/ AllocateCustomPayloadContainer(groupIndex /*number*/) 
	{ 
		return this.GetCustomSchedule(groupIndex).AllocatePayloadContainer(); 
	}

	/**
	* @param {number} 							groupIndex	int
	* @returns {NJsCoroutine_NPayload_FImpl} 				PayloadType
	*/
	/*NJsCoroutine_NPayload_FImpl*/ AllocateCustomPayload(groupIndex /*number*/) 
	{
		return this.GetCustomSchedule(groupIndex).AllocatePayload(); 
	}

	// #endregion Payload

	// Handle
	// #region Handle
	// public:

	/**
	* @param {number} 			groupIndex	int
	* @param {CsRoutineHandle} 	handle
	* @returns {boolean}
	*/
	/*boolean*/ IsCustomHandleValid(groupIndex /*number*/, handle /*CsRoutineHandle*/)
	{
		return this.GetCustomSchedule(groupIndex).GetRoutineContainer(handle) != null;
	}

	/**
	* @param {number} 			groupIndex	int
	* @param {CsRoutineHandle} handle
	* @returns {boolean}
	*/
	/*boolean*/ IsCustomRunning(groupIndex /*number*/, handle /*CsRoutineHandle*/)
	{
		return this.GetCustomSchedule(groupIndex).IsRunning(handle);
	}

	// #endregion Handle
};