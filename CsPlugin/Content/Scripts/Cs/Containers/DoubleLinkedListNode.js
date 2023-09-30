// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// self
/// <reference path="../../Cs/Containers/DoubleLinkedListNode.ts">/>

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
        /** @type {any} */                      this.Element = null;
        /** @type {FJsDoubleLinkedListNode} */  this.NextLink = null;
        /** @type {FJsDoubleLinkedListNode} */  this.PrevLink = null;
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

    /**
    * @param {FJsDoubleLinkedListNode} before 
    */
    LinkBefore(before /*FJsDoubleLinkedListNode*/)
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

    /**
    * @param {FJsDoubleLinkedListNode} after 
    */
    LinkAfter(after /*FJsDoubleLinkedListNode*/)
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

    /**
    * @returns {boolean}
    */
    /*boolean*/ IsLinked()
    {
        return IsValidObject(this.NextLink) || IsValidObject(this.PrevLink);
    }

    /**
    * @returns {any}
    */
    /*any*/ GetElement() { return this.Element; }

    /**
    * @returns {FJsDoubleLinkedListNode}
    */
    /*FJsDoubleLinkedListNode*/ Next() { return this.NextLink; }
    /**
    * @returns {FJsDoubleLinkedListNode}
    */
    /*FJsDoubleLinkedListNode*/ Prev() { return this.PrevLink; }
    /**
    * @returns {FJsDoubleLinkedListNode}
    */
    /*FJsDoubleLinkedListNode*/ GetNextLink() { return this.NextLink; }
    /**
    * @returns {FJsDoubleLinkedListNode}
    */
    /*FJsDoubleLinkedListNode*/ GetPrevLink() { return this.PrevLink; }
};