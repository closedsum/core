/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var checkf = CommonLibrary.checkf;

module.exports = class FJsEnum
{
    static FValue = class EnumValue
    {
        /**
         * @param {FJsEnum} outer
         * @param {string}  name 
         * @param {number}  value int
         */
        constructor(outer, name, value)
        {
            this.Outer = outer;
            this.Name = name;
            this.Value = value;
        }

        /**
         * @returns {FJsEnum}
         */
        /*FJsEnum*/ GetOuter() { return this.Outer; }

        /**
         * @returns {string}
         */
        /*string*/ GetName() { return this.Name; }

        /**
         * @returns {number} int
         */
        /*int*/ GetValue() { return this.Value; }

        /**
         * @returns {string} 
         */
        /*string*/ ToString() { return "{Outer:" + this.Outer.Name + ", Name:" + this.Name + ", Value:" + this.Value + "}"; }

        /**
         * '=' operator
         * 
         * @param {FJsEnum.FValue} from 
         */
        Equals(from /*FValue*/)
        {
            checkf(this.Outer === from.Outer, "FJsEnum.FValue.Equals: " + this.Outer.Name + " != " + from.Outer);

            this.Name = from.Name;
            this.Value = from.Value;
        }

        /**
         * '==' operator
         * 
         * @param {FJsEnum.FValue} a 
         */
        /*bool*/ EqualEqual(a /*FValue*/)
        {
            if (!CommonLibrary.IsInstanceOf(a, FJsEnum.FValue))
                return false;
            if (this.Outer !== a.GetOuter())
                return false;
            return this.Name === a.GetName() && this.Value === a.GetValue();
        }

        /**
         * @param {string} context 
         * @param {FJsEnum} type 
         * @returns {boolean}
         */
        /*bool*/ IsTypeChecked(context /*string*/, type /*FJsEnum*/)
        {
            check(CommonLibrary.IsInstanceOfChecked(context, type, FJsEnum));

            checkf(this.GetOuter() === type, context + ": " + this.Name + " is of type: " + this.GetOuter().GetName() + " NOT of type: " + type.GetName());

            return true;
        }

        /**
         * @param {string} context 
         * @param {string} enumName 
         * @returns {boolean}
         */
        /*bool*/ IsTypeByStringChecked(context /*string*/, enumName /*string*/)
        {
            check(CommonLibrary.IsStringChecked(context, enumName));

            checkf(this.GetOuter().GetName() === enumName, context + ": " + this.Name + " is of type: " + this.GetOuter().GetName() + " NOT of type: " + enumName);

            return true;
        }
    }

    /**
     * @param {string} name 
     */
    constructor(name /*string*/)
    {
        let context = "FJsEnum.constructor";

        check(CommonLibrary.IsStringChecked(context, name));

        this.Name = name;
        this.Enums = [];
        this.EnumMap = new Map();
        this.MAX = new FJsEnum.FValue(this, "Max", -1);
    }

    [Symbol.iterator]() { return this.Enums.values(); }

    /**
     * @returns {string}
     */
    /*string*/ GetName() { return this.Name; }

    /**
     * @param {string} context
     * @param {FJsEnum} lhs 
     * @param {FJsEnum} rhs
     * @returns {boolean} 
     */
    /*bool*/ EqualEqualChecked(context /*string*/, lhs /*FJsEnum*/, rhs /*FJsEnum*/)
    {
        check(CommonLibrary.IsInstanceOfChecked(context, lhs, FJsEnum));
  
        check(CommonLibrary.IsInstanceOfChecked(context, rhs, FJsEnum));

        checkf(lhs == this, context + ": lhs's type: " + lhs.Name + " != + " + this.Name);

        checkf(lhs === rhs, context + ": lhs's type: " + lhs.Name + " != " + rhs.Name);
        return true;
    }

    /**
     * @param {FJsEnum} lhs 
     * @param {FJsEnum} rhs
     * @returns {boolean} 
     */
    /*bool*/ EqualEqual(lhs /*FJsEnum*/, rhs /*FJsEnum*/)
    {
        if (!CommonLibrary.IsInstanceOf(lhs, FJsEnum))
            return false;
        if (!CommonLibrary.IsInstanceOf(rhs, FJsEnum))
            return false;
        return lhs === this && lhs === rhs;
    }

    /**
     * @param {string} name 
     * @returns {FJsEnum.FValue} FValue
     */
    /*FValue*/ Create(name /*string*/)
    { 
        let value = this.Enums.length;
        let e = new FJsEnum.FValue(this, name, value);
        this[name] = e;
        this.Enums[value] = e;
        this.EnumMap.set(name, e);
        this.MAX.Value = this.Enums.length;
        return e;
    }

    /**
     * @returns {FJsEnum.FValue} FValue
     */
    /*FValue*/ CreateInvalid()
    {
        return new FJsEnum.FValue(this, "", -1);
    }

    /**
     * @param {number}                index int
     * @returns {FJsEnum.FValue}      FValue
     */
    /*FValue*/ GetByIndex(index /*int*/)
    {
        return this.Enums[index];
    }

    /**
     * @returns {number}
    */
    /*int*/ Num() { return this.Enums.length; }

    /**
     * @returns {FJsEnum.FValue}  FValue
     */
    /*FValue*/ GetMAX() { return this.MAX; }

    /**
     * @param {number}          context
     * @param {FJsEnum.FValue}  a 
     * @returns {boolean}
     */
    /*bool*/ ContainsChecked(context /*string*/, a /*FValue*/)
    {
        check(CommonLibrary.IsInstanceOfChecked(context, a, FJsEnum.FValue));

        checkf(this.Contains(a), context + ": a:" + a.ToString() + " is NOT of type: " + this.Name);
        return true;
    }

    /**
     * @param {FJsEnum.FValue} a 
     * @returns {boolean}
     */
    /*bool*/ Contains(a /*FValue*/)
    {
        return this.Enums.find(e => e.Outer === a.Outer && e.Name === a.Name && e.Value === a.Value);
    }

    /**
     * @param {FJsEnum.FValue}  a 
     * @param {FJsEnum.FValue}  b
     * @returns {boolean}       a == b.
     */
    /*bool*/ AreValuesEqual(a /*FValue*/, b /*FValue*/)
    {
        let context = "FJsEnum.AreValuesEqual";

        check(this.ContainsChecked(context, a));
        check(this.ContainsChecked(context, b));

        return a.Outer === b.Outer &&a.Name === b.Name && a.Value === b.Value;
    }
};