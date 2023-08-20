/// <reference path="../typings/ue.d.ts">/>

// require("Cs/Core.js");

declare namespace FJsCore {
        class FScript {
            Index: number;
            Manager_Data: FJsManager_Data;
    }
}

declare class FJsCore {
    Engine: GameEngine;
    GameInstance: CsGameInstance;
    Manager_Time: CsManager_Time;
    Coordinator_GameEvent: CsCoordinator_GameEvent;
    World: World;
    GameState: GameState;
    PlayerController: PlayerController;
    PlayerState: PlayerState;
    PlayerPawn: Actor;
    Script: FJsCore.FScript;
    //this.CoroutineScheduler = null;
    GetEngine(): GameEngine;
    GetGameInstance(): CsGameInstance;
    GetManager_Time(): CsManager_Time;
    GetCoordinator_GameEvent(): CsCoordinator_GameEvent;
    GetWorld(): World;
    GetGameState(): GameState;
    GetPlayerController(): PlayerController;
    GetPlayerState(): PlayerState;
    GetPlayerPawn(): Actor;
    //GetCoroutineScheduler(): ;
    GetScript(): FJsCore.FScript;

    /**
    * @param {string} context 
    * @param {string} className 
    * @returns {Class}
    */
    GetClassChecked(context: string, className: string): Class;

    IsInstanceOfChecked(context: string, o: object, className: string): boolean;

    CompileClasses():void;
    Init():void;
    Shutdown(): void;
}