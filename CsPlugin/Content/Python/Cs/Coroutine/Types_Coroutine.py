# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue
from enum import Enum
import copy

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

INDEX_NONE = -1

ROUTINE_VALUE_SIZE = 16

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - functions
check           = CommonLibrary.check
checkf          = CommonLibrary.checkf
IsValidObject   = CommonLibrary.IsValidObject

class NPyCoroutine:
    class EState(Enum): 
        Free = 0
        Init = 1
        Update = 2
        End = 3
        EState_MAX = 4

    class EMessage(Enum):
        Notify = 0
        Listen = 1
        Abort = 2
        EMessage_MAX = 3

    class EEndReason(Enum):
        EndOfExecution = 0
        AbortMessage = 1
        AbortCondition = 2
        OwnerIsInvalid = 3
        Parent = 4
        UniqueInstance = 5
        Shutdown = 6
        Manual = 7
        EEndReason_MAX = 8

    class FOwner:
        class NCached:
            class NStr:
                SetObject: str = "NPyCoroutine.FOwner.SetObject"
        def __init__(self):
            self.Owner: object = None
            self.UEObject: ue.Object = None
            self.bObject: bool = False
            self.UEActor: ue.Actor = None

        def IsObject(self) -> bool:
             return self.bObject

        def SetObject(self, o: any):
            context: str = NPyCoroutine.FOwner.NCached.NStr.SetObject

            self.Owner = o

            if (isinstance(o, ue.Object)):
                self.UEObject = o
                self.bObject = True

            checkf(self.bObject, context + ": o is NOT a UObject.")

            if (isinstance(o, ue.Actor)):
                self.UEActor = o

        def Copy(self, b: any):
            checkf(isinstance(b, NPyCoroutine.FOwner), "b is NOT of type: NPyCoroutine.FOwner")
            
            self.Owner    = b.Owner
            self.UEObject = b.UEObject
            self.bObject  = b.bObject
            self.UEActor  = b.UEActor

        def Reset(self):
            self.Owner    = None
            self.UEObject = None
            self.bObject  = False
            self.UEActor  = None

    class NRegister:
        class FInfo:
            def __init__(self):
                self.Index = INDEX_NONE

        class FMap:
            def __init__(self):
                self.Infos = []

                self.Values     = [None] * ROUTINE_VALUE_SIZE
                self.UsedValues = [False] * ROUTINE_VALUE_SIZE

            def SetUsedValue(self, index: int):
                if (self.UsedValues[index] == False):
                    info        = NPyCoroutine.NRegister.FInfo()
                    info.Index  = index;
                   
                    self.Infos.append(info)

                    self.UsedValues[index] = True
                    
            def SetValue(self, i: int, v: any):
                self.SetUsedValue(i)
                self.Values[i] = v

            def GetValue(self, i: int) -> any:
                self.SetUsedValue(i)
                return self.Values[i]

            def Reset(self):
                for info in self.Infos:
                    self.UsedValues[info.Index] = False
                self.Infos = []

    class NPayload:
        class FImpl:
            def __init__(self):
                self.Index = INDEX_NONE

                UpdateGroupLibrary = ue.CsScriptLibrary_UpdateGroup
                self.Group         = UpdateGroupLibrary.get_max()

                self.CoroutineImpl = None
                self.StartTime = ue.CsTime()
                self.Owner = NPyCoroutine.FOwner()
                self.AbortImpls = []
                self.OnAborts = []
                self.OnEnds = []
                self.ParentHandle = ue.CsRoutineHandle()
                self.bDoInit = True
                self.bPerformFirstUpdate = True
                self.AbortMessages = []
                self.RegisterMap = NPyCoroutine.NRegister.FMap()
                self.Name = ""

            def SetIndex(self, index: int):
                 self.Index = index

            def GetIndex(self):
                return self.Index

            def SetValue(self, index: int, value: any):
                self.RegisterMap.SetValue(index, value)

            def Reset(self):
                self.CoroutineImpl = None
                self.StartTime = ue.CsTime()
                self.Owner.Reset()
                self.AbortImpls = []
                self.OnAborts = []
                self.OnEnds = []
                self.ParentHandle = ue.CsRoutineHandle()
                self.bDoInit = True
                self.bPerformFirstUpdate = True
                self.AbortMessages = []
                self.RegisterMap.Reset()
                self.Name = ""

            def Copy(self, b: any):
                checkf(isinstance(b, NPyCoroutine.NPayload.FImpl), "b is NOT of type: NPyCoroutine.NPayload.FImpl")

                self.Index = b.Index
                self.Group = b.Group
                self.CoroutineImpl = b.CoroutineImpl
                self.StartTime = copy.deepcopy(b.StartTime)
                self.Owner = b.Owner
                self.AbortImpls = copy.deepcopy(b.AbortImpls)
                self.OnAborts = copy.deepcopy(b.OnAborts)
                self.OnEnds = copy.deepcopy(b.OnEnds)
                self.ParentHandle = copy.deepcopy(b.ParentHandle)
                self.bDoInit = b.bDoInit
                self.bPerformFirstUpdate = b.bPerformFirstUpdate
                self.AbortMessages = copy.deepcopy(b.AbortMessages)
                # NOTE: Should create / use a copy function
                self.RegisterMap = copy.deepcopy(b.RegisterMap)
                self.Name = b.Name

            def IsValidChecked(self, context: str) -> bool:
                # TODO: Check self.CoroutineImpl is callable
                #check(isinstance(self.CoroutineImpl, types.GeneratorType))
                return True