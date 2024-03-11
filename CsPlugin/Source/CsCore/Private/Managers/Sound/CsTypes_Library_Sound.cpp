// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/CsTypes_Library_Sound.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"

// SoundSpawnFrequency
#pragma region

namespace NCsSoundSpawnFrequency
{
	namespace Ref
	{
		typedef EMCsSoundSpawnFrequency EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Once);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Count);
		CSCORE_API CS_ADD_TO_ENUM_MAP(TimeCount);
		CSCORE_API CS_ADD_TO_ENUM_MAP(TimeInterval);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSoundSpawnFrequency_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSoundSpawnFrequency_MAX;
}

namespace NCsSound
{
	namespace NSpawn
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
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFrequency_MAX, "MAX");
			}

			CSCORE_API const uint8 MAX = (uint8)EFrequency::EFrequency_MAX;
		}
	}
}

#pragma endregion SoundSpawnFrequency

// FCsSound_Spawn_FrequencyParams
#pragma region

#define ParamsType NCsSound::NSpawn::NParams::FFrequency
#define FrequencyType NCsSound::NSpawn::EFrequency

void FCsSound_Spawn_FrequencyParams::CopyToParams(ParamsType* Params)
{
	CS_COPY_TYPE_TO_PROXY(Params, Type, FrequencyType);
	CS_COPY_TO_PROXY(Params, Delay);
	CS_COPY_TO_PROXY(Params, Count);
	CS_COPY_TO_PROXY(Params, Interval);
	CS_COPY_TO_PROXY(Params, Time);
}

void FCsSound_Spawn_FrequencyParams::CopyToParamsAsValue(ParamsType* Params) const
{
	CS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Type, FrequencyType);
	CS_COPY_TO_PROXY_AS_VALUE(Params, Delay);
	CS_COPY_TO_PROXY_AS_VALUE(Params, Count);
	CS_COPY_TO_PROXY_AS_VALUE(Params, Interval);
	CS_COPY_TO_PROXY_AS_VALUE(Params, Time);
}

#undef ParamsType
#undef FrequencyType

#define FrequencyType ECsSoundSpawnFrequency

bool FCsSound_Spawn_FrequencyParams::IsValidChecked(const FString& Context) const
{
	// Once
	if (Type == FrequencyType::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == FrequencyType::Count)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsSoundSpawnFrequency::Count."), *Context);
		checkf(Interval >= 0.0f, TEXT("%s: Interval MUST be >= 0.0f if Type == ECsSoundSpawnFrequency::Count."), *Context);
	}
	// TimeCount
	else
	if (Type == FrequencyType::TimeCount)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsSoundSpawnFrequency::TimeCount."), *Context);
	}
	// TimeInterval
	else
	if (Type == FrequencyType::TimeInterval)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSoundSpawnFrequency::TimeInterval."), *Context);
	}
	// Infinite
	else
	if (Type == FrequencyType::Infinite)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsSoundSpawnFrequency::Infinite."), *Context);
	}
	return true;
}

bool FCsSound_Spawn_FrequencyParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Once
	if (Type == FrequencyType::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == FrequencyType::Count)
	{
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsSoundSpawnFrequency::Count."), *Context));
			return false;
		}

		if (Interval < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be >= 0.0f if Type == ECsSoundSpawnFrequency::Count."), *Context));
			return false;
		}
	}
	// TimeCount
	else
	if (Type == FrequencyType::TimeCount)
	{
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsSoundSpawnFrequency::TimeCount."), *Context));
			return false;
		}
	}
	// TimeInterval
	else
	if (Type == FrequencyType::TimeInterval)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsSoundSpawnFrequency::TimeInterval."), *Context));
			return false;
		}
	}
	// Infinite
	else
	if (Type == FrequencyType::Infinite)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsSoundSpawnFrequency::Infinite."), *Context));
			return false;
		}
	}
	return true;
}

float FCsSound_Spawn_FrequencyParams::CalculateTotalTime() const
{
	float TotalTime = 0.0f;

	// Once
	if (Type == FrequencyType::Once)
	{
		TotalTime += Delay;
	}
	// Count
	else
	if (Type == FrequencyType::Count)
	{
		TotalTime += Delay;
		TotalTime += Count * Interval;
	}
	// TimeCount
	else
	if (Type == FrequencyType::TimeCount)
	{
		TotalTime += Delay;
		TotalTime += Time;
	}
	// TimeInterval
	else
	if (Type == FrequencyType::TimeInterval)
	{
		TotalTime += Delay;
		TotalTime += Count * Interval;
	}
	// Infinite
	if (Type == FrequencyType::Infinite)
	{
		TotalTime = 0.0f;
	}
	return TotalTime;
}

