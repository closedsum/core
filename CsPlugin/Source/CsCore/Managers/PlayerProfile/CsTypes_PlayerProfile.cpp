// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"

#pragma once

// PlayerProfile
#pragma region

namespace NCsPlayerProfile
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile1);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile2);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile3);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile4);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile5);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile6);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile7);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile8);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPlayerProfile, ECsPlayerProfile_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPlayerProfile_MAX;
}

#pragma endregion PlayerProfile