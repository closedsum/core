// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// ; typing info for auto-completion in Visual Studio Code
// Containers
/// <reference path="../../Cs/Containers/DoubleLinkedListNode.ts">/>

declare class FJsAllocationOrder {
    Links: FJsDoubleLinkedListNode[];
	Head: FJsDoubleLinkedListNode;
	Tail: FJsDoubleLinkedListNode;
    Size: number;
	Shutdown(): void;
    Reset(): void;
    Create(size: number): void;
    Add(): void;
    AddToTail(link: FJsDoubleLinkedListNode): void;
    AddNewToTail(): void;
    AddBefore(link: FJsDoubleLinkedListNode, linkBefore: FJsDoubleLinkedListNode): void;
    AddBeforeHead(link: FJsDoubleLinkedListNode): void;
    MoveHeadToTail(): void;
    Remove(link: FJsDoubleLinkedListNode): void;
    MoveToHead(index: number): void;
    Advance(): void;
    Promote(index: number): void;
}