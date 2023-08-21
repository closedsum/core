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
        * @returns {SkeletalMesh}
        */
        Get(): SkeletalMesh;
        /**
        * @param {SkeletalMesh}
        */
        Set(ac: SkeletalMesh): void;
    }
}

declare type FSkeletalMesh = NJsTypes.FSkeletalMesh;