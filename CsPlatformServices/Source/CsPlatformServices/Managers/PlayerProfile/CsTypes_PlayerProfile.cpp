// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"

#pragma once

// PlayerProfile
#pragma region

namespace NCsPlayerProfile
{
	namespace Ref
	{
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile1);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile2);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile3);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile4);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile5);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile6);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile7);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(EMCsPlayerProfile, Profile8);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsPlayerProfile, ECsPlayerProfile_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsPlayerProfile_MAX;

	CSPLATFORMSERVICES_API const Type AllProfiles = Type::ECsPlayerProfile_MAX;
}

#pragma endregion PlayerProfile