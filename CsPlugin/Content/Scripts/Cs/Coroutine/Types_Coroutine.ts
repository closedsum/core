/// <reference path="../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

// require('Cs/Coroutine/Types_Coroutine.js')

declare namespace NJsCoroutine {
    var EState:
    {
        Free:       { Value: 0, Name: "Free" },
        Init:       { Value: 1, Name: "Init" },
        Update:     { Value: 2, Name: "Update" },
        End:        { Value: 3, Name: "End" },
        EState_MAX: { Value: 4, Name: "EState_MAX" }
    };
    var EMessage:
    {
        Notify:       { Value: 0, Name: "Notify" },
        Listen:       { Value: 1, Name: "Listen" },
        Abort:        { Value: 2, Name: "Abort" },
        EMessage_MAX: { Value: 3, Name: "EMessage_MAX" }
    };
    var EEndReason:
    {
        EndOfExecution: { Value: 0, Name: "EndOfExecution" },
        AbortMessage:   { Value: 1, Name: "AbortMessage" },
        AbortCondition: { Value: 2, Name: "AbortCondition" },
        OwnerIsInvalid: { Value: 3, Name: "OwnerIsInvalid" },
        Parent:         { Value: 4, Name: "Parent" },
        UniqueInstance: { Value: 5, Name: "UniqueInstance" },
        Shutdown:       { Value: 6, Name: "Shutdown" },
        Manual:         { Value: 7, Name: "Manual" },
        EEndReason_MAX: { Value: 8, Name: "EEndReason_MAX" }
    };

    class FOwner {
        Owner: object;
        UEObject: UObject;
        bObject: boolean;
        UEActor: Actor;
        IsObject(): boolean;
        SetObject(o: object): void;
        Copy(from: NJsCoroutine.FOwner): void;
        Reset(): void;
    }
}
declare namespace NJsCoroutine.NRegister {
    class FInfo {
        Index: number
    }

    class FMap {
        Infos: NJsCoroutine.NRegister.FInfo[];
        Values: any[];
        UseValues: boolean[];
        SetUsedValue(index: number): void;
        SetValue(i: number, v: any): void;
        GetValue(i: number): any;
        Reset(): void;
    }
}

declare namespace NJsCoroutine.NPayload {
    class FImpl {
        Index: number;;
        Group : ECsUpdateGroup;
        CoroutineImpl: IterableIterator<any>;
        StartTime: CsTime;
        Owner: NJsCoroutine.FOwner;
        AbortImpls: ((any) => boolean)[];
        OnAborts: ((any) => void)[];
        OnEnds: ((any) => void)[];
        ParentHandle: CsRoutineHandle;
        bDoInit: boolean;
        bPerformFirstUpdate: boolean;
        AbortMessages: string[];
        RegisterMap: NJsCoroutine.NRegister.FMap;
        Name: string;
        SetIndex(index: number): void;
        GetIndex(): number;
        SetValue(index: number, value: any): void;
        Reset(): void;
        Copy(from: NJsCoroutine.NPayload.FImpl): void;
        IsValidChecked(context: string): boolean;
    }
}