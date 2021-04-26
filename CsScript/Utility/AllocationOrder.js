/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');
// Containers
const FJsDoubleLinkedListNode = require('Cs/Containers/DoubleLinkedListNode.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - function
var checkf = CommonLibrary.checkf;
var IsNullObject = CommonLibrary.IsNullObject;

module.exports = class FJsAllocationOrder
{
    constructor()
    {
        this.Links = []
        this.Head = null;
        this.Tail = null;
        this.Size = 0;
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

    Create(size)
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

    GetLinks() { return this.Links; }
    GetHead() { return this.Head; }
    GetTail() { return this.Tail; }
    GetSize() { return this.Size; }

    Add()
    {
        this.AddNewToTail();

        ++this.Size;
    }

    AddToTail(link)
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

    AddBefore(link, linkBefore)
    {
        link.LinkBefore(linkBefore);

        if (linkBefore === this.Head)
        {
            this.Head = link;
        }
    }

    AddBeforeHead(link) { this.AddBefore(link, this.Head); }

    MoveHeadToTail()
    {
        let previousHead = this.Head;

        this.Head = this.Head.GetNextLink();

        previousHead.Unlink();
        this.AddToTail(previousHead);
    }

    Remove(link)
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

    MoveToHead(index)
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

    Promote(index) { this.MoveToHead(index); }
};