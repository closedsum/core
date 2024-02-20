/// <reference path="../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Managers
/// <reference path="Managers/Data/Manager_Data.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsFunction = require('Cs/Library/Library_Function.js');
// Managers
var FJsManager_Data = require('Cs/Managers/Data/Manager_Data.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;
var FunctionLibrary = NJsFunction.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;

// Constants
const INDEX_NONE = -1;

module.exports = class FJsCore
{
    static FScript = class Script
    {
        constructor()
        {
            /** @type {number} */           this.Index = INDEX_NONE;
            /** @type {Guid} */             this.Id = Guid.Invalidate_Guid();
            /** @type {FJsManager_Data} */  this.Manager_Data = new FJsManager_Data();
            /** @type {object[]} */         this.Objects = [];
        }

        /*number*/          GetIndex()          { return this.Index; }
        /*Guid*/            GetId()             { return this.Id; }
        /*FJsManager_Data*/ GetManager_Data()   { return this.Manager_Data; }

        Shutdown()
        {
            this.Index = INDEX_NONE;
            this.Id = Guid.Invalidate_Guid();
            this.Manager_Data.Shutdown();

            for (let o of this.Objects)
            {
                o.Shutdown();
            }
            this.Objects = [];

            this.Manager_Data = null;
        }

        /**
        * @param {object} o 
        */
        AddObject(o /*object*/)
        {
            // TODO: Check o has function Shutdown
            this.Objects.push(o);
        }
    }

    constructor()
    {
        /** @type {string} */           this.EntryFileName = "";
        /** @type {string} */           this.EntryFilePath = "";
        /** @type {UObject} */          this.ScriptOuter = null;
        /** @type {number} */           this.ScriptOuterId = INDEX_NONE;
        /** @type {GameEngine} */       this.Engine = null;
        /** @type {CsGameInstance} */   this.GameInstance = null;
        /** @type {CsManager_Time} */   this.Manager_Time = null;
        /** @type {CsCoordinator_GameEvent} */ this.Coordinator_GameEvent = null;
        /** @type {World} */            this.World = null;
        /** @type {GameState} */        this.GameState = null;
        /** @type {CsManager_Javascript} */ this.Manager_Javascript = null;
        /** @type {PlayerController}*/  this.PlayerController = null;
        /** @type {PlayerState} */      this.PlayerState = null;
        /** @type {Actor} */            this.PlayerPawn = null;

        /** @type {FJCoroutineScheduler} */ this.CoroutineScheduler = null;

        this.Classes = new Map();

        this.Script = new FJsCore.FScript();
    }

    /*string*/                  GetEntryFileName()      { return this.EntryFileName; }
    /*string*/                  GetEntryFilePath()      { return this.EntryFilePath; }
    /*UObject*/                 GetScriptOuter()        { return this.ScriptOuter; }
    /*number*/                  GetScriptOuterId()      { return this.ScriptOuterId; }
    /*GameEngine*/              GetEngine()             { return this.Engine; }
    /*CsGameInstance*/          GetGameInstance()       { return this.GameInstance; }
    /*CsManager_Time*/          GetManager_Time()       { return this.Manager_Time; }
    /*CsCoordinator_GameEvent*/ GetCoordinator_GameEvent() { return this.Coordinator_GameEvent; }
    /*World*/                   GetWorld()              { return this.World; }
    /*CsManager_Javascript*/    GetManager_Javascript() { return this.Manager_Javascript; }
    /*GameState*/               GetGameState()          { return this.GameState; }
    /*PlayerController*/        GetPlayerController()   { return this.PlayerController; }
    /*PlayerState*/             GetPlayerState()        { return this.PlayerState; }
    /*Actor*/                   GetPlayerPawn()         { return this.PlayerPawn; }
    /*FJCoroutineScheduler*/    GetCoroutineScheduler() { return this.CoroutineScheduler; }
    /*FJsCore.FScript*/         GetScript()             { return this.Script; }

    /**
     * @param {string} context 
     * @param {string} className 
     * @returns {Class}
     */
    GetClassChecked(context /*string*/, className /*string*/)
    {
        let args = [{value: className, type: "string"}];

        check(FunctionLibrary.IsArgsValidChecked(context, args));
        check(CommonLibrary.IsStringNotEmptyChecked(context, className));

        let c = this.Classes.get(className);

        check(CommonLibrary.IsClassChecked(context, c));
        return c;
    }

    IsInstanceOfChecked(context, o, className)
    {
        check(CommonLibrary.IsStringNotEmptyChecked(context, className));
        check(CommonLibrary.IsInstanceOfChecked(context, o, GetClassChecked(context, className)));

        return true;
    }

    CompileClasses(){}

    Init(){}

    Shutdown()
    {
        this.Script.Shutdown();
        this.Script = null;

        this.CoroutineScheduler.EndAll();
        this.CoroutineScheduler = null;

        this.EntryFileName = "";
        this.EntryFilePath = "";
        this.ScriptOuter = null;
        this.ScriptOuterId = INDEX_NONE;
        this.Engine = null;
        this.GameInstance = null;
        this.Manager_Time = null;
        this.Coordinator_GameEvent = null;
        this.World = null;
        this.GameState = null;
        this.PlayerController = null;
        this.PlayerState = null;
        this.PlayerPawn = null;

        this.Classes.clear();
    }
};