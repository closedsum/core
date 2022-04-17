// require('Cs/Library/Library_Common.js');

declare namespace NJsCommon {
    class FLibrary {

        /**
        * [static] 
        * @param {boolean} condition 
        * @param {string} message 
        */
        checkf(condition: boolean, message: string): void;
 
        /**
        * @param {boolean} condition 
        */
        check(condition: boolean): void;
 
        /**
        * 
        * @param {any} o
        * @returns {boolean} 
        */
        IsDefined(o: any): boolean;

        /**
        * @param {object} o 
        * @returns {boolean}
        */
        IsNullObject(o: object): boolean;
 
        /**
        * @param {string} context 
        * @param {object} o 
        * @returns {boolean}
        */
        IsNullObjectChecked(context: string, o: object): boolean;
 
        /**
        * @param {object} o 
        * @returns {boolean}
        */
        IsValidObject(o: string): boolean;

        /**
        * @param {string} context
        * @param {object} o
        * @returns {boolean}
        */
        IsValidObjectChecked(context: string, o: object): boolean;
 
        IsFunction(func: object | any): boolean;
 
        IsFunctionChecked(context: string, func: object | any): boolean;
 
        IsGenerator(gen: object | any): boolean;
 
        IsGeneratorChecked(context: string, gen: object | any): boolean
 
        IsClass(c: object | any): boolean
 
        IsClassChecked(context: string, c: object): boolean;
 
        IsClassOf(a: object | any, c: object | any): boolean; 
 
        IsClassOfChecked(context: string, a: object, c: object): boolean;
 
        IsInstanceOf(a: object, c: object): boolean;
 
        IsInstanceOfChecked(context: string, a: object, c: object): boolean;
         
        IsBool(a: boolean | any): boolean;
 
        IsBoolChecked(context: string, a: boolean): boolean;
 
        IsInt(a: number | any): boolean;
 
        IsIntChecked(context: string, a: number | any): boolean;
 
        IsFloat(a: number | any): boolean;
 
        IsFloatChecked(context: string, a: number): boolean;
 
        IsNumberChecked(context: string, a: number): boolean;
 
        IsNumber(a: number): boolean;
 
        IsStringChecked(context: string, s: string): boolean;
 
        IsStringNotEmptyChecked(context: string, s: string): boolean;

        /**
        * @param {object} o 
        * @param {string} key
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