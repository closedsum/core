// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;

template<typename ObjectType>
struct TCsWeakObjectPtr
{
	static_assert(std::is_base_of<UObject, ObjectType>(), "TCsWeakObjectPtr: ObjectType does not extend from UObject.");

private:

	ObjectType* Object;

	TWeakObjectPtr<ObjectType> WeakObject;

public:

	TCsWeakObjectPtr() :
		Object(nullptr),
		WeakObject(nullptr)
	{
	}

	FORCEINLINE TCsWeakObjectPtr<ObjectType>& operator=(ObjectType* InObject)
	{
		Object = InObject;
		WeakObject = InObject;
		return *this;
	}

	FORCEINLINE void Set(ObjectType* InObject)
	{
		Object = InObject;
		WeakObject = InObject;
	}

	FORCEINLINE ObjectType* Get() const
	{
		return Object;
	}

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE ObjectType* GetSafe() const
	{
		return WeakObject.IsValid() ? WeakObject.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* GetSafe() const
	{
		return Cast<T>(GetSafe());
	}

	void Reset()
	{
		Object = nullptr;
		WeakObject = nullptr;
	}
};