// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsData_Projectile_StatusEffect.generated.h"

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

namespace NCsProjectile
{
	namespace NData
	{
		namespace NStatusEffect
		{
		#define StatusEffectDataType NCsStatusEffect::NData::IData

			/**
			*
			*/
			struct CSSE_API IStatusEffect : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IStatusEffect() {}

				virtual const TArray<StatusEffectDataType*>& GetStatusEffects() const = 0;
			};

		#undef StatusEffectDataType
		}
	}
}

UINTERFACE(BlueprintType)
class CSSE_API UCsData_Projectile_StatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

/**
*
*/
class CSSE_API ICsData_Projectile_StatusEffect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define StatusEffectDataType NCsStatusEffect::NData::IData

public:

	virtual const TArray<StatusEffectDataType*>& GetStatusEffects() const = 0;

#undef StatusEffectDataType
};