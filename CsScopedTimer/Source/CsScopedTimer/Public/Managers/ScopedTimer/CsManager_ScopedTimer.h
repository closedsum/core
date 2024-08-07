// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
#include "Managers/Time/CsTypes_Time.h"

#define CS_SCOPED_TIMER_SIZE 4096

// Structs
#pragma region 

	// Routine

struct CSSCOPEDTIMER_API FCsResource_ScopedTimer : public TCsResourceContainer<FCsScopedTimer>
{
	~FCsResource_ScopedTimer(){}
};

struct CSSCOPEDTIMER_API FCsManager_ScopedTimer_Internal : public NCsResource::NManager::NValue::TFixed<FCsScopedTimer, FCsResource_ScopedTimer, CS_SCOPED_TIMER_SIZE>
{
	~FCsManager_ScopedTimer_Internal(){}
};

#pragma endregion Structs

struct FECsScopedGroup;
struct FECsCVarLog;

class CSSCOPEDTIMER_API FCsManager_ScopedTimer
{
protected:
	FCsManager_ScopedTimer();

	FCsManager_ScopedTimer(const FCsManager_ScopedTimer &) = delete;
	FCsManager_ScopedTimer(FCsManager_ScopedTimer &&) = delete;
public:
	~FCsManager_ScopedTimer();

	FORCEINLINE static FCsManager_ScopedTimer& Get()
	{
		static FCsManager_ScopedTimer Instance;
		return Instance;
	}

	void Update(const FCsDeltaTime& DeltaTime);

	FCsManager_ScopedTimer_Internal Internal;

	TArray<FCsScopedGroupTimer> GroupTimers;

	const FCsScopedTimerHandle& GetHandle(const FString* Name, const FECsScopedGroup& Group, const FECsCVarLog& CVar);

	void ClearHandle(const FCsScopedTimerHandle& Handle);
	void SilentClearHandle(const FCsScopedTimerHandle& Handle);

	void UpdateHandle(FCsScopedTimerHandle& Handle, double Time, bool bClear = false);
};