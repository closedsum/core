// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Weapon_Skin.h"

#include "CsData_Weapon_GetDefaultSkinType.generated.h"

namespace NCsWeapon
{
	namespace NData
	{
		/**
		*
		*/
		struct CSWP_API IGetDefaultSkinType : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IGetDefaultSkinType() {}

			/**
			*/
			virtual const FECsWeaponSkin& GetDefaultSkinType() const = 0;
		};
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_Weapon_GetDefaultSkinType : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSWP_API ICsData_Weapon_GetDefaultSkinType : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual const FECsWeaponSkin& GetDefaultSkinType() const = 0;
};