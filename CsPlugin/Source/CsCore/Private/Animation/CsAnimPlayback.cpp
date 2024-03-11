// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsAnimPlayback.h"

// AnimPlayback
#pragma region

namespace NCsAnimPlayback
{
	namespace Ref
	{
		typedef EMCsAnimPlayback EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Forward);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Reverse);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PingPong, "Ping Pong");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Loop);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopReverse, "Loop Reverse");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopPingPong, "Loop Ping Pong");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnimPlayback_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAnimPlayback_MAX;
}

namespace NCsAnim
{
	namespace NPlayback
	{
		namespace Ref
		{
			typedef EMPlayback EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Forward);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Reverse);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PingPong, "Ping Pong");
			CSCORE_API CS_ADD_TO_ENUM_MAP(Loop);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopReverse, "Loop Reverse");
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopPingPong, "Loop Ping Pong");
			CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPlayback_MAX, "MAX");
		}

		CSCORE_API const uint8 MAX = (uint8)Type::EPlayback_MAX;
	}
}

#pragma endregion AnimPlayback