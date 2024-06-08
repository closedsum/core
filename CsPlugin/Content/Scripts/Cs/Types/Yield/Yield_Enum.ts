// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../../Cs/Types/Enum/Enum.ts">/>
// ; typing info for auto-completion in Visual Studio Code

declare namespace NJsYield {
    class FEnum {
        Enum: FJsEnum.FValue;
        Type: FJsEnum;
        Value: FJsEnum.FValue;

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