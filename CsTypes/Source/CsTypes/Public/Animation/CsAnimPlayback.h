// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsAnimPlayback.generated.h"

// AnimPlayback
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsAnimPlayback : uint8
{
	Forward				UMETA(DisplayName = "Forward"),
	Reverse				UMETA(DisplayName = "Reverse"),
	PingPong			UMETA(DisplayName = "Ping Pong"),
	Loop				UMETA(DisplayName = "Loop"),
	LoopReverse			UMETA(DisplayName = "Loop Reverse"),
	LoopPingPong		UMETA(DisplayName = "Loop Ping Pong"),
	Custom				UMETA(DisplayName = "Custom"),
	ECsAnimPlayback_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsAnimPlayback : public TCsEnumMap<ECsAnimPlayback>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAnimPlayback, ECsAnimPlayback)
};

namespace NCsAnimPlayback
{
	typedef ECsAnimPlayback Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Forward;
		extern CSTYPES_API const Type Reverse;
		extern CSTYPES_API const Type PingPong;
		extern CSTYPES_API const Type Loop;
		extern CSTYPES_API const Type LoopReverse;
		extern CSTYPES_API const Type LoopPingPong;
		extern CSTYPES_API const Type Custom;
		extern CSTYPES_API const Type ECsAnimPlayback_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsAnim
{
	/**
	*/
	enum class EPlayback : uint8
	{
		Forward,
		Reverse,
		PingPong,
		Loop,
		LoopReverse,
		LoopPingPong,
		Custom,
		EPlayback_MAX
	};

	struct CSTYPES_API EMPlayback : public TCsEnumMap<EPlayback>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPlayback, EPlayback)
	};

	namespace NPlayback
	{
		typedef EPlayback Type;

		namespace Ref
		{
			extern CSTYPES_API const Type Forward;
			extern CSTYPES_API const Type Reverse;
			extern CSTYPES_API const Type PingPong;
			extern CSTYPES_API const Type Loop;
			extern CSTYPES_API const Type LoopReverse;
			extern CSTYPES_API const Type LoopPingPong;
			extern CSTYPES_API const Type Custom;
			extern CSTYPES_API const Type EPlayback_MAX;
		}

		extern CSTYPES_API const uint8 MAX;
	}
}

#pragma endregion AnimPlayback