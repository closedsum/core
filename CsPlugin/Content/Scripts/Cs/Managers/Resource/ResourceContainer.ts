// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

// ; typing info for auto-completion in Visual Studio Code

declare class FJsResourceContainer {
    Index: number;
	bAllocated: boolean;
	Resource: any;
	GetIndex(): number;
    SetIndex(index: number): void;
    IsAllocated(): boolean;
    Allocate(): void;
    Deallocate(): void;
    Get(): any;
    Set(r: any): void;
}