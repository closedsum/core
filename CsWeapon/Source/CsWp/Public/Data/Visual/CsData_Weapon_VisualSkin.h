// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

#include "CsData_Weapon_VisualSkin.generated.h"

// SkinType (NCsSkin::NData::NVisual::IVisual)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkin, NData, NVisual, IVisual)

namespace NCsWeapon
{
	namespace NData
	{
		namespace NVisual
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

				private:

					// Allow clearer names without name collisions
					struct _
					{
						using SkinType = NCsSkin::NData::NVisual::IVisual;
					};

				public:

					virtual ~ISkin(){}

					/**
					*/
					virtual _::SkinType* GetSkin() const = 0;

				#undef SkinType
				};
			}
		}
	}
}

using CsWeaponSkinDataType = NCsWeapon::NData::NVisual::NSkin::ISkin;

UINTERFACE(BlueprintType)
class CSWP_API UCsData_Weapon_VisualSkin : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

// SkinType (NCsSkin::NData::NVisual::IVisual)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkin, NData, NVisual, IVisual)

/**
*
*/
class CSWP_API ICsData_Weapon_VisualSkin : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

private:

	// Allow clearer names without name collisions
	struct _
	{
		using SkinType = NCsSkin::NData::NVisual::IVisual;
	};

public:

	/**
	*/
	virtual _::SkinType* GetSkin() const = 0;
};