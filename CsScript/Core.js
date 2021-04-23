/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class FJsCore
{
    constructor()
    {
        this.GameInstance = null;
        this.Manager_Time = null;
        this.World = null;
        this.GameState = null;
        this.PlayerController = null;
        this.PlayerState = null;
        this.PlayerPawn = null;

        this.CoroutineScheduler = null;
    }

    GetGameInstance() { return this.GameInstance; }
    GetManager_Time() { return this.Manager_Time; }
    GetWorld() { return this.World; }
    GetGameState() { return this.GameStates; }
    GetPlayerController() { return this.PlayerController; }
    GetPlayerState() { this.PlayerState; }
    GetPlayerPawn() { this.PlayerPawn; }
    GetCoroutineScheduler() { return this.CoroutineScheduler; }
};