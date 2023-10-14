// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
/// <reference path="../Library/Library_Common.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - library (c++)
var PropertyLibrary      = CsScriptLibrary_Property;
var SkeletalMeshLibrary  = CsScriptLibrary_SkeletalMesh;

// "typedefs" - functions
var check                = CommonLibrary.check;
var IsStringChecked      = CommonLibrary.IsStringChecked;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;
var IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked;

// Globals

module.exports = class NJsTypes
{
    static FSkeletalMesh = class SkeletalMesh
    {
        constructor()
        {  
            /** @type {string} */       this.Path = "";
            /** @type {SkeletalMesh} */ this.Mesh_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FSkeletalMesh" }

        /**
        * @returns {SkeletalMesh}
        */
        /*SkeletalMesh*/ Get() { return this.Mesh_Internal; }
        
        /**
        * @param {SkeletalMesh} mesh 
        */
        Set(mesh /*SkeletalMesh*/) { this.Mesh_Internal = mesh; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsStringChecked(context, this.Path);
            IsValidObjectChecked(context, this.Mesh_Internal);
            return true;
        }

        /**
        * @param {string} context 
        * @param {object} o 
        * @param {string} memberPath 
        */
        OverrideByUObject(context /*string*/, o /*object*/, memberPath /*string*/)
        {
            let result = PropertyLibrary.GetSoftObjectPtrAsStringByPath(context, o, memberPath + ".Mesh");
            check(result.OutSuccess);
            this.Path = result.$;
            result = SkeletalMeshLibrary.GetByPath(context, o, memberPath + ".Mesh_Internal");
            check(result.OutSuccess);
            this.Mesh_Internal = result.$;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            this.Mesh_Internal = SkeletalMeshLibrary.LoadByStringPath(context, this.Path);
        }
    }
};