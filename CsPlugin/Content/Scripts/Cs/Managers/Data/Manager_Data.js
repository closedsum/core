// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

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
var IsStringChecked = CommonLibrary.IsStringChecked;
var IsValidObjectChecked = CommonLibrary.IsValidObjectChecked;

var ClassName = "FJsManager_Data";

module.exports = class FJsManager_Data
{
    constructor()
    {  
        /** @type {Map<string, NJsData.IData>} */   this.DataByNameMap = new Map();
    }

    Shutdown()
    {
        this.UnloadAll();
        
        this.DataByNameMap.clear();
    }

    AddData(name /*string*/, data /*NJsData.IData*/)
    {
        let context = ClassName + ".AddData";

        IsStringChecked(context, name);
        // TODO: Check data interface
        IsValidObjectChecked(context, data);

        checkf(!this.DataByNameMap.has(name), context + " data with name: " + name + " has ALREADY been added.");

        this.DataByNameMap.set(name, data);
    }

    /**
     * @param {string}          name 
     * @returns {NJsData.IData}
     */
    /*NJsData.IData*/ GetData(name /*string*/)
    {
        let context = ClassName + ".GetData";

        checkf(this.DataByNameMap.has(name), context + " no data is associated with name: " + name);
        // TODO: Check Data is Valid
        return this.DataByNameMap.get(name);
    }

    Load(name /*string*/)
    {
        this.GetData(name).Load();
    }

    LoadAll()
    {
        for (var [name, data] of this.DataByNameMap)
        {
            data.Load();
        }
    }

    UnloadAll()
    {
        for (var [name, data] of this.DataByNameMap)
        {
            data.Unload();
        }
    }
};