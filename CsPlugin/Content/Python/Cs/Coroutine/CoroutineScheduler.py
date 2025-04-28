# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Math.py
import Cs.Library.Library_Math as Cs_Library_Math
# Coroutine
# - Cs/Coroutine/Types_Coroutine.py
import Cs.Coroutine.Types_Coroutine as Cs_Types_Coroutine
# - Cs/Coroutine/CoroutineSchedule.py
import Cs.Coroutine.CoroutineSchedule as Cs_CoroutineSchedule
# Resource
# - Cs/Managers/Resource/ResourceContainer.py
import Cs.Managers.Resource.ResourceContainer as Cs_ResourceContainer

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
PyMathLibrary = Cs_Library_Math.NPyMath.FLibrary

# "typedefs" - library (c++)
UpdateGroupLibrary = ue.CsScriptLibrary_UpdateGroup

# "typedefs" - class
DefaultScheduleType 	= Cs_CoroutineSchedule.NPyCoroutine.NSchedule.FDefault
CustomScheduleType 		= Cs_CoroutineSchedule.NPyCoroutine.NSchedule.FCustom
PayloadType             = Cs_Types_Coroutine.NPyCoroutine.NPayload.FImpl
FPyResourceContainer  	= Cs_ResourceContainer.FPyResourceContainer

# "typedefs" - functions
checkf	= CommonLibrary.checkf
check   = CommonLibrary.check

INDEX_NONE = -1

