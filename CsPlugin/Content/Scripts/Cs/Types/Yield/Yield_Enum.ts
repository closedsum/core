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