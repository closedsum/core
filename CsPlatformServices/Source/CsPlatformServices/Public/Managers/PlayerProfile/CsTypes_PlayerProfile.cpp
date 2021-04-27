// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"

#pragma once

// PlayerProfile
#pragma region

namespace NCsPlayerProfile
{
	namespace Ref
	{
		typedef EMCsPlayerProfile EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Common);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile1);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile2);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile3);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile4);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile5);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile6);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile7);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Profile8);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPlayerProfile_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsPlayerProfile_MAX;

	CSPLATFORMSERVICES_API const Type AllProfiles = Type::ECsPlayerProfile_MAX;
}

#pragma endregion PlayerProfile