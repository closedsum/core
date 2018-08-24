// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Process/CsProcess.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Types/CsTypes_String.h"

#include "Coroutine/CsCoroutineScheduler.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#endif // #if PLATFORM_WINDOWS

// Enums
#pragma region

EMCsProcess* EMCsProcess::Instance;

EMCsProcess& EMCsProcess::Get()
{
	if (!Instance)
		Instance = new EMCsProcess();
	return *Instance;
}

// ProcessRoutine

EMCsProcessRoutine* EMCsProcessRoutine::Instance;

EMCsProcessRoutine& EMCsProcessRoutine::Get()
{
	if (!Instance)
		Instance = new EMCsProcessRoutine();
	return *Instance;
}

namespace ECsProcessRoutine
{
	namespace Ref
	{
		CSCORE_API const Type StartRead_Internal = EMCsProcessRoutine::Get().Add(Type::StartRead_Internal, TEXT("StartRead_Internal"));
		CSCORE_API const Type ECsProcessRoutine_MAX = EMCsProcessRoutine::Get().Add(Type::ECsProcessRoutine_MAX, TEXT("ECsProcessRoutine_MAX"), TEXT("MAX"));
	}
}

// ProcessMonitorOutputEventPurpose

EMCsProcessMonitorOutputEventPurpose* EMCsProcessMonitorOutputEventPurpose::Instance;

EMCsProcessMonitorOutputEventPurpose& EMCsProcessMonitorOutputEventPurpose::Get()
{
	if (!Instance)
		Instance = new EMCsProcessMonitorOutputEventPurpose();
	return *Instance;
}

namespace ECsProcessMonitorOutputEventPurpose
{
	namespace Ref
	{
		CSCORE_API const Type FireOnce = EMCsProcessMonitorOutputEventPurpose::Get().Add(Type::FireOnce, TEXT("FireOnce"), TEXT("Fire Once"));
		CSCORE_API const Type Loop = EMCsProcessMonitorOutputEventPurpose::Get().Add(Type::Loop, TEXT("Loop"));
		CSCORE_API const Type ECsProcessMonitorOutputEventPurpose_MAX = EMCsProcessMonitorOutputEventPurpose::Get().Add(Type::ECsProcessMonitorOutputEventPurpose_MAX, TEXT("ECsProcessMonitorOutputEventPurpose_MAX"), TEXT("MAX"));
	}
}

namespace ECsProcessPriorityModifier
{
	namespace Str
	{
		CSCORE_API const TCsString Idle = TCsString(TEXT("Idle"), TEXT("idle"));
		CSCORE_API const TCsString Low = TCsString(TEXT("Low"), TEXT("low"));
		CSCORE_API const TCsString Normal = TCsString(TEXT("Normal"), TEXT("normal"));
		CSCORE_API const TCsString High = TCsString(TEXT("High"), TEXT("high"));
		CSCORE_API const TCsString Higher = TCsString(TEXT("Higher"), TEXT("higher"));
	}

	namespace Ref
	{
		CSCORE_API const Type Idle = Type::Idle;
		CSCORE_API const Type Low = Type::Low;
		CSCORE_API const Type Normal = Type::Normal;
		CSCORE_API const Type High = Type::High;
		CSCORE_API const Type Higher = Type::Higher;
		CSCORE_API const Type ECsProcessPriorityModifier_MAX = Type::ECsProcessPriorityModifier_MAX;
	}

	namespace Val
	{
		CSCORE_API const int32 Idle = -2;
		CSCORE_API const int32 Low = -1;
		CSCORE_API const int32 Normal = 0;
		CSCORE_API const int32 High = 1;
		CSCORE_API const int32 Higher = 2;
	}
}

#pragma endregion Enums

// Cache
#pragma region

namespace ECsProcessCached
{
	namespace Name
	{
		// Functions
		const FName StartRead_Internal = FName("UCsProcess::StartRead_Internal");
	};

	namespace Str
	{
		// Functions
		const FString StartRead_Internal = TEXT("UCsProcess::StartRead_Internal");
	};
}

#pragma endregion Cache

// Copied from: Engine\Source\Runtime\Core\Private\Misc\InteractiveProcess.cpp

static FORCEINLINE bool CreatePipeWrite(void*& ReadPipe, void*& WritePipe)
{
#if PLATFORM_WINDOWS
	SECURITY_ATTRIBUTES Attr = { sizeof(SECURITY_ATTRIBUTES), NULL, true };

	if (!::CreatePipe(&ReadPipe, &WritePipe, &Attr, 0))
	{
		return false;
	}

	if (!::SetHandleInformation(WritePipe, HANDLE_FLAG_INHERIT, 0))
	{
		return false;
	}

	return true;
#else
	return FPlatformProcess::CreatePipe(ReadPipe, WritePipe);
#endif // PLATFORM_WINDOWS
}

