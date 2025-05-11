# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import unreal as ue
from typing import TYPE_CHECKING

# TYPE_CHECKING

if TYPE_CHECKING:
    # Core
    # - Cs/Core.py
    import Cs.Core as Cs_Core
    # Coroutine
    # - Cs/Coroutine/CoroutineScheduler.py
    import Cs.Coroutine.CoroutineScheduler as Cs_Coroutine_CoroutineScheduler
    # - Cs/Coroutine/Routine.py
    import Cs.Coroutine.Routine as Cs_Routine
    # - Cs/Coroutine/Types_Coroutine.py
    import Cs.Coroutine.Types_Coroutine as Cs_Coroutine_Types_Coroutine

if TYPE_CHECKING:
    # "alias" - class (py)
    FPyCore = Cs_Core.FPyCore
    FPyCoroutineScheduler = Cs_Coroutine_CoroutineScheduler.FPyCoroutineScheduler
    # "alias" - struct (py)
    FPyRoutine = Cs_Routine.FPyRoutine
    FPyCoroutinePayload = Cs_Coroutine_Types_Coroutine.NPyCoroutine.NPayload.FImpl

# IMPORT

# Types
# - Cs/Types/MulticastDelegate.py
import Cs.Types.Delegate.MulticastDelegate as Cs_MulticastDelegate

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# ALIAS

# "alias" - library (c++)
CsUpdateGroupLibrary = ue.CsScriptLibrary_UpdateGroup

# "alias" - struct (c++)
FCsRoutineHandle = ue.CsRoutineHandle
FECsUpdateGroup = ue.ECsUpdateGroup

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "alias" - class (py)
FPyMulticastDelegate = Cs_MulticastDelegate.FPyMulticastDelegate

# "alias" - function (py)
checkf               = FPyCommonLibrary.checkf
IsValidObject        = FPyCommonLibrary.IsValidObject
IsValidObjectChecked = FPyCommonLibrary.IsValidObjectChecked

class FPyHeartbeat:
    def __init__(self):
        self.Interval: float = 1.0
        self.bSilent: bool = False
        self.StartInternalHandle: FCsRoutineHandle = None
        self.OnThrob_Event: FPyMulticastDelegate = FPyMulticastDelegate()

    def Init(self, core: 'FPyCore'):
        self.Core = core

     # IPyCsShutdown

    def HasShutdown(self) -> bool:
        return self.bShutdown

    def Shutdown(self):
        context: str = __class__.Shutdown.__qualname__

        self.bShutdown = True

        if IsValidObject(self.Core) == True:
            # End coroutines
            scheduler: 'FPyCoroutineScheduler' = self.Core.GetCoroutineScheduler()
        
            if IsValidObject(scheduler) == True:
                group: FECsUpdateGroup = CsUpdateGroupLibrary.get("GameState")

                handles: list[FCsRoutineHandle] = []

                if IsValidObject(self.StartInternalHandle):
                    handles.append(self.StartInternalHandle)

                for h in handles:
                    if IsValidObject(h) == True:
                        scheduler.EndByHandle(group, h)
        self.StartInternalHandle = None
        self.OnThrob_Event.Clear()
        self.Core = None
         
    def SetSilent(self, bSilent: bool):
        self.bSilent = bSilent

    def Start(self):
        scheduler                       = self.Core.GetCoroutineScheduler()
        group: FECsUpdateGroup          = CsUpdateGroupLibrary.get("GameState")
        payload: 'FPyCoroutinePayload'  = scheduler.AllocatePayload(group)

        func = self.Start_Internal()
        payload.CoroutineImpl = func
        payload.Owner.SetObject(self.Core.GetWorld())

        self.StartInternalHandleHandle = scheduler.Start(payload)

    def Start_Internal(self):
        context: str = self.Start_Internal.__qualname__
        # START COROUTINE
        r = yield
        
        
        while True:
            if not self.bSilent:
                ue.log("Heartbeat")

            self.OnThrob_Event.Broadcast()

            # Wait for Interval
            r = yield {"WaitForTime": 1.0}

        # END COROUTINE
        r = yield EndReasonType.EndOfExecution