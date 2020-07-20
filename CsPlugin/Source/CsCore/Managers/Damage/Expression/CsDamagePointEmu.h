// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpression.h"
#pragma once

/**
*
*/
struct CSCORE_API FCsDamagePointEmu : public ICsDamageExpression
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	float* Damage;

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

	FORCEINLINE float GetDamage() const
	{
		return const_cast<float&>(*Damage);
	}

	FORCEINLINE const FECsDamageType& GetType() const
	{
		return const_cast<FECsDamageType&>(*Type);
	}

#pragma endregion ICsDamageExpression

public:

	void SetDamage(float* Value)
	{
		Damage = Value;
	}

	void SetType(FECsDamageType* Value)
	{
		Type = Value;
	}
};