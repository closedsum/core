// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

declare namespace NJsYield {
    class FFunction {
        Fn: (args: any[]) => boolean;
        Caller: object;
        Args: any[];

        SetCore(core: object): void;

        /**
        * @param {object} yieldCommand 
        * @returns {boolean}
        */
        CopyFromYield(yieldCommand: object): boolean;

        /**
        * @returns {boolean}
        */
        Execute(): boolean;

        Reset(): void;
    }
}