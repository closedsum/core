// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_View.h"

// View
#pragma region

	// ViewType
#pragma region

namespace NCsViewType
{
	namespace Ref
	{
		typedef EMCsViewType EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstPerson, "1st Person");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ThirdPerson, "3rd Person");
		CSTYPES_API CS_ADD_TO_ENUM_MAP(VR);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsViewType_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)ECsViewType::ECsViewType_MAX;
}

#pragma endregion ViewType

#pragma endregion View