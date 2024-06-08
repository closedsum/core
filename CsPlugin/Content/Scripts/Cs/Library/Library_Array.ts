// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// require('Cs/Library/Library_Array.js');

declare namespace NJsArray {
    class FLibrary {
        
        /**
        * Get whether the Array 'a' is empty or not.
        * 
        * @param {Array}        a 
        * @returns {boolean}
        */
        IsEmpty(a: any[] | any): boolean;
 
        /**
        * Get whether the Array 'a' is NOT empty or not.
        *  Assert if NOT. 
        *  
        * @param {string}       context 
        * @param {Array}        a 
        * @returns {boolean}
        */
        IsNotEmptyChecked(context: string, a: any[]): boolean;
 
        /**
        * Get whether the Array 'a' is NOT empty or not.
        *  
        * @param {Array}        a 
        * @returns {boolean}
        */
        IsNotEmpty(a: any[] | any): boolean;
 
        /**
        * @param {Array}   a 
        * @param {number}  size    int
        * @returns {boolean} 
        */
        IsSize(a: any[] | any, size: number | any): boolean;
 
        /**
        * @param {string}  context
        * @param {Array}   a 
        * @param {number}  size    int
        * @returns {boolean} 
        */
        IsSizeChecked(context: string, a: any[], size: number): boolean;
 
        AreAllElements_Class_Checked(context: string, a: any[], classType: object): boolean;
 
        AreAllElements_Class(a: any[] | any, classType: object | any): boolean;

        AreAllElements2d_Class_Checked(context: string, a: any[][], classType: object): boolean;
 
        AreAllElements2d_Class(a: any[][] | any, classType: object | any): boolean;
 
        IsNotEmptyAndAllElements_Class_Checked(context: string, a: any[], classType: object): boolean;
 
        IsNotEmptyAndAllElements_Class(a: any[] | any, classType: object): boolean;
 
        IsNotEmptyAndAllElements2d_Class_Checked(context: string, a: any[][], classType: object): boolean;
 
        IsNotEmptyAndAllElements2d_Class(a: any[][], classType: object): boolean;
    }
}

declare type ArrayLibrary = NJsArray.FLibrary;