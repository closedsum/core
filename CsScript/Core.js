/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class FJsCore
{
    constructor()
    {
        this.GameInstance = null;
        this.Manager_Time = null;
        this.Coordinator_GameEvent = null;
        this.World = null;
        this.GameState = null;
        this.PlayerController = null;
        this.PlayerState = null;
        this.PlayerPawn = null;

        this.CoroutineScheduler = null;
    }

    GetGameInstance() { return this.GameInstance; }
    GetManager_Time() { return this.Manager_Time; }
    GetCoordinator_GameEvent() { return this.Coordinator_GameEvent; }
    GetWorld() { return this.World; }
    GetGameState() { return this.GameState; }
    GetPlayerController() { return this.PlayerController; }
    GetPlayerState() { this.PlayerState; }
    GetPlayerPawn() { this.PlayerPawn; }
    GetCoroutineScheduler() { return this.CoroutineScheduler; }
};