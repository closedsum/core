// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#pragma once

struct FCsInterfaceMap;

namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

/**
*
*/
struct CSCORE_API FCsData_DamagePointEmu : public ICsData_Damage
{
public:

	static const FName Name;

private:

	// ICsGetInterfaceMap

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsData_Damage

	NCsDamage::NValue::IValue* Value;

	FECsDamageType* Type;

public:

	FCsData_DamagePointEmu();
	~FCsData_DamagePointEmu();

	FORCEINLINE UObject* _getUObject() const { return nullptr; }

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsData_Damage
#pragma region
public:

	FORCEINLINE const NCsDamage::NValue::IValue* GetValue() const
	{
		return Value;
	}

	FORCEINLINE const FECsDamageType& GetType() const
	{
		return const_cast<FECsDamageType&>(*Type);
	}

#pragma endregion ICsData_Damage

public:

	void SetValue(float* InValue);

	void SetType(FECsDamageType* InValue)
	{
		Type = InValue;
	}
};