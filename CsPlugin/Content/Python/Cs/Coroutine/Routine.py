# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue
import copy

# Types
# - Cs/Coroutine/Types_Coroutine.py
import Cs.Coroutine.Types_Coroutine as Cs_Types_Coroutine
# - Cs/Types/Property/Property.py
import Cs.Types.Property.Property as Cs_Property
# - Cs/Types/Yield/Yield_Enum.py
import Cs.Types.Yield.Yield_Enum as Cs_Yield_Enum
# - Cs/Types/Yield/Yield_RoutineHandle.py
import Cs.Types.Yield.Yield_RoutineHandle as Cs_Yield_RoutineHandle
# - Cs/Types/Yield/Yield_Function.py
import Cs.Types.Yield.Yield_Function as Cs_Yield_Function
# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

INDEX_NONE = -1

EMPTY = 0

INVALID_LISTEN_MESSAGE = ""

ROUTINE_END = -1
ROUTINE_FREE = -2

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - library (c++)
UpdateGroupLibrary	= ue.CsScriptLibrary_UpdateGroup
TimeLibrary 		= ue.CsScriptLibrary_Time
RoutineLibrary 		= ue.CsScriptLibrary_Routine

# "typedefs" - classes
EnumYieldType 			= Cs_Yield_Enum.NPyYield.FEnum
RoutineHandleYieldType 	= Cs_Yield_RoutineHandle.NPyYield.FRoutineHandle
FunctionYieldType 	 	= Cs_Yield_Function.NPyYield.FFunction

# "typedefs" - function
check 				 = CommonLibrary.check
checkf 				 = CommonLibrary.checkf
IsValidObject 		 = CommonLibrary.IsValidObject
IsValidObjectChecked = CommonLibrary.IsValidObjectChecked

# "typedefs" - types
PayloadType		= Cs_Types_Coroutine.NPyCoroutine.NPayload.FImpl
FPyProperty 	= Cs_Property.FPyProperty
StateType 		= Cs_Types_Coroutine.NPyCoroutine.EState
EndReasonType 	= Cs_Types_Coroutine.NPyCoroutine.EEndReason
MessageType		= Cs_Types_Coroutine.NPyCoroutine.EMessage

#var OnEndType = null;

