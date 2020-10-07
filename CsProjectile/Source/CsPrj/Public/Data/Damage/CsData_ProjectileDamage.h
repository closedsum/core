// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_ProjectileDamage.generated.h"

// NCsDamage::NData::IData
namespace NCsDamage {
	namespace NData {
		struct IData; } }

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

				typedef NCsDamage::NData::IData DamageDataType;

			public:

				virtual DamageDataType* GetDamageData() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_ProjectileDamage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NData::IData
namespace NCsDamage {
	namespace NData {
		struct IData; } }

/**
*
*/
class CSPRJ_API ICsData_ProjectileDamage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	typedef NCsDamage::NData::IData DamageDataType;

public:

	virtual DamageDataType* GetDamageData() const = 0;
};