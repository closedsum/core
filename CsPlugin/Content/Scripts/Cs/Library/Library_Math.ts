// require('Cs/Library/Library_Math.js');

declare namespace NJsMath {
    class FLibrary {

        /**
        * @param {number}       bitmask 
        * @param {number}       bit
        * @returns {boolean}
        */
        BitFlag_Test(bitmask: number, bit: number): boolean;

        /**
        * @param {number}       bitmask 
        * @param {number}       bit
        * @returns {number}
        */
        BitFlag_Set(bitmask: number, bit: number): number;
 
        /**
        * @param {number}       bitmask 
        * @param {number}       bit
        * @returns {number}
        */
        BitFlag_Clear(bitmask: number, bit: number): number;

        /**
        * @param {number}       a 
        * @returns {boolean}
        */
        IsPositiveInt(a: number): boolean;
 
        /**
        * @param {string}       context
        * @param {number}       a 
        * @returns {boolean}
        */
        IsPositiveIntChecked(context: string, a: number): boolean;
 
        /**
        * @param {number}       a 
        * @returns {boolean}
        */
        IsNonNegativeInt(a: number): boolean;

        /**
        * @param {string}       context
        * @param {number}       a 
        * @returns {boolean}
        */
        IsNonNegativeIntChecked(context: string, a: number): boolean;
    }
}

declare type MathLibrary = NJsMath.FLibrary;