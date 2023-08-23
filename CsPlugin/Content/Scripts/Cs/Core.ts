/// <reference path="../typings/ue.d.ts">/>
// Managers
/// <reference path="Managers/Data/Manager_Data.ts">/>

// require("Cs/Core.js");

declare namespace FJsCore {
        class FScript {
            Index: number;
            Id: Guid;
            Manager_Data: FJsManager_Data;
            Objects: object[];
            GetIndex(): number;
            GetId(): Guid;
            GetManager_Data(): FJsManager_Data;
            Shutdown(): void;
            AddObject(o: object): void;
    }
}

declare class FJsCore {
    ScriptOuter: UObject;
    ScriptOuterId: number;
    Engine: GameEngine;
    GameInstance: CsGameInstance;
    Manager_Time: CsManager_Time;
    Coordinator_GameEvent: CsCoordinator_GameEvent;
    World: World;
    GameState: GameState;
    Manager_Javascript: CsManager_Javascript;
    PlayerController: PlayerController;
    PlayerState: PlayerState;
    PlayerPawn: Actor;
    Script: FJsCore.FScript;
    //this.CoroutineScheduler = null;
    GetScriptOuter(): UObject;
    GetScriptOuterId(): number;
    GetEngine(): GameEngine;
    GetGameInstance(): CsGameInstance;
    GetManager_Time(): CsManager_Time;
    GetCoordinator_GameEvent(): CsCoordinator_GameEvent;
    GetWorld(): World;
    GetGameState(): GameState;
    GetManager_Javascript(): CsManager_Javascript;
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