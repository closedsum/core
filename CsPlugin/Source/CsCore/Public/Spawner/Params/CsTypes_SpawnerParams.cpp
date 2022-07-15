// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsTypes_SpawnerParams.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"

// FCsSpawner_CountParams
#pragma region

#define ParamsType NCsSpawner::NParams::FCount

void FCsSpawner_CountParams::CopyToParams(ParamsType* Params)
{
	Params->SetCountPerSpawn(&CountPerSpawn);
	Params->SetTimeBetweenCountPerSpawn(&TimeBetweenCountPerSpawn);
}

void FCsSpawner_CountParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetCountPerSpawn(CountPerSpawn);
	Params->SetTimeBetweenCountPerSpawn(TimeBetweenCountPerSpawn);
}

#undef ParamsType

bool FCsSpawner_CountParams::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(CountPerSpawn, 1)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TimeBetweenCountPerSpawn, 0.0f)
	return true;
}

bool FCsSpawner_CountParams::IsValid(const FString& Context, void(*Log)(const FString&) /*-FCsLog::Warning*/) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL(CountPerSpawn, 1)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(TimeBetweenCountPerSpawn, 0.0f)
	return true;
}

namespace NCsSpawner
{
	namespace NParams
	{
		bool FCount::IsValidChecked(const FString& Context) const
		{
			CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetCountPerSpawn(), 1)

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTimeBetweenCountPerSpawn(), 0.0f)
			return true;
		}

		bool FCount::IsValid(const FString& Context, void(*Log)(const FString&) /*-FCsLog::Warning*/) const
		{
			CS_IS_INT_GREATER_THAN_OR_EQUAL(GetCountPerSpawn(), 1)

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTimeBetweenCountPerSpawn(), 0.0f)
			return true;
		}
	}
}

#pragma endregion FCsSpawner_CountParams

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
		CSCORE_API CS_ADD_TO_ENUM_MAP(InfiniteFillToCount);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerFrequency_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerFrequency_MAX;
}

namespace NCsSpawner
{
	namespace NFrequency
	{
		namespace Ref
		{
			typedef EMFrequency EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Once);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Count);
			CSCORE_API CS_ADD_TO_ENUM_MAP(TimeCount);
			CSCORE_API CS_ADD_TO_ENUM_MAP(TimeInterval);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Infinite);
			CSCORE_API CS_ADD_TO_ENUM_MAP(InfiniteFillToCount);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFrequency_MAX, "MAX");
		}

		CSCORE_API const uint8 MAX = (uint8)EFrequency::EFrequency_MAX;
	}
}

#pragma endregion SpawnerFrequency

// FCsSpawner_FrequencyParams
#pragma region

#define ParamsType NCsSpawner::NParams::FFrequency

void FCsSpawner_FrequencyParams::CopyToParams(ParamsType* Params)
{
	typedef NCsSpawner::EFrequency FrequencyType;

	Params->SetType((FrequencyType*)&Type);
	Params->SetDelay(&Delay);
	Params->SetCount(&Count);
	Params->SetInterval(&Interval);
	Params->SetTime(&Time);
}

void FCsSpawner_FrequencyParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsSpawner::EFrequency FrequencyType;

	Params->SetType((FrequencyType)Type);
	Params->SetDelay(Delay);
	Params->SetCount(Count);
	Params->SetInterval(Interval);
	Params->SetTime(Time);
}

#undef ParamsType

bool FCsSpawner_FrequencyParams::IsValidChecked(const FString& Context) const
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

		checkf(Interval >= 0.0f, TEXT("%s: Interval MUST be >= 0.0f if Type == ECsSpawnerFrequency::Count."), *Context);
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
	// InfiniteFillToCount
	else
	if (Type == ECsSpawnerFrequency::InfiniteFillToCount)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::InfiniteFillToCount."), *Context);

		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::InfiniteFillToCount."), *Context);
	}
	return true;
}

bool FCsSpawner_FrequencyParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

		if (Interval < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be >= 0.0f if Type == ECsSpawnerFrequency::Count."), *Context));
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
	// InfiniteFillToCount
	else
	if (Type == ECsSpawnerFrequency::InfiniteFillToCount)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsSpawnerFrequency::InfiniteFillToCount."), *Context));
			return false;
		}

		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsSpawnerFrequency::InfiniteFillToCount."), *Context));
			return false;
		}
	}
	return true;
}

float FCsSpawner_FrequencyParams::CalculateTotalTime() const
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

void FCsSpawner_FrequencyParams::Reset()
{
	Type = ECsSpawnerFrequency::Once;
	Delay = 0.0f;
	Count = 0;
	Interval = 0.0f;
	Time = 0.0f;
}

void FCsSpawner_FrequencyParams::Update()
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

void FCsSpawner_FrequencyParams::OnPostEditChange()
{
	Update();
}

