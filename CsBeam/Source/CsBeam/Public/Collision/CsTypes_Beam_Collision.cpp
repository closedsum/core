// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Collision/CsTypes_Beam_Collision.h"
#include "CsBeam.h"

// Library
#include "Library/CsLibrary_Valid.h"

// BeamCollisionFrequency
#pragma region

namespace NCsBeamCollisionFrequency
{
	namespace Ref
	{
		typedef EMCsBeamCollisionFrequency EnumMapType;

		CSBEAM_API CS_ADD_TO_ENUM_MAP(Once);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Count);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(TimeCount);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(TimeInterval);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamCollisionFrequency_MAX, "MAX");
	}

	CSBEAM_API const uint8 MAX = (uint8)Type::ECsBeamCollisionFrequency_MAX;
}

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NFrequency
		{
			namespace Ref
			{
				typedef EMFrequency EnumMapType;

				CSBEAM_API CS_ADD_TO_ENUM_MAP(Once);
				CSBEAM_API CS_ADD_TO_ENUM_MAP(Count);
				CSBEAM_API CS_ADD_TO_ENUM_MAP(TimeCount);
				CSBEAM_API CS_ADD_TO_ENUM_MAP(TimeInterval);
				CSBEAM_API CS_ADD_TO_ENUM_MAP(Infinite);
				CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFrequency_MAX, "MAX");
			}
		}
	}
}

#pragma endregion BeamCollisionFrequency

// FCsBeamCollisionFrequencyParams
#pragma region

#define ParamsType NCsBeam::NCollision::NParams::FFrequency

void FCsBeamCollisionFrequencyParams::CopyToParams(ParamsType* Params)
{
	typedef NCsBeam::NCollision::EFrequency FrequencyType;

	Params->SetType((FrequencyType*)&Type);
	Params->SetCount(&Count);
	Params->SetInterval(&Interval);
}

void FCsBeamCollisionFrequencyParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsBeam::NCollision::EFrequency FrequencyType;

	Params->SetType((FrequencyType)Type);
	Params->SetCount(Count);
	Params->SetInterval(Interval);
}

#undef ParamsType

bool FCsBeamCollisionFrequencyParams::IsValidChecked(const FString& Context) const
{
	typedef ECsBeamCollisionFrequency FrequencyType;

	// Once
	if (Type == FrequencyType::Once)
	{
		// No checks
	}
	// Count
	else
	if (Type == FrequencyType::Count)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsBeamCollisionFrequency::Count."), *Context);
	}
	// TimeCount
	else
	if (Type == FrequencyType::TimeCount)
	{
		checkf(Count >= 1, TEXT("%s: Count MUST be >= 1 if Type == ECsBeamCollisionFrequency::TimeCount."), *Context);
	}
	// TimeInterval
	else
	if (Type == FrequencyType::TimeInterval)
	{
		checkf(Interval > 0.0f, TEXT("%s: Interval MUST be > 0.0f if Type == ECsBeamCollisionFrequency::TimeInterval."), *Context);
	}
	// Infinite
	else
	if (Type == FrequencyType::Infinite)
	{
		checkf(Interval >= 0.0f, TEXT("%s: Interval MUST be >= 0.0f if Type == ECsBeamCollisionFrequency::Infinite."), *Context);
	}
	return true;
}

bool FCsBeamCollisionFrequencyParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	typedef ECsBeamCollisionFrequency FrequencyType;

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
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsBeamCollisionFrequency::Count."), *Context));
			return false;
		}
	}
	// TimeCount
	else
	if (Type == FrequencyType::TimeCount)
	{
		if (Count < 1)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Count MUST be >= 1 if Type == ECsBeamCollisionFrequency::TimeCount."), *Context));
			return false;
		}
	}
	// TimeInterval
	else
	if (Type == FrequencyType::TimeInterval)
	{
		if (Interval <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be > 0.0f if Type == ECsBeamCollisionFrequency::TimeInterval."), *Context));
			return false;
		}
	}
	// Infinite
	else
	if (Type == FrequencyType::Infinite)
	{
		if (Interval < 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Interval MUST be >= 0.0f if Type == ECsBeamCollisionFrequency::Infinite."), *Context));
			return false;
		}
	}
	return true;
}

void FCsBeamCollisionFrequencyParams::Reset()
{
	Type = ECsBeamCollisionFrequency::Once;
	Count = 0;
	Interval = 0.0f;
}

void FCsBeamCollisionFrequencyParams::Update(const float& Time)
{
	typedef ECsBeamCollisionFrequency FrequencyType;

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

void FCsBeamCollisionFrequencyParams::OnPostEditChange(const float& Time)
{
	Update(Time);
}

namespace NCsBeam
{
	namespace NCollision
	{
		namespace NParams
		{
			bool FFrequency::IsValidChecked(const FString& Context) const
			{
				typedef NCsBeam::NCollision::EFrequency FrequencyType;

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
				typedef NCsBeam::NCollision::EFrequency FrequencyType;

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

			void FFrequency::Reset()
			{
				typedef NCsBeam::NCollision::EFrequency FrequencyType;

				CS_RESET_MEMBER_WITH_PROXY(Type, FrequencyType::Once)
				CS_RESET_MEMBER_WITH_PROXY(Count, 0)
				CS_RESET_MEMBER_WITH_PROXY(Interval, 0.0f)
			}
		}
	}
}

#pragma endregion FCsBeamCollisionFrequencyParams