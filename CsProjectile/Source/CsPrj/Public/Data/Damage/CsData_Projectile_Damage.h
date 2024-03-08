// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

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

			#define DamageDataType NCsDamage::NData::IData

			public:

				virtual ~IDamage() {}

				virtual DamageDataType* GetDamageData() const = 0;

			#undef DamageDataType
			};
		}
	}
}

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

#define DamageDataType NCsDamage::NData::IData

public:

	virtual DamageDataType* GetDamageData() const = 0;

#undef DamageDataType
};