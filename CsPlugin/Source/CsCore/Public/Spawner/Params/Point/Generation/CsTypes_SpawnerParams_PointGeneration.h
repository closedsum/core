// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_SpawnerParams_PointGeneration.generated.h"

// SpawnerPointGenerationCondition
#pragma region

/**
* Describes how often to generate points for a Spawner.
*  Spawner is an object that implements the interface: ICsSpawner.
*/
UENUM(BlueprintType)
enum class ECsSpawnerPointGenerationCondition : uint8
{
	/** Only generate points ONCE. This is usually done when the spawner
		is initialized. */
	Once									UMETA(DisplayName = "Once"),
	/** Generate points after "cycling" through all the current
		generated points. */
	CycleComplete							UMETA(DisplayName = "User Defined"),
	ECsSpawnerPointGenerationCondition_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerPointGenerationCondition : public TCsEnumMap<ECsSpawnerPointGenerationCondition>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerPointGenerationCondition, ECsSpawnerPointGenerationCondition)
};

namespace NCsSpawnerPointGenerationCondition
{
	typedef ECsSpawnerPointGenerationCondition Type;

	namespace Ref
	{
		extern CSCORE_API const Type Once;
		extern CSCORE_API const Type CycleComplete;
		extern CSCORE_API const Type ECsSpawnerPointGenerationCondition_MAX;
	}
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NGeneration
		{
			/**
			* Describes how often to generate points for a Spawner.
			*  Spawner is an object that implements the interface: ICsSpawner.
			*/
			enum class ECondition
			{
				Once,
				CycleComplete,
				ECondition_MAX
			};

			struct CSCORE_API EMCondition : public TCsEnumMap<ECondition>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCondition, ECondition)
			};

			namespace NCondition
			{
				namespace Ref
				{
					typedef ECondition Type;

					extern CSCORE_API const Type Once;
					extern CSCORE_API const Type CycleComplete;
					extern CSCORE_API const Type ECondition_MAX;
				}
			}
		}
	}
}

#pragma endregion SpawnerPointGenerationCondition

// SpawnerPointGenerationCount
#pragma region

/**
* Describes the number of points to generate for a Spawner.
*  Spawner is an object that implements the interface: ICsSpawner.
*/
UENUM(BlueprintType)
enum class ECsSpawnerPointGenerationCount : uint8
{
	/** The number of points generated is depended on the max
		spawn count of the spawner. */
	SpawnCount							UMETA(DisplayName = "Spawn Count"),
	/**  The number of points is set / defined. */
	UserDefined							UMETA(DisplayName = "User Defined"),
	ECsSpawnerPointGenerationCount_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerPointGenerationCount : public TCsEnumMap<ECsSpawnerPointGenerationCount>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerPointGenerationCount, ECsSpawnerPointGenerationCount)
};

namespace NCsSpawnerPointGenerationCount
{
	typedef ECsSpawnerPointGenerationCount Type;

	namespace Ref
	{
		extern CSCORE_API const Type SpawnCount;
		extern CSCORE_API const Type UserDefined;
		extern CSCORE_API const Type ECsSpawnerPointGenerationCount_MAX;
	}
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace NGeneration
		{
			/**
			* Describes the number of points to generate for a Spawner.
			*  Spawner is an object that implements the interface: ICsSpawner.
			*/
			enum class ECount
			{
				SpawnCount,
				UserDefined,
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

					extern CSCORE_API const Type SpawnCount;
					extern CSCORE_API const Type UserDefined;
					extern CSCORE_API const Type ECount_MAX;
				}
			}
		}
	}
}

#pragma endregion SpawnerPointGenerationCount