namespace NCsSpawner
{
	namespace NParams
	{
		bool FFrequency::IsValidChecked(const FString& Context) const
		{
			typedef NCsSpawner::EFrequency FrequencyType;

			// Once
			if (GetType() == FrequencyType::Once)
			{
				// No checks
			}
			// Count
			else
			if (GetType() == FrequencyType::Count)
			{
				checkf(GetCount() >= 1, TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Count."), *Context);

				checkf(GetInterval() >= 0.0f, TEXT("%s: etInterval() MUST be >= 0.0f if Type == ECsSpawnerFrequency::Count."), *Context);
			}
			// TimeCount
			else
			if (GetType() == FrequencyType::TimeCount)
			{
				checkf(GetCount() >= 1, TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::TimeCount."), *Context);
			}
			// TimeInterval
			else
			if (GetType() == FrequencyType::TimeInterval)
			{
				checkf(GetInterval() > 0.0f, TEXT("%s: GetInterval() MUST be > 0.0f if GetType() == FrequencyType::TimeInterval."), *Context);
			}
			// Infinite
			else
			if (GetType() == FrequencyType::Infinite)
			{
				checkf(GetInterval() > 0.0f, TEXT("%s: GetInterval() MUST be > 0.0f if GetType() == FrequencyType::Infinite."), *Context);
			}
			// InfiniteFillToCount
			else
			if (GetType() == FrequencyType::InfiniteFillToCount)
			{
				checkf(GetInterval() > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == FrequencyType::InfiniteFillToCount."), *Context);

				checkf(GetCount() >= 1, TEXT("%s: Count MUST be >= 1 if Type == FrequencyType::InfiniteFillToCount."), *Context);
			}
			return true;
		}

		bool FFrequency::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			typedef NCsSpawner::EFrequency FrequencyType;

			// Once
			if (GetType() == FrequencyType::Once)
			{
				// No checks
			}
			// Count
			else
			if (GetType() == FrequencyType::Count)
			{
				if (GetCount() < 1)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::Count."), *Context));
					return false;
				}

				if (GetInterval() < 0.0f)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetInterval() MUST be >= 0.0f if Type == ECsSpawnerFrequency::Count."), *Context));
					return false;
				}
			}
			// TimeCount
			else
			if (GetType() == FrequencyType::TimeCount)
			{
				if (GetCount() < 1)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::TimeCount."), *Context));
					return false;
				}
			}
			// TimeInterval
			else
			if (GetType() == FrequencyType::TimeInterval)
			{
				if (GetInterval() <= 0.0f)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetInterval() MUST be > 0.0f if GetType() == FrequencyType::TimeInterval."), *Context));
					return false;
				}
			}
			// Infinite
			else
			if (GetType() == FrequencyType::Infinite)
			{
				if (GetInterval() <= 0.0f)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetInterval() MUST be > 0.0f if GetType() == FrequencyType::Infinite."), *Context));
					return false;
				}
			}
			// InfiniteFillToCount
			else
			if (GetType() == FrequencyType::InfiniteFillToCount)
			{
				if (GetInterval() <= 0.0f)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetInterval() MUST be > 0.0f if GetType() == FrequencyType::InfiniteFillToCount."), *Context));
					return false;
				}

				if (GetCount() < 1)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetCount() MUST be >= 1 if GetType() == FrequencyType::InfiniteFillToCount."), *Context));
					return false;
				}
			}
			return true;
		}

		float FFrequency::CalculateTotalTime() const
		{
			typedef NCsSpawner::EFrequency FrequencyType;

			float TotalTime = 0.0f;

			// Once
			if (GetType() == FrequencyType::Once)
			{
				TotalTime += GetDelay();
			}
			// Count
			else
			if (GetType() == FrequencyType::Count)
			{
				TotalTime += GetDelay();
				TotalTime += GetCount() * GetInterval();
			}
			// TimeCount
			else
			if (GetType() == FrequencyType::TimeCount)
			{
				TotalTime += GetDelay();
				TotalTime += GetTime();
			}
			// TimeInterval
			else
			if (GetType() == FrequencyType::TimeInterval)
			{
				TotalTime += GetDelay();
				TotalTime += GetCount() * GetInterval();
			}
			// Infinite
			if (GetType() == FrequencyType::Infinite)
			{
				TotalTime = 0.0f;
			}
			return TotalTime;
		}

		void FFrequency::Reset()
		{
			typedef NCsSpawner::EFrequency FrequencyType;

			CS_RESET_MEMBER_WITH_PROXY(Type, FrequencyType::Once)
			CS_RESET_MEMBER_WITH_PROXY(Delay, 0.0f)
			CS_RESET_MEMBER_WITH_PROXY(Count, 0)
			CS_RESET_MEMBER_WITH_PROXY(Interval, 0.0f)
			CS_RESET_MEMBER_WITH_PROXY(Time, 0.0f)
		}

		void FFrequency::Update()
		{
			typedef NCsSpawner::EFrequency FrequencyType;

			if (GetTime() > 0.0f)
			{
				// TimeCount
				if (GetType() == FrequencyType::TimeCount)
				{
					if (GetCount() >= 1)
					{
						SetInterval(GetTime() / (float)GetCount());
					}
				}
				// TimeInterval
				else
				if (GetType() == FrequencyType::TimeInterval)
				{
					if (GetInterval() > 0.0f)
					{
						SetCount(FMath::FloorToInt(GetTime() / GetInterval()));
					}
				}
			}
		}
	}
}

