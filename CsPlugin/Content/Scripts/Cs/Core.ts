/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

// require("Cs/Core.js");

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