// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>

// require('Cs/Material/Types_Material.js');

declare namespace NJsTypes {
    class FUserWidget {
        Path: string[];
        Widget_Class: UnrealEngineClass;
        /**
        * @returns {string} 
        */
        GetName(): string;
        /**
        * @returns {UnrealEngineClass}
        */
        GetClass(): UnrealEngineClass;
        /**
        * @param {UnrealEngineClass}  widgetClass
        */
        Set(widgetClass: UnrealEngineClass): void;
        /**
        * @param {string}   context
        * @returns {boolean}
        */
        IsValidChecked(context: string): boolean;
        /**
        * @param {string} context 
        * @param {object} o 
        * @param {string} memberPath 
        */
        OverrideByUObject(context: string, o: object, memberPath: string): void;
        Load(): void;
        Unload(): void;
    }
}

declare type FUserWidget = NJsTypes.FUserWidget;