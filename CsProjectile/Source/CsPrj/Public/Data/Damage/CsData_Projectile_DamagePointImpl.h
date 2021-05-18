// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"
// Data
#include "Data/Damage/CsData_ProjectileDamage.h"

#include "CsData_Projectile_DamagePointImpl.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_Projectile_DamagePointImpl
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsData_DamagePoint Damage;

public:

	FCsData_Projectile_DamagePointImpl() :
		Damage()
	{
	}
};
/*
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsProjectile
{
	namespace NData
	{
		namespace NDamage
		{
			namespace NPoint
			{
			#define PrjDamageDataType NCsProjectile::NDamage::NDamage::IDamage

				struct CSPRJ_API FImpl : public PrjDamageDataType
				{
				#define DamageDataType NCsDamage::NData::IData

				private:

					DamageDataType* DamageData;

				public:

					FImpl()
					{
					}

				#undef DamageDataType
				};

			#undef PrjDamageDataType
			}
		}
	}
}
*/