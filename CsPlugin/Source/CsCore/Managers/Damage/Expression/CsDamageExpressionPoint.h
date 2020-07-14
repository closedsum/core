// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Expression/CsDamageExpression.h"
#include "Containers/CsInterfaceMap.h"
#pragma once

struct ICsDamagePhysics;

/**
*
*/
struct CSCORE_API FCsDamageExpressionPoint : public ICsDamageExpression
{
public:

	static const FName Name;

private:

	FCsInterfaceMap InterfaceMap;

public:

	float* Damage;

	FECsDamageType* Type;

public:

	FCsDamageExpressionPoint();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return const_cast<FCsInterfaceMap*>(&InterfaceMap);
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