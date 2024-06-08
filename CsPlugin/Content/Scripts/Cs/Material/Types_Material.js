// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
var NJsArray = require('Cs/Library/Library_Array.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;
/** @type {ArrayLibrary} */ var ArrayLibrary   = NJsArray.FLibrary;

// "typedefs" - library (c++)
var MaterialLibrary  = CsScriptLibrary_Material;

// "typedefs" - functions
var check                   = CommonLibrary.check;
var IsValidObjectChecked    = CommonLibrary.IsValidObjectChecked;
var IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked;
var IsNotEmptyChecked       = ArrayLibrary.IsNotEmptyChecked;

module.exports = class NJsTypes
{
    static FMaterialInterface = class MaterialInterfaceClass
    {
        constructor()
        {
            /** @type {string} */             this.Path = "";
            /** @type {MaterialInterface} */  this.Material_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FMaterialInterface" }

        /**
        * @returns {MaterialInterface}
        */
        /*MaterialInterface*/ Get() { return this.Material_Internal; }

        /**
        * @param {MaterialInterface} mat 
        */
        Set(mat /*MaterialInterface*/) { this.Material_Internal = mat; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsStringNotEmptyChecked(context, this.Path);
            IsValidObjectChecked(context, this.Material_Internal);
            return true;
        }

        /**
        * @param {string} context 
        * @param {object} o 
        * @param {string} memberPath 
        */
        OverrideByUObject(context /*string*/, o /*object*/, memberPath /*string*/)
        {
            let result = MaterialLibrary.GetSoftObjectAsStringByPath(context, o, memberPath + ".Material");
            check(result.OutSuccess);
            this.Path = result.OutPath;
            result = MaterialLibrary.GetByPath(context, o, memberPath + ".Material_Internal");
            IsValidObjectChecked(context, result);
            this.Material_Internal = result;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            let result = MaterialLibrary.LoadByStringPath(context, this.Path);
            IsValidObjectChecked(context, result);
            this.Material_Internal = result;
        }

        Unload()
        {
            this.Material_Internal = null;
        }
    }

    static FTArrayMaterialInterface = class TArrayMaterialInterface
    {
        constructor()
        {  
            /** @type {string[]} */             this.Paths = [];
            /** @type {MaterialInterface[]} */  this.Materials_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FTArrayMaterialInterface" }

        /**
        * @returns {MaterialInterface[]}
        */
        /*MaterialInterface[]*/ Get() { return this.Materials_Internal; }

        /**
        * @param {MaterialInterface[]} mats 
        */
        Set(mats /*MaterialInterface[]*/) { this.Materials_Internal = mats; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsNotEmptyChecked(context, this.Paths);
            IsNotEmptyChecked(context, this.Materials_Internal);
            // TODO: Need to check Array has valid objects.
            return true;
        }

        /**
        * @param {string} context 
        * @param {object} o 
        * @param {string} memberPath 
        */
        OverrideByUObject(context /*string*/, o /*object*/, memberPath /*string*/)
        {
            let result = MaterialLibrary.GetSoftObjectArrayAsStringByPath(context, o, memberPath + ".Materials");
            check(result.OutSuccess);
            this.Paths = result.OutArray;
            result = MaterialLibrary.GetArrayByPath(context, o, memberPath + ".Materials_Internal");
            check(result.OutSuccess);
            IsNotEmptyChecked(context, result.OutArray);
            this.Materials_Internal = result.OutArray;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            let result = MaterialLibrary.LoadByStringPaths(context, this.Paths);
            check(result.$);
            IsNotEmptyChecked(context, result.OutMaterials);
            this.Materials_Internal = result.OutMaterials;
        }

        Unload()
        {
            this.Materials_Internal = [];
        }
    }
};