// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsAnimPlayRate.generated.h"
#pragma once

// AnimPlayRate
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsAnimPlayRate : uint8
{
	PR_0_001						UMETA(DisplayName = "0.001s"),
	PR_0_01							UMETA(DisplayName = "0.01s"),
	PR_0_1							UMETA(DisplayName = "0.1s"),
	PR_1							UMETA(DisplayName = "1s"),
	PR_10							UMETA(DisplayName = "10s"),
	PR_100							UMETA(DisplayName = "100s"),
	PR_15Fps						UMETA(DisplayName = "15 fps"),
	PR_24Fps						UMETA(DisplayName = "24 fps (film)"),
	PR_25Fps						UMETA(DisplayName = "25 fps (PAL/25)"),
	PR_29_97Fps						UMETA(DisplayName = "29.97 fps (NTSC/30)"),
	PR_30Fps						UMETA(DisplayName = "30 fps"),
	PR_48Fps						UMETA(DisplayName = "48 fps"),
	PR_50Fps						UMETA(DisplayName = "50 fps (PAL/50)"),
	PR_59_94Fps						UMETA(DisplayName = "59.94 fps (NTSC/60)"),
	PR_60Fps						UMETA(DisplayName = "60 fps"),
	PR_120Fps						UMETA(DisplayName = "120 fps"),
	/** DeltaTime and the number of frames are used to calculate the
		TotalTime and TotalCount. */
	PR_CustomDeltaTime				UMETA(DisplayName = "Custom Delta Time"),
	/** TotalTime and the number of frames are used to calculate the
		DeltaTime and TotalCount. */
	PR_CustomTotalTime				UMETA(DisplayName = "Custom Total Time"),
	/** TotalTime and DeltaTime are used to calculate the TotalCount. */
	PR_CustomDeltaTimeAndTotalTime	UMETA(DisplayName = "Custom Delta Time and Total Time"),
	/** Each frame has its own DeltaTime. TotalTime is the sum of each frame's DeltaTime. */
	PR_CustomDeltaTimePerFrame		UMETA(DisplayName = "Custom Delta Time per Frame"),
	/** DeltaTime, TotalTime, and TotalCount are determined by a custom
		implementation */
	PR_Custom						UMETA(DisplayName = "Custom"),
	ECsAnimPlayRate_MAX				UMETA(Hidden),
};

struct CSCORE_API EMCsAnimPlayRate : public TCsEnumMap<ECsAnimPlayRate>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAnimPlayRate, ECsAnimPlayRate)
};

namespace NCsAnimPlayRate
{
	typedef ECsAnimPlayRate Type;

	namespace Ref
	{
		extern CSCORE_API const Type PR_0_001;
		extern CSCORE_API const Type PR_0_01;
		extern CSCORE_API const Type PR_0_1;
		extern CSCORE_API const Type PR_1;
		extern CSCORE_API const Type PR_10;
		extern CSCORE_API const Type PR_100;
		extern CSCORE_API const Type PR_15Fps;
		extern CSCORE_API const Type PR_24Fps;
		extern CSCORE_API const Type PR_25Fps;
		extern CSCORE_API const Type PR_29_97Fps;
		extern CSCORE_API const Type PR_30Fps;
		extern CSCORE_API const Type PR_48Fps;
		extern CSCORE_API const Type PR_50Fps;
		extern CSCORE_API const Type PR_59_94Fps;
		extern CSCORE_API const Type PR_60Fps;
		extern CSCORE_API const Type PR_120Fps;
		extern CSCORE_API const Type PR_CustomDeltaTime;
		extern CSCORE_API const Type PR_CustomTotalTime;
		extern CSCORE_API const Type PR_CustomDeltaTimeAndTotalTime;
		extern CSCORE_API const Type PR_CustomDeltaTimePerFrame;
		extern CSCORE_API const Type PR_Custom;
		extern CSCORE_API const Type ECsAnimPlayRate_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsAnim
{
	/**
	*/
	enum class EPlayRate : uint8
	{
		PR_0_001,
		PR_0_01,
		PR_0_1,
		PR_1,
		PR_10,
		PR_100,
		PR_15Fps,
		PR_24Fps,
		PR_25Fps,
		PR_29_97Fps,
		PR_30Fps,
		PR_48Fps,
		PR_50Fps,
		PR_59_94Fps	,
		PR_60Fps,
		PR_120Fps,
		/** DeltaTime and the number of frames are used to calculate the
			TotalTime and TotalCount. */
		PR_CustomDeltaTime,
		/** TotalTime and the number of frames are used to calculate the
			DeltaTime and TotalCount. */
		PR_CustomTotalTime,
		/** TotalTime and DeltaTime are used to calculate the TotalCount. */
		PR_CustomDeltaTimeAndTotalTime,
		/** Each frame has its own DeltaTime. TotalTime is the sum of each frame's DeltaTime. */
		PR_CustomDeltaTimePerFrame,
		/** DeltaTime, TotalTime, and TotalCount are determined by a custom
			implementation */
		PR_Custom,
		EPlayRate_MAX
	};

	struct CSCORE_API EMPlayRate : public TCsEnumMap<EPlayRate>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPlayRate, EPlayRate)
	};

	namespace NPlayRate
	{
		typedef EPlayRate Type;

		namespace Ref
		{
			extern CSCORE_API const Type PR_0_001;
			extern CSCORE_API const Type PR_0_01;
			extern CSCORE_API const Type PR_0_1;
			extern CSCORE_API const Type PR_1;
			extern CSCORE_API const Type PR_10;
			extern CSCORE_API const Type PR_100;
			extern CSCORE_API const Type PR_15Fps;
			extern CSCORE_API const Type PR_24Fps;
			extern CSCORE_API const Type PR_25Fps;
			extern CSCORE_API const Type PR_29_97Fps;
			extern CSCORE_API const Type PR_30Fps;
			extern CSCORE_API const Type PR_48Fps;
			extern CSCORE_API const Type PR_50Fps;
			extern CSCORE_API const Type PR_59_94Fps;
			extern CSCORE_API const Type PR_60Fps;
			extern CSCORE_API const Type PR_120Fps;
			extern CSCORE_API const Type PR_CustomDeltaTime;
			extern CSCORE_API const Type PR_CustomTotalTime;
			extern CSCORE_API const Type PR_CustomDeltaTimeAndTotalTime;
			extern CSCORE_API const Type PR_CustomDeltaTimePerFrame;
			extern CSCORE_API const Type PR_Custom;
			extern CSCORE_API const Type EPlayRate_MAX;
		}

		extern CSCORE_API const uint8 MAX;

		float GetDeltaTime(const EPlayRate& PlayRate);
	}
}

#pragma endregion AnimPlayRate