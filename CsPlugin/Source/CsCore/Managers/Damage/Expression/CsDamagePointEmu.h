// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpression.h"
#pragma once

struct FCsInterfaceMap;
struct ICsDamageValue;

/**
*
*/
struct CSCORE_API FCsDamagePointEmu : public ICsDamageExpression
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsDamageExpression

	ICsDamageValue* Value;

	FECsDamageType* Type;

public:

	FCsDamagePointEmu();
	~FCsDamagePointEmu();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsDamageExpression
#pragma region
public:

	FORCEINLINE const ICsDamageValue* GetValue() const
	{
		return Value;
	}

	FORCEINLINE const FECsDamageType& GetType() const
	{
		return const_cast<FECsDamageType&>(*Type);
	}

#pragma endregion ICsDamageExpression

public:

	void SetValue(float* InValue);

	void SetType(FECsDamageType* InValue)
	{
		Type = InValue;
	}
};