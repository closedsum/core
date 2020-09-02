// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
#pragma once

/**
* Basic implementation of the interface: ICsDamageValue
*/
struct CSCORE_API FCsDamageValuePointImpl : public ICsDamageValue,
											public ICsDamageValuePoint,
											public ICsReset
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap InterfaceMap;

public:

	// ICsDamageValuePoint

	float Value;

public:

	FCsDamageValuePointImpl();

	FCsDamageValuePointImpl(const FCsDamageValuePointImpl&) = delete;
	FCsDamageValuePointImpl& operator = (const FCsDamageValuePointImpl&) = delete;

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return const_cast<FCsInterfaceMap*>(&InterfaceMap);
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageValue
#pragma region
public:

#pragma endregion ICsDamageValue

// ICsDamageValuePoint
#pragma region
public:

	FORCEINLINE const float& GetValue() const
	{
		return Value;
	}

#pragma endregion ICsDamageValuePoint

// ICsReset
#pragma region
public:

	void Reset();

#pragma endregion ICsReset
};