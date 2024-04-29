// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

#include "CsData_StatusEffect_Damage.generated.h"

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NDamage
		{
			/**
			* Interface for describing a Status Effect for Damage Value or Damage Range.
			*  Damage Value is an object that implements the interface: NCsDamage::NValue::IValue.
			*  Damage Range is an object that implements the interface: NCsDamage::NRange::IRange.
			*/
			struct CSSE_API IDamage : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define DmgModifierType NCsDamage::NModifier::IModifier

			public:

				virtual ~IDamage(){}

				virtual const TArray<FECsDamageData>& GetDamageDataTypes() const = 0;

				virtual const TArray<DmgModifierType*>& GetDamageModifiers() const  = 0;

			#undef DmgModifierType
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect_Damage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

/**
* Interface for describing a Status Effect for Damage Value or Damage Range.
*  Damage Value is an object that implements the interface: NCsDamage::NValue::IValue.
*  Damage Range is an object that implements the interface: NCsDamage::NRange::IRange.
*/
class CSSE_API ICsData_StatusEffect_Damage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define DmgModifierType NCsDamage::NModifier::IModifier

public:

	virtual const TArray<FECsDamageData>& GetDamageDataTypes() const = 0;

	virtual const TArray<DmgModifierType*>& GetDamageModifiers() const = 0;

#undef DmgModifierType
};