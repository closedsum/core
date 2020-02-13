// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

template<typename InterfaceType>
struct TCsInterfaceObject
{
protected:

	InterfaceType* Interface;
	TWeakObjectPtr<UObject> WeakObject;
	UObject* Object;

	bool bObject;
	bool bScript;

public:

	TCsInterfaceObject() :
		Interface(nullptr),
		WeakObject(nullptr),
		Object(nullptr),
		bObject(false),
		bScript(false)
	{
	}


	virtual ~TCsInterfaceObject() {}

	FORCEINLINE InterfaceType* GetInterface() const
	{
		return Interface;
	}

	template<typename InterfaceChildType>
	FORCEINLINE InterfaceChildType* GetInterface() const
	{
		static_assert(std::is_base_of<InterfaceType, InterfaceChildType>(), TEXT("TCsInterfaceObject::GetInterface: InterfaceChildType does NOT implement interface: InterfaceType."));

		return (InterfaceChildType*)Interface;
	}

	virtual void SetInterface(InterfaceType* InInterface)
	{
		Interface = InInterface;
	}

	FORCEINLINE UObject* GetSafeObject() const
	{
		return WeakObject.IsValid() ? WeakObject.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* GetSafeObject() const
	{
		return Cast<T>(GetSafeObject());
	}

	FORCEINLINE UObject* GetObject() const
	{
		return Object;
	}

	template<typename T>
	FORCEINLINE T* GetObject() const
	{
		return Cast<T>(GetObject());
	}

	virtual void SetObject(UObject* InObject)
	{
		Object	   = InObject;
		WeakObject = Object;
		bObject	   = Object != nullptr;
	}

	FORCEINLINE const bool& IsObject() const
	{
		return bObject;
	}

	void SetScript()
	{
		bScript = true;
	}

	FORCEINLINE const bool& IsScript() const
	{
		return bScript;
	}

	FORCEINLINE bool IsValid() const
	{
		return Interface != nullptr || (bScript && Object != nullptr);
	}

	virtual void Reset()
	{
		Interface = nullptr;
		WeakObject = nullptr;
		Object = nullptr;
		bObject = false;
		bScript = false;
	}
};