UCsProcess::UCsProcess(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsProcess::Init(const int32 &Index, const FECsProcess &Type)
{
}

void UCsProcess::Allocate(FCsProcessPayload* Payload)
{
	// For reading from child process
	FPlatformProcess::CreatePipe(ReadPipeParent, WritePipeChild);
	// For writing to child process
	CreatePipeWrite(ReadPipeChild, WritePipeParent);

	const FString& URL						= Payload->URL;
	const FString& Params					= Payload->Params;
	const bool& bLaunchDetached				= Payload->bLaunchDetached;
	const bool& bLaucnhHidden				= Payload->bLaunchHidden;
	const bool& bLaunchReallyHidden			= Payload->bLaunchReallyHidden;
	const int32& PriorityModifier			= ECsProcessPriorityModifier::ToInt32(Payload->PriorityModifier);
	const TCHAR* OptionalWorkingDirectory	= Payload->bOptionalWorkingDirectory ? *(Payload->OptionalWorkingDirectory) : nullptr;

	ProcessHandle = FPlatformProcess::CreateProc(*URL, *Params, bLaunchDetached, bLaucnhHidden, bLaunchReallyHidden, &ProcessID, PriorityModifier, OptionalWorkingDirectory, WritePipeChild, ReadPipeChild);

	StartRead();
}

// Interface
#pragma region

void UCsProcess::OnCreatePool()
{
	Super::OnCreatePool();
}

void UCsProcess::DeAllocate()
{
	StopRead();

	if (ProcessHandle.IsValid())
	{
		FPlatformProcess::TerminateProc(ProcessHandle, true);

		if (ReadPipeParent || WritePipeChild)
		{
			FPlatformProcess::ClosePipe(ReadPipeParent, WritePipeChild);
			ReadPipeParent = WritePipeChild = nullptr;
		}

		if (ReadPipeChild || WritePipeParent)
		{
			FPlatformProcess::ClosePipe(ReadPipeChild, WritePipeParent);
			ReadPipeChild = WritePipeParent = nullptr;
		}
	}
	ProcessID = 0;
	ProcessHandle.Reset();

	Cache.Reset();

	Super::DeAllocate();
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
	if (CsCVarLogProcessIO->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Process::RunCommand (%s-WritePipe): %s"), *(Cache.Name), *Command);
	}

	FPlatformProcess::WritePipe(WritePipeParent, Command);

	//StartRead();
}

// Read / Output
#pragma region

void UCsProcess::StartRead()
{
	if (StartRead_Internal_Routine && StartRead_Internal_Routine->IsValid())
		StartRead_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	ReadFlag = true;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload = Scheduler->AllocatePayload();

	const ECsCoroutineSchedule& Schedule = NCsCoroutineSchedule::Ref::Tick;

	Payload->Schedule		= Schedule;
	Payload->Function		= &UCsProcess::StartRead_Internal;
	Payload->Object			= this;
	Payload->Stop.Add(&UCsCommon::CoroutineStopCondition_CheckObject);
	Payload->Add			= &UCsProcess::AddRoutine;
	Payload->Remove			= &UCsProcess::RemoveRoutine;
	Payload->Type			= (uint8)ECsProcessRoutine::StartRead_Internal;
	Payload->DoInit			= true;
	Payload->PerformFirstRun = false;
	Payload->Name			= ECsProcessCached::Name::StartRead_Internal;
	Payload->NameAsString	= ECsProcessCached::Str::StartRead_Internal;

	FCsRoutine* R = Scheduler->Allocate(Payload);

	Scheduler->StartRoutine(Schedule, R);
}

CS_COROUTINE(UCsProcess, StartRead_Internal)
{
	UCsProcess* p			 = r->GetRObject<UCsProcess>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const float INTERVAL = 0.1f;
	float& Elapsed		 = r->timers[CS_FIRST];
	Elapsed				+= r->deltaSeconds;
	FString& LastRead	 = r->strings[CS_FIRST];

	CS_COROUTINE_BEGIN(r);

	do
	{
		{
			const FString Output = FPlatformProcess::ReadPipe(p->ReadPipeParent);

			TArray<FString> Lines;

			FCsStringHelper::GetLines(Output, Lines);

			const int32 Count = Lines.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				p->OnOutputRecieved(Lines[I]);
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

void UCsProcess::AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent &Event)
{
	MonitorOutputEvents.Add(Event);
}

void UCsProcess::ProcessMonitorOuputEvents(const FString &Output)
{
	const int32 Count = MonitorOutputEvents.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsProcessMonitorOutputEvent& Event = MonitorOutputEvents[I];

		Event.ProcessOutput(Output);

		if (Event.HasCompleted())
		{
			Event.Clear();

			// FireOnce
			if (Event.Purpose == ECsProcessMonitorOutputEventPurpose::FireOnce)
			{
				MonitorOutputEvents.RemoveAt(I);
				//StopRead();
			}
		}
	}
}

void UCsProcess::OnOutputRecieved(const FString &Output)
{
	if (CsCVarLogProcessIO->GetInt() == CS_CVAR_SHOW_LOG)
	{
		UE_LOG(LogCs, Log, TEXT("Process::OnOutputRecieved (%s-ReadPipe): %s"), **(Cache.Name), *Output);
	}

	OnOutputRecieved_Event.Broadcast(Output);
#if WITH_EDITOR
	OnOutputRecieved_ScriptEvent.Broadcast(Output);
#endif // #if WITH_EDITOR
	ProcessMonitorOuputEvents(Output);
}

#pragma endregion Read / Output