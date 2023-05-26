// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Params/Start/CsTypes_PointWeapon_Start.h"

// Library
#include "Library/CsLibrary_Valid.h"

// PointWeaponStart
#pragma region

namespace NCsPointWeaponStart
{
	namespace Ref
	{
		typedef EMCsPointWeaponStart EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Destination);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponStart_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NStart
		{
			namespace Ref
			{
				typedef EMStart EnumMapType;

				CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
				CSWP_API CS_ADD_TO_ENUM_MAP(Destination);
				CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
				CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EStart_MAX, "MAX");
			}
		}
	}
}

#pragma endregion PointWeaponStart