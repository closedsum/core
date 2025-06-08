# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import unreal as ue
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    # Core
    # - Cs/Core/Core.py
    import Cs.Core as Cs_Core

if TYPE_CHECKING:
    # "alias" - class (py)
    FPyCore = Cs_Core.FPyCore

# IMPORT

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

# ALIAS

# "alias" - library (c++)
CsObjectLibrary = ue.CsScriptLibrary_Object
CsUpdateGroupLibrary = ue.CsScriptLibrary_UpdateGroup

# "alias" - class (c++)
UObject = ue.Object

# "alias" struct (c++)
FCsRoutineHandle = ue.CsRoutineHandle
FCsDeltaTime = ue.CsDeltaTime
	# enum
FECsUpdateGroup = ue.ECsUpdateGroup

# "alias" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
PyMathLibrary = Cs_Library_Math.NPyMath.FLibrary

# "alias" - class (py)
DefaultScheduleType 	= Cs_CoroutineSchedule.NPyCoroutine.NSchedule.FDefault
CustomScheduleType 		= Cs_CoroutineSchedule.NPyCoroutine.NSchedule.FCustom
PayloadType             = Cs_Types_Coroutine.NPyCoroutine.NPayload.FImpl
FPyResourceContainer  	= Cs_ResourceContainer.FPyResourceContainer

# "alias" - functions (py)
checkf					= CommonLibrary.checkf
check   				= CommonLibrary.check
IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked

INDEX_NONE = -1

