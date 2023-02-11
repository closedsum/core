// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Math.h"

#include "CsData_DamageCone.generated.h"

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NCone
			{
				/**
				* Interface to describe the Cone shape of Damage. 
				* This should be used with the interface "base" NCsDamage::NData::IData.
				*/
				struct CSDMG_API ICone : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ICone(){}

				#define DotDimensionType NCsDot::EDimension

					virtual const DotDimensionType& GetDotDimension() const = 0;
					
					virtual const float& GetMinDot() const = 0;

				#undef DotDimensionType
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_DamageCone : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the Cone shape of Damage.
* This should be used with the interface "base" NCsDamage::NData::IData.
*/
class CSDMG_API ICsData_DamageCone : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define DotDimensionType NCsDot::EDimension

	virtual const DotDimensionType& GetDotDimension() const = 0;

	virtual const float& GetMinDot() const = 0;

#undef DotDimensionType
};