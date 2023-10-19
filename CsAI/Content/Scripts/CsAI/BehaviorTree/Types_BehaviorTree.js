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
/** @type {ArrayLibrary} */ var ArrayLibrary   = NJsArray.FLibrary;

// "typedefs" - library (c++)
var BehaviorTreeLibrary  = CsScriptLibrary_BehaviorTree;

// "typedefs" - functions
var check                = CommonLibrary.check;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;

module.exports = class NJsTypes
{
    static FBehaviorTree = class BehaviorTreeClass
    {
        constructor()
        {  
            /** @type {string[]} */      this.Path = "";
            /** @type {BehaviorTree} */  this.Tree_Internal = null;
        }

        /*string*/ GetName() { return " NJsTypes.FBehaviorTree" }

        /**
        * @returns {BehaviorTree}
        */
        /*BehaviorTree*/ Get() { return this.Tree_Internal; }

        /**
        * @param {BehaviorTree} tree 
        */
        Set(tree /*BehaviorTree*/) { this.Tree_Internal = tree; }

        /**
        * @param {string}   context
        * @return {boolean} 
        */
        /*boolean*/ IsValidChecked(context /*string*/)
        {
            IsNotEmptyChecked(context, this.Path);
            IsValidObjectChecked(context, this.Tree_Internal);
            return true;
        }

        /**
        * @param {string} context 
        * @param {object} o 
        * @param {string} memberPath 
        */
        OverrideByUObject(context /*string*/, o /*object*/, memberPath /*string*/)
        {
            // let result = MaterialLibrary.GetSoftObjectArrayAsStringByPath(context, o, memberPath + ".Materials");
            // check(result.OutSuccess);
            // this.Paths = result.OutArray;
            // result = MaterialLibrary.GetArrayByPath(context, o, memberPath + ".Materials_Internal");
            // check(result.OutSuccess);
            // IsNotEmptyChecked(context, result.OutArray);
            // this.Materials_Internal = result.OutArray;
        }

        Load()
        {
            let context = this.GetName() + ".Load";

            let tree = BehaviorTreeLibrary.LoadByStringPath(context, this.Path);
            IsValidObjectChecked(context, tree);
            this.Tree_Internal = tree;
        }

        Unload()
        {
            this.Tree_Internal = null;
        }
    }
};