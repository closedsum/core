/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

module.exports = class FJsCore
{
    constructor()
    {
        this.Engine = null;
        this.GameInstance = null;
        this.Manager_Time = null;
        this.Coordinator_GameEvent = null;
        this.World = null;
        this.GameState = null;
        this.PlayerController = null;
        this.PlayerState = null;
        this.PlayerPawn = null;

        this.CoroutineScheduler = null;

        this.Classes = new Map();
    }

    GetEngine() { return this.Engine; }
    GetGameInstance() { return this.GameInstance; }
    GetManager_Time() { return this.Manager_Time; }
    GetCoordinator_GameEvent() { return this.Coordinator_GameEvent; }
    GetWorld() { return this.World; }
    GetGameState() { return this.GameState; }
    GetPlayerController() { return this.PlayerController; }
    GetPlayerState() { this.PlayerState; }
    GetPlayerPawn() { this.PlayerPawn; }
    GetCoroutineScheduler() { return this.CoroutineScheduler; }

    GetClassChecked(context, className)
    {
        let args = [{value: className, type: "string"}];

        check(FunctionLibrary.IsArgsValidChecked(context, args));
        check(CommonLibrary.IsStringNotEmptyChecked(context, className));

        let c = this.Classes.get(className);

        check(CommonLibrary.IsClassChecked(context, c));
        return c;
    }

    CompileClasses(){}

    Init(){}
};