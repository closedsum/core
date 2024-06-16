// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core

/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code
// Coroutine
/// <reference path="../Coroutine/Routine.ts">/>
// Managers
/// <reference path="../Managers/Resource/Manager_Resource_Fixed.ts">/>

declare namespace NJsCoroutine {
    namespace NSchedule {
        class FDefault {
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
    }

    namespace NSchedule {
        class FCustom {
            Manager_OwnerID: FJsManager_Resource_Fixed;
            MaxOwners: number;
            MaxRoutinesPerOwner: number;
            OwnerRoutineIDs: [number];
            RoutineStrideByOwnerID: [number];
            Group: ECsUpdateGroup;
            Manager_Routine: FJsManager_Resource_Fixed;
            Manager_Payload: FJsManager_Resource_Fixed;
            OwnerQueueEndHandles: [CsRoutineHandle];
            QueueEndHandleStrideByOwnerID: [number];
            AllocateOwnerID(): number;
            DeallocateOwnerID(ownerID: number): void;
            HasFreeOwnerID(): boolean;
            GetOwnerID(routineIndex: number): number;
            GetOwnerIDByRoutine(r: FJsRoutine): number;
            GetOwnerIDByHandle(handle: CsRoutineHandle): number;
            SetGroup(group: ECsUpdateGroup);
            GetRoutineContainer(handle: CsRoutineHandle): FJsResourceContainer;
            GetRoutine(handle: CsRoutineHandle): FJsRoutine;
            IsHandleValid(handle: CsRoutineHandle): boolean;
            IsRunning(handle: CsRoutineHandle): boolean;
            StartByContainer(ownerID: number, payloadContainer: FJsResourceContainer): CsRoutineHandle;
            Start(ownerID: number, payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
            StartChildByContainer(ownerID: number, payloadContainer: FJsResourceContainer): CsRoutineHandle;
            StartChild(ownerID: number, payload: NJsCoroutine_NPayload_FImpl): CsRoutineHandle;
            EndAll(): void;
            End(ownerID: number, handle: CsRoutineHandle): boolean;
            HasEnded(handle: CsRoutineHandle): boolean;
            HasJustEnded(handle: CsRoutineHandle): boolean;
            Update(deltaTime: CsDeltaTime): void;
            AllocatePayloadContainer(): FJsResourceContainer;
            AllocatePayload(): NJsCoroutine_NPayload_FImpl;
            GetPayloadContainer(payload: NJsCoroutine_NPayload_FImpl): FJsResourceContainer;
            BroadcastMessage(type: any, message: string, owner: object): void;
        }
    }
}

declare type NJsCoroutine_NSchedule_FDefault = NJsCoroutine.NSchedule.FDefault;
declare type NJsCoroutine_NSchedule_FCustom = NJsCoroutine.NSchedule.FCustom;