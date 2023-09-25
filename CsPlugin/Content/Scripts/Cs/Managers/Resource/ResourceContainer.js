// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// ; typing info for auto-completion in Visual Studio Code

"use strict"

const INDEX_NONE = -1;

module.exports = class FJsResourceContainer
{
    constructor()
    {
        /** @type {number} */   this.Index      = INDEX_NONE;
        /** @type {boolean} */  this.bAllocated = false;
        /** @type {any} */      this.Resource   = null;
    }

    /*number*/ GetIndex()       { return this.Index; }
    SetIndex(index /*number*/)  { this.Index = index; }

    /*boolean*/ IsAllocated() { return this.bAllocated; }
    Allocate()                { return this.bAllocated = true; }
    Deallocate()              { return this.bAllocated = false; }

    /*any*/ Get()   { return this.Resource; }
    Set(r /*any*/)  { this.Resource = r; }
};