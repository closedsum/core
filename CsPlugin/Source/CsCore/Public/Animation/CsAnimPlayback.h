// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsAnimPlayback.generated.h"
#pragma once

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

struct CSCORE_API EMCsAnimPlayback : public TCsEnumMap<ECsAnimPlayback>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAnimPlayback, ECsAnimPlayback)
};

namespace NCsAnimPlayback
{
	typedef ECsAnimPlayback Type;

	namespace Ref
	{
		extern CSCORE_API const Type Forward;
		extern CSCORE_API const Type Reverse;
		extern CSCORE_API const Type PingPong;
		extern CSCORE_API const Type Loop;
		extern CSCORE_API const Type LoopReverse;
		extern CSCORE_API const Type LoopPingPong;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsAnimPlayback_MAX;
	}

	extern CSCORE_API const uint8 MAX;
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

	struct CSCORE_API EMPlayback : public TCsEnumMap<EPlayback>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPlayback, EPlayback)
	};

	namespace NPlayback
	{
		typedef EPlayback Type;

		namespace Ref
		{
			extern CSCORE_API const Type Forward;
			extern CSCORE_API const Type Reverse;
			extern CSCORE_API const Type PingPong;
			extern CSCORE_API const Type Loop;
			extern CSCORE_API const Type LoopReverse;
			extern CSCORE_API const Type LoopPingPong;
			extern CSCORE_API const Type Custom;
			extern CSCORE_API const Type EPlayback_MAX;
		}

		extern CSCORE_API const uint8 MAX;
	}
}

#pragma endregion AnimPlayback