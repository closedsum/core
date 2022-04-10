/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

declare namespace NJsYield {
    class FRoutineHandle {
        Handle: CsRoutineHandle;
        Group: ECsUpdateGroup;
        bNative: boolean;

        SetCore(core: object): void;

        /**
        * @param {object} yieldCommand 
        * @returns {boolean}
        */
        CopyFromYield(yieldCommand: object): boolean;

        /**
        * @returns {boolean}
        */
        IsRunning(): boolean;
        
        /**
        * @returns {boolean}
        */
        Execute(): boolean;

        Reset(): void;
    }
}