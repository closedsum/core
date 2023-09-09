// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstPerson, "1st Person");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ThirdPerson, "3rd Person");
		CSCORE_API CS_ADD_TO_ENUM_MAP(VR);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsViewType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)ECsViewType::ECsViewType_MAX;
}

#pragma endregion ViewType

#pragma endregion View