// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsAnimPlayRate.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsAnimPlayRate)

// AnimPlayRate
#pragma region

namespace NCsAnimPlayRate
{
	namespace Ref
	{
		typedef EMCsAnimPlayRate EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_001, "0.001s");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_01, "0.01s");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_1, "0.1s");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_1, "1s");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_10, "10s");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_100, "100s");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_15Fps, "15 fps");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_24Fps, "24 fps (film)");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_25Fps, "25 fps (PAL/25)");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_29_97Fps, "29.97 fps (NTSC/30)");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_30Fps, "30 fps");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_48Fps, "48 fps");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_50Fps, "50 fps (PAL/50)");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_59_94Fps, "59.94 fps (NTSC/60)");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_60Fps, "60 fps");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_120Fps, "120 fps");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTime, "Custom Delta Time");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomTotalTime, "Custom Total Time");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTimeAndTotalTime, "Custom Delta Time and Total Time");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTimePerFrame, "Custom Delta Time per Frame");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_Custom, "Custom");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnimPlayRate_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsAnimPlayRate_MAX;
}

namespace NCsAnim
{
	namespace NPlayRate
	{
		namespace Ref
		{
			typedef EMPlayRate EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_001, "0.001s");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_01, "0.01s");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_1, "0.1s");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_1, "1s");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_10, "10s");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_100, "100s");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_15Fps, "15 fps");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_24Fps, "24 fps (film)");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_25Fps, "25 fps (PAL/25)");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_29_97Fps, "29.97 fps (NTSC/30)");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_30Fps, "30 fps");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_48Fps, "48 fps");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_50Fps, "50 fps (PAL/50)");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_59_94Fps, "59.94 fps (NTSC/60)");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_60Fps, "60 fps");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_120Fps, "120 fps");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTime, "Custom Delta Time");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomTotalTime, "Custom Total Time");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTimeAndTotalTime, "Custom Delta Time and Total Time");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTimePerFrame, "Custom Delta Time per Frame");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_Custom, "Custom");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPlayRate_MAX, "MAX");
		}

		CSTYPES_API const uint8 MAX = (uint8)Type::EPlayRate_MAX;

		float GetDeltaTime(const EPlayRate& PlayRate)
		{
			if (PlayRate == EPlayRate::PR_0_001){ return 0.001f; }
			if (PlayRate == EPlayRate::PR_0_01){ return 0.01f; }
			if (PlayRate == EPlayRate::PR_0_1){ return 0.1f; }
			if (PlayRate == EPlayRate::PR_1){ return 1.0f; }
			if (PlayRate == EPlayRate::PR_10){ return 10.0f; }
			if (PlayRate == EPlayRate::PR_100){ return 100.0f; }
			if (PlayRate == EPlayRate::PR_15Fps){ return 0.066667f; }
			if (PlayRate == EPlayRate::PR_24Fps){ return 0.041667f; }
			if (PlayRate == EPlayRate::PR_25Fps){ return 0.04f; }
			if (PlayRate == EPlayRate::PR_29_97Fps){ return 0.0333667f; }
			if (PlayRate == EPlayRate::PR_30Fps){ return 0.033333f; }
			if (PlayRate == EPlayRate::PR_48Fps){ return 0.020833f; }
			if (PlayRate == EPlayRate::PR_50Fps){ return 0.02f; }
			if (PlayRate == EPlayRate::PR_59_94Fps){ return 0.01668335f; }
			if (PlayRate == EPlayRate::PR_60Fps){ return 0.0166667f; }
			if (PlayRate == EPlayRate::PR_120Fps){ return 0.008333f; }
			return 0.0f;
		}
	}
}

#pragma endregion AnimPlayRate