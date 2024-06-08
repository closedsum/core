// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../../typings/ue.d.ts">/>
/// <reference path="../../Data/Data.ts">/>

// require('Cs/Managers/Data/Manager_Data.js');

declare class FJsManager_Data 
{
    DataByNameMap: Map<string, NJsData.IData>;
    /**
    */
    Shutdown(): void;
    /**
    * @param {string}
    * @param {NJsData.IData} 
    */
    AddData(name: string, data: NJsData.IData): void;
    /**
    * @param {string} 
    * @returns {NJsData.IData}
    */
    GetData(name: string): NJsData.IData;
    /**
    */
    LoadAll(): void;
}