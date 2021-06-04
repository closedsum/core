/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

module.exports = class FJsEnum
{
    constructor()
    {
        this.Enums = [];
        this.EnumMap = new Map();
        this.MAX = { Value: -1, Name: "MAX" };
    }

    Create(name)
    { 
        let value = this.Enums.length;
        let e = { Value: value, Name: name };
        this[name] = e;
        this.Enums[value] = e;
        this.EnumMap.set(name, e);
        this.MAX.Value = this.Enums.length;
        return e;
    }

    GetByIndex(index)
    {
        return this.Enums[index];
    }

    Num() { return this.Enums.length; }
    GetMAX() { return this.MAX; }
};