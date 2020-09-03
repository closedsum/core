// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

struct CSUI_API FCsPayload_UserWidgetImpl final : public ICsPayload_PooledObject,
												  public ICsPayload_UserWidget
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

	bool bAllocated;

public:

	// ICsPayload_PooledObject

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;
	
	FCsTime Time;

	// ICsPayload_UserWidget

	ESlateVisibility Visibility;

public:

	FCsPayload_UserWidgetImpl();
	~FCsPayload_UserWidgetImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsPayload_PooledObject
#pragma region
public:

	FORCEINLINE const bool& IsAllocated() const
	{
		return bAllocated;
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		return Instigator;
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Owner;
	}

	FORCEINLINE UObject* GetParent() const
	{
		return Parent;
	}

	FORCEINLINE const FCsTime& GetTime() const
	{
		return Time;
	}

	FORCEINLINE void Allocate()
	{
		bAllocated = true;
	}

	void Reset();

#pragma endregion ICsPayload_PooledObject

public:

	template<typename T>
	FORCEINLINE T* GetInstigator() const
	{
		return Cast<T>(GetInstigator());
	}

	template<typename T>
	FORCEINLINE T* GetOwner() const
	{
		return Cast<T>(GetOwner());
	}

	template<typename T>
	FORCEINLINE T* GetParent() const
	{
		return Cast<T>(GetParent());
	}

// ICsPayload_UserWidget
#pragma region
public:

	FORCEINLINE const ESlateVisibility& GetVisibility() const
	{
		return Visibility;
	}

#pragma endregion ICsPayload_UserWidget
};