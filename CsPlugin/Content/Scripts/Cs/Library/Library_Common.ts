// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// require('Cs/Library/Library_Common.js');

declare namespace NJsCommon {
    class FLibrary {

        /**
        * Assert if condition is FALSE and display a message.
        * 
        * @param {boolean}  condition 
        * @param {string}   message 
        */
        checkf(condition: boolean, message: string): void;
 
        /**
        * Assert if condition is FALSE. 
        * 
        * @param {boolean} condition 
        */
        check(condition: boolean): void;
 
        /**
        * Get whether or not 'o' is defined (NOT undefined).
        * 
        * @param {any}          o
        * @returns {boolean} 
        */
        IsDefined(o: any): boolean;

        /**
        * Get whether or not 'o' is null. 
        * 
        * @param {object}       o 
        * @returns {boolean}
        */
        IsNullObject(o: object): boolean;
 
        /**
        * Get whether or not 'o' is null. 
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {object}       o 
        * @returns {boolean}
        */
        IsNullObjectChecked(context: string, o: object): boolean;
 
        /**
        * Get whether or not 'o' is a valid object. 
        * 
        * @param {object}   o 
        * @returns {boolean}
        */
        IsValidObject(o: object): boolean;

        /**
        * Get whether or not 'o' is a valid object.
        *  Assert if NOT.  
        * 
        * @param {string}       context
        * @param {object}       o
        * @returns {boolean}
        */
        IsValidObjectChecked(context: string, o: object): boolean;
 
        /**
        * Get whether or not 'func' is a function. 
        * 
        * @param {object | any} func 
        * @return {boolean}
        */
        IsFunction(func: object | any): boolean;
 
        /**
        * Get whether or not 'func' is a function. 
        *  Assert if NOT.
        * 
        * @param {string}       context
        * @param {object | any} func 
        * @return {boolean}
        */
        IsFunctionChecked(context: string, func: object | any): boolean;
 
        /**
        * Get whether or not 'gen' is a generator.  
        * 
        * @param {object | any}       gen 
        * @returns {boolean}
        */
        IsGenerator(gen: object | any): boolean;
 
        /**
        * Get whether or not 'gen' is a generator. 
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {object | any} gen 
        * @returns {boolean}
        */
        IsGeneratorChecked(context: string, gen: object | any): boolean
 
        /**
        * Get whether or not 'c' is a class.
        * 
        * @param {object}       c 
        * @returns {boolean}
        */
        IsClass(c: object | any): boolean
 
        /**
        * Get whether or not 'c' is a class.
        *  Assert if NOT.
        *  
        * @param {string}  context
        * @param {object}  c
        * @returns {boolean}
        */
        IsClassChecked(context: string, c: object): boolean;
 
        /**
        * Get whether or not 'a' is a class of 'c'.
        * 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        IsClassOf(a: object | any, c: object | any): boolean; 
 
        /**
        * Get whether or not 'a' is a class of 'c'.
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        IsClassOfChecked(context: string, a: object, c: object): boolean;
 
        /**
        * Get whether or not 'a' is an instance of 'c'.
        * 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        IsInstanceOf(a: object, c: object): boolean;
 
        /**
        * Get whether or not 'a' is an instance of 'c'.
        *  Assert if NOT.
        * 
        * @param {string}       context 
        * @param {object}       a 
        * @param {object}       c 
        * @returns {boolean}
        */
        IsInstanceOfChecked(context: string, a: object, c: object): boolean;
         
        /**
        * Get whether or not 'a' is a boolean.
        *  
        * @param {boolean}  a 
        * @returns {boolean}
        */
        IsBool(a: boolean | any): boolean;
 
        /**
        * Get whether or not 'a' is a boolean.
        *  Assert if NOT. 
        * 
        * @param {string}   context
        * @param {boolean}  a 
        * @returns {boolean}
        */
        IsBoolChecked(context: string, a: boolean): boolean;
 
        /**
        * Get whether or not 'a' is an integer. 
        * 
        * @param {number}   a 
        * @returns {boolean}
        */
        IsInt(a: number | any): boolean;
 
        /**
        * Get whether or not 'a' is an integer.
        *  Assert if NOT. 
        * 
        * @param {string}   context
        * @param {number}   a 
        * @returns {boolean}
        */
        IsIntChecked(context: string, a: number | any): boolean;
 
