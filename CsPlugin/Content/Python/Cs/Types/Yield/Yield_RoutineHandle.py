# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - library (c++)
UpdateGroupLibrary = unreal.CsScriptLibrary_UpdateGroup
SchedulerLibrary = unreal.CsScriptLibrary_CoroutineScheduler

# "typedefs" - class

# "typedefs" - functions
check   = CommonLibrary.check
checkf  = CommonLibrary.checkf

class NPyYield:
    class FRoutineHandle:
        class NCached:
            class NStr:
                CopyFromYield = "NPyYield.FRoutineHandle.CopyFromYield"
                IsRunning = "NPyYield.FRoutineHandle.IsRunning"
        def __init__(self):
            # NOTE: FPyCore "typed" as any to prevent circular import
            self.Core: any = None
            self.Handle: unreal.CsRoutineHandle = None
            self.Group: unreal.ECsUpdateGroup = None
            self.bNative: bool = False

        # NOTE: FPyCore "typed" as any to prevent circular import
        def SetCore(self, core: any):
            self.Core = core

        def CopyFromYield(self, yieldCommand: dict) -> bool:
            context = NPyYield.FRoutineHandle.NCached.NStr.CopyFromYield

            check(CommonLibrary.IsValidDictChecked(context, yieldCommand))

            # Check 'WaitForRoutineHandle' key exists for yieldCommand
            if "WaitForRoutineHandle" in yieldCommand:
                # Check yieldCommand.WaitForRoutineHandle is of type: CsRoutineHandle
                check(CommonLibrary.IsInstanceOfChecked(context, yieldCommand["WaitForRoutineHandle"], unreal.CsRoutineHandle))
                # Check 'Group' key of type: ECsUpdateGroup exists for yieldCommand
                check(CommonLibrary.DoesKeyOfInstanceExistChecked(context, yieldCommand, 'Group', unreal.ECsUpdateGroup))
                # Check 'bNative' key of type: boolean exists for yieldCommand
                check(CommonLibrary.DoesKeyOfBoolExistChecked(context, yieldCommand, 'bNative'));

                self.Handle = yieldCommand["WaitForRoutineHandle"]
                self.Group = yieldCommand["Group"]
                self.bNative = yieldCommand["bNative"]

                # Check coroutine associated with handle is running
                groupName: str = UpdateGroupLibrary.to_string(self.Group)

                if self.bNative == True:
                    result: bool = SchedulerLibrary.is_running(context, self.Core.GetWorld(), self.Group,self.Handle)

                    checkf(result, context + ": coroutine assocated with NATIVE Handle for Group: " + groupName + " is NOT running.")
                else:
                    result: bool = self.Core.GetCoroutineScheduler().IsRunning(self.Group, self.Handle)

                    checkf(result, context + ": coroutine assocated with SCRIPT Handle for Group: " + groupName + " is NOT running.")
                return True
            return False

        def IsRunning(self) -> bool:
            context = NPyYield.FRoutineHandle.NCached.NStr.IsRunning

            if self.bNative == True:
                return SchedulerLibrary.is_running(context, self.Core.GetWorld(), self.Group, self.Handle)
            return self.Core.GetCoroutineScheduler().IsRunning(self.Group, self.Handle)
        
        def Execute(self) -> bool:
            return self.IsRunning()

        def Reset(self):
            self.Handle = None
            self.Group = None
            self.bNative = False