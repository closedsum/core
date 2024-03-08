// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_Weapon.generated.h"

namespace NCsWeapon
{
	namespace NData
	{
		struct CSWP_API IData : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IData(){}
		};
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_Weapon : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsData_Weapon : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};