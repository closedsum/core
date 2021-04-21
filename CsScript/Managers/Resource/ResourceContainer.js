/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

const INDEX_NONE = -1;

module.exports = class FJsResourceContainer
{
    constructor()
    {
        this.Index      = INDEX_NONE;
        this.bAllocated = false;
        this.Resource   = null;
    }

    GetIndex() { return this.Index; }
    SetIndex(index) { this.Index = index; }

    IsAllocated() { return this.bAllocated; }
    Allocate() { return this.bAllocated = true; }
    Deallocate() { return this.bAllocated = false; }

    Get() { return this.Resource; }
    Set(r) { this.Resource = r; }
};