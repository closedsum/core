// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_ProjectileStatusEffect.generated.h"

// NCsStatusEffect::NData::IData
namespace NCsStatusEffect {
	namespace NData {
		struct IData; } }

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

				virtual const TArray<StatusEffectDataType*>& GetStatusEffects() const = 0;
			};

#undef StatusEffectDataType
		}
	}
}

UINTERFACE(BlueprintType)
class CSSE_API UCsData_ProjectileStatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_StatusEffect;

/**
*
*/
class CSSE_API ICsData_ProjectileStatusEffect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual const TArray<ICsData_StatusEffect*>& GetStatusEffects() const = 0;
};