// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformAffinity.h"
#include "Managers/Runnable/CsTypes_Runnable.h"
#pragma once

class UObject;
struct ICsRunnableTask;

/**
*/
struct CSCORE_API FCsRunnableTaskPayload
{
private:

	int32 Index;

public:

	TWeakObjectPtr<UObject> Owner;

	ICsRunnableTask* Task;

	FCsRunnableHandle Handle;

	FCsRunnableTaskPayload() :
		Index(INDEX_NONE),
		Owner(nullptr),
		Task(nullptr),
		Handle()
	{
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	FORCEINLINE bool IsPooled() const
	{
		return Index != INDEX_NONE;
	}

	void Reset()
	{
		Owner.Reset();
		Owner = nullptr;
		Task = nullptr;
		Handle = FCsRunnableHandle::Invalid;
	}

	UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	
	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }
};