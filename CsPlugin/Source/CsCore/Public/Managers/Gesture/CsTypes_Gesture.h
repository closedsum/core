// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Gesture.generated.h"


// GestureDevice
#pragma region

UENUM(BlueprintType)
enum class ECsGestureDevice : uint8
{
	Mouse					UMETA(DisplayName = "Mouse"),
	MotionController		UMETA(DisplayName = "MotionController"),
	ECsGestureDevice_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsGestureDevice : public TCsEnumMap<ECsGestureDevice>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsGestureDevice, ECsGestureDevice)
};

namespace NCsGestureDevice
{
	typedef ECsGestureDevice Type;

	namespace Ref
	{
		extern CSCORE_API const Type Mouse;
		extern CSCORE_API const Type MotionController;
		extern CSCORE_API const Type ECsGestureDevice_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion GestureDevice

// GestureType
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsGestureType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsGestureType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsGestureType)

struct CSCORE_API EMCsGestureType : public TCsEnumStructMap<FECsGestureType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsGestureType, FECsGestureType, uint8)
};

#pragma endregion GestureType