// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsParams_Projectile_Tracking.generated.h"

// ProjectileTrackingDestination
#pragma region

/**
* Describes the Destination a Projectile is Tracking.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
UENUM(BlueprintType)
enum class ECsProjectileTrackingDestination : uint8
{
	/** AActor or USceneComponent */
	Object									UMETA(DisplayName = "Object"),
	/** Bone on a USkeletalMeshComponent */
	Bone									UMETA(DisplayName = "Bone"),
	/** World Space position */
	Location								UMETA(DisplayName = "Location"),
	ECsProjectileTrackingDestination_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileTrackingDestination : public TCsEnumMap<ECsProjectileTrackingDestination>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileTrackingDestination, ECsProjectileTrackingDestination)
};

namespace NCsProjectileTrackingDestination
{
	typedef ECsProjectileTrackingDestination Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Object;
		extern CSPRJ_API const Type Bone;
		extern CSPRJ_API const Type Location;
		extern CSPRJ_API const Type ECsProjectileTrackingDestination_MAX;
	}
}

namespace NCsProjectile
{
	namespace NTracking
	{
		/**
		* Describes the Destination a Projectile is Tracking.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		enum class EDestination : uint8
		{
			/** AActor or USceneComponent */
			Object,
			/** Bone on a USkeletalMeshComponent */
			Bone,
			/** World Space position */
			Location,
			EDestination_MAX
		};

		struct CSPRJ_API EMDestination : public TCsEnumMap<EDestination>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDestination, EDestination)
		};

		namespace NDestination
		{
			namespace Ref
			{
				typedef EDestination Type;

				extern CSPRJ_API const Type Object;
				extern CSPRJ_API const Type Bone;
				extern CSPRJ_API const Type Location;
				extern CSPRJ_API const Type EDestination_MAX;
			}
		}
	}
}

#pragma endregion ProjectileTrackingDestination

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

	/** Offset applied to location of what is being Tracked. 
		If Destination == ECsProjectileTrackingDestination::Bone,
			the offset is applied in the direction of the Bone's world space orientation. 
			(i.e. Offset.X = Forward, Offset.Y = Right, Offset.Z = Up) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CImpl|Projectile|Tracking")
	FVector Offset;

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

	FCsProjectile_TrackingParams() :
		Destination(ECsProjectileTrackingDestination::Object),
		Offset(0.0f),
		Delay(0.0f),
		Duration(0.0f),
		RotationRate(0.0f)
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

			/** Offset applied to location of what is being Tracked. 
				If Destination == ECsProjectileTrackingDestination::Bone,
					the offset is applied in the direction of the Bone's world space orientation. 
					(i.e. Offset.X = Forward, Offset.Y = Right, Offset.Z = Up) */
			CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector)

			/** Time before Tracking starts. */
			CS_DECLARE_MEMBER_WITH_PROXY(Delay, float)

			/** How long the Tracking is active for.
				If Duration == 0.0f, then the Tracking is forever / indefinite. */
			CS_DECLARE_MEMBER_WITH_PROXY(Duration, float)

			/** The speed in degrees per second at which the Projectile will rotate toward what is being tracked. */
			CS_DECLARE_MEMBER_WITH_PROXY(RotationRate, float)

		public:

			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Destination, DestinationType::Object),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Delay, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Duration, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(RotationRate, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(Destination);
				CS_CTOR_SET_MEMBER_PROXY(Offset);
				CS_CTOR_SET_MEMBER_PROXY(Delay);
				CS_CTOR_SET_MEMBER_PROXY(Duration);
				CS_CTOR_SET_MEMBER_PROXY(RotationRate);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Destination, DestinationType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Delay, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Duration, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(RotationRate, float)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

		#undef DestinationType
		};
	}
}

#pragma endregion FCsProjectile_TrackingParams