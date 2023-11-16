// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>

// require('Cs/Material/Types_Material.js');

declare namespace NJsTypes {
    class FMaterialInterface {
        Path: string;
        Material_Internal: MaterialInterface;
        /**
        * @returns {string} 
        */
        GetName(): string;
        /**
        * @returns {MaterialInterface}
        */
        Get(): MaterialInterface;
        /**
        * @param {MaterialInterface}  mat
        */
        Set(mat: MaterialInterface): void;
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
    class FTArrayMaterialInterface {
        Paths: string[];
        Materials_Internal: MaterialInterface[];
        /**
        * @returns {string} 
        */
        GetName(): string;
        /**
        * @returns {MaterialInterface[]}
        */
        Get(): MaterialInterface[];
        /**
        * @param {MaterialInterface[]}  mats
        */
        Set(mats: MaterialInterface[]): void;
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

declare type FMaterialInterface = NJsTypes.FMaterialInterface;
declare type FTArrayMaterialInterface = NJsTypes.FTArrayMaterialInterface;