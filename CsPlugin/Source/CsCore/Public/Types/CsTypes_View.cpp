// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"

// View
#pragma region

	// ViewType
#pragma region

namespace NCsViewType
{
	typedef ECsViewType Type;

	CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsViewType, FirstPerson, "1st Person");
	CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsViewType, ThirdPerson, "3rd Person");
	CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsViewType, VR);
	CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsViewType, ECsViewType_MAX, "MAX");

	CSCORE_API const uint8 MAX = (uint8)ECsViewType::ECsViewType_MAX;
}

#pragma endregion ViewType

#pragma endregion View