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