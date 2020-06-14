// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// FCsScopedTimerHandle
#pragma region

struct CSCORE_API FCsScopedTimerHandle
{
public:

	static const FCsScopedTimerHandle Invalid;

public:

	int32 Index;

	FGuid Handle;

	FCsScopedTimerHandle() :
		Index(INDEX_NONE),
		Handle()
	{
	}

	FORCEINLINE bool operator==(const FCsScopedTimerHandle& B) const
	{
		return Index == B.Index && Handle == B.Handle;
	}

	FORCEINLINE bool operator!=(const FCsScopedTimerHandle& B) const
	{
		return !(*this == B);
	}

	friend uint32 GetTypeHash(const FCsScopedTimerHandle& InHandle)
	{
		return GetTypeHash(InHandle.Handle);
	}

	FORCEINLINE bool IsValid() const
	{
		return Index > INDEX_NONE && Handle.IsValid();
	}

	FORCEINLINE void New()
	{
		Handle = FGuid::NewGuid();
	}

	FORCEINLINE void Reset()
	{
		Handle.Invalidate();
	}
};

#pragma endregion FCsScopedTimerHandle

// FCsScopedTimer
#pragma region

struct CSCORE_API FCsScopedTimer
{
public:

	FCsScopedTimerHandle Handle;

	FString* Name;

	FECsCVarLog CVar;

	double Time;
	double AvgTime;
	double TotalTime;

	int32 Ticks;

	FCsScopedTimer();
	~FCsScopedTimer();

	void Init(const FString* InName, const FECsCVarLog& InCVar);

	void SetTime(const double& InTime);

	void Reset();

	void Log();
};

#pragma endregion FCsScopedTimer

// FCsScopedTimerInternal
#pragma region

struct CSCORE_API FCsScopedTimerInternal
{
public:

	FCsScopedTimerHandle Handle;

	double StartTime;

	FCsScopedTimerInternal(const FCsScopedTimerHandle& InHandle);
	~FCsScopedTimerInternal();
};

#pragma endregion FCsScopedTimerInternal

#if !UE_BUILD_SHIPPING
#define CS_GET_SCOPED_TIMER_HANDLE(Handle, Name, CVar) Handle = FCsManager_ScopedTimer::Get().GetHandle((Name), CVar)
#define CS_SCOPED_TIMER(Handle) FCsScopedTimerInternal __Temp_ScopedTimerInternal__(Handle)
#else
#define CS_GET_SCOPED_TIMER_HANDLE(Handle, Name, CVar)
#define CS_SCOPED_TIMER(Handle)
#endif // #if !UE_BUILD_SHIPPING