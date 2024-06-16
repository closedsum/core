// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Coroutine
/// <reference path="../Coroutine/CoroutineSchedule.ts">/>

declare class FJCoroutineScheduler {
    DefaultSchedules: NJsCoroutine_NSchedule_FDefault[];
    CleanUp(): void;
    // Default
	StartByContainer(payloadContainer: FJsResourceContainer): CsRoutineHandle;
    Start(payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
    StartChildByContainer(payloadContainer: FJsResourceContainer): CsRoutineHandle;
    StartChild(payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
    Update(deltaTime: CsDeltaTime): void;
    EndByGroup(group: ECsUpdateGroup): boolean;
    EndByHandle(group: ECsUpdateGroup, handle: CsRoutineHandle): boolean;
    EndAll(): void;
    HasEnded(group: ECsUpdateGroup,handle: CsRoutineHandle): boolean;
    HasJustEnded(group: ECsUpdateGroup,handle: CsRoutineHandle): boolean;
    AllocatePayloadContainer(group: ECsUpdateGroup): FJsResourceContainer;
    AllocatePayload(group: ECsUpdateGroup): NJsCoroutine_NPayload_FImpl;
    IsHandleValid(group: ECsUpdateGroup, handle: CsRoutineHandle): boolean;
    IsRunning(group: ECsUpdateGroup, handle: CsRoutineHandle): boolean;
    // Custom
    IsValidGroupIndexChecked(context: string, groupIndex: number): boolean;
    GetCustomSchedule(groupIndex: number): NJsCoroutine_NSchedule_FCustom;
    AllocateCustomGroupIndexAndOwnerID(): {GroupIndex: number, OwnerID: number};
    DeallocateOwnerID(groupIndex: number, ownerID: number): void;
    CustomStartByContainer(groupIndex: number, ownerID: number, payloadContainer: FJsResourceContainer): CsRoutineHandle;
    CustomStart(groupIndex: number, ownerID: number, payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
    CustomStartChildByContainer(groupIndex: number, ownerID: number, payloadContainer: FJsResourceContainer): CsRoutineHandle;
    CustomStartChild(groupIndex: number, ownerID: number, payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
    CustomUpdate(groupIndex: number, ownerID: number, deltaTime: CsDeltaTime): void;
    CustomEnd(groupIndex: number, handle: CsRoutineHandle): boolean;
    HasCustomEnded(groupIndex: number, handle: CsRoutineHandle): boolean;
    HasCustomJustEnded(groupIndex: number, handle: CsRoutineHandle): boolean;
    AllocateCustomPayloadContainer(groupIndex: number): FJsResourceContainer;
    AllocateCustomPayload(groupIndex: number): NJsCoroutine_NPayload_FImpl;
    IsCustomHandleValid(groupIndex: number, handle: CsRoutineHandle): boolean;
    IsCustomRunning(groupIndex: number, handle: CsRoutineHandle): boolean;
}