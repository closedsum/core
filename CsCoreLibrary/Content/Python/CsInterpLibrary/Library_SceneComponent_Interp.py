# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue

# Core
# - Cs/Core.py
import Cs.Core as Cs_Core
# Types
# - CsInterpLibrary/Types/Types_SceneComponent_Interp.py
import CsInterpLibrary.Types.Types_SceneComponent_Interp as Cs_Types_SceneComponent_Interp
# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# Coroutine
# - Cs/Coroutine/CoroutineScheduler.py
import Cs.Coroutine.CoroutineScheduler as Cs_CoroutineScheduler
# - Cs/Coroutine/Types_Coroutine.py
import Cs.Coroutine.Types_Coroutine as Cs_Types_Coroutine
# - Cs/Coroutine/Routine.py
import Cs.Coroutine.Routine as Cs_Routine

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - library (c++)
ObjectLibrary       = ue.CsScriptLibrary_Object
UpdateGroupLibrary  = ue.CsScriptLibrary_UpdateGroup

# "typedefs" - class
FPyCore               = Cs_Core.FPyCore
FPyCoroutineScheduler = Cs_CoroutineScheduler.FPyCoroutineScheduler
PayloadType           = Cs_Types_Coroutine.NPyCoroutine.NPayload.FImpl
FPyRoutine            = Cs_Routine.FPyRoutine

# "typedefs" - functions
check           = CommonLibrary.check
checkf          = CommonLibrary.checkf

# "typedefs" - types
SceneComponentLaunchWithGravityParamsType = Cs_Types_SceneComponent_Interp.NPySceneComponent.NInterp.NLaunchWithGravity.FParams;
EndReasonType = Cs_Types_Coroutine.NPyCoroutine.EEndReason

class NPySceneComponent:
    class NInterp:
        class FLibrary:
            class NCached:
                class NStr:  
                    # Number
                    LaunchWithGravityChecked          = "NPySceneComponent.FLibrary.LaunchWithGravityChecked"
                    LaunchWithGravityChecked_Internal = "NPySceneComponent.FLibrary.LaunchWithGravityChecked_Internal"

            # class FDisableCheck:
            #     # Number
            #     @staticmethod
            #     def IsGreaterThanChecked(context: str, a: int | float, b: int | float) -> bool:
            #         return True
            #     @staticmethod
            #     def IsGreaterThanChecked2(a: int | float, b: int | float) -> 
            #         return True

            @staticmethod
            def LaunchWithGravityChecked_Internal():
                lib: NPySceneComponent.NInterp.FLibrary = NPySceneComponent.NInterp.FLibrary

                context: str = lib.NCached.NStr.LaunchWithGravityChecked_Internal
                
                # COROUTINE BEGIN
                r: FPyRoutine = yield
                
                totalTime: float    = 2.0
                halfTime: float     = 0.5 * totalTime
                elapsedTime: float  = 0.0
                gravity: float      = -980.0

                velocity: float = -gravity * halfTime
                
                params: SceneComponentLaunchWithGravityParamsType = r.GetValue(0)

                component: ue.SceneComponent = params.Component

                location: ue.Vector = component.get_world_location()
                initialZ: float     = location.z

                doCondition: bool = True

                while True:
                    if doCondition or (elapsedTime <= totalTime):
                        doCondition = False

                        if ObjectLibrary.is_valid_object(component) == False:
                            break

                        z: float = (velocity * elapsedTime) + 0.5 * (elapsedTime * elapsedTime) * gravity
                        z       += initialZ 

                        location.z = z

                        component.set_world_location(location, False, True)

                        r = yield

                        elapsedTime += r.DeltaTime.time
                    else:
                        break
                # COROUTINE END
                ue.log_warning("end of execution")
                r = yield EndReasonType.EndOfExecution
            @staticmethod
            def LaunchWithGravityChecked(context: str, params: SceneComponentLaunchWithGravityParamsType) -> ue.CsRoutineHandle:
                lib: NPySceneComponent.NInterp.FLibrary = NPySceneComponent.NInterp.FLibrary

                check(params.IsValidChecked(context))
                
                core: FPyCore = params.Core

                scheduler: FPyCoroutineScheduler = core.GetCoroutineScheduler()

                customGroup = UpdateGroupLibrary.get("Custom")
                
                # Custom
                if UpdateGroupLibrary.equal_equal(params.UpdateGroup, customGroup) == True:
                    groupIndex: int          = params.GroupIndex
                    ownerID: int             = params.OwnerID
                    payload: PayloadType     = scheduler.AllocateCustomPayload(groupIndex)
                    
                    func = lib.LaunchWithGravityChecked_Internal()     
                    payload.CoroutineImpl = func
                    payload.StartTime.time = 0.0
                    payload.Owner.SetObject(params.Component)

                    payload.SetValue(0, params)
                    
                    scheduler.CustomStart(groupIndex, ownerID, payload)
                # Default
                else:
                    group: ue.ECsUpdateGroup    = params.UpdateGroup
                    payload: PayloadType        = scheduler.AllocatePayload(group)

                    func = lib.LaunchWithGravityChecked_Internal()
                    payload.CoroutineImpl = func
                    payload.StartTime.time = 0.0
                    payload.Owner.SetObject(params.Component)

                    payload.SetValue(0, params)
                    
                    scheduler.Start(payload)