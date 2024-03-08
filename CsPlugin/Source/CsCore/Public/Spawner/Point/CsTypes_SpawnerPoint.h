// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_SpawnerPoint.generated.h"

// SpawnerPointCount
#pragma region

/**
* Describes the number of spawn points for the spawner.
*/
UENUM(BlueprintType)
enum class ECsSpawnerPointCount : uint8
{
	/** No count is necessary. This is the case when spawn frequency == Infinite (ECsSpawnerFrequency::Infinite) */
	None						UMETA(DisplayName = "None"),
	/** Use the total count based on the CountParams and FrequencyParams */
	TotalCount					UMETA(DisplayName = "Total Count"),
	/** Use the count per spawn "group" */
	CountPerSpawn				UMETA(DisplayName = "Count per Spawn"),
	ECsSpawnerPointCount_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerPointCount : public TCsEnumMap<ECsSpawnerPointCount>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerPointCount, ECsSpawnerPointCount)
};

namespace NCsSpawnerPointCount
{
	typedef ECsSpawnerPointCount Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type TotalCount;
		extern CSCORE_API const Type CountPerSpawn;
		extern CSCORE_API const Type ECsSpawnerPointCount_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	namespace NPoint
	{
		/**
		* Describes the number of spawn points for the spawner.
		*/
		enum class ECount
		{
			/** No count is necessary. This is the case when spawn frequency == Infinite (ECsSpawnerFrequency::Infinite) */
			None,
			/** Use the total count based on the CountParams and FrequencyParams */
			TotalCount,
			/** Use the count per spawn "group" */
			CountPerSpawn,
			ECount_MAX
		};

		struct CSCORE_API EMCount : public TCsEnumMap<ECount>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCount, ECount)
		};

		namespace NCount
		{
			namespace Ref
			{
				typedef ECount Type;

				extern CSCORE_API const Type None;
				extern CSCORE_API const Type TotalCount;
				extern CSCORE_API const Type CountPerSpawn;
				extern CSCORE_API const Type ECount_MAX;
			}
		}
	}
}

#pragma endregion SpawnerPointCount

// SpawnerPointOrder
#pragma region

/**
* The order in which to use spawn points.
*/
UENUM(BlueprintType)
enum class ECsSpawnerPointOrder : uint8
{
	Random						UMETA(DisplayName = "Random"),
	RandomShuffle				UMETA(DisplayName = "Random Shuffle"),
	FirstToLast					UMETA(DisplayName = "First to Last"),
	Custom						UMETA(DisplayName = "Custom"),
	ECsSpawnerPointOrder_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerPointOrder : public TCsEnumMap<ECsSpawnerPointOrder>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerPointOrder, ECsSpawnerPointOrder)
};

namespace NCsSpawnerPointOrder
{
	typedef ECsSpawnerPointOrder Type;

	namespace Ref
	{
		extern CSCORE_API const Type Random;
		extern CSCORE_API const Type RandomShuffle;
		extern CSCORE_API const Type FirstToLast;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsSpawnerPointOrder_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	namespace NPoint
	{
		/**
		* The order in which to use spawn points.
		*/
		enum class EOrder : uint8
		{
			Random,
			RandomShuffle,
			FirstToLast,
			Custom,
			EOrder_MAX
		};

		struct CSCORE_API EMOrder : public TCsEnumMap<EOrder>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMOrder, EOrder)
		};

		namespace NOrder
		{
			namespace Ref
			{
				typedef EOrder Type;

				extern CSCORE_API const Type Random;
				extern CSCORE_API const Type RandomShuffle;
				extern CSCORE_API const Type FirstToLast;
				extern CSCORE_API const Type Custom;
				extern CSCORE_API const Type EOrder_MAX;
			}

			extern CSCORE_API const uint8 MAX;
		}
	}
}

#pragma endregion SpawnerPointOrder