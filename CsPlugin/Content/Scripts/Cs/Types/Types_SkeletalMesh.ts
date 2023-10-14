// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>

// require('Cs/Types/Types_SkeletalMesh.js');

declare namespace NJsTypes {
    class FSkeletalMesh {
        Path: string;
        Mesh_Internal: SkeletalMesh;
        /**
        * @returns {string}
        */
        GetName(): string;
        /**
        * @returns {SkeletalMesh}
        */
        Get(): SkeletalMesh;
        /**
        * @param {SkeletalMesh}
        */
        Set(ac: SkeletalMesh): void;
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

declare type FSkeletalMesh = NJsTypes.FSkeletalMesh;