// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsTypes_SpawnerParams.h"

// SpawnerFrequency
#pragma region

namespace NCsSpawnerFrequency
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, Once);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, Count);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, Time);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerFrequency, Infinite);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSpawnerFrequency, ECsSpawnerFrequency_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerFrequency_MAX;
}

#pragma endregion SpawnerFrequency

// FCsSpawnerCountParams
#pragma region

bool FCsSpawnerCountParams::IsValidChecked(const FString& Context) const
{
	checkf(CountPerSpawn >= 1, TEXT("%s: CountPerSpawn MUST be >= 1."), *Context);
	return true;
}

#pragma endregion FCsSpawnerCountParams

// FCsSpawnerFrequencyParams
#pragma region

bool FCsSpawnerFrequencyParams::IsValidChecked(const FString& Context) const
{
	// Once
	if (Type == ECsSpawnerFrequency::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == ECsSpawnerFrequency::Count)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::Count."), *Context);
	}
	// Time
	else
	if (Type == ECsSpawnerFrequency::Time)
	{
		// TODO
	}
	// Infinite
	else
	if (Type == ECsSpawnerFrequency::Infinite)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::Infinite."), *Context);
	}
	return true;
}

#pragma endregion FCsSpawnerFrequencyParams


// SpawnerTransform
#pragma region

namespace NCsSpawnerTransform
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerTransform, Self);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerTransform, Transform);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerTransform, Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSpawnerTransform, Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSpawnerTransform, ECsSpawnerTransform_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerTransform_MAX;
}

#pragma endregion SpawnerTransform
