/// <reference path="../../typings/ue.d.ts">/>
/// <reference path="../../Cs/Coroutine/Types_Coroutine.ts">/>
/// <reference path="../../Cs/Types/Property/Property.ts">/>
/// <reference path="../../Cs/Types/Yield/Yield_Enum.ts">/>
/// <reference path="../../Cs/Types/Yield/Yield_Function.ts">/>
/// <reference path="../../Cs/Types/Yield/Yield_RoutineHandle.ts">/>
// ; typing info for auto-completion in Visual Studio Code

declare class FJsRoutine {
    self: FJsRoutine;
    Group: ECsUpdateGroup;
    StartTime: CsTime;
    ElapsedTime: CsDeltaTime;
    DeltaTime: CsDeltaTime;
    /** int */
    TickCount: number;
    /** float */
    Delay: number;
    Handle: CsRoutineHandle;
    AbortImpls: ((routine: FJsRoutine) => boolean)[];
    OnAborts: ((routine: FJsRoutine) => void)[];
    State: typeof NJsCoroutine.EState;
    /** int */
    Index: number;
    Name: string;
    EndReason: typeof NJsCoroutine.EEndReason;
    OnEnds: ((routine: FJsRoutine) => void)[];
    Owner: NJsCoroutine.FOwner;
    Parent: FJsRoutine;
    Children: FJsRoutine[];
    RegisterMap: NJsCoroutine.NRegister.FMap;
    Messages: [string[], string[]];
    Messages_Recieved: [string[], string[]];
    bWaitForFrame: boolean;
    /** int */
    WaitForFrameCounter: number;
    /** int */
    WaitForFrame: number;
    WaitForFrameType: FJsProperty;
    bWaitForTime: boolean;
    /** float */
    WaitForTime: number;
    /** float */
    WaitForTimeTimer: number;
    WaitForTimeType: FJsProperty;
    bWaitForFlag: boolean;
    WaitForFlagType: FJsProperty;
    bWaitForListenMessage: boolean;
    WaitForListenMessage: string;
    WaitForListenMessageType: FJsProperty;
    bWaitForEnum: boolean;
    WaitForEnum: NJsYield.FEnum;
    bWaitForRoutineHandle: boolean;
    WaitForRoutineHandle: NJsYield.FRoutineHandle;
    bWaitForFunction: boolean;
    WaitForFunction: NJsYield.FFunction;
}