// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Library
/// <reference path="../Library/Library_Common.ts">/>
// Containers
/// <reference path="../../Cs/Containers/DoubleLinkedListNode.ts">/>

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
// Containers
/** @type {FJsDoubleLinkedListNode} */
const FJsDoubleLinkedListNode = require('Cs/Containers/DoubleLinkedListNode.js');

// "typedefs" - class
/** @type {CommonLibrary} */ var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - function
var checkf          = CommonLibrary.checkf;
var IsNullObject    = CommonLibrary.IsNullObject;

module.exports = class FJsAllocationOrder
{
    constructor()
    {
        /** @type {FJsDoubleLinkedListNode[]} */this.Links = []
        /** @type {FJsDoubleLinkedListNode} */  this.Head = null;
        /** @type {FJsDoubleLinkedListNode} */  this.Tail = null;
        /** @type {number} */                   this.Size = 0;
    }

    Shutdown()
    {
        this.Links = [];
        this.Head = null;
        this.Tail = null;
        this.Size = 0;
    }

    Reset()
    {
        for (let i = 0; i < this.Size; ++i)
        {
            let link = this.Links[i];
            link.Unlink();
        }

        this.Head = null;
        this.Tail = null;

        for (let i = 0; i < this.Size; ++i)
        {
            let link = this.Links[i];

            this.AddToTail(link);
        }
    }

    /**
    * @param {number} size 
    */
    Create(size /*number*/)
    {
        checkf(CommonLibrary.IsInt(size), "FJsAllocationOrder.Create: s is NOT an Integer.");

        checkf(size > 0, "FJsAllocationOrder.Create: size: %d is NOT > 0.", size);

        checkf(size !== this.Size, "FJsAllocationOrder.Create: Size is already size: %d.", size);

        this.Shutdown();

        this.Size = size;

        this.Links = [];

        for (let i = 0; i < this.Size; ++i)
        {
            this.AddNewToTail();
        }
    }

    /** @type {FJsDoubleLinkedListNode[]} */GetLinks() { return this.Links; }
    /** @type {FJsDoubleLinkedListNode} */  GetHead() { return this.Head; }
    /** @type {FJsDoubleLinkedListNode} */  GetTail() { return this.Tail; }
    /** @type {number} */                   GetSize() { return this.Size; }

    Add()
    {
        this.AddNewToTail();

        ++this.Size;
    }

    /**
    * @param {FJsDoubleLinkedListNode} link 
    */
    AddToTail(link /*FJsDoubleLinkedListNode*/)
    {
        if (this.Tail)
        {
            link.LinkAfter(this.Tail);
        }
        else
        {
            this.Head = link;
            this.Tail = this.Head;
        }
    }

    AddNewToTail()
    {
        let link = new FJsDoubleLinkedListNode();
    
        this.Links.push(link);

        link.Element = this.Links.length - 1;

        this.AddToTail(link);
    }

    /**
    * @param {FJsDoubleLinkedListNode} link
    * @param {FJsDoubleLinkedListNode} linkBefore 
    */
    AddBefore(link /*FJsDoubleLinkedListNode*/, linkBefore /*FJsDoubleLinkedListNode*/)
    {
        link.LinkBefore(linkBefore);

        if (linkBefore === this.Head)
        {
            this.Head = link;
        }
    }

    /**
    * @param {FJsDoubleLinkedListNode} link 
    */
    AddBeforeHead(link /*FJsDoubleLinkedListNode*/) { this.AddBefore(link, this.Head); }

    MoveHeadToTail()
    {
        let previousHead = this.Head;

        this.Head = this.Head.GetNextLink();

        previousHead.Unlink();
        this.AddToTail(previousHead);
    }

    /**
    * @param {FJsDoubleLinkedListNode} link 
    */
    Remove(link /*FJsDoubleLinkedListNode*/)
    {
        // Check to Update HEAD
        if (link === this.Head)
        {
            this.Head = link.GetNextLink();

            if (IsNullObject(this.Head))
            {
                this.Tail = null;
            }
        }
        // Check to Update TAIL
        else
        if (link === this.Tail)
        {
            this.Tail = link.GetPrevLink();
        }
        link.Unlink();
    }

    /**
    * @param {number} index 
    */
    MoveToHead(index /*number*/)
    {
        let link = this.Links[index];

        this.Remove(link);
        this.AddBeforeHead(link);
    }

    Advance()
    {
        let value = this.Head.Element;
        
        this.MoveHeadToTail();

        return value;
    }

    /**
    * @param {number} index 
    */
    Promote(index /*number*/) { this.MoveToHead(index); }
};