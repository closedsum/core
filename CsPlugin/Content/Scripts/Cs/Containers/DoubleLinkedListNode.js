/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

// Library
var NJsCommon = require('Cs/Library/Library_Common.js');

// "typedefs" - class
var CommonLibrary = NJsCommon.FLibrary;

// "typedefs" - functions
var checkf = CommonLibrary.checkf;
var IsValidObject = CommonLibrary.IsValidObject;
var IsInstanceOf = CommonLibrary.IsInstanceOf;

module.exports = class FJsDoubleLinkedListNode
{
    constructor()
    {
        this.Element = null;
        this.NextLink = null;
        this.PrevLink = null;
    }

    Unlink()
    {
        if (IsValidObject(this.NextLink))
            this.NextLink.PrevLink = this.PrevLink;

        if (IsValidObject(this.PrevLink))
            this.PrevLink.NextLink = this.NextLink;
       
        this.NextLink = null;
        this.PrevLink = null;
    }

    LinkBefore(before)
    {
        checkf(IsValidObject(before), "FJsDoubleLinkedListNode.LinkBefore: is NULL.");

        checkf(IsInstanceOf(before, FJsDoubleLinkedListNode), "FJsDoubleLinkedListNode.LinkBefore: n is NOT an instance of: FJsDoubleLinkedListNode.");

        if (IsValidObject(this.NextLink))
            this.NextLink.PrevLink = this.PrevLink;

        if (IsValidObject(this.PrevLink))
            this.PrevLink.NextLink = this.NextLink;

        this.PrevLink = before.PrevLink;

        if (IsValidObject(before.PrevLink))
            before.PrevLink.NextLink = this;

        before.PrevLink = this;
        this.NextLink   = before;
    }

    LinkAfter(after)
    {
        checkf(IsValidObject(after), "FJsDoubleLinkedListNode.LinkBefore: is NULL.");
        
        checkf(IsInstanceOf(after, FJsDoubleLinkedListNode), "FJsDoubleLinkedListNode.LinkBefore: n is NOT an instance of: FJsDoubleLinkedListNode.");

        if (IsValidObject(this.NextLink))
            this.NextLink.PrevLink = this.PrevLink;

        if (IsValidObject(this.PrevLink))
            this.PrevLink.NextLink = this.NextLink;

        this.PrevLink = after;

        if (IsValidObject(after.NextLink))
            after.NextLink.PrevLink = this;

        this.NextLink  = after.NextLink;
        after.NextLink = this;
    }

    IsLinked()
    {
        return IsValidObject(this.NextLink) || IsValidObject(this.PrevLink);
    }

    GetElement() { return this.Element; }

    Next() { return this.NextLink; }
    Prev() { return this.PrevLink; }
    GetNextLink() { return this.NextLink; }
    GetPrevLink() { return this.PrevLink; }
};