void FCsSound_Spawn_FrequencyParams::Reset()
{
	Type = FrequencyType::Once;
	Delay = 0.0f;
	Count = 0;
	Interval = 0.0f;
	Time = 0.0f;
}

void FCsSound_Spawn_FrequencyParams::Update()
{
	if (Time > 0.0f)
	{
		// TimeCount
		if (Type == FrequencyType::TimeCount)
		{
			if (Count >= 1)
			{
				Interval = Time / (float)Count;
			}
		}
		// TimeInterval
		else
		if (Type == FrequencyType::TimeInterval)
		{
			if (Interval > 0.0f)
			{
				Count = FMath::FloorToInt(Time / Interval);
			}
		}
	}
}

void FCsSound_Spawn_FrequencyParams::OnPostEditChange()
{
	Update();
}

#undef FrequencyType

namespace NCsSound
{
	namespace NSpawn
	{
		namespace NParams
		{
			#define FrequencyType NCsSound::NSpawn::EFrequency

			bool FFrequency::IsValidChecked(const FString& Context) const
			{
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
				return true;
			}

			bool FFrequency::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
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
				return true;
			}

			float FFrequency::CalculateTotalTime() const
			{
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
				CS_RESET_MEMBER_WITH_PROXY(Type, FrequencyType::Once)
				CS_RESET_MEMBER_WITH_PROXY(Delay, 0.0f)
				CS_RESET_MEMBER_WITH_PROXY(Count, 0)
				CS_RESET_MEMBER_WITH_PROXY(Interval, 0.0f)
				CS_RESET_MEMBER_WITH_PROXY(Time, 0.0f)
			}

			void FFrequency::Update()
			{
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

			#undef FrequencyType
		}
	}
}

#pragma endregion FCsSound_Spawn_FrequencyParams

namespace NCsSound
{
	namespace NSpawn
	{
		namespace NParams
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				// Check Sound is Valid.
				CS_IS_VALID_CHECKED(Sound);
				CS_IS_FLOAT_GREATER_THAN_CHECKED(VolumeMultiplier, 0.0f)
				CS_IS_FLOAT_GREATER_THAN_CHECKED(PitchMultiplier, 0.0f)
				// Check Frequency Params are Valid.
				CS_IS_VALID_CHECKED(FrequencyParams);
				// Check Group is Valid.
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check Sound is Valid.
				CS_IS_VALID(Sound)
				CS_IS_FLOAT_GREATER_THAN(VolumeMultiplier, 0.0f)
				CS_IS_FLOAT_GREATER_THAN(PitchMultiplier, 0.0f)
				// Check Frequency Params are Valid.
				CS_IS_VALID(FrequencyParams)
				// Check Group is Valid.
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
				return true;
			}

			UObject* FParams::GetObject() const { return Object.IsValid() ? Object.Get() : nullptr; }

			void FParams::Update()
			{
				FrequencyParams.Update();
			}

			void FParams::Reset()
			{
				Sound.Reset();
				FrequencyParams.Reset();
				Object = nullptr;
				Group = EMCsUpdateGroup::Get().GetMAX();
			}
		}
	}
}

#define ParamsType NCsSound::NSpawn::NParams::FParams
void FCsSound_Spawn_Params::CopyToParams(ParamsType* Params) const
{
#undef ParamsType

	Params->Sound = Sound;
	Params->VolumeMultiplier = VolumeMultiplier;
	Params->PitchMultiplier = PitchMultiplier;
	Params->Object = Object;
	FrequencyParams.CopyToParamsAsValue(Params->GetFrequencyParamsPtr());
	Params->Group = Group;
}

bool FCsSound_Spawn_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Sound is Valid
	CS_IS_VALID(Sound)
	CS_IS_FLOAT_GREATER_THAN(VolumeMultiplier, 0.0f)
	CS_IS_FLOAT_GREATER_THAN(PitchMultiplier, 0.0f)
	// Check FrequencyParams is Valid
	CS_IS_VALID(FrequencyParams)
	// Check Group is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
	return true;
}

void FCsSound_Spawn_Params::Update()
{
	FrequencyParams.Update();
}