class FPyCoroutineScheduler:
	class NCached:
		class NStr:
			# Custom
			GetCustomSchedule				   = "FPyCoroutineScheduler.GetCustomSchedule"
			AllocateCustomGroupIndexAndOwnerID = "FPyCoroutineScheduler.AllocateCustomGroupIndexAndOwnerID"
			
	def __init__(self, core: any):
		# NOTE: FPyCore "typed" as any to prevent circular import
		self.Core = core
		
		count: int = UpdateGroupLibrary.get_count()

		self.DefaultSchedules: list[DefaultScheduleType] = [None] * count
		self.CustomSchedules: list[CustomScheduleType] = [None] * count

		# Default
		if True:
			# NOTE: UpdateGroup: Custom = 0
			#		 This is skipped for DefaultSchedules

			count: int = UpdateGroupLibrary.get_count()

			for i in range(0, count):
				schedule: DefaultScheduleType = DefaultScheduleType(self.Core)

				schedule.SetGroup(UpdateGroupLibrary.get_by_index(i))

				self.DefaultSchedules[i] = schedule
		# Custom
		if True:
			# TODO: Get from settings
			maxGroups: int = 4

			for i in range (0, maxGroups):
				schedule: CustomScheduleType = CustomScheduleType(self.Core)

				schedule.SetGroup(UpdateGroupLibrary.get("Custom"))

				self.CustomSchedules[i] = schedule

	def CleanUp(self):
		count: int = len(self.DefaultSchedules)

		for i in range(0, count):
			self.DefaultSchedules[i].EndAll()
		self.DefaultSchedules = []

    # Start
	#region Start
	# public:

	def StartByContainer(self, payloadContainer: FPyResourceContainer) -> ue.CsRoutineHandle:
		payload: PayloadType = payloadContainer.Get()

		return self.DefaultSchedules[payload.Group.value].StartByContainer(payloadContainer)

	def Start(self, payload: PayloadType) -> ue.CsRoutineHandle:
		return self.DefaultSchedules[payload.Group.value].Start(payload)

	def StartChildByContainer(self, payloadContainer: FPyResourceContainer) -> ue.CsRoutineHandle:
		payload: PayloadType = payloadContainer.Get()

		return self.DefaultSchedules[payload.Group.value].StartChildByContainer(payloadContainer)

	def StartChild(self, payload: PayloadType) -> ue.CsRoutineHandle:
		return self.DefaultSchedules[payload.Group.value].StartChild(payload)

	#endregion Start

	# Update
	#region Update
	# public:

	def Update(self, group: ue.ECsUpdateGroup, deltaTime: ue.CsDeltaTime): 
		self.DefaultSchedules[group.value].Update(deltaTime)

	#endregion Update

	# End
	#region End
	# public:

	def EndByGroup(self, group: ue.ECsUpdateGroup) -> bool:
		return self.DefaultSchedules[group.value].End()

	def EndByHandle(self, group: ue.ECsUpdateGroup, handle: ue.CsRoutineHandle) -> bool:
		return self.DefaultSchedules[group.value].End(handle)

	def EndAll(self):
		count: int = len(self.DefaultSchedules)

		for i in range(0, count):
			self.DefaultSchedules[i].EndAll()

	def HasEnded(self, group: ue.ECsUpdateGroup, handle: ue.CsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group and Handle has already ended.
		 NOTE: This returns True if Handle is NOT Valid.

		:param ue.ECsUpdateGroup group:
		:param ue.CsRoutineHandle handle:   Handle to a routine.
		:return bool:                       Whether the routine has already ended.
		""" 
		return self.DefaultSchedules[group.value].HasEnded(handle)

	def HasJustEnded(self, group: ue.ECsUpdateGroup, handle: ue.CsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group and Handle has just ended.

		:param ue.ECsUpdateGroup group:
		:param ue.CsRoutineHandle handle:   Handle to a routine.
		:return bool:                       Whether the routine has already ended.
		""" 
		return self.DefaultSchedules[group.value].HasJustEnded(handle)

	#endregion End

	# Payload
	#region Payload
	# public:

	def AllocatePayloadContainer(self, group: ue.ECsUpdateGroup) -> FPyResourceContainer:
		return self.DefaultSchedules[group.value].AllocatePayloadContainer()

	def AllocatePayload(self, group: ue.ECsUpdateGroup) -> PayloadType:
		return self.DefaultSchedules[group.value].AllocatePayload()

	#endregion Payload

	# Handle
	#region Handle
	# public:

	def IsHandleValid(self, group: ue.ECsUpdateGroup, handle: ue.CsRoutineHandle) -> bool:
		return self.DefaultSchedules[group.value].GetRoutineContainer(handle) != None

	def IsRunning(self, group: ue.ECsUpdateGroup, handle: ue.CsRoutineHandle) -> bool:
		return self.DefaultSchedules[group.value].IsRunning(handle)

	#endregion Handle

	# Custom
	#region Custom
	# public:

	def IsValidGroupIndexChecked(self, context: str, groupIndex: int) -> bool:
		check(PyMathLibrary.IsIntInRangeInclusiveChecked(context, groupIndex, 0, len(self.CustomSchedules)))
		return True

	# private:

	def GetCustomSchedule(self, groupIndex: int) -> CustomScheduleType:
		context: str = FPyCoroutineScheduler.NCached.NStr.GetCustomSchedule
		
		check(self.IsValidGroupIndexChecked(context, groupIndex))
		
		return self.CustomSchedules[groupIndex]

	#endregion Custom

	# Owner
	#region Owner
	# public:

	def AllocateCustomGroupIndexAndOwnerID(self) -> dict[int, int]:
		"""
		:return dict[int, int]:	{"GroupIndex": int, "OwnerID": int}
		""" 
		context: str = FPyCoroutineScheduler.NCached.NStr.AllocateCustomGroupIndexAndOwnerID

		count: int = len(self.CustomSchedules)

		output: dict[int, int] = {"GroupIndex": INDEX_NONE, "OwnerID": INDEX_NONE}
		
		for i in range(0, count):
			schedule: CustomScheduleType = self.CustomSchedules[i]
			
			if schedule.HasFreeOwnerID() == True:
				output["OwnerID"]	 = schedule.AllocateOwnerID()
				output["GroupIndex"] = i
				return output
		checkf(0, context + ": All Custom Schedules are Exhausted.")
		return output

	def DeallocateOwnerID(self, groupIndex: int, ownerID: int):
		self.GetCustomSchedule(groupIndex).DeallocateOwnerID(ownerID)

	#endregion Owner

	# Start
	#region Start
	# public:

	def CustomStartByContainer(self, groupIndex: int, ownerID: int, payloadContainer: FPyResourceContainer) -> ue.CsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).Start(ownerID, payloadContainer)
	
	def CustomStart(self, groupIndex: int, ownerID: int, payload: PayloadType) -> ue.CsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).Start(ownerID, payload)

	def CustomStartChildByContainer(self, groupIndex: int, ownerID: int, payloadContainer: FPyResourceContainer) -> ue.CsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).StartChild(ownerID, payloadContainer)

	def CustomStartChild(self, groupIndex: int, ownerID: int, payload: PayloadType) -> ue.CsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).StartChild(ownerID, payload)
	
	#endregion Start

	# Update
	#region Update
	# public:

	def CustomUpdate(self, groupIndex: int, ownerID: int, deltaTime:  ue.CsDeltaTime):
		self.GetCustomSchedule(groupIndex).Update(ownerID, deltaTime)

	#endregion Update

	# End
	#region End
	# public:

	def CustomEnd(self, groupIndex: int, handle: ue.CsRoutineHandle) -> bool:
		return self.GetCustomSchedule(groupIndex).End(groupIndex, handle)

	def HasCustomEnded(self, groupIndex: int, handle: ue.CsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group: Custom, GroupIndex and Handle has already ended.
		 NOTE: This returns True if Handle is NOT Valid.

		:param int groupIndex:
		:param ue.CsRoutineHandle handle:   Handle to a routine.
		:return bool:                       Whether the routine has already ended.
		""" 
		return self.GetCustomSchedule(groupIndex).HasEnded(handle)

	def HasCustomJustEnded(self, groupIndex: int, handle: ue.CsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group: Custom, GroupIndex and Handle has just ended.

		:param int groupIndex:
		:param ue.CsRoutineHandle handle:   Handle to a routine.
		:return bool:                       Whether the routine has already ended.
		""" 
		return self.GetCustomSchedule(groupIndex).HasJustEnded(handle)

	#endregion End

	# Payload
	#region Payload
	# public:

	def AllocateCustomPayloadContainer(self, groupIndex: int) -> FPyResourceContainer:
		return self.GetCustomSchedule(groupIndex).AllocatePayloadContainer()

	def AllocateCustomPayload(self, groupIndex: int) -> PayloadType:
		return self.GetCustomSchedule(groupIndex).AllocatePayload()

	#endregion Payload

	# Handle
	#region Handle
	# public:

	def IsCustomHandleValid(self, groupIndex: int, handle: ue.CsRoutineHandle) -> bool:
		return self.GetCustomSchedule(groupIndex).GetRoutineContainer(handle) != None

	def IsCustomRunning(self, groupIndex: int, handle: ue.CsRoutineHandle) -> bool:
		return self.GetCustomSchedule(groupIndex).IsRunning(handle)

	#endregion Handle