        /**
        * Get whether or not 'a' is an integer.
        *  Assert if NOT. 
        * 
        * @param {number}   a 
        * @returns {boolean}
        */
        IsIntChecked2(a: number | any): boolean;

        /**
        * Get whether or not 'a' is an float / double (number). 
        * 
        * @param {number}   a 
        * @returns {boolean}
        */
        IsFloat(a: number | any): boolean;
 
        /**
        * Get whether or not 'a' is an float / double (number). 
        *  Assert if NOT.
        * 
        * @param {string}   context
        * @param {number}   a 
        * @returns {boolean}
        */
        IsFloatChecked(context: string, a: number): boolean;
 
        /**
        * Get whether or not 'a' is an float / double (number). 
        *  Assert if NOT.
        * 
        * @param {number}   a 
        * @returns {boolean}
        */
        IsFloatChecked2(a: number): boolean;

        /**
        * Get whether or not 'a' is a number.
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {number}       a 
        * @returns {boolean}
        */
        IsNumberChecked(context: string, a: number): boolean;
 
        /**
        * Get whether or not 'a' is a number.
        * 
        * @param {number}       a 
        * @returns {boolean}
        */
        IsNumber(a: number): boolean;
 
        /**
        * Get whether or not 's' is a string.
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {string}       s 
        * @returns {boolean}
        */
        IsStringChecked(context: string, s: string): boolean;
 
        /**
        * Get whether or not 's' is a string.
        *  Assert if NOT. 
        * 
        * @param {string}       s 
        * @returns {boolean}
        */
        IsStringChecked2(s: string): boolean;

        /**
        * Get whether or not 's' is NOT empty ('')..
        *  Assert if NOT. 
        * 
        * @param {string}       context 
        * @param {string}       s 
        * @returns {boolean}
        */
        IsStringNotEmptyChecked(context: string, s: string): boolean;

        /**
        * Get wheter or not 'key' is a key / member of 'o'. 
        * 
        * @param {object}       o 
        * @param {string}       key
        * @returns {boolean} 
        */
        DoesKeyExist(o: object | any, key: string): boolean;
  
        /**
        * @param {string} context
        * @param {object} o 
        * @param {string} key
        * @returns {boolean} 
        */
        DoesKeyExistChecked(context: string, o: object, key: string): boolean;
 
        /**
        * @param {object} o 
        * @param {string} key
        * @returns {boolean} 
        */
        DoesKeyOfBoolExist(o: object | any, key: string): boolean;
   
        /**
        * @param {string} context
        * @param {object} o 
        * @param {string} key
        * @returns {boolean} 
        */
        DoesKeyOfBoolExistChecked(context: string, o: object, key: string): boolean;
 
        /**
        * @param {object} o 
        * @param {string} key
        * @returns {boolean} 
        */
        DoesKeyOfArrayExist(o: object | any, key: string): boolean;
 
        /**
        * @param {string} context
        * @param {object} o 
        * @param {string} key
        * @returns {boolean} 
        */
        DoesKeyOfArrayExistChecked(context: string, o: object, key: string): boolean;
 
        /**
        * @param {object} o 
        * @param {string} key
        * @param {function} classType
        * @returns {boolean} 
        */
        DoesKeyOfInstanceExist(o: object | any, key: string, classType: object): boolean;
   
        /**
        * @param {string} context
        * @param {object} o 
        * @param {string} key
        * @param {function} classType
        * @returns {boolean} 
        */
        DoesKeyOfInstanceExistChecked(context: string, o: object, key: string, classType: object): boolean;
 
        /**
        * @param {object} o 
        * @param {string} key
        * @param {function} classType
        * @returns {boolean} 
        */
        DoesKeyOfClassExist(o: object | any, key: string, classType: object): boolean;
  
        /**
        * @param {string} context
        * @param {object} o 
        * @param {string} key
        * @param {function} classType
        * @returns {boolean} 
        */
        DoesKeyOfClassExistChecked(context: string, o: object, key: string, classType: object): boolean;
 
        /**
        * @param {object} o 
        * @param {string} key
        * @param {function} fn
        * @returns {boolean} 
        */
        DoesKeyOfFunctionExist(o: object | any, key: string, fn: object | any): boolean;
  
        /**
        * @param {string} context
        * @param {object} o 
        * @param {string} key
        * @param {function} fn
        * @returns {boolean} 
        */
        DoesKeyOfFunctionExistChecked(context: string, o: object, key: string, fn: object): boolean;
    }
}

declare type CommonLibrary = NJsCommon.FLibrary;