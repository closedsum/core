// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Process/CsProcess.h"
#include "CsCore.h"

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

void UCsProcess::RunCommand(const FString &Command){}

// Read / Output
#pragma region

void UCsProcess::StartRead()
{

}

CS_COROUTINE(UCsProcess, StartRead_Internal)
{
	CS_COROUTINE_BEGIN(r);

	CS_COROUTINE_END(r);
}

void UCsProcess::StopRead()
{

}

void UCsProcess::AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent &Event)
{
	MonitorOutputEvents.Add(Event);
}

void UCsProcess::ProcessMonitorOuputEvents(const FString &Output)
{
}

void UCsProcess::OnOutputRecieved(const FString &Output)
{
}

#pragma endregion Read / Output