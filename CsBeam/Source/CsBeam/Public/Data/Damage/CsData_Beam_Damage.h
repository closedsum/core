// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsData_Beam_Damage.generated.h"

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsBeam
{
	namespace NData
	{
		namespace NDamage
		{
			struct CSBEAM_API IDamage : public ICsGetInterfaceMap
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
class CSBEAM_API UCsData_Beam_Damage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

/**
*
*/
class CSBEAM_API ICsData_Beam_Damage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

#define DamageDataType NCsDamage::NData::IData

public:

	virtual DamageDataType* GetDamageData() const = 0;

#undef DamageDataType
};