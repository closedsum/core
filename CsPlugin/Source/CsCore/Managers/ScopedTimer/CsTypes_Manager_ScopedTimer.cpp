// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
#include "CsCore.h"

// CVar
#include "CsCVars.h"
// Managers
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"

const FCsScopedTimerHandle FCsScopedTimerHandle::Invalid;

// FCsScopedTimer
#pragma region

FCsScopedTimer::FCsScopedTimer() :
	Handle(),
	Name(nullptr),
	CVar(nullptr),
	Time(0.0),
	AvgTime(0.0),
	TotalTime(0.0),
	Ticks(0)
{
}

FCsScopedTimer::~FCsScopedTimer()
{
	Name = nullptr;
}

void FCsScopedTimer::Init(const FString* InName, const FECsCVarLog* InCVar)
{
	checkf(CVar, TEXT("FCsScopedTimer::Init: CVar is NULL."));

	Name = const_cast<FString*>(InName);
	CVar = const_cast<FECsCVarLog*>(InCVar);

	Handle.New();
}

void FCsScopedTimer::SetTime(const double& InTime)
{
	++Ticks;

	Time      = InTime;
	AvgTime   = (AvgTime + Time) / Ticks;
	TotalTime += Time;
}

void FCsScopedTimer::Reset()
{
	Handle.Reset();

	Name = nullptr;

	CVar = nullptr;

	Time = 0.0;
	AvgTime = 0.0;
	TotalTime = 0.0;

	Ticks = 0;
}

void FCsScopedTimer::Log()
{
	if (FCsCVarLogMap::Get().IsShowing(*CVar))
	{
		UE_LOG(LogCs, Log, TEXT("%s: Time: %f AvgTime: %f TotalTime: %f Ticks: %d"), **Name, (float)Time, (float)AvgTime, (float)TotalTime, Ticks);
	}
}

#pragma endregion FCsScopedTimer

// FCsScopedTimerInternal
#pragma region

FCsScopedTimerInternal::FCsScopedTimerInternal(const FCsScopedTimerHandle& InHandle)
{
	Handle = InHandle;

	StartTime = FPlatformTime::Seconds();
}

FCsScopedTimerInternal::~FCsScopedTimerInternal()
{
	FCsManager_ScopedTimer::Get().UpdateHandle(Handle, FPlatformTime::Seconds() - StartTime);
}

#pragma endregion FCsScopedTimerInternal