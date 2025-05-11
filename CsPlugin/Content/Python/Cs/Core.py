# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core

import unreal as ue

# IMPORT
# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# Coroutine
# - Cs/Coroutine/CoroutineScheduler.py
import Cs.Coroutine.CoroutineScheduler as Cs_CoroutineScheduler
# Utility
# - Cs/Utility/Heartbeat.py
import Cs.Utility.Heartbeat as Cs_Utility_Heartbeat

# ALIAS

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "alias" - class (py)
FPyCoroutineScheduler = Cs_CoroutineScheduler.FPyCoroutineScheduler
FPyHeartbeat = Cs_Utility_Heartbeat.FPyHeartbeat

# "alias" - functions (py)
check           = FPyCommonLibrary.check
checkf          = FPyCommonLibrary.checkf
IsValidObject   = FPyCommonLibrary.IsValidObject

# Constants
INDEX_NONE = -1

class FPyCore:
    class FScript:
        def __init__(self):
            self.Outer: 'FPyCore' = None
            self.Objects: list = []
            self.Heartbeat: FPyHeartbeat = FPyHeartbeat()

        def Init(self, core: 'FPyCore'):
            self.Outer = core
            self.Heartbeat.Init(core)

        def Shutdown(self):
            for o in self.Objects:
                o.Shutdown()

            if IsValidObject(self.Heartbeat) == True:
                self.Heartbeat.Shutdown()
            
            self.Outer = None
            self.Heartbeat = None
            self.Objects = []

        def GetHeartbeat(self) -> FPyHeartbeat:
            return self.Heartbeat

        def AddObject(self, o: object):
            # TODO: Check o has function Shutdown
            self.Objects.append(o)
    
    def __init__(self):
        context = "FPyCore.FScript.__init__"

        self.bShutdown: bool           = False
        self.bGameInstanceOrigin: bool = False

        self.Engine: ue.Engine                                  = ue.CsScriptLibrary_Engine.get()
        self.World: ue.World                                    = ue.CsScriptLibrary_Engine.get_world_object(context)
        self.GameInstance: ue.CsGameInstance                    = ue.CsScriptLibrary_GameInstanceImpl.get(context, self.World)
        self.Manager_Time: ue.CsManager_Time                    = ue.CsScriptLibrary_Manager_Time.get(context, self.World)
        self.Coordinator_GameEvent: ue.CsCoordinator_GameEvent  = ue.CsScriptLibrary_Coordinator_GameEvent.get(context, self.World)
        self.GameState: ue.GameStateBase                        = ue.CsScriptLibrary_GameState.get(context, self.World)
        self.PlayerController: ue.PlayerController              = ue.CsScriptLibrary_PlayerController.get_first_local(context, self.World)
        self.PlayerState: ue.PlayerState                        = self.PlayerController.player_state
        self.PlayerPawn: ue.Pawn                                = self.PlayerController.get_controlled_pawn()
        self.CoroutineScheduler: FPyCoroutineScheduler          = FPyCoroutineScheduler(self)

        self.Script: FPyCore.FScript = FPyCore.FScript()

    def GetEngine(self) -> ue.Engine:
        return self.Engine
    def GetGameInstance(self) -> ue.CsGameInstance:
        return self.GameInstance
    def GetManager_Time(self) -> ue.CsManager_Time:
        return self.Manager_Time
    def GetCoordinator_GameEvent(self) -> ue.CsCoordinator_GameEvent:
        return self.Coordinator_GameEvent
    def GetWorld(self) -> ue.World:
         return self.World
    def GetGameState(self) -> ue.GameStateBase:
        return self.GameState
    def GetPlayerController(self) -> ue.PlayerController:
        return self.PlayerController
    def GetPlayerState(self) -> ue.PlayerState:
        return self.PlayerState
    def GetPlayerPawn(self) -> ue.Pawn:
        return self.PlayerPawn
    def GetCoroutineScheduler(self) -> FPyCoroutineScheduler:
        return self.CoroutineScheduler
    def GetScript(self) -> 'FPyCore.FScript':
        return self.Script

    def Init(self):
        self.Script.Init(self)

    def HasShutdown(self) -> bool:
        return self.bShutdown
    
    def Shutdown(self):
        self.bShutdown = True

        if IsValidObject(self.Script) == True:
           self.Script.Shutdown()
        self.Script = None

        self.CoroutineScheduler.EndAll()
        self.CoroutineScheduler = None

        self.Engine = None
        self.GameInstance = None
        self.Manager_Time = None
        self.Coordinator_GameEvent = None
        self.World = None
        self.GameState = None
        self.PlayerController = None
        self.PlayerState = None
        self.PlayerPawn = None