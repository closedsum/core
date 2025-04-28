# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue

#Core
# - Cs/Core
import Cs.Core as Cs_Core
# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "typedefs" - library (py)
CommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "typedefs" - library (c++)
UpdateGroupLibrary = ue.CsScriptLibrary_UpdateGroup

# "typedefs" - class
FPyCore = Cs_Core.FPyCore

# "typedefs" - functions
check = CommonLibrary.check

INDEX_NONE = -1

class NPySceneComponent:
    class NInterp:
        class NLaunchWithGravity:
            class FParams:
                def __init__(self):
                    self.Core: FPyCore = None
                    self.UpdateGroup: ue.ECsUpdateGroup = UpdateGroupLibrary.get("GameState")
                    # GroupIndex is used if this.UpdateGroup == Custom
                    self.GroupIndex: int = INDEX_NONE
                    # OwnerID is used if this.UpdateGroup == Custom
                    self.OwnerID: int = INDEX_NONE
                    self.TotalTime: float = 0.0
                    self.Velocity: ue.Vector = ue.Vector(0.0, 0.0, 0.0)
                    self.GravityScale: float = 1.0
                    self.Gravity: float = -980.0
                    self.Component: ue.SceneComponent = None
                    self.bFallToGround: bool = False
                    self.GroundZ: float = 0.0

                def SetTotalTime(self, totalTime: float):
                    # TODO: Add checks
                    self.TotalTime  = totalTime
                    halfTime: float = 0.5 * self.TotalTime
                    self.Velocity.z = self.Gravity * halfTime

                def SetVelocity(self, velocity: ue.Vector):
                    # TODO: Add checks
                    halfTime: float = self.Velocity.z / self.Gravity
                    self.TotalTime = 2.0 * halfTime

                def IsValidChecked(self, context: str) -> bool:
                    return True

                def IsValid(self, context: str) -> bool:
                    return True