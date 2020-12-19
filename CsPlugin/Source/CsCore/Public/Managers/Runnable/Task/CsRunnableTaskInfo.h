// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformAffinity.h"
#include "Managers/Runnable/CsTypes_Runnable.h"
#pragma once

class UObject;
struct ICsRunnableTask;

/**
*/
struct CSCORE_API FCsRunnableTaskInfo
{
private:

	int32 Index;

public:

	FString* Name;

	TWeakObjectPtr<UObject> Owner;

	ICsRunnableTask* Task;

	FCsRunnableHandle Handle;

	FCsRunnableTaskInfo() :
		Index(INDEX_NONE),
		Name(nullptr),
		Owner(nullptr),
		Task(nullptr),
		Handle()
	{
	}

	FORCEINLINE const int32& GetIndex() const
	{
		return Index;
	}

	FORCEINLINE void SetIndex(const int32& InIndex)
	{
		Index = InIndex;
	}

	void Reset()
	{
		Name = nullptr;
		Owner.Reset();
		Owner = nullptr;
		Task = nullptr;
		Handle = FCsRunnableHandle::Invalid;
	}

	UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	
	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }
};