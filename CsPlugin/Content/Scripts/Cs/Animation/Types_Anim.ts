// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>

// require('Cs/Animation/Types_Anim.js');

declare namespace NJsTypes {
    class FAnimBlueprint {
        Path: string;
        Blueprint_Internal: AnimBlueprintGeneratedClass;
        /**
        * @return {string} 
        */
        GetName(): string;
        /**
        * @returns {AnimBlueprintGeneratedClass}
        */
        Get(): AnimBlueprintGeneratedClass;
        /**
        * @param {AnimBlueprintGeneratedClass}  ac
        */
        Set(ac: AnimBlueprintGeneratedClass): void;
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
    }
    class FAnimSequence {
        Path: string;
        Anim_Internal: AnimSequence;
        /**
        * @return {string} 
        */
        GetName(): string;
        /**
        * @returns {AnimSequence}
        */
        Get(): AnimSequence;
        /**
        * @param {AnimSequence}  a
        */
        Set(a: AnimSequence): void;
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
    }
    class FBlendSpace {
        Path: string;
        Blend_Internal: BlendSpace;
        /**
        * @return {string} 
        */
        GetName(): string;
        /**
        * @returns {BlendSpace}
        */
        Get(): BlendSpace;
        /**
        * @param {BlendSpace}  b
        */
        Set(b: BlendSpace): void;
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
    }
    class FBlendSpace1D {
        Path: string;
        Blend_Internal: BlendSpace1D;
        /**
        * @return {string} 
        */
        GetName(): string;
        /**
        * @returns {BlendSpace1D}
        */
        Get(): BlendSpace1D;
        /**
        * @param {BlendSpace1D}  b
        */
        Set(b: BlendSpace1D): void;
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
    }
}

declare type FAnimBlueprint = NJsTypes.FAnimBlueprint;
declare type FAnimSequence = NJsTypes.FAnimSequence;
declare type FBlendSpace = NJsTypes.FBlendSpace;
declare type FBlendSpace1D = NJsTypes.FBlendSpace1D;