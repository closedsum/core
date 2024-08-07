// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Platform.generated.h"

// Platform
#pragma region

UENUM(BlueprintType)
enum class ECsPlatform : uint8
{
	Windows			UMETA(DisplayName = "Windows"),
	IOS				UMETA(DisplayName = "IOS"),
	Android			UMETA(DisplayName = "Android"),
	Xbox			UMETA(DisplayName = "Xbox"),
	PlayStation		UMETA(DisplayName = "PlayStation"),
	ECsPlatform_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsPlatform : public TCsEnumMap<ECsPlatform>
{
	CS_ENUM_MAP_BODY(EMCsPlatform, ECsPlatform)
};

namespace NCsPlatform
{
	typedef ECsPlatform Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Windows;
		extern CSTYPES_API const Type IOS;
		extern CSTYPES_API const Type Android;
		extern CSTYPES_API const Type Xbox;
		extern CSTYPES_API const Type PlayStation;
		extern CSTYPES_API const Type ECsPlatform_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

#pragma endregion Platform