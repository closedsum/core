// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
#include "Types/CsTypes_Projectile_Tracking.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsParams_Projectile_Tracking.generated.h"

// FCsProjectile_TrackingParams
#pragma region

// NCsProjectile::NTracking::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NTracking, FParams)

/**
* Describes any information related a Projectile Tracking (another object, bone, location, ... etc).
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_TrackingParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes what is being Tracked. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking")
	ECsProjectileTrackingDestination Destination;

	/** Whether to reacquire the Destination if the Destination is "Lost". 
		A Destination is typically "Lost" if it refers to an Object or Bone and it
		is no longer valid. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking")
	bool bReacquireDestination;

	/** Offset applied to location of what is being Tracked. 
		If Destination == ECsProjectileTrackingDestination::Bone,
			the offset is applied in the direction of the Bone's world space orientation. 
			(i.e. Offset.X = Forward, Offset.Y = Right, Offset.Z = Up) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking")
	FVector3f Offset;

	/** Time before Tracking starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Delay;

	/** How long the Tracking is active for.
		If Duration == 0.0f, then the Tracking is forever / indefinite. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Duration;

	/** The speed in degrees per second at which the Projectile will rotate toward what is being tracked. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float RotationRate;

	/** Minimum Dot product between the current direction of the Projectile (velocity) and the direction to the destination (target)
		for Tracking to happen. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking", meta = (UIMin = "-1.0", ClampMin = "-1.0", UIMax = "1.0", ClampMax = "1.0"))
	float MinDotThreshold;

	/** Maximum Dot product between the current direction of the Projectile (velocity) and the direction to the destination (target)
		before using the Pitch when rotating toward the destination.
		This is useful to prevent a Projectile from adjusting along the Z when Tracking toward the destination.
		NOTE: For now, this is done by ignoring the Z value in the direction to the destination. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking", meta = (UIMin = "-1.0", ClampMin = "-1.0", UIMax = "1.0", ClampMax = "1.0"))
	float MaxDotBeforeUsingPitch;

	FCsProjectile_TrackingParams() :
		Destination(ECsProjectileTrackingDestination::Object),
		bReacquireDestination(false),
		Offset(0.0f),
		Delay(0.0f),
		Duration(0.0f),
		RotationRate(0.0f),
		MinDotThreshold(-1.0f),
		MaxDotBeforeUsingPitch(-1.0f)
	{
	}

#define ParamsType NCsProjectile::NTracking::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NTracking
	{
		/**
		* Describes any information related a Projectile Tracking (another object, bone, location, ... etc).
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FParams
		{
		#define DestinationType NCsProjectile::NTracking::EDestination

		private:

			/** Describes what is being Tracked. */
			CS_DECLARE_MEMBER_WITH_PROXY(Destination, DestinationType)

			/** Whether to reacquire the Destination if the Destination is "Lost". 
				A Destination is typically "Lost" if it refers to an Object or Bone and it
				is no longer valid. */
			CS_DECLARE_MEMBER_WITH_PROXY(bReacquireDestination, bool)

			/** Offset applied to location of what is being Tracked. 
				If Destination == ECsProjectileTrackingDestination::Bone,
					the offset is applied in the direction of the Bone's world space orientation. 
					(i.e. Offset.X = Forward, Offset.Y = Right, Offset.Z = Up) */
			CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector3f)

			/** Time before Tracking starts. */
			CS_DECLARE_MEMBER_WITH_PROXY(Delay, float)

			/** How long the Tracking is active for.
				If Duration == 0.0f, then the Tracking is forever / indefinite. */
			CS_DECLARE_MEMBER_WITH_PROXY(Duration, float)

			/** The speed in degrees per second at which the Projectile will rotate toward what is being tracked. */
			CS_DECLARE_MEMBER_WITH_PROXY(RotationRate, float)

			/** Minimum Dot product between the current direction of the Projectile (velocity) and the direction to the destination (target)
				for Tracking to happen. */
			CS_DECLARE_MEMBER_WITH_PROXY(MinDotThreshold, float)

			/** Maximum Dot product between the current direction of the Projectile (velocity) and the direction to the destination (target)
				before using the Pitch when rotating toward the destination.
				This is useful to prevent a Projectile from adjusting along the Z when Tracking toward the destination.
				NOTE: For now, this is done by ignoring the Z value in the direction to the destination. */
			CS_DECLARE_MEMBER_WITH_PROXY(MaxDotBeforeUsingPitch, float)

		public:

			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Destination, DestinationType::Object),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bReacquireDestination, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Delay, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Duration, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(RotationRate, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(MinDotThreshold, -1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxDotBeforeUsingPitch, -1.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(Destination);
				CS_CTOR_SET_MEMBER_PROXY(bReacquireDestination);
				CS_CTOR_SET_MEMBER_PROXY(Offset);
				CS_CTOR_SET_MEMBER_PROXY(Delay);
				CS_CTOR_SET_MEMBER_PROXY(Duration);
				CS_CTOR_SET_MEMBER_PROXY(RotationRate);
				CS_CTOR_SET_MEMBER_PROXY(MinDotThreshold);
				CS_CTOR_SET_MEMBER_PROXY(MaxDotBeforeUsingPitch);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Destination, DestinationType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bReacquireDestination, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector3f)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Delay, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Duration, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(RotationRate, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinDotThreshold, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxDotBeforeUsingPitch, float)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

		#undef DestinationType
		};
	}
}

#pragma endregion FCsProjectile_TrackingParams