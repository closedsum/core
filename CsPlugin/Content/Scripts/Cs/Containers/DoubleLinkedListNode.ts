// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// ; typing info for auto-completion in Visual Studio Code

declare class FJsDoubleLinkedListNode {
    Element: any;
	NextLink: FJsDoubleLinkedListNode;
	PrevLink: FJsDoubleLinkedListNode;
	Unlink(): void;
	/**
    * @param {FJsDoubleLinkedListNode} before 
    */
    LinkBefore(before: FJsDoubleLinkedListNode): void;
	/**
    * @param {FJsDoubleLinkedListNode} after 
    */
    LinkAfter(after: FJsDoubleLinkedListNode): void;
	/**
    * @returns {boolean}
    */
    IsLinked(): boolean;
	/**
    * @returns {any}
    */
    GetElement(): any;
	/**
    * @returns {FJsDoubleLinkedListNode}
    */
    Next(): FJsDoubleLinkedListNode;
	/**
    * @returns {FJsDoubleLinkedListNode}
    */
    Prev(): FJsDoubleLinkedListNode;
	/**
    * @returns {FJsDoubleLinkedListNode}
    */
    GetNextLink(): FJsDoubleLinkedListNode;
	/**
    * @returns {FJsDoubleLinkedListNode}
    */
    GetPrevLink(): FJsDoubleLinkedListNode;
}