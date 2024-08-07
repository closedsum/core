// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_PlayerProfile)

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