class FPyCoroutineScheduler:
	def __init__(self, core: 'FPyCore'):
		self.Core: 'FPyCore' = core
		
		count: int = CsUpdateGroupLibrary.get_count()

		self.DefaultSchedules: list[DefaultScheduleType] = [None] * count
		self.CustomSchedules: list[CustomScheduleType] = [None] * count

		# Default
		if True:
			# NOTE: UpdateGroup: Custom = 0
			#		 This is skipped for DefaultSchedules

			count: int = CsUpdateGroupLibrary.get_count()

			for i in range(0, count):
				schedule: DefaultScheduleType = DefaultScheduleType(self.Core)

				schedule.SetGroup(CsUpdateGroupLibrary.get_by_index(i))

				self.DefaultSchedules[i] = schedule
		# Custom
		if True:
			# TODO: Get from settings
			maxGroups: int = 4

			for i in range (0, maxGroups):
				schedule: CustomScheduleType = CustomScheduleType(self.Core)

				schedule.SetGroup(CsUpdateGroupLibrary.get("Custom"))

				self.CustomSchedules[i] = schedule

	def CleanUp(self):
		count: int = len(self.DefaultSchedules)

		for i in range(0, count):
			self.DefaultSchedules[i].EndAll()
		self.DefaultSchedules = []

    # Start
	#region Start
	# public:

	def StartByContainer(self, payloadContainer: FPyResourceContainer) -> FCsRoutineHandle:
		payload: PayloadType = payloadContainer.Get()

		return self.DefaultSchedules[payload.Group.value].StartByContainer(payloadContainer)

	def Start(self, payload: PayloadType) -> FCsRoutineHandle:
		return self.DefaultSchedules[payload.Group.value].Start(payload)

	def StartChildByContainer(self, payloadContainer: FPyResourceContainer) -> FCsRoutineHandle:
		payload: PayloadType = payloadContainer.Get()

		return self.DefaultSchedules[payload.Group.value].StartChildByContainer(payloadContainer)

	def StartChild(self, payload: PayloadType) -> FCsRoutineHandle:
		return self.DefaultSchedules[payload.Group.value].StartChild(payload)

	def SetupAndStartUObject(self, obj: UObject, group: str, func: any) -> FCsRoutineHandle:
		context: str = __class__.SetupAndStartUObject.__qualname__

		# TODO: update type for func
			
		check(CsObjectLibrary.is_valid_object(obj))
		check(IsStringNotEmptyChecked(context, group))

		# TODO: Check if group is valid

		group: FECsUpdateGroup  = CsUpdateGroupLibrary.get("GameState")
		payload: PayloadType    = self.AllocatePayload(group)

		payload.CoroutineImpl = func
		payload.Owner.SetObject(obj)

		return self.Start(payload)

	#endregion Start

	# Update
	#region Update
	# public:

	def Update(self, group: FECsUpdateGroup, deltaTime: FCsDeltaTime): 
		self.DefaultSchedules[group.value].Update(deltaTime)

	#endregion Update

	# End
	#region End
	# public:

	def EndByGroup(self, group: FECsUpdateGroup) -> bool:
		return self.DefaultSchedules[group.value].End()

	def EndByHandle(self, group: FECsUpdateGroup, handle: FCsRoutineHandle) -> bool:
		return self.DefaultSchedules[group.value].End(handle)

	def EndAll(self):
		count: int = len(self.DefaultSchedules)

		for i in range(0, count):
			self.DefaultSchedules[i].EndAll()

	def HasEnded(self, group: FECsUpdateGroup, handle: FCsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group and Handle has already ended.
		 NOTE: This returns True if Handle is NOT Valid.

		:param ue.ECsUpdateGroup group:
		:param FCsRoutineHandle handle:   Handle to a routine.
		:return bool:                       Whether the routine has already ended.
		""" 
		return self.DefaultSchedules[group.value].HasEnded(handle)

	def HasJustEnded(self, group: FECsUpdateGroup, handle: FCsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group and Handle has just ended.

		:param ue.ECsUpdateGroup group:
		:param FCsRoutineHandle handle:   Handle to a routine.
		:return bool:                       Whether the routine has already ended.
		""" 
		return self.DefaultSchedules[group.value].HasJustEnded(handle)

	#endregion End

	# Payload
	#region Payload
	# public:

	def AllocatePayloadContainer(self, group: FECsUpdateGroup) -> FPyResourceContainer:
		return self.DefaultSchedules[group.value].AllocatePayloadContainer()

	def AllocatePayload(self, group: FECsUpdateGroup) -> PayloadType:
		return self.DefaultSchedules[group.value].AllocatePayload()

	#endregion Payload

	# Handle
	#region Handle
	# public:

	def IsHandleValid(self, group: FECsUpdateGroup, handle: FCsRoutineHandle) -> bool:
		return self.DefaultSchedules[group.value].GetRoutineContainer(handle) != None

	def IsRunning(self, group: FECsUpdateGroup, handle: FCsRoutineHandle) -> bool:
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
		context: str = __class__.GetCustomSchedule.__qualname__
		
		check(self.IsValidGroupIndexChecked(context, groupIndex))
		
		return self.CustomSchedules[groupIndex]

	#endregion Custom

	# Owner
	#region Owner
	# public:

	def AllocateCustomGroupIndexAndOwnerID(self) -> dict[int, int]:
		"""
		Allocate a GroupIndex and OwnerID for a Custom Schedule.

		:return dict[int, int]:	{"GroupIndex": int, "OwnerID": int}
		""" 
		context: str = __class__.AllocateCustomGroupIndexAndOwnerID.__qualname__

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

	def CustomStartByContainer(self, groupIndex: int, ownerID: int, payloadContainer: FPyResourceContainer) -> FCsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).Start(ownerID, payloadContainer)
	
	def CustomStart(self, groupIndex: int, ownerID: int, payload: PayloadType) -> FCsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).Start(ownerID, payload)

	def CustomStartChildByContainer(self, groupIndex: int, ownerID: int, payloadContainer: FPyResourceContainer) -> FCsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).StartChild(ownerID, payloadContainer)

	def CustomStartChild(self, groupIndex: int, ownerID: int, payload: PayloadType) -> FCsRoutineHandle:
		return self.GetCustomSchedule(groupIndex).StartChild(ownerID, payload)
	
	#endregion Start

	# Update
	#region Update
	# public:

	def CustomUpdate(self, groupIndex: int, ownerID: int, deltaTime: FCsDeltaTime):
		self.GetCustomSchedule(groupIndex).Update(ownerID, deltaTime)

	#endregion Update

	# End
	#region End
	# public:

	def CustomEnd(self, groupIndex: int, handle: FCsRoutineHandle) -> bool:
		return self.GetCustomSchedule(groupIndex).End(groupIndex, handle)

	def HasCustomEnded(self, groupIndex: int, handle: FCsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group: Custom, GroupIndex and Handle has already ended.
		 NOTE: This returns True if Handle is NOT Valid.

		:param int groupIndex:
		:param FCsRoutineHandle handle:   Handle to a routine.
		:return bool:                       Whether the routine has already ended.
		""" 
		return self.GetCustomSchedule(groupIndex).HasEnded(handle)

	def HasCustomJustEnded(self, groupIndex: int, handle: FCsRoutineHandle) -> bool:
		"""
		Check if a routine associated with the Group: Custom, GroupIndex and Handle has just ended.

		:param int groupIndex:
		:param FCsRoutineHandle handle:   Handle to a routine.
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

	def IsCustomHandleValid(self, groupIndex: int, handle: FCsRoutineHandle) -> bool:
		return self.GetCustomSchedule(groupIndex).GetRoutineContainer(handle) != None

	def IsCustomRunning(self, groupIndex: int, handle: FCsRoutineHandle) -> bool:
		return self.GetCustomSchedule(groupIndex).IsRunning(handle)

	#endregion Handle