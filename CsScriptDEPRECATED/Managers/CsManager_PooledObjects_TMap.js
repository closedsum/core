/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var me;

module.exports = class JsCsManager_PooledObjects_TMap
{
    constructor()
    {
        me = this;
        
        this.ptr = null;
        this.root = null;

        this.Pool = [];
        this.Pools = [];
    }

    Init(inPtr, inRoot)
    {
        this.ptr = Actor.C(inPtr);
        this.root = inRoot;
    }

    CleanUp()
    {
    }
};