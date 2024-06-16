// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// ; typing info for auto-completion in Visual Studio Code
// Utility
/// <reference path="../../Utility/AllocationOrder.ts">/>
// Resource
/// <reference path="ResourceContainer.ts">/>

declare class FJsManager_Resource_Fixed {
    Name: string;
	ResourceContainers: FJsResourceContainer[];
	Resources: any[];
    Pool: FJsResourceContainer[];
    PoolSize: number;
    PoolSizeMinusOne: number;
    PoolIndex: number;
    /** function */
    AdvancePoolIndex: any;
    Links: FJsDoubleLinkedListNode[];
    AllocatedHead: FJsDoubleLinkedListNode;
    AllocatedTail: FJsDoubleLinkedListNode;
    AllocatedSize: number;
    AllocationOrder: FJsAllocationOrder;
	Clear(): void;
    Shutdown(): void;
    CreatePool(size: number, resourceClassType: any): void;
    GetPool(): FJsResourceContainer[];
    GetPoolSize(): number;
    GetAllocatedSize(): number;
    IsExhaused(): boolean;
    AdvancePoolIndexByIncrement(): void;
    AdvancePoolIndexByOrder(): void;
    GetAt(index: number): FJsResourceContainer;
    GetAtChecked(context: string, index: number): FJsResourceContainer;
    GetResourceAt(index: number): any;
    GetAllocatedContainer(resource: any): FJsResourceContainer;
    AddAllocatedLink(link: FJsDoubleLinkedListNode): void;
    AddAllocatedLinkAfter(link: FJsDoubleLinkedListNode, resourceContainer: FJsResourceContainer): void;
    AddAllocatedLinkBefore(link: FJsDoubleLinkedListNode, resourceContainer: FJsResourceContainer): void;
    RemoveActiveLink(link: FJsDoubleLinkedListNode): void;
    GetAllocatedHead(): FJsDoubleLinkedListNode;
    GetAllocatedTail(): FJsDoubleLinkedListNode;
    Allocate(): FJsResourceContainer;
    AllocateResource(): any;
    AllocateAfter(resourceContainer: FJsResourceContainer): FJsResourceContainer;
    AllocateAfterHead(): FJsResourceContainer;
    AllocateBefore(): FJsResourceContainer;
    AllocateBeforeHead(): FJsResourceContainer;
    IsAllocatedChecked(context: string, index: number): boolean;
    IsAllocated(index: number): boolean;
    Deallocate(resourceContainer: FJsResourceContainer): boolean;
    DeallocateByResource(resource: any): boolean;
    DeallocateAtByIndex(index: number): boolean;
    DeallocateAt(resource: any, index: number): boolean;
    DeallocateHead(): boolean;
    DeallocateAll(): void;
    Enqueue(): FJsResourceContainer;
    Dequeue(): FJsResourceContainer;
    Push(): FJsResourceContainer;
    Pop(): FJsResourceContainer;
}