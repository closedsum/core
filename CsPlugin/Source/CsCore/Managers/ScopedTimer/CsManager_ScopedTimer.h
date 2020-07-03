// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"
#include "Managers/Time/CsTypes_Time.h"

#define CS_SCOPED_TIMER_SIZE 4096

// Structs
#pragma region 

	// Routine

struct CSCORE_API FCsResource_ScopedTimer : public TCsResourceContainer<FCsScopedTimer>
{
};

struct CSCORE_API FCsManager_ScopedTimer_Internal : public TCsManager_ResourceValueType_Fixed<FCsScopedTimer, FCsResource_ScopedTimer, CS_SCOPED_TIMER_SIZE>
{
};

#pragma endregion Structs

struct FECsCVarLog;

class CSCORE_API FCsManager_ScopedTimer
{
protected:
	FCsManager_ScopedTimer();

	FCsManager_ScopedTimer(const FCsManager_ScopedTimer &) = delete;
	FCsManager_ScopedTimer(FCsManager_ScopedTimer &&) = delete;
public:
	~FCsManager_ScopedTimer();

	static FCsManager_ScopedTimer& Get();

	void Update(const FCsDeltaTime& DeltaTime);

	FCsManager_ScopedTimer_Internal Internal;

	const FCsScopedTimerHandle& GetHandle(const FString* Name, const FECsCVarLog* CVar);

	void ClearHandle(const FCsScopedTimerHandle& Handle);

	void UpdateHandle(FCsScopedTimerHandle& Handle, double Time);
};