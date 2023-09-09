// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsData_TraceDamage.generated.h"

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsTrace
{
	namespace NData
	{
		namespace NDamage
		{
			struct CSCORE_API IDamage : public ICsGetInterfaceMap
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
class CSCORE_API UCsData_TraceDamage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

/**
*
*/
class CSCORE_API ICsData_TraceDamage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define DamageDataType NCsDamage::NData::IData

public:

	virtual DamageDataType* GetDamageData() const = 0;

#undef DamageDataType
};