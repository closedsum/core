// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Coroutine
/// <reference path="../Coroutine/CoroutineSchedule.ts">/>

declare class FJCoroutineScheduler {
    Schedules: FJCoroutineSchedule[];
    CleanUp(): void;
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
    IsRunning(group: ECsUpdateGroup, handle: CsRoutineHandle): boolean
}