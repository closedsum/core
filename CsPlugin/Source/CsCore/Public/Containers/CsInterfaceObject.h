// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;

/**
* Container holding a pointer to an object that implements (natively or through script) InterfaceType.
*/
template<typename InterfaceType>
struct TCsInterfaceObject
{
protected:

	FName Name;

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
		Name(NAME_None),
		Interface(nullptr),
		WeakObject(nullptr),
		Object(nullptr),
		Class(nullptr),
		bObject(false),
		bScript(false)
	{
	}


	virtual ~TCsInterfaceObject() {}

	FORCEINLINE const FName& GetName() const { return Name; }

	FORCEINLINE InterfaceType* GetInterface() const
	{
		return Interface;
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

	FORCEINLINE UObject* GetObjectChecked(const FString& Context) const
	{
		checkf(Object, TEXT("%s: Object is NULL."), *Context);
		return Object;
	}

	template<typename T>
	FORCEINLINE T* GetObjectChecked(const FString& Context) const
	{
		checkf(Object, TEXT("%s: Object is NULL."), *Context);

		T* O = Cast<T>(Object);

		checkf(O, TEXT("%s: Failed to Cast Object: %s with Class: %s to type: %s."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()), *(T::StaticClass()->GetName()));
		return O;
	}

	virtual void SetObject(UObject* InObject)
	{
		Object	   = InObject;
		WeakObject = Object;
		Class	   = Object ? Object->GetClass() : nullptr;
		bObject	   = Object != nullptr;
		Name	   = Object ? Object->GetFName() : NAME_None;
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

	FORCEINLINE bool IsValidObject() const
	{
		return WeakObject.IsValid() && WeakObject.Get() == Object && Object != nullptr;
	}

	virtual void Reset()
	{
		Name = NAME_None;
		Interface = nullptr;
		WeakObject = nullptr;
		Object = nullptr;
		bObject = false;
		bScript = false;
	}
};