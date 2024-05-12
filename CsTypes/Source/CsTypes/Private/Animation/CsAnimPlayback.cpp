// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsAnimPlayback.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsAnimPlayback)

// AnimPlayback
#pragma region

namespace NCsAnimPlayback
{
	namespace Ref
	{
		typedef EMCsAnimPlayback EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Forward);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Reverse);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PingPong, "Ping Pong");
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Loop);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopReverse, "Loop Reverse");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopPingPong, "Loop Ping Pong");
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Custom);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnimPlayback_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsAnimPlayback_MAX;
}

namespace NCsAnim
{
	namespace NPlayback
	{
		namespace Ref
		{
			typedef EMPlayback EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(Forward);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Reverse);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PingPong, "Ping Pong");
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Loop);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopReverse, "Loop Reverse");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopPingPong, "Loop Ping Pong");
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Custom);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPlayback_MAX, "MAX");
		}

		CSTYPES_API const uint8 MAX = (uint8)Type::EPlayback_MAX;
	}
}

#pragma endregion AnimPlayback