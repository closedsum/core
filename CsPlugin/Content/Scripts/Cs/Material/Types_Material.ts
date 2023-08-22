// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>

// require('Cs/Material/Types_Material.js');

declare namespace NJsTypes {
    class FTArrayMaterialInterface {
        Path: string[];
        Mesh_Internal: MaterialInterface[];
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
    }
}

declare type FTArrayMaterialInterface = NJsTypes.FTArrayMaterialInterface;