#pragma endregion FCsSpawner_FrequencyParams

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

//// FCsSpawnerPointHelper
//#pragma region
//
//void FCsSpawnerPointHelper::PrepareSpawns()
//{
//	// NO spawns to prepare for Self
//	if (Params->Type == ECsSpawnerPoint::Self)
//		return;
//
//	typedef NCsArray::FLibrary ArrayLibrary;
//
//	// Transform
//	if (Params->Type == ECsSpawnerPoint::Transform)
//	{
//		const TArray<FTransform>& _Transforms = Params->Transforms;
//
//		Transforms.Reset(FMath::Max(Transforms.Max(), _Transforms.Num()));
//		Transforms.Append(_Transforms);
//
//		// RandomShuffle
//		if (Params->Order == ECsSpawnerPointOrder::RandomShuffle)
//			ArrayLibrary::Shuffle<FTransform>(Transforms);
//	}
//	// Actor
//	else
//	if (Params->Type == ECsSpawnerPoint::Actor)
//	{
//		const TArray<AActor*>& _Actors = Params->Actors;
//
//		Actors.Reset(FMath::Max(Actors.Max(), _Actors.Num()));
//		Actors.Append(_Actors);
//
//		// RandomShuffle
//		if (Params->Order == ECsSpawnerPointOrder::RandomShuffle)
//			ArrayLibrary::Shuffle<AActor*>(Actors);
//	}
//}
//
//void FCsSpawnerPointHelper::AdvanceIndex()
//{
//	int32 Count = Params->Type == ECsSpawnerPoint::Transform ? Params->Transforms.Num() : Params->Actors.Num();
//
//	// FirstToLast
//	if (Params->Order == ECsSpawnerPointOrder::FirstToLast)
//		Index = (Index + 1) % Count;
//	// RandomShuffle
//	else
//	if (Params->Order == ECsSpawnerPointOrder::RandomShuffle)
//		Index = (Index + 1) % Count;
//	// Random
//	else
//	if (Params->Order == ECsSpawnerPointOrder::Random)
//		Index = FMath::RandRange(0, Count - 1);
//}
//
//FTransform FCsSpawnerPointHelper::GetSpawnTransform() const
//{
//	// Self
//	if (Params->Type == ECsSpawnerPoint::Self)
//		return SpawnerAsActor->GetActorTransform();
//	// Transform
//	if (Params->Type == ECsSpawnerPoint::Transform)
//		return Transforms[Index];
//	// Actor
//	if (Params->Type == ECsSpawnerPoint::Actor)
//		return Actors[Index]->GetActorTransform();
//	return FTransform::Identity;
//}
//
//FVector FCsSpawnerPointHelper::GetSpawnLocation() const
//{
//	// Self
//	if (Params->Type == ECsSpawnerPoint::Self)
//		return SpawnerAsActor->GetActorLocation();
//	// Transform
//	if (Params->Type == ECsSpawnerPoint::Transform)
//		return Transforms[Index].GetTranslation();
//	// Actor
//	if (Params->Type == ECsSpawnerPoint::Actor)
//		return Actors[Index]->GetActorLocation();
//	return FVector::ZeroVector;
//}
//
//#pragma endregion FCsSpawnerPointHelper

// SpawnerShape
#pragma region

namespace NCsSpawnerShape
{
	namespace Ref
	{
		typedef EMCsSpawnerShape EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Circle);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Rectangle);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sphere);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Box);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerShape_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerShape_MAX;
}

namespace NCsSpawner
{
	namespace NShape
	{
		namespace Ref
		{
			typedef EMShape EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Circle);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Rectangle);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Sphere);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Box);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EShape_MAX, "MAX");
		}
	}
}

#pragma endregion SpawnerShape

// SpawnerShapeCenter
#pragma region

namespace NCsSpawnerShapeCenter
{
	namespace Ref
	{
		typedef EMCsSpawnerShapeCenter EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Self);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Transform);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerShapeCenter_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerShapeCenter_MAX;
}

namespace NCsSpawner
{
	namespace NShape
	{
		namespace NCenter
		{
			namespace Ref
			{
				typedef EMCenter EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP(Self);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Transform);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECenter_MAX, "MAX");
			}
		}
	}
}

#pragma endregion SpawnerShapeCenter

// SpawnerDistribution
#pragma region

namespace NCsSpawnerDistribution
{
	namespace Ref
	{
		typedef EMCsSpawnerDistribution EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Uniform);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpawnerDistribution_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSpawnerDistribution_MAX;
}

namespace NCsSpawner
{
	namespace NDistribution
	{
		namespace Ref
		{
			typedef EMDistribution EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Uniform);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDistribution_MAX, "MAX");
		}
	}
}

#pragma endregion SpawnerDistribution