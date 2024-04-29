// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

#include "CsData_TraceDamage.generated.h"

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsTrace
{
	namespace NData
	{
		namespace NDamage
		{
			struct CSPHYSICS_API IDamage : public ICsGetInterfaceMap
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
class CSPHYSICS_API UCsData_TraceDamage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

/**
*
*/
class CSPHYSICS_API ICsData_TraceDamage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define DamageDataType NCsDamage::NData::IData

public:

	virtual DamageDataType* GetDamageData() const = 0;

#undef DamageDataType
};