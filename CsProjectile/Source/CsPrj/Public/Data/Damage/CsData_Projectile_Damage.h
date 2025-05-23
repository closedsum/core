// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

#include "CsData_Projectile_Damage.generated.h"

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsProjectile
{
	namespace NData
	{
		namespace NDamage
		{
			struct CSPRJ_API IDamage : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using DamageDataType = NCsDamage::NData::IData;
				};

			public:

				virtual ~IDamage() {}

				virtual _::DamageDataType* GetDamageData() const = 0;
			};
		}
	}
}

using CsProjectileDamageDataType = NCsProjectile::NData::NDamage::IDamage;
using CsPrjDamageDataType = NCsProjectile::NData::NDamage::IDamage;

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_Damage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

/**
*
*/
class CSPRJ_API ICsData_Projectile_Damage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using DamageDataType = NCsDamage::NData::IData;
	};

public:

	virtual _::DamageDataType* GetDamageData() const = 0;
};