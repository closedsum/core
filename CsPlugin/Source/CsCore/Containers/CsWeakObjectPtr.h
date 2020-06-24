// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

	FORCEINLINE ObjectType* GetSafe() const
	{
		return WeakObject.IsValid() ? WeakObject.Get() : nullptr;
	}

	void Reset()
	{
		Object = nullptr;
		WeakObject = nullptr;
	}
};