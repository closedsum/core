// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Process/CsProcess.h"
#include "CsCore.h"
#include "Types/CsTypes_String.h"

#include "Coroutine/CsCoroutineScheduler.h"

// Enums
#pragma region

namespace ECsProcessRoutine
{
	namespace Str
	{
		const TCsString StartRead_Internal = TCsString(TEXT("StartRead_Internal"), TEXT("startread_internal"));
	}

	namespace Ref
	{
		const Type StartRead_Internal = Type::StartRead_Internal;
		const Type ECsProcessRoutine_MAX = Type::ECsProcessRoutine_MAX;
	}
}

namespace ECsProcessMonitorOutputEventPurpose
{
	namespace Str
	{
		const TCsString FireOnce = TCsString(TEXT("FireOnce"), TEXT("fireonce"));
		const TCsString Loop = TCsString(TEXT("Loop"), TEXT("Loop"));
	}

	namespace Ref
	{
		const Type FireOnce = Type::FireOnce;
		const Type Loop = Type::Loop;
		const Type ECsProcessMonitorOutputEventPurpose_MAX = Type::ECsProcessMonitorOutputEventPurpose_MAX;
	}
}

namespace ECsProcessPriorityModifier
{
	namespace Str
	{
		const TCsString Idle = TCsString(TEXT("Idle"), TEXT("idle"));
		const TCsString Low = TCsString(TEXT("Low"), TEXT("low"));
		const TCsString Normal = TCsString(TEXT("Normal"), TEXT("normal"));
		const TCsString High = TCsString(TEXT("High"), TEXT("high"));
		const TCsString Higher = TCsString(TEXT("Higher"), TEXT("higher"));
	}

	namespace Ref
	{
		const Type Idle = Type::Idle;
		const Type Low = Type::Low;
		const Type Normal = Type::Normal;
		const Type High = Type::High;
		const Type Higher = Type::Higher;
		const Type ECsProcessPriorityModifier_MAX = Type::ECsProcessPriorityModifier_MAX;
	}

	namespace Val
	{
		const int32 Idle = -2;
		const int32 Low = -1;
		const int32 Normal = 0;
		const int32 High = 1;
		const int32 Higher = 2;
	}
}

#pragma endregion Enums

UCsProcess::UCsProcess(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsProcess::Init(const int32 &Index, const FECsProcess &Type)
{
}

void UCsProcess::Allocate(const int32 &Index, FCsProcessPayload* Payload)
{
	const FString& URL						= Payload->URL;
	const FString& Params					= Payload->Params;
	const bool& bLaunchDetached				= Payload->bLaunchDetached;
	const bool& bLaucnhHidden				= Payload->bLaunchHidden;
	const bool& bLaunchReallyHidden			= Payload->bLaunchReallyHidden;
	const int32& PriorityModifier			= ECsProcessPriorityModifier::ToInt32(Payload->PriorityModifier);
	const TCHAR* OptionalWorkingDirectory	= Payload->bOptionalWorkingDirectory ? *(Payload->OptionalWorkingDirectory) : nullptr;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	ProcessHandle = FPlatformProcess::CreateProc(*URL, *Params, bLaunchDetached, bLaucnhHidden, bLaunchReallyHidden, &ProcessID, PriorityModifier, OptionalWorkingDirectory, WritePipe, ReadPipe);
}

// Interface
#pragma region

void UCsProcess::OnCreatePool()
{
}



void UCsProcess::DeAllocate()
{
	Super::DeAllocate();

	if (ProcessHandle.IsValid())
	{
		FPlatformProcess::TerminateProc(ProcessHandle, true);

		if (ReadPipe || WritePipe)
		{
			FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
			ReadPipe = WritePipe = nullptr;
		}
	}
	Cache.Reset();
}

#pragma endregion Interface

// Routines
#pragma region

/*static*/ void UCsProcess::AddRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsProcess>(InProcess)->AddRoutine_Internal(Routine, Type);
}

bool UCsProcess::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsProcessRoutine RoutineType = (TCsProcessRoutine)Type;

	// CreateKeystore_Internal
	if (RoutineType == ECsProcessRoutine::StartRead_Internal)
	{
		StartRead_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void UCsProcess::RemoveRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsProcess>(InProcess)->RemoveRoutine_Internal(Routine, Type);
}

bool UCsProcess::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	const TCsProcessRoutine RoutineType = (TCsProcessRoutine)Type;

	// CreateKeystore_Internal
	if (RoutineType == ECsProcessRoutine::StartRead_Internal)
	{
		check(StartRead_Internal_Routine == Routine);
		StartRead_Internal_Routine = nullptr;
		return true;
	}
	return false;
}

#pragma endregion Routines

void UCsProcess::RunCommand(const FString &Command)
{
	FPlatformProcess::WritePipe(WritePipe, Command);
	FPlatformProcess::WritePipe(WritePipe, ECsStringEscapeCharacter::LF);

	StartRead();
}

// Read / Output
#pragma region

void UCsProcess::StartRead()
{
	if (StartRead_Internal_Routine && StartRead_Internal_Routine->IsValid())
		StartRead_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	ReadFlag = true;
}

CS_COROUTINE(UCsProcess, StartRead_Internal)
{
	UCsProcess* p			 = r->GetRObject<UCsProcess>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const float INTERVAL = 0.1f;
	float& Elapsed		 = r->timers[0];
	Elapsed				+= r->deltaSeconds;
	FString& LastRead	 = r->strings[0];

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			const FString Output = FPlatformProcess::ReadPipe(p->ReadPipe);

			TArray<FString> Lines;

			FCsStringHelper::GetLines(Output, Lines);

			const int32 Count = Lines.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				UE_LOG(LogCs, Log, TEXT("Process::StartRead: ReadPipe: Output: %s"), *(Lines[I]));
			}
		}

		if (p->ReadFlag)
		{
			Elapsed = 0.0f;

			CS_COROUTINE_WAIT_UNTIL(r, Elapsed >= INTERVAL)
		}
	} while (p->ReadFlag);

	CS_COROUTINE_END(r);
}

void UCsProcess::StopRead()
{
	ReadFlag = false;

	if (StartRead_Internal_Routine && StartRead_Internal_Routine->IsValid())
		StartRead_Internal_Routine->End(ECsCoroutineEndReason::Manual);
}

void UCsProcess::AddMonitorOutputEvent(FCsProcessMonitorOutputEvent &Event)
{
	MonitorOutputEvents.Add(&Event);
}

void UCsProcess::ProcessMonitorOuputEvents(const FString &Output)
{
	const int32 Count = MonitorOutputEvents.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsProcessMonitorOutputEvent* Event = MonitorOutputEvents[I];

		Event->ProcessOutput(Output);

		if (Event->HasCompleted())
		{
			Event->Clear();

			// FireOnce
			if (Event->Purpose == ECsProcessMonitorOutputEventPurpose::FireOnce)
				MonitorOutputEvents.RemoveAt(I);
		}
	}
}

void UCsProcess::OnOutputRecieved(const FString &Output)
{
	OnOutputRecieved_Event.Broadcast(Output);
#if WITH_EDITOR
	OnOutputRecieved_ScriptEvent.Broadcast(Output);
#endif // #if WITH_EDITOR
	ProcessMonitorOuputEvents(Output);
}

#pragma endregion Read / Output