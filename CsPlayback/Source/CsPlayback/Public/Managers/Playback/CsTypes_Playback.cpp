// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Playback/CsTypes_Playback.h"
#include "CsPlayback.h"

// PlaybackEventRepeatedState
#pragma region

namespace NCsPlaybackEventRepeatedState
{
	namespace Ref
	{
		typedef EMCsPlaybackEventRepeatedState EnumMapType;

		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(None);
		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(Start);
		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP(End);
		CSPLAYBACK_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPlaybackEventRepeatedState_MAX, "MAX");
	}
}

#pragma endregion PlaybackEventRepeatedState

const FCsPlaybackByEvent FCsPlaybackByEvent::Invalid;