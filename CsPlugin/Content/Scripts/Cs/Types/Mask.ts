// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>

// require('Cs/Types/Mask.js');

declare class FJsMask 
{
    Value: number;
    /**
    * @param {number}
    */
    Equal(val: number): void;
    /**
    */
    Reset(): void;
    /**
    * @returns {boolean}
    */
    AnySet(): boolean;
    /**
    * @param {number}
    */
    Set(bit: number): void;
    /**
    * @param {number}
    */
    Clear(bit: number): void;
    /**
    * @param {number}
    * @returns {boolean}
    */
    Test(bit: number): boolean;
}