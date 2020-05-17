// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_PlayerProfile.generated.h"
#pragma once

// PlayerProfile
#pragma region

UENUM(BlueprintType)
enum class ECsPlayerProfile : uint8
{
	Profile1				UMETA(DisplayName = "Profile 1"),
	Profile2				UMETA(DisplayName = "Profile 2"),
	Profile3				UMETA(DisplayName = "Profile 3"),
	Profile4				UMETA(DisplayName = "Profile 4"),
	Profile5				UMETA(DisplayName = "Profile 5"),
	Profile6				UMETA(DisplayName = "Profile 6"),
	Profile7				UMETA(DisplayName = "Profile 7"),
	Profile8				UMETA(DisplayName = "Profile 8"),
	ECsPlayerProfile_MAX	UMETA(Hidden),
};

struct CSPLATFORMSERVICES_API EMCsPlayerProfile final : public TCsEnumMap<ECsPlayerProfile>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPlayerProfile, ECsPlayerProfile)
};

namespace NCsPlayerProfile
{
	typedef ECsPlayerProfile Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type Profile1;
		extern CSPLATFORMSERVICES_API const Type Profile2;
		extern CSPLATFORMSERVICES_API const Type Profile3;
		extern CSPLATFORMSERVICES_API const Type Profile4;
		extern CSPLATFORMSERVICES_API const Type Profile5;
		extern CSPLATFORMSERVICES_API const Type Profile6;
		extern CSPLATFORMSERVICES_API const Type Profile7;
		extern CSPLATFORMSERVICES_API const Type Profile8;
		extern CSPLATFORMSERVICES_API const Type ECsPlayerProfile_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;

	extern CSPLATFORMSERVICES_API const Type AllProfiles;
}

#pragma endregion PlayerProfile