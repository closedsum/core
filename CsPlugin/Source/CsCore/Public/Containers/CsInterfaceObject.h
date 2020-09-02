// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

/**
* Container holding a pointer to an object that implements (natively or through script) InterfaceType.
*/
template<typename InterfaceType>
struct TCsInterfaceObject
{
protected:

	/** Pointer to InterfaceType. */
	InterfaceType* Interface;

	/** Weak pointer to UObject. */
	TWeakObjectPtr<UObject> WeakObject;

	/** Pointer to UObject. */
	UObject* Object;

	/** Pointer to UClass. */
	UClass* Class;

	/** Whether the container holds a UObject. */
	bool bObject;

	/** Whether the container holds a "script" object. 
	    A script object is usually a UObject that does NOT 
		directly implement InterfaceType. */
	bool bScript;

public:

	TCsInterfaceObject() :
		Interface(nullptr),
		WeakObject(nullptr),
		Object(nullptr),
		Class(nullptr),
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
		Class	   = Object ? Object->GetClass() : nullptr;
		bObject	   = Object != nullptr;
	}

	FORCEINLINE const bool& IsObject() const
	{
		return bObject;
	}

	FORCEINLINE UClass* GetClass() const
	{
		return Class;
	}

	FORCEINLINE UClass* GetClassChecked(const FString& Context) const
	{
		checkf(Class, TEXT("%s: Class is NULL."));

		return Class;
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