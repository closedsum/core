// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Params/Tracking/CsParams_Projectile_Tracking.h"

// Library
#include "Library/CsLibrary_Valid.h"

// ProjectileTrackingDestination
#pragma region

namespace NCsProjectileTrackingDestination
{
	namespace Ref
	{
		typedef EMCsProjectileTrackingDestination EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Object);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Bone);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Location);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileTrackingDestination_MAX, "MAX");
	}
}

namespace NCsProjectile
{
	namespace NTracking
	{
		namespace NDestination
		{
			namespace Ref
			{
				typedef EMDestination EnumMapType;

				CSPRJ_API CS_ADD_TO_ENUM_MAP(Object);
				CSPRJ_API CS_ADD_TO_ENUM_MAP(Bone);
				CSPRJ_API CS_ADD_TO_ENUM_MAP(Location);
				CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDestination_MAX, "MAX");
			}
		}
	}
}

#pragma endregion ProjectileTrackingDestination

// FCsProjectile_TrackingParams
#pragma region

#define ParamsType NCsProjectile::NTracking::FParams

void FCsProjectile_TrackingParams::CopyToParams(ParamsType* Params)
{
	typedef NCsProjectile::NTracking::EDestination DestinationType;

	Params->SetDestination((DestinationType*)(&Destination));
	Params->SetOffset(&Offset);
	Params->SetDelay(&Delay);
	Params->SetDuration(&Duration);
	Params->SetRotationRate(&RotationRate);
}

void FCsProjectile_TrackingParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsProjectile::NTracking::EDestination DestinationType;

	Params->SetDestination((DestinationType)Destination);
	Params->SetOffset(Offset);
	Params->SetDelay(Delay);
	Params->SetDuration(Duration);
	Params->SetRotationRate(RotationRate);
}

#undef ParamsType

bool FCsProjectile_TrackingParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileTrackingDestination, Destination)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Delay, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Duration, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(RotationRate, 0.0f)
	return true;
}

bool FCsProjectile_TrackingParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsProjectileTrackingDestination, ECsProjectileTrackingDestination, Destination)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Delay, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Duration, 0.0f)
	CS_IS_FLOAT_GREATER_THAN(RotationRate, 0.0f)
	return true;
}

namespace NCsProjectile
{
	namespace NTracking
	{
		bool FParams::IsValidChecked(const FString& Context) const
		{
			typedef NCsProjectile::NTracking::EMDestination DestinationMapType;

			CS_IS_ENUM_VALID_CHECKED(DestinationMapType, GetDestination())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetDelay(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetDuration(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRotationRate(), 0.0f)
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
		{
			typedef NCsProjectile::NTracking::EDestination DestinationType;
			typedef NCsProjectile::NTracking::EMDestination DestinationMapType;

			CS_IS_ENUM_VALID(DestinationMapType, DestinationType, GetDestination())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetDelay(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetDuration(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN(GetRotationRate(), 0.0f)
			return true;
		}
	}
}

#pragma endregion FCsProjectile_TrackingParams