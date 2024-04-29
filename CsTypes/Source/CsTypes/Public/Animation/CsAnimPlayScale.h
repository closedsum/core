// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsAnimPlayScale.generated.h"

/**
* Describes how any time related information for an animation should be scaled.
*/
UENUM(BlueprintType)
enum class ECsAnimPlayScale : uint8
{
	/** For 2D, scaling the time scales the TotalTime and the DeltaTime. */
	Default					UMETA(DisplayName = "Default"),
	/** For 2D, scaling the time ONLY scales the TotalTime. This is useful
		for looping animations with a custom DeltaTime and DeltaTime should NOT
		be scaled. */
	TotalTime				UMETA(DisplayName = "Total Time"),
	ECsAnimPlayScale_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsAnimPlayScale : public TCsEnumMap<ECsAnimPlayScale>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAnimPlayScale, ECsAnimPlayScale)
};

namespace NCsAnimPlayScale
{
	typedef ECsAnimPlayScale Type;
	
	namespace Ref
	{
		extern CSTYPES_API const Type Default;
		extern CSTYPES_API const Type TotalTime;
		extern CSTYPES_API const Type ECsAnimPlayScale_MAX;
	}

	extern CSTYPES_API const uint8 MAX;
}

namespace NCsAnim
{
	/**
	* Describes how any time related information for an animation should be scaled.
	*/
	enum class EPlayScale : uint8
	{
		/** For 2D, scaling the time scales the TotalTime and the DeltaTime. */
		Default,
		/** For 2D, scaling the time ONLY scales the TotalTime. This is useful
			for looping animations with a custom DeltaTime and DeltaTime should NOT
			be scaled. */
		TotalTime,
		EPlayScale_MAX
	};

	struct CSTYPES_API EMPlayScale : public TCsEnumMap<EPlayScale>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPlayScale, EPlayScale)
	};

	namespace NPlayScale
	{
		typedef EPlayScale Type;

		namespace Ref
		{
			extern CSTYPES_API const Type Default;
			extern CSTYPES_API const Type TotalTime;
			extern CSTYPES_API const Type EPlayScale_MAX;
		}

		extern CSTYPES_API const uint8 MAX;
	}
}