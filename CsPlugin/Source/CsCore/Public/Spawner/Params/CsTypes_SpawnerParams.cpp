// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsTypes_SpawnerParams.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Array.h"

// SpawnerFrequency
#pragma region

namespace NCsSpawnerFrequency
{
	namespace Ref
	{
		typedef EMCsSpawnerFrequency EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Once);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Count);
		CSCORE_API CS_ADD_TO_ENUM_MAP(TimeCount);
		CSCORE_API CS_ADD_TO_ENUM_MAP(TimeInterval);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerFrequency_MAX, "MAX");
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
	// TimeCount
	else
	if (Type == ECsSpawnerFrequency::TimeCount)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::TimeCount."), *Context);
	}
	// TimeInterval
	else
	if (Type == ECsSpawnerFrequency::TimeInterval)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::TimeInterval."), *Context);
	}
	// Infinite
	else
	if (Type == ECsSpawnerFrequency::Infinite)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::Infinite."), *Context);
	}
	return true;
}

bool FCsSpawnerFrequencyParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::Count."), *Context));
			return false;
		}
	}
	// TimeCount
	else
	if (Type == ECsSpawnerFrequency::TimeCount)
	{
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::TimeCount."), *Context));
			return false;
		}
	}
	// TimeInterval
	else
	if (Type == ECsSpawnerFrequency::TimeInterval)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::TimeInterval."), *Context));
			return false;
		}
	}
	// Infinite
	else
	if (Type == ECsSpawnerFrequency::Infinite)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::Infinite."), *Context));
			return false;
		}
	}
	return true;
}

float FCsSpawnerFrequencyParams::CalculateTotalTime() const
{
	float TotalTime = 0.0f;

	// Once
	if (Type == ECsSpawnerFrequency::Once)
	{
		TotalTime += Delay;
	}
	// Count
	else
	if (Type == ECsSpawnerFrequency::Count)
	{
		TotalTime += Delay;
		TotalTime += Count * Interval;
	}
	// TimeCount
	else
	if (Type == ECsSpawnerFrequency::TimeCount)
	{
		TotalTime += Delay;
		TotalTime += Time;
	}
	// TimeInterval
	else
	if (Type == ECsSpawnerFrequency::TimeInterval)
	{
		TotalTime += Delay;
		TotalTime += Count * Interval;
	}
	// Infinite
	if (Type == ECsSpawnerFrequency::Infinite)
	{
		TotalTime = 0.0f;
	}
	return TotalTime;
}

void FCsSpawnerFrequencyParams::Reset()
{
	Type = ECsSpawnerFrequency::Once;
	Delay = 0.0f;
	Count = 0;
	Interval = 0.0f;
	Time = 0.0f;
}

void FCsSpawnerFrequencyParams::Update()
{
	if (Time > 0.0f)
	{
		// TimeCount
		if (Type == ECsSpawnerFrequency::TimeCount)
		{
			if (Count >= 1)
			{
				Interval = Time / (float)Count;
			}
		}
		// TimeInterval
		else
		if (Type == ECsSpawnerFrequency::TimeInterval)
		{
			if (Interval > 0.0f)
			{
				Count = FMath::FloorToInt(Time / Interval);
			}
		}
	}
}

void FCsSpawnerFrequencyParams::OnPostEditChange()
{
	Update();
}

#pragma endregion FCsSpawnerFrequencyParams

// SpawnerPoint
#pragma region

namespace NCsSpawnerPoint
{
	namespace Ref
	{
		typedef EMCsSpawnerPoint EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Self);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Transform);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPoint_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerPoint_MAX;
}

namespace NCsSpawner
{
	namespace NPoint
	{
		namespace Ref
		{
			typedef EMPoint EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Self);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Transform);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPoint_MAX, "MAX");
		}
	}
}

#pragma endregion SpawnerPoint

// SpawnerPointOrder
#pragma region

namespace NCsSpawnerPointOrder
{
	namespace Ref
	{
		typedef EMCsSpawnerPointOrder EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(FirstToLast);
		CSCORE_API CS_ADD_TO_ENUM_MAP(RandomShuffle);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Random);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerPointOrder_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerPointOrder_MAX;
}

#pragma endregion SpawnerPointOrder

// FCsSpawnerPointHelper
#pragma region

void FCsSpawnerPointHelper::PrepareSpawns()
{
	// NO spawns to prepare for Self
	if (Params->Type == ECsSpawnerPoint::Self)
		return;

	typedef NCsArray::FLibrary ArrayLibrary;

	// Transform
	if (Params->Type == ECsSpawnerPoint::Transform)
	{
		const TArray<FTransform>& _Transforms = Params->Transforms;

		Transforms.Reset(FMath::Max(Transforms.Max(), _Transforms.Num()));
		Transforms.Append(_Transforms);

		// RandomShuffle
		if (Params->Order == ECsSpawnerPointOrder::RandomShuffle)
			ArrayLibrary::Shuffle<FTransform>(Transforms);
	}
	// Actor
	else
	if (Params->Type == ECsSpawnerPoint::Actor)
	{
		const TArray<AActor*>& _Actors = Params->Actors;

		Actors.Reset(FMath::Max(Actors.Max(), _Actors.Num()));
		Actors.Append(_Actors);

		// RandomShuffle
		if (Params->Order == ECsSpawnerPointOrder::RandomShuffle)
			ArrayLibrary::Shuffle<AActor*>(Actors);
	}
}

void FCsSpawnerPointHelper::AdvanceIndex()
{
	int32 Count = Params->Type == ECsSpawnerPoint::Transform ? Params->Transforms.Num() : Params->Actors.Num();

	// FirstToLast
	if (Params->Order == ECsSpawnerPointOrder::FirstToLast)
		Index = (Index + 1) % Count;
	// RandomShuffle
	else
	if (Params->Order == ECsSpawnerPointOrder::RandomShuffle)
		Index = (Index + 1) % Count;
	// Random
	else
	if (Params->Order == ECsSpawnerPointOrder::Random)
		Index = FMath::RandRange(0, Count - 1);
}

FTransform FCsSpawnerPointHelper::GetSpawnTransform() const
{
	// Self
	if (Params->Type == ECsSpawnerPoint::Self)
		return SpawnerAsActor->GetActorTransform();
	// Transform
	if (Params->Type == ECsSpawnerPoint::Transform)
		return Transforms[Index];
	// Actor
	if (Params->Type == ECsSpawnerPoint::Actor)
		return Actors[Index]->GetActorTransform();
	return FTransform::Identity;
}

FVector FCsSpawnerPointHelper::GetSpawnLocation() const
{
	// Self
	if (Params->Type == ECsSpawnerPoint::Self)
		return SpawnerAsActor->GetActorLocation();
	// Transform
	if (Params->Type == ECsSpawnerPoint::Transform)
		return Transforms[Index].GetTranslation();
	// Actor
	if (Params->Type == ECsSpawnerPoint::Actor)
		return Actors[Index]->GetActorLocation();
	return FVector::ZeroVector;
}

#pragma endregion FCsSpawnerPointHelper