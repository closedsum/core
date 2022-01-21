// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Platform.generated.h"
#pragma once

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

struct CSCORE_API EMCsPlatform : public TCsEnumMap<ECsPlatform>
{
	CS_ENUM_MAP_BODY(EMCsPlatform, ECsPlatform)
};

namespace NCsPlatform
{
	typedef ECsPlatform Type;

	namespace Ref
	{
		extern CSCORE_API const Type Windows;
		extern CSCORE_API const Type IOS;
		extern CSCORE_API const Type Android;
		extern CSCORE_API const Type Xbox;
		extern CSCORE_API const Type PlayStation;
		extern CSCORE_API const Type ECsPlatform_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion Platform