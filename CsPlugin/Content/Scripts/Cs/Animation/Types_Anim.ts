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
        * @returns {AnimBlueprintGeneratedClass}
        */
        Get(): AnimBlueprintGeneratedClass;
        /**
        * @param {AnimBlueprintGeneratedClass}
        */
        Set(ac: AnimBlueprintGeneratedClass): void;
    }
}

declare type FAnimBlueprint = NJsTypes.FAnimBlueprint;