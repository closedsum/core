// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_StatusEffect.h"

#include "CsData_Projectile_OnHit_StatusEffect.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NOnHit
		{
			namespace NStatusEffect
			{
				/**
				*
				*/
				struct CSSE_API IStatusEffect : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IStatusEffect() {}

					virtual const TArray<FECsStatusEffect>& GetStatusEffectsOnHit() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSSE_API UCsData_Projectile_OnHit_StatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSSE_API ICsData_Projectile_OnHit_StatusEffect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual const TArray<FECsStatusEffect>& GetStatusEffectsOnHit() const = 0;
};