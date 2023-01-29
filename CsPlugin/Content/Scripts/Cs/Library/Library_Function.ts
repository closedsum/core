// require('Cs/Library/Library_Function.js');

declare namespace NJsFunction {
    class FLibrary {
        
        /**
        * @param {string}                  context 
        * @param {{type: any, value: any}} param 
        * @param {number}                  index       int 
        * @returns {boolean}
        */
        IsArgFormatValidChecked(context: string, param: {type: any, value: any}, index: number): boolean;
 
        /**
        * @param {string}                      context 
        * @param {{type: any, value: any}[]}   args 
        * @returns {boolean}
        */
        IsArgsValidChecked(context: string, args: {type: any, value: any}): boolean;
 
        /**
        * @param {string}      context 
        * @param {function}    fn 
        * @param {object}      caller 
        * @returns {boolean}
        */
        IsReturn_Bool_Checked(context: string, fn: (...args: any) => boolean, caller: object): boolean;
 
        /**
        * @param {function}    fn 
        * @param {object}      caller 
        * @returns {boolean}
        */
        IsReturn_Bool(fn: (...args: any) => boolean | any, caller: object | any): boolean;

        IsReturn_Int_Checked(context: string, fn: (...args: any) => number, caller: object): boolean;
 
        IsReturn_Int(fn: (...args: any) => number | any, caller: object | any); 
 
        IsReturn_Number_Checked(context: string, fn: (...args: any) => number, caller: object): boolean
 
        IsReturn_Number(fn: (...args: any) => number | any, caller: object | any): boolean;
 
        IsReturn_Array_Checked(context: string, fn: (...args: any) => any[], caller: object): boolean; 
 
        IsReturn_Array(fn: (...args: any) => any[] | any, caller: object | any): boolean;

        IsReturn_ArrayAndNotEmpty_Checked(context: string, fn: (...args: any) => any[], caller: object): boolean;
 
        IsReturn_ArrayAndNotEmpty(fn: (...args: any) => any[] | any, caller: object | any): boolean;
 
        IsReturn_Instance_Checked(context: string, fn: (...args: any) => object, caller: object, classType: object): boolean; 

        IsReturn_Instance(fn: (...args: any) => object | any, caller: object | any, classType: object | any): boolean; 

        IsReturn_Class_Checked(context: string, fn: (...args: any) => object, caller: object, classType: object): boolean; 
 
        IsReturn_Class(fn: (...args: any) => object | any, caller: object | any, classType: object | any): boolean; 
 
        IsReturn_Function_Checked(context: string, fn: (...args: any) => ((...args: any) => any), caller: object): boolean; 
 
        IsReturn_Function(fn: (...args: any) => ((...args: any) => any) | any, caller: object | any): boolean; 
 
        /**
        * @param {string}      context 
        * @param {function}    fn 
        * @param {number}      argCount    int 
        * @returns {boolean} 
        */
        IsArgCountChecked(context: string, fn: (...args: any) => any, argCount: number): boolean;
 
        /**
        * @param {function}    fn 
        * @param {number}      argCount    int
        * @returns {boolean} 
        */
        IsArgCount(fn: (...args: any) => any | any, argCount: number): boolean;
 
        /**
        * @param {string}      context
        * @param {function}    fn 
        * @param {number}      argCount    int
        * @param {object}      caller
        * @returns {boolean} 
        */
        IsArgCountAndReturn_Bool_Checked(context: string, fn: (...args: any) => boolean, argCount: number, caller: object, args: any[]): boolean;

        IsArgCountAndReturn_Bool(fn: (...args: any) => boolean | any, argCount: number, caller: object): boolean;
 
        IsArgCountAndReturn_Int_Checked(context: string, fn: (...args: any) => boolean, argCount: number, caller: object): boolean; 

        IsArgCountAndReturn_Int(fn: (...args: any) => number | any, argCount: number, caller: object): boolean;
 
        IsArgCountAndReturn_Number_Checked(context: string, fn: (...args: any) => number, argCount: number, caller: object): boolean;
 
        IsArgCountAndReturn_Number(fn: (...args: any) => number, argCount: number, caller: object): boolean; 
 
        IsArgCountAndReturn_ArrayAndNotEmpty_Checked(context: string, fn: (...args: any) => any[], argCount: number, caller: object): boolean; 
 
        IsArgCountAndReturn_ArrayAndNotEmpty(fn: (...args: any) => any[] | any, argCount: number, caller: object): boolean; 

        IsArgCountAndReturn_Instance_Checked(context: string, fn: (...args: any) => object, argCount: number, caller: object, classType: object): boolean; 
 
        IsArgCountAndReturn_Instance(fn: (...args: any) => object | any, argCount: number, caller: object, classType: object): boolean;
 
        IsArgCountAndReturn_Class_Checked(context: string, fn: (...args: any) => object, argCount: number, caller: object, classType: object): boolean; 
 
        IsArgCountAndReturn_Class(fn: (...args: any) => object | any, argCount: number, caller: object, classType: object): boolean; 
 
        IsArgCountAndReturn_Function_Checked(context: string, fn: (...args: any) => object, argCount: number, caller: object): boolean; 
 
        IsArgCountAndReturn_Function(fn: (...args: any) => object | any, argCount: number, caller: object): boolean;
    }
}

declare type FunctionLibrary = NJsFunction.FLibrary;