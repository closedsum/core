// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

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

    // #region Number

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        IsGreaterThanChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a   
        * @param {number}       b   
        * @returns {boolean}
        */
        IsGreaterThanChecked2(a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        IsGreaterThanOrEqualChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a   
        * @param {number}       b   
        * @returns {boolean}
        */
        IsGreaterThanOrEqualChecked2(a: number, b: number): boolean;

         /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           
        * @param {number}       b           
        * @returns {boolean}
        */
        IsLessThanChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a  
        * @param {number}       b  
        * @returns {boolean}
        */
        IsLessThanChecked2(a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context    The calling context.
        * @param {number}       a          
        * @param {number}       b          
        * @returns {boolean}
        */
        IsLessThanOrEqualChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a  int
        * @param {number}       b  int
        * @returns {boolean}
        */
        IsLessThanOrEqualChecked2(a: number, b: number): boolean;
        
    // #endregion Number

    // #region Int

        /**
        * Get whether or not 'a' is a positive integer (a > 0). 
        * 
        * @param {number}       a   int
        * @returns {boolean}
        */
        IsPositiveInt(a: number): boolean;
 
        /**
        * Get whether or not 'a' is a positive integer (a > 0).
        *  Assert if NOT.   
        * 
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @returns {boolean}
        */
        IsPositiveIntChecked(context: string, a: number): boolean;
 
        /**
        * Get whether or not 'a' is a positive integer (a > 0).
        *  Assert if NOT.   
        * 
        * @param {number}       a   int
        * @returns {boolean}
        */
        IsPositiveIntChecked2(a: number): boolean;

        /**
        * Get whether or not 'a' is a non-negative integer (a >= 0).
        *   
        * @param {number}       a   int
        * @returns {boolean}
        */
        IsNonNegativeInt(a: number): boolean;

        /**
        * Get whether or not 'a' is a non-negative integer (a >= 0).
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @returns {boolean}
        */
        IsNonNegativeIntChecked(context: string, a: number): boolean;

        /**
        * Get whether or not 'a' is a non-negative integer (a >= 0).
        *  Assert if NOT.  
        * 
        * @param {number}       a   int
        * @returns {boolean}
        */
        IsNonNegativeIntChecked2(a: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        IsIntGreaterThanChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a   int
        * @param {number}       b   int
        * @returns {boolean}
        */
        IsIntGreaterThanChecked2(a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
        IsIntGreaterThanOrEqualChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a   int
        * @param {number}       b   int
        * @returns {boolean}
        */
        IsIntGreaterThanOrEqualChecked2(a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           int
        * @param {number}       b           int
        * @returns {boolean}
        */
         IsIntLessThanChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a  int
        * @param {number}       b  int
        * @returns {boolean}
        */
        IsIntLessThanChecked2(a: number, b: number): boolean;
 
        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context    The calling context.
        * @param {number}       a          int
        * @param {number}       b          int
        * @returns {boolean}
        */
        IsIntLessThanOrEqualChecked(context: string, a: number, b: number): boolean;
 
        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a  int
        * @param {number}       b  int
        * @returns {boolean}
        */
        IsIntLessThanOrEqualChecked2(a: number, b: number): boolean;

    // #endregion Int

    // #region Float
    
        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        IsFloatGreaterThanChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN (>) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a   float
        * @param {number}       b   float
        * @returns {boolean}
        */
        IsFloatGreaterThanChecked2(a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        IsFloatGreaterThanOrEqualChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is GREATER THAN OR EQUAL (>=) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a   float
        * @param {number}       b   float
        * @returns {boolean}
        */
        IsFloatGreaterThanOrEqualChecked2(a: number, b: number): boolean;

         /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context     The calling context.
        * @param {number}       a           float
        * @param {number}       b           float
        * @returns {boolean}
        */
        IsFloatLessThanChecked(context: string, a: number, b: number): boolean;

        /**
        * Get whether or not 'a' is LESS THAN (<) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a  float
        * @param {number}       b  float
        * @returns {boolean}
        */
        IsFloatLessThanChecked2(a: number, b: number): boolean;
 
        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT. 
        *  
        * @param {string}       context    The calling context.
        * @param {number}       a          float
        * @param {number}       b          float
        * @returns {boolean}
        */
        IsFloatLessThanOrEqualChecked(context: string, a: number, b: number): boolean;
 
        /**
        * Get whether or not 'a' is LESS THAN OR EQUAL (<=) 'b'.
        *  Assert if NOT.  
        * 
        * @param {number}       a  float
        * @param {number}       b  float
        * @returns {boolean}
        */
        IsFloatLessThanOrEqualChecked2(a: number, b: number): boolean;

    // #endregion Float
    }
}

declare type JsMathLibrary = NJsMath.FLibrary;