// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Coroutine
/// <reference path="../Coroutine/Routine.ts">/>
// Managers
/// <reference path="../Managers/Resource/Manager_Resource_Fixed.ts">/>

declare class FJCoroutineSchedule {
    Group: ECsUpdateGroup;
    Manager_Routine: FJsManager_Resource_Fixed;
    Manager_Payload: FJsManager_Resource_Fixed;
    SetGroup(group: ECsUpdateGroup);
    GetRoutineContainer(handle: CsRoutineHandle): FJsResourceContainer;
    GetRoutine(handle: CsRoutineHandle): FJsRoutine;
    IsHandleValid(handle: CsRoutineHandle): boolean;
    IsRunning(handle: CsRoutineHandle): boolean;
    StartByContainer(payloadContainer: FJsResourceContainer): CsRoutineHandle;
    Start(payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
    StartChildByContainer(payloadContainer: FJsResourceContainer): CsRoutineHandle;
    StartChild(payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
    EndAll(): void;
    End(handle: CsRoutineHandle): boolean;
    HasEnded(handle: CsRoutineHandle): boolean;
    HasJustEnded(handle: CsRoutineHandle): boolean;
    Update(deltaTime: CsDeltaTime): void;
    AllocatePayloadContainer(): FJsResourceContainer;
    AllocatePayload(): NJsCoroutine_NPayload_FImpl;
    GetPayloadContainer(payload: NJsCoroutine_NPayload_FImpl): FJsResourceContainer;
    BroadcastMessage(type: any, message: string, owner: object): void;
}