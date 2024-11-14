// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/CsTypes_Library_FX.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Actor
#include "GameFramework/Actor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Library_FX)

using LogClassType = NCsFX::FLog;

// FXSpawnFrequency
#pragma region

namespace NCsFXSpawnFrequency
{
	namespace Ref
	{
		typedef EMCsFXSpawnFrequency EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(Once);
		CSFX_API CS_ADD_TO_ENUM_MAP(Count);
		CSFX_API CS_ADD_TO_ENUM_MAP(TimeCount);
		CSFX_API CS_ADD_TO_ENUM_MAP(TimeInterval);
		CSFX_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXSpawnFrequency_MAX, "MAX");
	}

	CSFX_API const uint8 MAX = (uint8)Type::ECsFXSpawnFrequency_MAX;
}

namespace NCsFX
{
	namespace NSpawn
	{
		namespace NFrequency
		{
			namespace Ref
			{
				typedef EMFrequency EnumMapType;

				CSFX_API CS_ADD_TO_ENUM_MAP(Once);
				CSFX_API CS_ADD_TO_ENUM_MAP(Count);
				CSFX_API CS_ADD_TO_ENUM_MAP(TimeCount);
				CSFX_API CS_ADD_TO_ENUM_MAP(TimeInterval);
				CSFX_API CS_ADD_TO_ENUM_MAP(Infinite);
				CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFrequency_MAX, "MAX");
			}

			CSFX_API const uint8 MAX = (uint8)EFrequency::EFrequency_MAX;
		}
	}
}

#pragma endregion FXSpawnFrequency

// FCsFX_Spawn_FrequencyParams
#pragma region

namespace NCsFX_Spawn_FrequenceParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Type, FrequencyType);
		CS_THIS_COPY_TO_PROXY(Params, Delay);
		CS_THIS_COPY_TO_PROXY(Params, Count);
		CS_THIS_COPY_TO_PROXY(Params, Interval);
		CS_THIS_COPY_TO_PROXY(Params, Time);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Type, FrequencyType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Delay);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Count);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Interval);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Time);
	}
}

CS_DEFINE_STATIC_LOG_WARNING(FCsFX_Spawn_FrequencyParams, LogClassType::Warning);

bool FCsFX_Spawn_FrequencyParams::IsValidChecked(const FString& Context) const
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
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsFXSpawnFrequency::Count."), *Context);
		checkf(Interval >= 0.0f, TEXT("%s: Interval MUST be >= 0.0f if Type == ECsFXSpawnFrequency::Count."), *Context);
	}
	// TimeCount
	else
	if (Type == FrequencyType::TimeCount)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsFXSpawnFrequency::TimeCount."), *Context);
	}
	// TimeInterval
	else
	if (Type == FrequencyType::TimeInterval)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsFXSpawnFrequency::TimeInterval."), *Context);
	}
	// Infinite
	else
	if (Type == FrequencyType::Infinite)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsFXSpawnFrequency::Infinite."), *Context);
	}
	return true;
}

bool FCsFX_Spawn_FrequencyParams::IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING_COMMENT) const
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
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsFXSpawnFrequency::Count."), *Context));
			return false;
		}

		if (Interval < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be >= 0.0f if Type == ECsFXSpawnFrequency::Count."), *Context));
			return false;
		}
	}
	// TimeCount
	else
	if (Type == FrequencyType::TimeCount)
	{
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsFXSpawnFrequency::TimeCount."), *Context));
			return false;
		}
	}
	// TimeInterval
	else
	if (Type == FrequencyType::TimeInterval)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsFXSpawnFrequency::TimeInterval."), *Context));
			return false;
		}
	}
	// Infinite
	else
	if (Type == FrequencyType::Infinite)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsFXSpawnFrequency::Infinite."), *Context));
			return false;
		}
	}
	return true;
}

float FCsFX_Spawn_FrequencyParams::CalculateTotalTime() const
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

void FCsFX_Spawn_FrequencyParams::Reset()
{
	Type = FrequencyType::Once;
	Delay = 0.0f;
	Count = 0;
	Interval = 0.0f;
	Time = 0.0f;
}

void FCsFX_Spawn_FrequencyParams::Update()
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

void FCsFX_Spawn_FrequencyParams::OnPostEditChange()
{
	Update();
}

namespace NCsFX
{
	namespace NSpawn
	{
		namespace NParams
		{
			CS_DEFINE_STATIC_LOG_WARNING(FFrequency, LogClassType::Warning);

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

			bool FFrequency::IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING_COMMENT) const
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
		}
	}
}

#pragma endregion FCsFX_Spawn_FrequencyParams

namespace NCsFX
{
	namespace NSpawn
	{
		namespace NParams
		{
			CS_DEFINE_STATIC_LOG_WARNING(FParams, LogClassType::Warning);

			bool FParams::IsValidChecked(const FString& Context) const
			{
				CS_IS_VALID_CHECKED(FX);
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Delay, 0.0f)
				CS_IS_VALID_CHECKED(FrequencyParams);
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, Group)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
			{
				CS_IS_VALID(FX)
				CS_IS_FLOAT_GREATER_THAN_CHECKED(Delay, 0.0f)
				CS_IS_VALID(FrequencyParams)
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
				return true;
			}

			AActor* FParams::GetActor() const { return Actor.IsValid() ? Actor.Get() : nullptr; }

			void FParams::Update()
			{
				FrequencyParams.Update();
			}

			void FParams::Reset()
			{
				FX.Reset();
				Actor = nullptr;
				Delay = 0.0f;
				FrequencyParams.Reset();		
				Group = EMCsUpdateGroup::Get().GetMAX();
			}
		}
	}
}

namespace NCsFX_Spawn_Params
{
	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		Params->FX = This->FX;
		Params->Delay = This->Delay;
		Params->Actor = This->Actor;
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, FrequencyParams);
		Params->Group = This->Group;
	}
}

CS_DEFINE_STATIC_LOG_WARNING(FCsFX_Spawn_Params, LogClassType::Warning);

bool FCsFX_Spawn_Params::IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING_COMMENT) const
{
	CS_IS_VALID(FX)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Delay, 0.0f)
	CS_IS_VALID(FrequencyParams)
	CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
	return true;
}

void FCsFX_Spawn_Params::Update()
{
	FrequencyParams.Update();
}

namespace NCsFX
{
	namespace NLibrary
	{
		namespace NSetArrayFloatChecked
		{
			bool FPayload::IsValidChecked(const FString& Context) const
			{
				CS_IS_INT_GREATER_THAN_CHECKED(Count, 0)
				CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)
				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Indices.Num(), Count)
				CS_IS_INT_GREATER_THAN_CHECKED(Stride, 0)
				CS_IS_TARRAY_EMPTY_CHECKED(Values, float)

				const int32 MinValuesSize = Stride * Count;

				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Values.Num(), MinValuesSize)
				return true;
			}
		}
	}
}