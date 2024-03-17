// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Macro/CsMacro_Namespace.h"

#include "CsGetDamageModifiers.generated.h"

UINTERFACE(Blueprintable)
class CSDMG_API UCsGetDamageModifiers : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

class CSDMG_API ICsGetDamageModifiers
{
	GENERATED_IINTERFACE_BODY()

#define DmgModifierType NCsDamage::NModifier::IModifier

public:

	virtual void GetDamageModifiers(TArray<DmgModifierType*>& OutModifiers) const = 0;

#undef DmgModifierType
};