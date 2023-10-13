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
var check             = CommonLibrary.check;
var IsNotEmptyChecked = ArrayLibrary.IsNotEmptyChecked;

module.exports = class NJsTypes
{
    static FTArrayMaterialInterface = class TArrayMaterialInterface
    {
        constructor()
        {  
            /** @type {string[]} */             this.Paths = [];
            /** @type {MaterialInterface[]} */  this.Materials_Internal = null;
        }

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

        OverrideByUObject(context, o, memberPath)
        {
            let result = MaterialLibrary.GetSoftObjectArrayAsStringByPath(context, o, memberPath + ".Materials");
            check(result.OutSuccess);
            this.Paths = result.OutArray;
            result = MaterialLibrary.GetArrayByPath(context, o, memberPath + ".Materials_Internal");
            check(result.OutSuccess);
            this.Materials_Internal = result.OutArray;
        }

        Load()
        {
            let context = ClassName = ".Load";

            let result = MaterialLibrary.LoadByStringPaths(context, this.Path);
            check(result.$);
            this.Materials_Internal = result.OutMaterials;
        }
    }
};