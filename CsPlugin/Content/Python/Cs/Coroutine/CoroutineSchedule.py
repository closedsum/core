# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import unreal as ue
 
# Type
# - Cs/Types/Property/Property.py
import Cs.Types.Property.Property as Cs_Property
# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Math.py
import Cs.Library.Library_Math as Cs_Library_Math
# Managers
# - Cs/Managers/Resource/Manager_Resource_Fixed.py
import Cs.Managers.Resource.Manager_Resource_Fixed as Cs_Manager_Resource_Fixed
# Resource
# - Cs/Managers/Resource/ResourceContainer.py
import Cs.Managers.Resource.ResourceContainer as Cs_ResourceContainer
# Containers
# - Cs/Containers/DoubleLinkedListNode.py
import Cs.Containers.DoubleLinkedListNode as Cs_DoubleLinkedListNode
# Coroutine
# - Cs/Coroutine/Types_Coroutine.py
import Cs.Coroutine.Types_Coroutine as Cs_Types_Coroutine
# - Cs/Coroutine/Routine.py
import Cs.Coroutine.Routine as Cs_Routine

ROUTINE_POOL_SIZE = 2048
COROUTINE_PAYLOAD_SIZE = 64
INDEX_NONE = -1

# ALIAS

# "alias" - library (c++)
RoutineLibrary      = ue.CsScriptLibrary_Routine
UpdateGroupLibrary  = ue.CsScriptLibrary_UpdateGroup

# "alias" struct (c++)
FCsRoutineHandle = ue.CsRoutineHandle

# "alias" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
PyMathLibrary = Cs_Library_Math.NPyMath.FLibrary

# "alias" - class (py)
PayloadType               = Cs_Types_Coroutine.NPyCoroutine.NPayload.FImpl
FPyManager_Resource_Fixed = Cs_Manager_Resource_Fixed.FPyManager_Resource_Fixed
FPyRoutine                = Cs_Routine.FPyRoutine
FPyResourceContainer      = Cs_ResourceContainer.FPyResourceContainer
FPyDoubleLinkedListNode   = Cs_DoubleLinkedListNode.FPyDoubleLinkedListNode
FPyProperty 	          = Cs_Property.FPyProperty

# "alias" - functions (py)
checkf              = CommonLibrary.checkf
check               = CommonLibrary.check
IsValidObject       = CommonLibrary.IsValidObject
IsValidObjectChecked = CommonLibrary.IsValidObjectChecked
IsInstanceOfChecked = CommonLibrary.IsInstanceOfChecked
IsIntChecked        = CommonLibrary.IsIntChecked

# "typedefs" - functions (c++)
IsEqual_UpdateGroup = lambda: UpdateGroupLibrary.equal_equal

# "typedefs" - enums
StateType     = Cs_Types_Coroutine.NPyCoroutine.EState
EndReasonType = Cs_Types_Coroutine.NPyCoroutine.EEndReason
MessageType		= Cs_Types_Coroutine.NPyCoroutine.EMessage

