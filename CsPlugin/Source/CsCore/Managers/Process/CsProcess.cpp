// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Process/CsProcess.h"
#include "CsCore.h"
#include "CsCVars.h"

// Types
#include "Types/CsTypes_String.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#endif // #if PLATFORM_WINDOWS

// Enums
#pragma region

	// ProcessRoutine
namespace NCsProcessRoutine
{
	namespace Ref
	{
		CSCORE_API const Type StartRead_Internal = EMCsProcessRoutine::Get().Add(Type::StartRead_Internal, TEXT("StartRead_Internal"));
		CSCORE_API const Type ECsProcessRoutine_MAX = EMCsProcessRoutine::Get().Add(Type::ECsProcessRoutine_MAX, TEXT("ECsProcessRoutine_MAX"), TEXT("MAX"));
	}
}

	// ProcessMonitorOutputEventPurpose
namespace NCsProcessMonitorOutputEventPurpose
{
	namespace Ref
	{
		CSCORE_API const Type FireOnce = EMCsProcessMonitorOutputEventPurpose::Get().Add(Type::FireOnce, TEXT("FireOnce"), TEXT("Fire Once"));
		CSCORE_API const Type Loop = EMCsProcessMonitorOutputEventPurpose::Get().Add(Type::Loop, TEXT("Loop"));
		CSCORE_API const Type ECsProcessMonitorOutputEventPurpose_MAX = EMCsProcessMonitorOutputEventPurpose::Get().Add(Type::ECsProcessMonitorOutputEventPurpose_MAX, TEXT("ECsProcessMonitorOutputEventPurpose_MAX"), TEXT("MAX"));
	}
}

	// ProcessPriorityModifier
namespace NCsProcessPriorityModifier
{
	namespace Ref
	{
		CSCORE_API const Type Idle = EMCsProcessPriorityModifier::Get().Add(Type::Idle, TEXT("Idle"));
		CSCORE_API const Type Low = EMCsProcessPriorityModifier::Get().Add(Type::Low, TEXT("Low"));
		CSCORE_API const Type Normal = EMCsProcessPriorityModifier::Get().Add(Type::Normal, TEXT("Normal"));
		CSCORE_API const Type High = EMCsProcessPriorityModifier::Get().Add(Type::High, TEXT("High"));
		CSCORE_API const Type Higher = EMCsProcessPriorityModifier::Get().Add(Type::Higher, TEXT("Higher"));
		CSCORE_API const Type ECsProcessPriorityModifier_MAX = EMCsProcessPriorityModifier::Get().Add(Type::ECsProcessPriorityModifier_MAX, TEXT("ECsProcessPriorityModifier_MAX"), TEXT("MAX"));
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

namespace NCsProcessCached
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

void UCsProcess::Init(const int32 &Index, const FECsProcess& Type)
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
	const int32& PriorityModifier			= NCsProcessPriorityModifier::ToInt32(Payload->PriorityModifier);
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

/*static*/ void UCsProcess::AddRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8& Type)
{
	Cast<UCsProcess>(InProcess)->AddRoutine_Internal(Routine, Type);
}

bool UCsProcess::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type)
{
	const ECsProcessRoutine RoutineType = (ECsProcessRoutine)Type;

	// CreateKeystore_Internal
	if (RoutineType == ECsProcessRoutine::StartRead_Internal)
	{
		StartRead_Internal_Routine = Routine;
		return true;
	}
	return false;
}

/*static*/ void UCsProcess::RemoveRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8& Type)
{
	Cast<UCsProcess>(InProcess)->RemoveRoutine_Internal(Routine, Type);
}

bool UCsProcess::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type)
{
	const ECsProcessRoutine RoutineType = (ECsProcessRoutine)Type;

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

void UCsProcess::RunCommand(const FString& Command)
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
	if (StartRead_Internal_Routine)
		StartRead_Internal_Routine->End(ECsCoroutineEndReason::UniqueInstance);

	ReadFlag = true;

	const FECsUpdateGroup& Group = NCsUpdateGroup::GameInstance;
	
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();
	FCsCoroutinePayload* Payload	 = Scheduler->AllocatePayload(Group);

	Payload->Coroutine.BindStatic(&UCsProcess::StartRead_Internal);
	Payload->StartTime = UCsManager_Time::Get()->GetTime(Group);
	Payload->Owner.SetObject(this);

	Payload->SetName(NCsProcessCached::Str::StartRead_Internal);
	Payload->SetFName(NCsProcessCached::Name::StartRead_Internal);

	Scheduler->Start(Payload);
}

CS_COROUTINE(UCsProcess, StartRead_Internal)
{
	UCsProcess* p = r->GetOwnerAsObject<UCsProcess>();
	UCsCoroutineScheduler* s = UCsCoroutineScheduler::Get();

	const float INTERVAL = 0.1f;
	float& Elapsed		 = r->GetValue_Float(CS_FIRST);
	Elapsed				+= r->DeltaTime.Time;
	FString& LastRead	 = r->GetValue_String(CS_FIRST);

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

	if (StartRead_Internal_Routine)
		StartRead_Internal_Routine->End(ECsCoroutineEndReason::Manual);
}

void UCsProcess::AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent& Event)
{
	MonitorOutputEvents.Add(Event);
}

void UCsProcess::ProcessMonitorOuputEvents(const FString& Output)
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

void UCsProcess::OnOutputRecieved(const FString& Output)
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