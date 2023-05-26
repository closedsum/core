// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_Weapon_Skin.generated.h"

namespace NCsWeapon
{
	namespace NData
	{
		namespace NSkin
		{
			/**
			*
			*/
			struct CSWP_API ISkin : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ISkin(){}
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_Weapon_Skin : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_Weapon_Skin : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;
};