class NPyCoroutine:
    class NSchedule:
        class FDefault:
            class NCached:
                class NStr:
                    GetRoutineContainer   = "NPyCoroutine.NSchedule.FDefault.GetRoutineContainer"
                    StartByContainer      = "NPyCoroutine.NSchedule.FDefault.StartByContainer"
                    StartChildByContainer = "NPyCoroutine.NSchedule.FDefault.Start"

            def __init__(self, core: any):
                # NOTE: FPyCore "typed" as any to prevent circular import
                self.Core: any = core

                self.Group: ue.ECsUpdateGroup = None

                self.Manager_Routine: FPyManager_Resource_Fixed[FPyRoutine] = FPyManager_Resource_Fixed[FPyRoutine]()
                self.Manager_Routine.CreatePool(ROUTINE_POOL_SIZE, FPyRoutine)

                # Set Index for fast look up

                # Routine
                if True:
                    pool: list[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[FPyRoutine] = pool[i]
                        r: FPyRoutine                   = container.Get()
                        index: int                      = container.GetIndex()
                        r.SetIndex(index)

                self.Manager_Payload: FPyManager_Resource_Fixed[PayloadType] = FPyManager_Resource_Fixed[PayloadType]()
                self.Manager_Payload.CreatePool(COROUTINE_PAYLOAD_SIZE, PayloadType)

                # Set Index for fast look up

                # Payload
                if True:
                    pool: list[FPyResourceContainer[PayloadType]] = self.Manager_Payload.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[PayloadType] = pool[i]
                        r: PayloadType                  = container.Get()
                        index: int                      = container.GetIndex()
                        r.SetIndex(index)

                self.QueueEndHandles: list[FCsRoutineHandle] = []

            # Schedule
            #region Schedule
            # public:

            def SetGroup(self, group: ue.ECsUpdateGroup):
                self.Group = group

                # Routine
                if True:
                    pool: list[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[FPyRoutine] = pool[i]
                        r: FPyRoutine                   = container.Get()
                        r.SetGroup(group)
                
                # Payload
                if True:
                    pool: list[FPyResourceContainer[PayloadType]] = self.Manager_Payload.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[PayloadType] = pool[i]
                        r: PayloadType                  = container.Get()
                        r.Group                         = group

            #endregion Schedule

            # Routine
            #region Routine
            # public:

            def GetRoutineContainer(self, handle: FCsRoutineHandle) -> FPyResourceContainer[FPyRoutine]:
                context: str = __class__.GetRoutineContainer.__qualname__
                
                check(IsInstanceOfChecked(context, handle, FCsRoutineHandle))

                if RoutineLibrary.is_valid(handle) == False:
                    # console.log("FCsCoroutineSchedule::GetRoutineContainer: Handle is NOT valid: " + handle.Index + " " + Guid.Conv_GuidToString(handle.Handle));
                    return None

                poolSize: int = self.Manager_Routine.GetPoolSize()
                
                index: int = INDEX_NONE
                
                if (type(handle.index) is int) and (handle.index >= 0):
                    index = handle.index

                if index >= poolSize:
                    ue.log_warning(f"{context}: Handle's Index: {index} is not associated with any Routine with Group: {self.Group.name_internal}.")
                    return None

                container: FPyResourceContainer[FPyRoutine] = self.Manager_Routine.GetAt(index)
                r: FPyRoutine		            = container.Get()

                IsEqual = RoutineLibrary.equal_equal
                
                if IsEqual(r.GetHandle(), handle) == True:
                    return container
                return None

            def GetRoutine(self, handle: FCsRoutineHandle) -> FPyRoutine:
                container: FPyResourceContainer[FPyRoutine] = self.GetRoutineContainer(handle)

                return container.Get() if IsValidObject(container) else None
            
            #endregion Routine

            # Handle
            #region Handle
            # public:

            def IsHandleValid(self, handle: FCsRoutineHandle) -> bool:
                return self.GetRoutineContainer(handle) != None

            def IsRunning(self, handle: FCsRoutineHandle) -> bool:
                r: FPyRoutine = self.GetRoutine(handle)

                if IsValidObject(r) == True:
                    return r.IsRunning()
                return False
            
            #endregion Handle

            # Starts
            #region Start
            # public:

            def StartByContainer(self, payloadContainer: FPyResourceContainer[PayloadType]) -> FCsRoutineHandle:
                context: str = __class__.StartByContainer.__qualname__

                payload: PayloadType = payloadContainer.Get()

                checkf(IsValidObject(payload), f"{context}: payloadContainer does NOT contain a reference to a payload.")
                check(payload.IsValidChecked(context))
                checkf(UpdateGroupLibrary.equal_equal(self.Group, payload.Group), f"{context}: Mismatch between payload.Group: {str(payload.Group.name_internal)} and Group: {str(self.Group.name_internal)}")

                r: FPyRoutine = self.Manager_Routine.AllocateResource()
                
                r.Init(payload)

                if payload.bPerformFirstUpdate == True:
                    r.StartUpdate()
                    # NOTE: The double update since an initial yield is needed to set the Routine (r).
                    #       Currently there doesn't seem to be a way to "seed" the Routine without doing this.
                    r.Update(ue.CsDeltaTime())
                    r.Update(ue.CsDeltaTime())

                #LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? TransactionType::Start : TransactionType::Allocate, R);

                payload.Reset()
                self.Manager_Payload.Deallocate(payloadContainer)
                return r.GetHandle()

            def Start(self, payload: PayloadType) -> FCsRoutineHandle:
                return self.StartByContainer(self.GetPayloadContainer(payload))

            def StartChildByContainer(self, payloadContainer: FPyResourceContainer[PayloadType]) -> FCsRoutineHandle:
                context: str = __class__.StartChildByContainer.__qualname__

                payload: PayloadType = payloadContainer.Get()

                checkf(IsValidObject(payload), f"{context}: payloadContainer does NOT contain a reference to a payload.")
                checkf(payload.IsValidChecked(context))
                checkf(UpdateGroupLibrary.equal_equal(self.Group, payload.Group), f"{context}: Mismatch between payload.Group: {payload.Group.name_internal} and Group: {self.Group.name_internal}")

                parentContainer: FPyResourceContainer[FPyRoutine] = self.GetRoutineContainer(payload.ParentHandle)

                checkf(IsValidObject(parentContainer), f"{context}: Failed to find a container for payload.")

                parent: FPyRoutine    = parentContainer.Get()
                lastChild: FPyRoutine = parent.GetLastChild()

                routineContainer: FPyResourceContainer[FPyRoutine] = None

                # Add after Last Child
                if lastChild != None:
                    lastChildContainer: FPyResourceContainer[FPyRoutine] = self.Manager_Routine.GetAt(lastChild.GetIndex())

                    routineContainer = self.Manager_Routine.AllocateAfter(lastChildContainer)
                # Add after Parent
                else:
                    routineContainer = self.Manager_Routine.AllocateAfter(parentContainer)

                r: FPyRoutine = routineContainer.Get()

                parent.AddChild(r)

                r.Init(payload)

                r.StartUpdate()
                # NOTE: The double update since an initial yield is needed to set the Routine (r).
                #       Currently there doesn't seem to be a way to "seed" the Routine without doing this.
                r.Update(ue.CsDeltaTime())
                r.Update(ue.CsDeltaTime())
                payload.Reset()
                #UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
                return r.GetHandle()

            def StartChild(self, payload: PayloadType) -> FCsRoutineHandle:
                return self.StartChildByContainer(self.GetPayloadContainer(payload))

            #endregion Start

            # End
            #region End
            # public:

            def EndAll(self):
                """
                End all coroutines.
                """ 
                result: bool = False

                current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetAllocatedHead()
                next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]	 = current

                while next != None:
                    current				                   = next
                    routineContainer: FPyResourceContainer[FPyRoutine] = current.Element
                    next				                   = current.GetNextLink()

                    r: FPyRoutine = routineContainer.Get()

                    r.End(EndReasonType.Shutdown)

                    #LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

                    r.Reset()
                    self.Manager_Routine.Deallocate(routineContainer)

                    result = True
                return result

            def End(self, handle: FCsRoutineHandle) -> bool:
                """
                End the routine associated with the Handle.

                :param FCsRoutineHandle handle:   Handle to a routine.
                :return bool:                       Whether the routine has successful ended.
                                                    NOTE: If the routine has already ended, this will return false.
                """ 
                container: FPyResourceContainer[FPyRoutine] = self.GetRoutineContainer(handle)

                if IsValidObject(container) == True:
                    r: FPyRoutine = container.Get()

                    # If the Routine has already Ended, exit
                    if r.HasEnded() or r.HasJustEnded():
                        return False

                    # If the Routine is currently being Updated, queue the End for either the
                    # beginning of the next Update or the end of the current Update.
                    if r.IsUpdateComplete() == False:
                        self.QueueEndHandles.append(handle)
                        return False

                    r.End(EndReasonType.Manual)

                    #LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

                    r.Reset()
                    self.Manager_Routine.Deallocate(container)
                    return True
                return False

            def HasEnded(self, handle: FCsRoutineHandle) -> bool:
                """
                Check if a routine associated with the Handle has already ended.
                 NOTE: This returns True if Handle is NOT Valid.

                :param FCsRoutineHandle handle:   Handle to a routine.
                :return bool:                       Whether the routine has successful ended.
                """ 
                r: FPyRoutine = self.GetRoutine(handle)

                if IsValidObject(r) == True:
                    return r.HasEnded()
                return True

            def HasJustEnded(self, handle: FCsRoutineHandle) -> bool:
                """
                CCheck if a routine associated with the Handle has just ended.

                :param FCsRoutineHandle handle:   Handle to a routine.
                :return bool:                       Whether the routine has successful ended.
                """ 
                r: FPyRoutine = self.GetRoutine(handle)

                if IsValidObject(r) == True:
                    return r.HasJustEnded()
                return True

            #endregion End

            # Update
            #region Update
            # public:

            def Update(self, deltaTime: ue.CsDeltaTime):
                # End any pending Handles requested for End from the previous Update
                for handle in self.QueueEndHandles:
                    self.End(handle)

                self.QueueEndHandles = []

                current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetAllocatedHead()
                next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]    = current
                #ue.log_warning(str(self.Manager_Routine.GetAllocatedSize()))
                while next != None:
                    current				                   = next
                    routineContainer: FPyResourceContainer[FPyRoutine] = current.Element
                    next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]] 		   = current.GetNextLink()
                    
                    r: FPyRoutine = routineContainer.Get()

                    state: StateType = r.State
                    
                    # Init -> Update
                    if state == StateType.Init:
                        r.StartUpdate()
                        r.Update(deltaTime)
                    # Update
                    elif state == StateType.Update:
                        r.Update(deltaTime)

                    # End
                    if state == StateType.End:
                        #LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);
                        r.Reset()
                        self.Manager_Routine.Deallocate(routineContainer)

                # End any Handles requested for End on the current Update
                for handle in self.QueueEndHandles:
                    self.End(handle)

                self.QueueEndHandles = []

            #endregion Update

            # Payload
            #region Payload
            # public:

            def AllocatePayloadContainer(self) -> FPyResourceContainer[PayloadType]:
                return self.Manager_Payload.Allocate()

            def AllocatePayload(self) -> PayloadType:
                return self.Manager_Payload.AllocateResource()

            # protected:

            def GetPayloadContainer(self, payload: PayloadType) -> FPyResourceContainer[PayloadType]:
                if payload.GetIndex() == INDEX_NONE:
                    container: FPyResourceContainer[PayloadType] = self.Manager_Payload.Allocate()
                    p: PayloadType		            = self.container.Get()

                    p.Copy(payload)

                    return container
                return self.Manager_Payload.GetAt(payload.GetIndex())

            #endregion Payloads

            # Message
            #region Message
            # public:

            def BroadcastMessage(self, type: MessageType, message: str, owner: object):
                current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetAllocatedHead()
                next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]    = current

                while next != None:
                    current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]  = next
                    routineContainer: FPyResourceContainer[FPyRoutine]                  = current.Element
                    next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]     = current.GetNextLink()

                    r: FPyRoutine = routineContainer.Get()

                    if IsValidObject(owner) == True:
                        if r.Owner.Owner == owner:
                            r.ReceiveMessage(type, message)
                    else:
                        r.ReceiveMessage(type, message)
            #endregion Message

        class FCustom:
            class NCached:
                class NStr:
                    # Owner
                    GetOwnerID            = "NPyCoroutine.NSchedule.FCustom.GetOwnerID"
                    GetOwnerIDByRoutine   = "NPyCoroutine.NSchedule.FCustom.GetOwnerIDByRoutine"
                    # Routine
                    GetRoutineContainer   = "NPyCoroutine.NSchedule.FCustom.GetRoutineContainer"
                    # Start
                    StartByContainer      = "NPyCoroutine.NSchedule.FCustom.StartByContainer"
                    StartChildByContainer = "NPyCoroutine.NSchedule.FCustom.Start"
                    # End
                    End                   = "NPyCoroutine.NSchedule.FCustom.End"
                    # Update
                    Update                = "NPyCoroutine.NSchedule.FCustom.Update"

            def __init__(self, core: any):
                # NOTE: FPyCore "typed" as any to prevent circular import
                self.Core: any = core

                self.Group: ue.ECsUpdateGroup = None

                # Owner
                self.Manager_OwnerID: FPyManager_Resource_Fixed[FPyProperty] = FPyManager_Resource_Fixed[FPyProperty]()
                self.Manager_OwnerID.CreatePool(ROUTINE_POOL_SIZE, FPyProperty)

                if True:
                    pool: list[FPyResourceContainer[FPyProperty]] = self.Manager_OwnerID.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[FPyProperty] = pool[i]
                        p: FPyProperty                               = container.Get()
                        p.Value                                      = container.GetIndex()

                # TODO: Get from settings
                self.MaxOwners = 128
                self.MaxRoutinesPerOwner = 16
                # Max Owners * Max Allocated Routines (Stride)
                self.OwnerRoutineIDs: list[int] = [INDEX_NONE] * ROUTINE_POOL_SIZE
                self.RoutineStrideByOwnerID: list[int] = [0] * self.MaxOwners
                # Handles to End either beginning of the next Update or the end of the
                #   current Update.
                #   NOTE: This list is populated when a Routine is currently being Executed and
                #         requested to End.
                self.OwnerQueueEndHandles: list[FCsRoutineHandle] = [None] * ROUTINE_POOL_SIZE
                self.QueueEndHandleStrideByOwnerID: list[int] = [0] * self.MaxOwners

                for i in range(0, ROUTINE_POOL_SIZE):
                    self.OwnerRoutineIDs[i] = INDEX_NONE
                    self.OwnerQueueEndHandles[i] = None

                for i in range(0, self.MaxOwners):
                    self.RoutineStrideByOwnerID[i] = 0
                    self.QueueEndHandleStrideByOwnerID[i] = 0

                self.Manager_Routine: FPyManager_Resource_Fixed[FPyRoutine] = FPyManager_Resource_Fixed[FPyRoutine]()
                self.Manager_Routine.CreatePool(ROUTINE_POOL_SIZE, FPyRoutine)

                # Set Index for fast look up

                # Routine
                if True:
                    pool: list[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[FPyRoutine] = pool[i]
                        r: FPyRoutine                   = container.Get()
                        index: int                      = container.GetIndex()
                        r.SetIndex(index);

                self.Manager_Payload: FPyManager_Resource_Fixed[PayloadType] = FPyManager_Resource_Fixed[PayloadType]()
                self.Manager_Payload.CreatePool(COROUTINE_PAYLOAD_SIZE, PayloadType)

                # Set Index for fast look up

                # Payload
                if True:
                    pool: list[FPyResourceContainer[PayloadType]] = self.Manager_Payload.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[PayloadType] = pool[i]
                        r: PayloadType                  = container.Get()
                        index: int                      = container.GetIndex()
                        r.SetIndex(index);

            # Owner
            #region Owner

            def AllocateOwnerID(self) -> int:
                return self.Manager_OwnerID.AllocateResource().Get()

            def DeallocateOwnerID(self, ownerID: int):
                self.End(ownerID)
                self.Manager_OwnerID.DeallocateAtByIndex(ownerID)
        
            def HasFreeOwnerID(self) -> bool:
                return self.Manager_OwnerID.IsExhausted() == False
        
            def GetOwnerID(self, routineIndex: int) -> int:
                context: str = __class__.GetOwnerID.__qualname__

                check(IsIntChecked(context, routineIndex))
                check(PyMathLibrary.IsIntInRangeInclusiveChecked(context, routineIndex, 0, self.Manager_Routine.GetPoolSize()))

                current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyProperty]] = self.Manager_OwnerID.GetAllocatedHead()
                next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyProperty]]	 = current

                while IsValidObject(next) != None:
                    current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyProperty]]  = next
                    idContainer: FPyResourceContainer[FPyProperty] = current.GetElement()
                    next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyProperty]]	  = current.GetNextLink()

                    # FPyResourceContainer -> contains FPyProperty (int) -> Get
                    id: int = idContainer.Get().Get()

                    start: int  = id * self.MaxRoutinesPerOwner
                    stride: int = self.RoutineStrideByOwnerID[id]
                        
                    for i in range(0, stride):
                        index: int = start + i

                        if self.OwnerRoutineIDs[index] == routineIndex:
                            return id

                checkf(0, f"{context}: Failed to find OwnerID associated with RoutineIndex: {routineIndex}.")
                return INDEX_NONE

            def GetOwnerIDByRoutine(self, r: FPyRoutine) -> int:
                context: str = __class__.GetOwnerIDByRoutine.__qualname__

                check(IsValidObjectChecked(context, r))
                return self.GetOwnerID(r.GetIndex())

            def GetOwnerIDByHandle(self, handle: FCsRoutineHandle) -> int:
                container: FPyResourceContainer[FPyRoutine] = self.GetRoutineContainer(handle)

                if IsValidObject(container) == True:
                    return self.GetOwnerIDByRoutine(container.Get())
                return INDEX_NONE

            #endregion Owner

            # Schedule
            #region Schedule
            # public:

            def SetGroup(self, group: ue.ECsUpdateGroup):
                self.Group = group

                # Routine
                if True:
                    pool: list[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[FPyRoutine] = pool[i]
                        r: FPyRoutine                   = container.Get()
                        r.SetGroup(group)
                # Payload
                if True:
                    pool: list[FPyResourceContainer[PayloadType]] = self.Manager_Payload.GetPool()

                    count: int = len(pool)

                    for i in range(0, count):
                        container: FPyResourceContainer[PayloadType] = pool[i]
                        r: PayloadType                  = container.Get()
                        r.Group                         = group

            #endregion Schedule

            # Routine
            #region Routine
            # public:

            def GetRoutineContainer(self, handle: FCsRoutineHandle) -> FPyResourceContainer[FPyRoutine]:
                context: str = __class__.GetRoutineContainer.__qualname__
                
                check(IsInstanceOfChecked(context, handle, FCsRoutineHandle))

                if RoutineLibrary.is_valid(handle) == False:
                    #console.log("FCsCoroutineSchedule::GetRoutineContainer: Handle is NOT valid: " + handle.Index + " " + Guid.Conv_GuidToString(handle.Handle));
                    return None

                poolSize: int = self.Manager_Routine.GetPoolSize()
                
                index: int = INDEX_NONE
                
                if (type(handle.index) is int) and (index.Index >= 0):
                    index = handle.index

                if index >= poolSize:
                    ue.log_warning(f"{context}: Handle's Index: {index} is not associated with any Routine with Group: {self.Group.name_internal}.")
                    return None

                container: FPyResourceContainer[FPyRoutine] = self.Manager_Routine.GetAt(index)
                r: FPyRoutine		            = container.Get()

                IsEqual = RoutineLibrary.equal_equal
                
                if IsEqual(r.GetHandle(), handle) == True:
                    return container
                return None

            def GetRoutine(self, handle: FCsRoutineHandle) -> FPyRoutine:
                container: FPyResourceContainer[FPyRoutine] = self.GetRoutineContainer(handle)

                return container.Get() if IsValidObject(container) == True else None

            #endregion Routine

            # Handle
            #region Handle
            # public:

            def IsHandleValid(self, handle: FCsRoutineHandle) -> bool:
                return self.GetRoutineContainer(handle) != None

            def IsRunning(self, handle: FCsRoutineHandle) -> bool:
                r: FPyRoutine = self.GetRoutine(handle)

                if IsValidObject(r) == True:
                    return r.IsRunning()
                return False
            
            #endregion Handle

            # Start
            #region Start
            # public:

            def StartByContainer(self, ownerID: int, payloadContainer: FPyResourceContainer[PayloadType]) -> FCsRoutineHandle:
                context: str = __class__.StartByContainer.__qualname__
                
                check(self.Manager_OwnerID.IsAllocatedChecked(context, ownerID))
                
                payload: PayloadType = payloadContainer.Get()

                checkf(IsValidObject(payload), f"{context}: payloadContainer does NOT contain a reference to a payload.")
                check(payload.IsValidChecked(context))
                checkf(UpdateGroupLibrary.equal_equal(self.Group, payload.Group), f"{context}: Mismatch between payload.Group: {payload.Group.name_internal} and Group: {self.Group.name_internal}")

                r: FPyRoutine = self.Manager_Routine.AllocateResource()

                checkf(self.RoutineStrideByOwnerID[ownerID] < self.MaxRoutinesPerOwner, f"{context}: Owner ID: {ownerID} has ALREADY allocated {self.RoutineStrideByOwnerID[ownerID]} Max Routines Per Owner: {self.MaxRoutinesPerOwner}.")
    
                routineIdIndex: int		             = (ownerID * self.MaxRoutinesPerOwner) + self.RoutineStrideByOwnerID[ownerID]
                self.OwnerRoutineIDs[routineIdIndex] = r.GetIndex();

                self.RoutineStrideByOwnerID[ownerID] += 1

                r.Init(payload)

                if payload.bPerformFirstUpdate == True:
                    r.StartUpdate()
                    # NOTE: The double update since an initial yield is needed to set the Routine (r).
                    #       Currently there doesn't seem to be a way to "seed" the Routine without doing this.
                    r.Update(ue.CsDeltaTime())
                    r.Update(ue.CsDeltaTime())

                #LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? TransactionType::Start : TransactionType::Allocate, R);

                payload.Reset()
                self.Manager_Payload.Deallocate(payloadContainer)
                return r.GetHandle()

            def Start(self, ownerID: int, payload: PayloadType) -> FCsRoutineHandle:
                return self.StartByContainer(ownerID, self.GetPayloadContainer(payload))

            def StartChildByContainer(self, ownerID: int, payloadContainer: FPyResourceContainer[PayloadType]) -> FCsRoutineHandle:
                context: str = __class__.StartChildByContainer.__qualname__
                
                check(self.Manager_OwnerID.IsAllocatedChecked(context, ownerID))

                payload: PayloadType = payloadContainer.Get()

                checkf(IsValidObject(payload), f"{context}: payloadContainer does NOT contain a reference to a payload.")
                checkf(payload.IsValidChecked(context))
                checkf(UpdateGroupLibrary.equal_equal(self.Group, payload.Group), f"{context}: Mismatch between payload.Group: {payload.Group.name_internal} and Group: {self.Group.name_internal}")

                parentContainer: FPyResourceContainer[FPyRoutine] = self.GetRoutineContainer(payload.ParentHandle)

                checkf(IsValidObject(parentContainer), f"{context}: Failed to find a container for payload.")

                parent: FPyRoutine    = parentContainer.Get()
                lastChild: FPyRoutine = parent.GetLastChild()

                routineContainer: FPyResourceContainer[FPyRoutine] = None

                # Add after Last Child
                if lastChild != None:
                    lastChildContainer: FPyResourceContainer[FPyRoutine] = self.Manager_Routine.GetAt(lastChild.GetIndex())

                    routineContainer = self.Manager_Routine.AllocateAfter(lastChildContainer)
                # Add after Parent
                else:
                    routineContainer = self.Manager_Routine.AllocateAfter(parentContainer)

                r: FPyRoutine = routineContainer.Get()

                checkf(self.RoutineStrideByOwnerID[ownerID] < self.MaxRoutinesPerOwner, f"{context}: Owner ID: {ownerID} has ALREADY allocated {self.RoutineStrideByOwnerID[ownerID]} Max Routines Per Owner: {self.MaxRoutinesPerOwner}.")
    
                routineIdIndex: int		             = (ownerID * self.MaxRoutinesPerOwner) + self.RoutineStrideByOwnerID[ownerID]
                self.OwnerRoutineIDs[routineIdIndex] = r.GetIndex()

                self.RoutineStrideByOwnerID[ownerID] += 1

                parent.AddChild(r)

                r.Init(payload)

                r.StartUpdate()
                # NOTE: The double update since an initial yield is needed to set the Routine (r).
                #       Currently there doesn't seem to be a way to "seed" the Routine without doing this.
                r.Update(ue.CsDeltaTime())
                r.Update(ue.CsDeltaTime())

                payload.Reset()
                #UE_LOG(LogCs, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
                return r.GetHandle()

            def StartChild(self, ownerID: int, payload: PayloadType) -> FCsRoutineHandle:
                return self.StartChildByContainer(self.GetPayloadContainer(payload))

            #endregion Start

            # End
            #region End
            # public:

            def EndAll(self):
                """
                End all coroutines.
                """ 
                result: bool = False

                current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetAllocatedHead()
                next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]	 = current

                while next != None:
                    current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]	   = next
                    routineContainer: FPyResourceContainer[FPyRoutine] = current.Element
                    next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]		   = current.GetNextLink()

                    r: FPyRoutine = routineContainer.Get()

                    r.End(EndReasonType.Shutdown)

                    #LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

                    r.Reset()
                    self.Manager_Routine.Deallocate(routineContainer)

                    result = True
                return result

            def End(self, ownerID: int) -> bool:
                """
                End all routines associated with the ownerID.

                :param int ownerID:
                :return bool:       Whether the routine has successful ended.
                                    NOTE: If the routine has already ended, this will return false.
                """ 
                context: str = __class__.End.__qualname__

                result: bool = False

                if self.Manager_OwnerID.IsAllocated(ownerID) == False:
                    return False

                start: int  = ownerID * self.MaxRoutinesPerOwner
                stride: int	= self.RoutineStrideByOwnerID[ownerID]
                        
                for i in range(0, stride):
                    index: int        = start + i
                    routineIndex: int = self.OwnerRoutineIDs[index]

                    routineContainer: FPyResourceContainer[FPyRoutine] = self.Manager_Routine.GetAt(routineIndex)
                    r: FPyRoutine				           = routineContainer.Get()

                    # If the Routine is currently being Updated, queue the End for either the
                    # beginning of the next Update or the end of the current Update.
                    if r.IsUpdateComplete() == False:
                        handleStride: int = self.QueueEndHandleStrideByOwnerID[ownerID]
                        handleIndex: int  = (ownerID * self.MaxRoutinesPerOwner) + handleStride

                        self.OwnerQueueEndHandles[handleIndex] = r.GetHandle()

                        self.QueueEndHandleStrideByOwnerID[ownerID] += 1
                        continue
                    
                    if r.HasEnded() == False:
                        r.End(EndReasonType.Shutdown)
                    
                    #LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

                    r.Reset()
                    self.Manager_Routine.Deallocate(routineContainer)

                    result = True

                # Clear out routine information for ownerID
                self.RoutineStrideByOwnerID[ownerID] = 0

                for i in range(0, self.MaxRoutinesPerOwner):
                    index: int                  = start + i
                    self.OwnerRoutineIDs[index] = INDEX_NONE
                return result

            def EndHandle(self, ownerID: int, handle: FCsRoutineHandle) -> bool:
                """
                End the routine associated with the Handle.

                :param int ownerID:
                :param FCsRoutineHandle handle:   Handle to a routine.
                :return bool:                       Whether the routine has successful ended.
                                                    NOTE: If the routine has already ended, this will return false.
                """ 
                context: str = __class__.EndHandle.__qualname__

                container: FPyResourceContainer[FPyRoutine] = self.GetRoutineContainer(handle)

                if IsValidObject(container) == True:
                    r: FPyRoutine = container.Get()

                    # If the Routine has already Ended, exit
                    if (r.HasEnded() == True) or (r.HasJustEnded() == True):
                        return False

                    check(self.Manager_OwnerID.IsAllocatedChecked(context, ownerID))

                    # If the Routine is currently being Updated, queue the End for either the
                    # beginning of the next Update or the end of the current Update.
                    if r.IsUpdateComplete() == False:
                        stride: int = self.QueueEndHandleStrideByOwnerID[ownerID]
                        index: int  = (ownerID * self.MaxRoutinesPerOwner) + stride

                        self.OwnerQueueEndHandles[index] = handle

                        self.QueueEndHandleStrideByOwnerID[ownerID] += 1
                        return False

                    r.End(EndReasonType.Manual)

                    #LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

                    r.Reset()
                    self.Manager_Routine.Deallocate(container)
                    return True
                return False

            def HasEnded(self, handle: FCsRoutineHandle) -> bool:
                """
                Check if a routine associated with the Handle has already ended.
                 NOTE: This returns True if Handle is NOT Valid.

                :param FCsRoutineHandle handle:   Handle to a routine.
                :return bool:                       Whether the routine has already ended.
                """ 
                r: FPyRoutine = self.GetRoutine(handle)

                if IsValidObject(r) == True:
                    return r.HasEnded()
                return True

            def HasJustEnded(self, handle: FCsRoutineHandle) -> bool:
                """
                Check if a routine associated with the Handle has just ended.

                :param FCsRoutineHandle handle:   Handle to a routine.
                :return bool:                       Whether the routine has already ended.
                """ 
                r: FPyRoutine = self.GetRoutine(handle)

                if IsValidObject(r) == True:
                    return r.HasJustEnded()
                return True

            #endregion End

            # Update
            #region Update
            # public:

            def Update(self, ownerID: int, deltaTime: ue.CsDeltaTime):
                context: str = __class__.Update.__qualname__
                
                check(self.Manager_OwnerID.IsAllocatedChecked(context, ownerID))

                # End any pending Handles requested for End from the previous Update
                if True:
                    stride = self.QueueEndHandleStrideByOwnerID[ownerID]
                    start  = ownerID * self.MaxRoutinesPerOwner
                    
                    for i in range(0, stride):
                        index: int                  = start + i
                        handle: FCsRoutineHandle  = self.OwnerQueueEndHandles[index]

                        self.End(ownerID, handle)

                        self.OwnerQueueEndHandles[index] = None

                    self.QueueEndHandleStrideByOwnerID[ownerID] = 0

                if True:
                    start: int  = ownerID * self.MaxRoutinesPerOwner
                    stride: int = self.RoutineStrideByOwnerID[ownerID]
                            
                    # Indices "with in" the Stride (local to the Stride, so in the Range [0, Stride - 1])
                    indicesToDeallocate: list[int] = []

                    for i in range(0, stride):
                        index: int        = start + i
                        routineIndex: int = self.OwnerRoutineIDs[index]

                        routineContainer: FPyResourceContainer[FPyRoutine] = self.Manager_Routine.GetAt(routineIndex)
                        r: FPyRoutine                          = routineContainer.Get()

                        state: StateType = r.State
                        
                        # Init -> Update
                        if state == StateType.Init:
                            r.StartUpdate()
                            r.Update(deltaTime)
                        # Update
                        elif state == StateType.Update:
                            r.Update(deltaTime)

                        # End
                        if state == StateType.End:
                            #LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

                            r.Reset()
                            self.Manager_Routine.Deallocate(routineContainer)

                            indicesToDeallocate.append(i)
                    
                    # "Bubble" the Routines that have Ended to the End of the Stride
                    for i in range(stride - 1, -1, -1):
                        if i in indicesToDeallocate:
                            continue
                    
                        for j in range(i, stride -1):
                            index: int                      = start + j
                            temp: int			            = self.OwnerRoutineIDs[index + 1]
                            self.OwnerRoutineIDs[index + 1] = self.OwnerRoutineIDs[index]
                            self.OwnerRoutineIDs[index]	    = temp

                    self.RoutineStrideByOwnerID[ownerID] -= len(indicesToDeallocate)

                # End any Handles requested for End on the current Update
                if True:
                    stride: int = self.QueueEndHandleStrideByOwnerID[ownerID]
                    start: int  = ownerID * self.MaxRoutinesPerOwner
                    
                    for i in range(0, stride):
                        index: int                  = start + i
                        handle: FCsRoutineHandle  = self.OwnerQueueEndHandles[index]

                        self.End(ownerID, handle)

                        self.OwnerQueueEndHandles[index] = None

                    self.QueueEndHandleStrideByOwnerID[ownerID] = 0

            #endregion Update

            # Payload
            #region Payload
            # public:

            def AllocatePayloadContainer(self) -> FPyResourceContainer[PayloadType]:
                return self.Manager_Payload.Allocate()

            def AllocatePayload(self) -> PayloadType:
                return self.Manager_Payload.AllocateResource()

            # protected:

            def GetPayloadContainer(self, payload: PayloadType) -> FPyResourceContainer[PayloadType]:
                if payload.GetIndex() == INDEX_NONE:
                    container: FPyResourceContainer[PayloadType] = self.Manager_Payload.Allocate()
                    p: PayloadType		                         = container.Get()

                    p.Copy(payload)

                    return container
                return self.Manager_Payload.GetAt(payload.GetIndex())

            #endregion Payloads

            # Message
            #region Message
            # public:

            def BroadcastMessage(self, type: MessageType, message: str, owner: object):
                current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]] = self.Manager_Routine.GetAllocatedHead()
                next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]    = current

                while next != None:
                    current: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]  = next
                    routineContainer: FPyResourceContainer[FPyRoutine]                  = current.Element
                    next: FPyDoubleLinkedListNode[FPyResourceContainer[FPyRoutine]]     = current.GetNextLink()

                    r = routineContainer.Get();

                    if IsValidObject(owner) == True:
                        if r.Owner.Owner == owner:
                            r.ReceiveMessage(type, message)
                    else:
                        r.ReceiveMessage(type, message)
            #endregion Message