class FPyRoutine:
	class FOnEnd:
		class NCached:
			class NStr:
				Set: str = "FPyRoutine.FOnEnd.Set"
				Execute: str = "FPyRoutine.FOnEnd.Execute"
		def __init__(self):
			self.Fn: any = None
		def Set(self, fn: any):
			context: str = FPyRoutine.FOnEnd.NCached.NStr.Set
			
			check(CommonLibrary.IsFunctionChecked(context, fn))
			# TODO: Check Function returns bool
			self.Fn = fn
		def Execute(self, r: object) -> bool:
			context: str = FPyRoutine.FOnEnd.NCached.NStr.Execute

			check(CommonLibrary.IsInstanceOfChecked(context, r, FPyRoutine)) 
			return self.Fn()
		def Reset(self):
			self.Fn = None
	class NCached:
		class NStr:
			AddChild: str = "FPyRoutine.AddChild"
			EndChild: str = "FPyRoutine.EndChild"
	def __init__(self):
		# NOTE: FPyCore "typed" as any to prevent circular import
		self.Core: any = None

		self.OnEndType = FPyRoutine.FOnEnd

		self.Group: ue.ECsUpdateGroup = UpdateGroupLibrary.get_max();

		# Time
		self.StartTime: ue.CsTime 				= ue.CsTime()
		self.ElapsedTime: ue.CsDeltaTime 		= ue.CsDeltaTime()
		self.DeltaTime: ue.CsDeltaTime 			= ue.CsDeltaTime()
		self.TickCount: int 					= 0
		self.Delay: float						= 0.0
		self.bDeltaTimeScale: bool				= False
		self.DeltaTimeScale: FPyProperty 		= None

		self.Handle: ue.CsRoutineHandle = ue.CsRoutineHandle()
		
		self.AbortImpls = []
		self.OnAborts = []

		self.State: StateType = StateType.Free

		self.Index: int = INDEX_NONE

		self.Name: str = ""

		self.bUpdateComplete: bool = False
		self.bExecuteComplete: bool = False

		self.CoroutineImpl: any = None

		# End
		self.EndReason: EndReasonType = EndReasonType.EEndReason_MAX

		self.OnEnds: list[FPyRoutine.FOnEnd] = []

		# Owner
		
		self.Owner: Cs_Types_Coroutine.NPyCoroutine.FOwner  = Cs_Types_Coroutine.NPyCoroutine.FOwner();

		# Children

		self.Parent: FPyRoutine = None
		self.Children: list[FPyRoutine] = []

		self.RegisterMap: Cs_Types_Coroutine.NPyCoroutine.NRegister.FMap = Cs_Types_Coroutine.NPyCoroutine.NRegister.FMap()

		self.Messages = dict()
		self.Messages_Recieved = dict()

		for e in MessageType:
			self.Messages[e._name_] = []
			self.Messages_Recieved[e._name_] = []

		self.bWaitForFrame: bool 			= False
		self.WaitForFrameCounter: int 		= 0
		self.WaitForFrame: int 				= 0
		self.WaitForFrameType: FPyProperty 	= None
		self.bWaitForTime: bool 			= False
		self.WaitForTime: float 			= 0.0
		self.WaitForTimeTimer: float		= 0.0
		self.WaitForTimeType: FPyProperty	= None
		self.bWaitForFlag: bool				= False
		self.WaitForFrameType: FPyProperty 	= None
		self.bWaitForListenMessage: bool	= False
		self.WaitForListenMessage: str		= None
		self.WaitForListenMessageType: FPyProperty = None
		self.bWaitForEnum: bool				= False
		self.WaitForEnum: EnumYieldType		= EnumYieldType()
		self.bWaitForRoutineHandle: bool	= False
		self.WaitForRoutineHandle: RoutineHandleYieldType = RoutineHandleYieldType()
		self.bWaitForFunction: bool			= False
		self.WaitForFunction: FunctionYieldType = FunctionYieldType()
	
	# NOTE: FPyCore "typed" as any to prevent circular import
	def SetCore(self, core: any):
		self.Core = core
		self.WaitForRoutineHandle.SetCore(core)

	def SetGroup(self, group: ue.ECsUpdateGroup):
		self.Group = group
	def GetGroup(self) -> ue.ECsUpdateGroup:
		return self.Group

	def GetHandle(self) -> ue.CsRoutineHandle:
		return self.Handle

	def SetIndex(self, index: int):  
		self.Index = index
		self.Handle.index = index
	def GetIndex(self) -> int:
		return self.Index

	def AddOnEnd(self, fn: any):
		onEnd = self.OnEndType()
		onEnd.Set(fn)
		self.OnEnds.append(onEnd)
	
	def Init(self, payload: PayloadType):
		self.State = StateType.Init;

		self.CoroutineImpl = payload.CoroutineImpl;

		self.StartTime = TimeLibrary.fcstime_copy(payload.StartTime)

		self.Owner.Copy(payload.Owner)
		
		self.Messages[MessageType.Abort._name_] = copy.deepcopy(payload.AbortMessages)

		self.AbortImpls = []

		for fn in payload.AbortImpls:
			self.AbortImpls.append(fn)

		self.OnEnds = []

		for fn in payload.OnEnds:
			self.OnEnds.append(fn)

		self.Name = payload.Name;

		for info in payload.RegisterMap.Infos:
			idx: int = info.Index

			self.RegisterMap.Values[idx] = payload.RegisterMap.Values[idx]
			self.RegisterMap.SetUsedValue(idx)

		self.Handle	= RoutineLibrary.new(self.Handle)[1]

	def StartUpdate(self):
		self.State = StateType.Update

	def Update(self, deltaTime: ue.CsDeltaTime):
		self.bUpdateComplete = False
		
		# Check for Abort Messages
		msgs: list		    = self.Messages[MessageType.Abort._name_]
		msgs_recieved: list = self.Messages_Recieved[MessageType.Abort._name_]
		
		if len(msgs) > EMPTY:
			found: bool = False

			for recieved in msgs_recieved:
				if recieved in msgs:
					self.Messages[MessageType.Abort._name_] = []

					self.End(EndReasonType.AbortMessage)

					found = True
				if found:
					break

		self.Messages_Recieved[MessageType.Abort._name_] = []

		# If the Coroutine has been eneded by an Abort Message, EXIT
		if (self.State == StateType.End) and (self.EndReason == EndReasonType.AbortMessage):
			self.bUpdateComplete = True
			return
		
		# If the Owner of the Coroutine is a UObject, check if the object
		# is still valid
		if IsValidObject(self.Owner.Owner) == False:
			self.End(EndReasonType.OwnerIsInvalid)

			self.bUpdateComplete = True
			return

		# Check if Coroutine should be aborted
		iMax: int = len(self.AbortImpls)
		jMax: int = len(self.OnAborts)

		for i in range(0, iMax):
			impl: any = self.AbortImpls[i]

			if impl(self):		
				for j in range(0, jMax):
					self.OnAborts[i](self)

				self.End(EndReasonType.AbortCondition)

				self.bUpdateComplete = True
				return

		# Check if Coroutine has been ended
		if self.State == StateType.End:
			if self.EndReason == EndReasonType.EEndReason_MAX:
				self.End(EndReasonType.EndOfExecution)

			self.bUpdateComplete = True
			return

		move: bool = True

        # Check WaitForFrame
		if self.bWaitForFrame == True:
			if self.WaitForFrameType != None:
				self.WaitForFrame = self.WaitForFrameType.Get()
				
				if self.WaitForFrame < 0:
					self.WaitForFrame	  = 0
					self.WaitForFrameType = None

					checkf(False, "FPyRoutine.Update: yield return value of type 'FPyRoutine.FrameType' is used for WaitForFrame. yield return value must be >= 0.")
					
				self.WaitForFrameCounter += 1
				
				move = self.WaitForFrameCounter >= self.WaitForFrame
				
			if move == True:
				self.WaitForFrame = 0
				self.bWaitForFrame = False
				self.WaitForFrameCounter = 0

        # Check WaitForTime
		if self.bWaitForTime == True:
			if self.WaitForTimeType != None:
				self.WaitForTime = self.WaitForTimeType.Get()
				
				if self.WaitForTime < 0.0:
					self.WaitForTime     = 0.0
					self.WaitForTimeType = None

					checkf(False, "FPyRoutine.Update: yield return value of type 'FPyRoutine.TimeType' is used for WaitForTime. yield return value must be >= 0.0f.")
					
			self.WaitForTimeTimer += deltaTime.time
			
			move = self.WaitForTimeTimer >= self.WaitForTime
			
			if move == True:
				self.WaitForTime	  = 0
				self.bWaitForTime	  = False
				self.WaitForTimeTimer = 0.0

        # Check WaitingFor
		
        # if (bWaitingFor)
        # {
        #     move = WaitingFor.State != ECgRoutineState.Running;

        #     if (move)
        #     {
        #         WaitingFor.Blocking = null;
        #         WaitingFor  = null;
        #         bWaitingFor = false;
        #     }
        # }
		
        # Check WaitForFlag
		#  TODO: WaitForFlagType with function IsEqual needs to be defined
		if self.bWaitForFlag == True:
			move = (self.WaitForBoolType != None and self.WaitForBoolType.Get() == True) or (self.WaitForFlagType != None and self.WaitForFlagType.IsEqual() == True)
			
			if move == True:
				self.WaitForBoolType = None
				self.bWaitForFlag    = False

        # WaitForListenMessage
		if self.bWaitForListenMessage == True:
			if self.WaitForListenMessageType != None:
				self.WaitForListenMessage = self.WaitForListenMessageType.Get()
				
				if self.WaitForListenMessage == INVALID_LISTEN_MESSAGE:
					checkf(False, "FJsRoutine.Update: yield return value of type 'FJsRoutine.ListenMessageType' is used for WaitForListenMessage. yield return value must NOT be empty.")
					
			move = self.WaitForListenMessage == INVALID_LISTEN_MESSAGE
			
			if move == True:
				self.WaitForListenMessage  = INVALID_LISTEN_MESSAGE
				self.bWaitForListenMessage = False
            
		# WaitForEnum
		if self.bWaitForEnum == True:
			move = self.WaitForEnum.Execute()
			
			if move == True:
				self.bWaitForEnum = False
				self.WaitForEnum.Reset()

		# WaitForRoutineHandle
		if self.bWaitForRoutineHandle == True:
			move = self.WaitForRoutineHandle.Execute()
			
			if move == True:
				self.bWaitForRoutineHandle = False
				self.WaitForRoutineHandle.Reset()

		# WaitForFunction
		if self.bWaitForFunction == True:
			move = self.WaitForFunction.Execute()
			
			if move == True:
				self.bWaitForFunction = False
				self.WaitForFunction.Reset()

		self.DeltaTime   = TimeLibrary.fcsdeltatime_copy(deltaTime)
		self.ElapsedTime = TimeLibrary.add_delta_time(self.ElapsedTime, deltaTime)
		
		if move == False:
			self.bUpdateComplete = True
			return
		
		self.TickCount += 1

		self.bExecuteComplete = False

		result: any = None
		
		if self.TickCount == 1:
			result = self.CoroutineImpl.send(None)
		else:
			result = self.CoroutineImpl.send(self)

		self.bExecuteComplete = True

		done: bool = False

		if (isinstance(result, EndReasonType)) and (result == EndReasonType.EndOfExecution):
			done = True

		if done == False:
			yieldCommand: any = result

			waitForTimeByObject: bool = False

			# Check for alternatives ways for commands due to coercion or other caveats
			if (CommonLibrary.IsValidDict(yieldCommand)):
				# Objects that contain the 'WaitForTime' key are used
				# when floats (i.e. 1.0) get coerced to integers (i.e. 1.0 -> 1)
				# and the yieldCommand get interpretted as WaitForFrame
				# Format: yield {WaitForTime: 'seconds'}
				if "WaitForTime" in yieldCommand:
					checkf(CommonLibrary.IsIntOrFloat(yieldCommand["WaitForTime"]), "FPyRoutine.Update: yieldCommand with key 'WaitForTime' does NOT have a numeric value.")

					waitForTimeByObject = True
				# WaitForEnum
				elif self.WaitForEnum.CopyFromYield(yieldCommand):
					self.bWaitForEnum = True
				# WaitForRoutineHandle
				elif self.WaitForRoutineHandle.CopyFromYield(yieldCommand):
					self.bWaitForRoutineHandle = True
				# WaitForFunction
				elif self.WaitForFunction.CopyFromYield(yieldCommand):
					self.bWaitForFunction = True
				else:
					self.WaitForEnum.Reset()
					self.WaitForRoutineHandle.Reset()
					self.WaitForFunction.Reset()

			if yieldCommand == None:
				yieldCommand = 1

			# WaitForFrame - yield 'int'
			if type(yieldCommand) is int:
				self.WaitForFrame = yieldCommand
				
				if self.WaitForFrame < 0:
					self.WaitForFrame = 0

					checkf(False, "FPyRoutine.Update: yield return value of type 'int' is used for WaitForFrame. yield return value must be >= 0.")
				else:
					self.bWaitForFrame		 = True
					self.WaitForFrameCounter = 0
			# WaitForFrameType - yield 'int property'
			elif (isinstance(yieldCommand, FPyProperty)) and (yieldCommand.IsInt()):
				self.WaitForFrameType = yieldCommand
				
				if self.WaitForFrameType.Get() < 0:
					self.WaitForFrameType = None

					checkf(False, "FPyRoutine.Update: yield return value of type 'FPyRoutine.FrameType' is used for WaitForFrame. yield return value must be >= 0.")
				else:
					self.bWaitForFrame		 = True
					self.WaitForFrameCounter = 0
            # WaitForTime | 'waitForTimeByObject'
			elif (type(yieldCommand) is float) or (waitForTimeByObject == True):
				self.WaitForTime = yieldCommand["WaitForTime"] if waitForTimeByObject == True else yieldCommand
				
				if self.WaitForTime < 0.0:
					self.WaitForTime = 0.0

					checkf(False, "FPyRoutine.Run: yield return value of type 'float' is used for WaitForTime. yield return value must be >= 0.0f.")
				else:
					self.bWaitForTime	  = True
					self.WaitForTimeTimer = 0.0
			# WaitForTimeType - yield 'float property'
			elif (isinstance(yieldCommand, FPyProperty)) and yieldCommand.IsFloat():
				self.WaitForTimeType = yieldCommand
				
				if self.WaitForTimeType.Get() < 0.0:
					self.WaitForTimeType = None

					checkf(False, "FPyRoutine.Run: yield return value of type 'FPyRoutine.FTimeType' is used for WaitForTime. yield return value must be >= 0.0f.")
				else:
					self.bWaitForTime	  = True
					self.WaitForTimeTimer = 0.0
            # WaitingFor
			# 
            # else
            # if (type == typeof(FCgRoutine))
            # {
            #     WaitingFor = (FCgRoutine)yieldCommand;
            #     WaitingFor.Blocking = this;
            #     bWaitingFor = true;

            #     // Fix linkage. Prev / Next
            #     InsertRoutine(Schedule, this, WaitingFor);
            # }
			# 
            # WaitForFlag - yield 'flag property'
			elif (isinstance(yieldCommand, FPyProperty)) and yieldCommand.IsBoolean():
				self.WaitForBoolType = yieldCommand
				
				if self.WaitForBoolType.Get() == False:
					self.bWaitForFlag = True
            # WaitForListenMessage
			elif type(yieldCommand) is str:
				self.WaitForListenMessage = yieldCommand
				
				if self.WaitForListenMessage == INVALID_LISTEN_MESSAGE:
					checkf(False, "FPyRoutine.Update: yield return value of type 'string' is used for WaitForListenMessage. yield return value must NOT be empty.")
				else:
					self.bWaitForListenMessage = True
			# WaitForListenMessageType
			elif (isinstance(yieldCommand, FPyProperty)) and yieldCommand.IsString():
				self.WaitForListenMessageType = yieldCommand
				
				if self.WaitForListenMessageType.Get() == INVALID_LISTEN_MESSAGE:
					checkf(False, "FPyRoutine.Update: yield return value of type 'string' is used for WaitForListenMessage. yield return value must NOT be empty.")
				else:
					self.bWaitForListenMessage = True
			# WaitForEnum
			elif self.bWaitForEnum == True:
				# Do Nothing, already set
				pass
			# WaitForRoutineHandle
			elif self.bWaitForRoutineHandle == True:
				# Do Nothing, already set
				pass
			# WaitForFunction
			elif self.bWaitForFunction == True:
				# Do Nothing, already set
				pass
            # INVALID Type
			else:
				checkf(False, "FPyRoutine.Update: Invalid Type: " + str(type(yieldCommand)) + " for yield. yield return value must be of type: int, FPyRoutine.FrameType, float, FJsRoutine.TimeType, FJsRoutine, FJsRoutine.BoolType, string, or FJsRoutine.ListenMessageType.")
        # Finished
		else:
			if (self.EndReason == EndReasonType.EEndReason_MAX) and (self.TickCount > 0):
				self.End(EndReasonType.EndOfExecution)
		self.bUpdateComplete = True

	def IsUpdateComplete(self) -> bool:
		return self.bUpdateComplete
	def IsExecuteComplete(self) -> bool:
		return self.bExecuteComplete
	def IsRunning(self) -> bool:
		return self.State == StateType.Update
	
	def End(self, endReason: EndReasonType):
		self.EndChildren()

		self.State = StateType.End;

		if isinstance(endReason, StateType) == False or endReason == None:
			self.EndReason = EndReasonType.EndOfExecution;
		else:
			self.EndReason = endReason

		for onEnd in self.OnEnds:
			onEnd.Execute(self)
		self.OnEnds = []

	def EndOfExecution(self):
		self.End(EndReasonType.EndOfExecution)

	def HasJustEnded(self) -> bool:
		return self.State == StateType.End
	def HasEnded(self):
		return (self.State == StateType.End) or (self.State == StateType.Free)
	
	def Reset(self):
		if IsValidObject(self.Parent) == True:
			if self in self.Parent.Children:
				self.Parent.Children.remove(self)

		self.Parent = None
		
		self.EndChildren()

		self.CoroutineImpl = None

		# Time
		self.StartTime = ue.CsTime()
		self.ElapsedTime = ue.CsDeltaTime()
		self.DeltaTime = ue.CsDeltaTime()
		self.TickCount = 0
		self.Delay = 0.0

		self.Handle = RoutineLibrary.reset(self.Handle)[0]
		self.AbortImpls = []
		self.OnAborts = []

		self.State = StateType.Free

		self.Name = ""

		self.EndReason = EndReasonType.EEndReason_MAX
		self.OnEnds = []

		self.Owner.Reset()

		self.RegisterMap.Reset()
		
		self.Messages.clear()
		self.Messages_Recieved.clear()
		
		for e in MessageType:
			self.Messages[e._name_] = []
			self.Messages_Recieved[e._name_] = []

		self.bWaitForFrame = False
		self.WaitForFrameCounter = 0
		self.WaitForFrame = 0
		self.WaitForFrameType = None
		self.bWaitForTime = False
		self.WaitForTime = 0.0
		self.WaitForTimeTimer = 0.0
		self.WaitForTimeType = None
		self.bWaitForFlag = False
		self.WaitForFlagType = None
		self.bWaitForListenMessage = False
		self.WaitForListenMessage = None
		self.WaitForListenMessageType = None
		self.bWaitForEnum = False
		self.WaitForEnum.Reset()
		self.bWaitForRoutineHandle = False
		self.WaitForRoutineHandle.Reset()
		self.bWaitForFunction = False
		self.WaitForFunction.Reset()
		
	def AddChild(self, child: any):
		context = FPyRoutine.NCached.NStr.AddChild
		check(CommonLibrary.IsInstanceOfChecked(context, child, FPyRoutine))
		child.Parent = self
		self.Children.append(child)

	def EndChildren(self):
		for child in self.Children:
			child.End(EndReasonType.EndOfExecution)
		self.Children = []

	def EndChild(self, child: any):
		context = FPyRoutine.NCached.NStr.EndChild
		toRemove = None

		for c in self.Children:
			if child == c:
				child.End()
				toRemove.append(c)
				break

		if toRemove != None:
			self.Children.remove(toRemove)

	def SetValue(self, index: int, value: any):
		self.RegisterMap.SetValue(index, value)

	def GetValue(self, index: int) -> any:
		return self.RegisterMap.GetValue(index)

	def AddMessage(self, messageType: MessageType, message: str):
		self.Messages[messageType._name_].append(message)

	def ReceiveMessage(self, messageType: MessageType, message: str):
		self.Messages_Recieved[messageType._name_].append(message)