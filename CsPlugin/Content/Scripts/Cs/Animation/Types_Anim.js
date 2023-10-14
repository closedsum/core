// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - library (js)
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - library (c++)
var PropertyLibrary      = CsScriptLibrary_Property;
var AnimInstanceLibrary  = CsScriptLibrary_AnimInstance;
var AnimSequenceLibrary  = CsScriptLibrary_AnimSequence;
var AnimMontageLibrary   = CsScriptLibrary_AnimMontage;
var BlendSpaceLibrary    = CsScriptLibrary_BlendSpace;

// "typedefs" - functions
var check                   = CommonLibrary.check;
var IsClassChecked          = CommonLibrary.IsClassChecked;
var IsValidObjectChecked    = CommonLibrary.IsValidObjectChecked;
var IsStringChecked         = CommonLibrary.IsStringChecked;
var IsStringNotEmptyChecked = CommonLibrary.IsStringNotEmptyChecked;

module.exports = class NJsTypes
{
    static FAnimBlueprint = class AnimBlueprint
    {
        constructor()
        {  
            /** @type {string} */                       this.Path = "";
            /** @type {AnimBlueprintGeneratedClass} */  this.Blueprint_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FAnimBlueprint" }

        /**
        * @returns {AnimBlueprintGeneratedClass}
        */
        /*AnimBlueprintGeneratedClass*/ Get() { return this.Blueprint_Internal; }
        
        /**
        * @param {AnimBlueprintGeneratedClass} ac 
        */
        Set(ac /*AnimBlueprintGeneratedClass*/) { this.Blueprint_Internal = ac; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsStringChecked(context, this.Path);
            IsClassChecked(context, this.Blueprint_Internal);
            return true;
        }

        OverrideByUObject(context, o, memberPath)
        {
            let result = PropertyLibrary.GetSoftObjectPtrAsStringByPath(context, o, memberPath + ".Blueprint");
            check(result.OutSuccess);
            IsStringNotEmptyChecked(context, result.$);
            this.Path = result.$;
            result = AnimInstanceLibrary.GetClassByPath(context, o, memberPath + ".Blueprint_Internal");
            check(result.OutSuccess);
            IsClassChecked(context, result.$);
            this.Blueprint_Internal = result.$;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            this.Blueprint_Internal = AnimInstanceLibrary.LoadAndGetGeneratedClassByStringPath(context, this.Path);
        }
    }

    static FAnimSequence = class AnimSequence
    {
        constructor()
        {  
            /** @type {string} */       this.Path = "";
            /** @type {AnimSequence} */ this.Anim_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FAnimSequence" }

        /**
        * @returns {AnimSequence}
        */
        /*AnimSequence*/ Get() { return this.Anim_Internal; }
        
        /**
        * @param {AnimSequence} a
        */
        Set(a /*AnimSequence*/) { this.Anim_Internal = a; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsStringChecked(context, this.Path);
            IsValidObjectChecked(context, this.Anim_Internal);
            return true;
        }

        OverrideByUObject(context, o, memberPath)
        {
            let result = PropertyLibrary.GetSoftObjectPtrAsStringByPath(context, o, memberPath + ".Anim");
            check(result.OutSuccess);
            IsStringNotEmptyChecked(context, result.$);
            this.Path = result.$;
            result = AnimSequenceLibrary.GetByPath(context, o, memberPath + ".Anim_Internal");
            check(result.OutSuccess);
            IsValidObjectChecked(context, result.$);
            this.Anim_Internal = result.$;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            this.Anim_Internal = AnimSequenceLibrary.LoadByStringPath(context, this.Path);
        }
    }

    static FBlendSpace = class BlendSpace
    {
        constructor()
        {  
            /** @type {string} */       this.Path = "";
            /** @type {BlendSpace} */   this.Blend_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FBlendSpace" }

        /**
        * @returns {BlendSpace}
        */
        /*BlendSpace*/ Get() { return this.Blend_Internal; }
        
        /**
        * @param {BlendSpace} b
        */
        Set(b /*BlendSpace*/) { this.Blend_Internal = b; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsStringChecked(context, this.Path);
            IsClassChecked(context, this.Blend_Internal);
            return true;
        }

        OverrideByUObject(context, o, memberPath)
        {
            let result = PropertyLibrary.GetSoftObjectPtrAsStringByPath(context, o, memberPath + ".Blend");
            check(result.OutSuccess);
            IsStringNotEmptyChecked(context, result.$);
            this.Path = result.$;
            result = BlendSpaceLibrary.GetByPath(context, o, memberPath + ".Blend_Internal");
            check(result.OutSuccess);
            IsValidObjectChecked(context, result.$);
            this.Blend_Internal = result.$;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            this.Blend_Internal = BlendSpaceLibrary.LoadByStringPath(context, this.Path);
        }
    }

    static FBlendSpace1D = class BlendSpace1D
    {
        constructor()
        {  
            /** @type {string} */       this.Path = "";
            /** @type {BlendSpace1D} */ this.Blend_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FBlendSpace1D" }

        /**
        * @returns {BlendSpace1D}
        */
        /*BlendSpace1D*/ Get() { return this.Blend_Internal; }
        
        /**
        * @param {BlendSpace1D} a
        */
        Set(b /*BlendSpace1D*/) { this.Blend_Internal = b; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsStringChecked(context, this.Path);
            IsClassChecked(context, this.Blend_Internal);
            return true;
        }

        /**
        * @param {string} context 
        * @param {object} o 
        * @param {string} memberPath 
        */
        OverrideByUObject(context /*string*/, o /*object*/, memberPath /*string*/)
        {
            let result = PropertyLibrary.GetSoftObjectPtrAsStringByPath(context, o, memberPath + ".Blend");
            check(result.OutSuccess);
            IsStringNotEmptyChecked(context, result.$);
            this.Path = result.$;
            result = BlendSpaceLibrary.Get1DByPath(context, o, memberPath + ".Blend_Internal");
            check(result.OutSuccess);
            IsValidObjectChecked(context, result.$);
            this.Blend_Internal = result.$;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            this.Blend_Internal = BlendSpaceLibrary.Load1DByStringPath(context, this.Path);
        }
    }
};