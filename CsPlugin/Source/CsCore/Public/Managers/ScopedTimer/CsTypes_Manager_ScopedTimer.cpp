// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
#include "CsCore.h"

// CVar
#include "CsCVars.h"
// Managers
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"

const FCsScopedTimerHandle FCsScopedTimerHandle::Invalid;

// FCsScopedTimer
#pragma region

namespace NCsScopedTimer
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsScopedTimer, Init);
		}
	}
}

FCsScopedTimer::FCsScopedTimer() :
	Handle(),
	Name(nullptr),
	Group(),
	CVar(),
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

void FCsScopedTimer::Init(const FString* InName, const FECsScopedGroup& InGroup, const FECsCVarLog& InCVar)
{
	using namespace NCsScopedTimer::NCached;

	const FString& Context = Str::Init;

	checkf(InName, TEXT("%s: InName is NULL."), *Context);

	check(EMCsScopedGroup::Get().IsValidEnumChecked(Context, InGroup));

	check(EMCsCVarLog::Get().IsValidEnumChecked(Context, InCVar));

	Name = const_cast<FString*>(InName);
	Group = InGroup;
	CVar = InCVar;

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

	Group = EMCsScopedGroup::Get().GetMAX();
	CVar = EMCsCVarLog::Get().GetMAX();

	Time = 0.0;
	AvgTime = 0.0;
	TotalTime = 0.0;

	Ticks = 0;

	bDirty = false;
}

void FCsScopedTimer::Log()
{
	if (FCsCVarLogMap::Get().IsShowing(CVar))
	{
		UE_LOG(LogCs, Log, TEXT("%s: Time: %fms AvgTime: %fms TotalTime: %fms Ticks: %d"), **Name, (float)(1000.0 * Time), (float)(1000.0 * AvgTime), (float)(1000.0 * TotalTime), Ticks);
	}
}

#pragma endregion FCsScopedTimer

// FCsScopedTimerInternal
#pragma region

FCsScopedTimerInternal::FCsScopedTimerInternal(const FCsScopedTimerHandle& InHandle)
{
	bOneShot = false;
	Handle	 = InHandle;

	StartTime = FPlatformTime::Seconds();
}

FCsScopedTimerInternal::FCsScopedTimerInternal(const FString* Name, const FECsScopedGroup& Group, const FECsCVarLog& CVar)
{
	bOneShot = true;
	Handle	 = FCsManager_ScopedTimer::Get().GetHandle(Name, Group, CVar);

	StartTime = FPlatformTime::Seconds();
}

FCsScopedTimerInternal::~FCsScopedTimerInternal()
{
	FCsManager_ScopedTimer::Get().UpdateHandle(Handle, FPlatformTime::Seconds() - StartTime, bOneShot);
}

#pragma endregion FCsScopedTimerInternal

// FCsScopedGroupTimer
#pragma region

void FCsScopedGroupTimer::Init(const FECsScopedGroup& InGroup)
{
	Group = InGroup;
}

void FCsScopedGroupTimer::AddTime(const FCsScopedTimer& Timer)
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
	if (FCsScopedGroupMap::Get().IsShowing(Group))
	{
		UE_LOG(LogCs, Log, TEXT("%s: Time: %fms AvgTime: %fms Ticks: %d"), Group.DisplayNameToChar(), (float)(1000.0 * Time), (float)(1000.0 * AvgTime), Ticks);
	}
}

#pragma endregion FCsScopedGroupTimer