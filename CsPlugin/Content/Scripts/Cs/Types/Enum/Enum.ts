/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

declare namespace FJsEnum {
    class FValue {
        Outer: FJsEnum;
        Name: string;
        Value: number;

        /**
        * @returns {FJsEnum}
        */
        GetOuter(): FJsEnum;

        /**
        * @returns {string}
        */
        GetName(): string;

        /**
        * @returns {number} int
        */
        GetValue(): number;

        /**
        * @returns {string} 
        */
        ToString(): string

        /**
        * '=' operator
        * 
        * @param {FJsEnum.FValue} from 
        */
        Equals(from: FJsEnum.FValue): boolean;
 
        /**
        * '==' operator
        * 
        * @param {FJsEnum.FValue} a 
        */
        EqualEqual(a: FJsEnum.FValue): boolean;

        /**
        * @param {string} context 
        * @param {FJsEnum} type 
        * @returns {boolean}
        */
        IsTypeChecked(context: string, type: FJsEnum): boolean;
 
        /**
        * @param {string} context 
        * @param {string} enumName 
        * @returns {boolean}
        */
        IsTypeByStringChecked(context: string, enumName: string): boolean;
    }
}

declare class FJsEnum {
    Name: string;
    Enums: FJsEnum.FValue[];
    EnumMap: Map<string, FJsEnum.FValue>;
    MAX: FJsEnum.FValue;

    /**
    * @returns {string}
    */
    GetName(): string;

    /**
    * @param {string} context
    * @param {FJsEnum} lhs 
    * @param {FJsEnum} rhs
    * @returns {boolean} 
    */
    EqualEqualChecked(context: string, lhs: FJsEnum, rhs: FJsEnum): boolean;

    /**
    * @param {FJsEnum} lhs 
    * @param {FJsEnum} rhs
    * @returns {boolean} 
    */
    EqualEqual(lhs: FJsEnum, rhs: FJsEnum): boolean;

    /**
    * @param {string} name 
    * @returns {FJsEnum.FValue} FValue
    */
    Create(name: string): FJsEnum.FValue;

    /**
    * @returns {FJsEnum.FValue} FValue
    */
    CreateInvalid(): FJsEnum.FValue;

    /**
    * @param {number}                index int
    * @returns {FJsEnum.FValue}      FValue
    */
    GetByIndex(index : number): FJsEnum.FValue;

    /**
    * @returns {number}
    */
    Num(): number;

    /**
    * @returns {FJsEnum.FValue}  FValue
    */
    GetMAX(): FJsEnum.FValue;

    /**
    * @param {number}          context
    * @param {FJsEnum.FValue}  a 
    * @returns {boolean}
    */
    ContainsChecked(context: string, a: FJsEnum.FValue): boolean;

    /**
    * @param {FJsEnum.FValue} a 
    * @returns {boolean}
    */
    Contains(a: FJsEnum.FValue): boolean;

    /**
    * @param {FJsEnum.FValue}  a 
    * @param {FJsEnum.FValue}  b
    * @returns {boolean}       a == b.
    */
    AreValuesEqual(a: FJsEnum.FValue, b: FJsEnum.FValue): boolean;
}
