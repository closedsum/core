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
	Group(nullptr),
	CVar(nullptr),
	Time(0.0),
	AvgTime(0.0),
	TotalTime(0.0),
	Ticks(0),
	bDirty(false)
{
}

FCsScopedTimer::~FCsScopedTimer()
{
	Name = nullptr;
}

void FCsScopedTimer::Init(const FString* InName, const FECsCVarLog* InCVar)
{
	checkf(InName, TEXT("FCsScopedTimer::Init: InName is NULL."));

	checkf(InCVar, TEXT("FCsScopedTimer::Init: InCVar is NULL."));

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

	bDirty = false;
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

// FCsScopedGroupTimer
#pragma region

void FCsScopedGroupTimer::Init(const FECsScopedGroup* InGroup)
{
	Group = const_cast<FECsScopedGroup*>(InGroup);
}

void FCsScopedGroupTimer::Add(const FCsScopedTimer& Timer)
{
	if (!bDirty)
	{
		Time = 0.0;

		++Ticks;

		bDirty = true;
	}

	Time += Timer.Time;
}

void FCsScopedGroupTimer::Resolve()
{
	AvgTime = (AvgTime + Time) / Ticks;
}

void FCsScopedGroupTimer::Log()
{
	if (FCsScopedGroupMap::Get().IsShowing(*Group))
	{
		UE_LOG(LogCs, Log, TEXT("%s: Time: %f AvgTime: %f Ticks: %d"), Group->DisplayNameToChar(), (float)Time, (float)AvgTime, Ticks);
	}
}

#pragma endregion FCsScopedGroupTimer