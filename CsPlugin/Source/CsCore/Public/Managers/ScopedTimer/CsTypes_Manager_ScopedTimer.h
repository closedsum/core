// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// FCsScopedTimerHandle
#pragma region

/**
*/
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

	FORCEINLINE const int32& GetIndex() const { return Index; }

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

struct FECsScopedGroup;
struct FECsCVarLog;

/**
*/
struct CSCORE_API FCsScopedTimer
{
public:

	FCsScopedTimerHandle Handle;

	FString* Name;

	FECsScopedGroup* Group;

	FECsCVarLog* CVar;

	double Time;
	double AvgTime;
	double TotalTime;

	int32 Ticks;

	bool bDirty;

	FCsScopedTimer();
	~FCsScopedTimer();

	void Init(const FString* InName, const FECsScopedGroup* InGroup, const FECsCVarLog* InCVar);

	FORCEINLINE const FECsScopedGroup& GetGroup() const 
	{
		return *Group;
	}

	void SetTime(const double& InTime);

	FORCEINLINE void MarkDirty()
	{
		bDirty = true;
	}

	FORCEINLINE void ClearDirty()
	{
		bDirty = false;
	}

	FORCEINLINE bool IsDirty() const
	{
		return bDirty;
	}

	void Reset();

	void Log();
};

#pragma endregion FCsScopedTimer

// FCsScopedTimerInternal
#pragma region

/**
*/
struct CSCORE_API FCsScopedTimerInternal
{
public:

	FCsScopedTimerHandle Handle;

	double StartTime;

	FCsScopedTimerInternal(const FCsScopedTimerHandle& InHandle);
	~FCsScopedTimerInternal();
};

#pragma endregion FCsScopedTimerInternal

// FCsScopedGroupTimer
#pragma region

struct FECsScopedGroup;

/**
*/
struct CSCORE_API FCsScopedGroupTimer
{
public:

	FECsScopedGroup* Group;

	double Time;
	double AvgTime;

	int32 Ticks;

	bool bDirty;

	FCsScopedGroupTimer() :
		Group(nullptr),
		Time(0.0),
		AvgTime(0.0),
		Ticks(0),
		bDirty(false)
	{
	}

	void Init(const FECsScopedGroup* InGroup);

	FORCEINLINE void ClearDirty()
	{
		bDirty = false;
	}

	FORCEINLINE bool IsDirty() const
	{
		return bDirty;
	}

	void AddTime(const FCsScopedTimer& Timer);

	void Resolve();

	void Log();
};

#pragma endregion FCsScopedGroupTimer

#if !UE_BUILD_SHIPPING
#define CS_GET_SCOPED_TIMER_HANDLE(Handle, Name, Group, CVar) Handle = FCsManager_ScopedTimer::Get().GetHandle((Name), (&(Group)), (&(CVar)))
#define CS_CLEAR_SCOPED_TIMER_HANDLE(Handle) FCsManager_ScopedTimer::Get().ClearHandle(Handle)
#define CS_SCOPED_TIMER(Handle) FCsScopedTimerInternal __Temp_##Handle##_ScopedTimerInternal__(Handle)
#else
#define CS_GET_SCOPED_TIMER_HANDLE(Handle, Name, Group, CVar)
#define CS_CLEAR_SCOPED_TIMER_HANDLE(Handle)
#define CS_SCOPED_TIMER(Handle)
#endif // #if !UE_BUILD_SHIPPING