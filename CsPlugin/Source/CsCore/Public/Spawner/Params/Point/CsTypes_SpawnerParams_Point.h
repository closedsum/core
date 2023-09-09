// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_SpawnerParams_Point.generated.h"

// SpawnerPointSelection
#pragma region

/**
* Describes the order in which points are selected for a Spawner to 
* spawn object at.
*  Spawner is an object that implements the interface: ICsSpawner.
*/
UENUM(BlueprintType)
enum class ECsSpawnerPointSelection : uint8
{	
	/** Use the spawn index to determine the point to choose. */
	Index							UMETA(DisplayName = "Index"),
	FirstToLast						UMETA(DisplayName = "First to Last"),
	LastToFirst						UMETA(DisplayName = "Last to First"),
	Random							UMETA(DisplayName = "Random"),
	ECsSpawnerPointSelection_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerPointSelection : public TCsEnumMap<ECsSpawnerPointSelection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerPointSelection, ECsSpawnerPointSelection)
};

namespace NCsSpawnerPointSelection
{
	typedef ECsSpawnerPointSelection Type;

	namespace Ref
	{
		extern CSCORE_API const Type Index;
		extern CSCORE_API const Type FirstToLast;
		extern CSCORE_API const Type LastToFirst;
		extern CSCORE_API const Type Random;
		extern CSCORE_API const Type ECsSpawnerPointSelection_MAX;
	}
}

namespace NCsSpawner
{
	namespace NPoint
	{
		/**
		* Describes the order in which points are selected for a Spawner to
		* spawn object at.
		*  Spawner is an object that implements the interface: ICsSpawner.
		*/
		enum class ESelection
		{
			Index,
			FirstToLast,
			LastToFirst,
			Random,
			ESelection_MAX
		};

		struct CSCORE_API EMSelection : public TCsEnumMap<ESelection>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMSelection, ESelection)
		};

		namespace NSelection
		{
			namespace Ref
			{
				typedef ESelection Type;

				extern CSCORE_API const Type Index;
				extern CSCORE_API const Type FirstToLast;
				extern CSCORE_API const Type LastToFirst;
				extern CSCORE_API const Type Random;
				extern CSCORE_API const Type ESelection_MAX;
			}
		}
	}
}

#pragma endregion SpawnerPointSelection