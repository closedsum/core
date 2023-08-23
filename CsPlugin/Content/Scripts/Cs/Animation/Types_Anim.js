// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var check = CommonLibrary.check;
var IsClassChecked = CommonLibrary.IsClassChecked;
var IsStringChecked = CommonLibrary.IsStringChecked;

module.exports = class NJsTypes
{
    static FAnimBlueprint = class AnimBlueprint
    {
        constructor()
        {  
            /** @type {string} */                       this.Path = "";
            /** @type {AnimBlueprintGeneratedClass} */  this.Blueprint_Internal = null;
        }

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
    }

    static FAnimSequence = class AnimSequence
    {
        constructor()
        {  
            /** @type {string} */       this.Path = "";
            /** @type {AnimSequence} */ this.Anim_Internal = null;
        }

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
            IsClassChecked(context, this.Anim_Internal);
            return true;
        }
    }

    static FBlendSpace = class BlendSpace
    {
        constructor()
        {  
            /** @type {string} */       this.Path = "";
            /** @type {BlendSpace} */   this.Blend_Internal = null;
        }

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
    }

    static FBlendSpace1D = class BlendSpace1D
    {
        constructor()
        {  
            /** @type {string} */       this.Path = "";
            /** @type {BlendSpace1D} */ this.Blend_Internal = null;
        }

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
    }
};