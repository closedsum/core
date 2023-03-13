// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Projectile_Tracking.generated.h"

// ProjectileTrackingState
#pragma region

namespace NCsProjectile
{
	namespace NTracking
	{
		enum class EState : uint8
		{
			Inactive,
			Delay,
			Active
		};
	}
}

#pragma endregion ProjectileTrackingState

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
	Custom									UMETA(DisplayName = "Custom"),
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
		extern CSPRJ_API const Type Custom;
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
			Custom,
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
				extern CSPRJ_API const Type Custom;
				extern CSPRJ_API const Type EDestination_MAX;
			}
		}
	}
}

#pragma endregion ProjectileTrackingDestination

// ProjectileTrackingDestinationFlag
#pragma region

namespace NCsProjectile
{
	namespace NTracking
	{
		namespace NDestination
		{
			enum class EFlag : uint32
			{
				Reacquire = 1 << 0
			};

			namespace NFlag
			{
				FORCEINLINE void SetReacquire(uint32& Mask) { Mask = (uint32)EFlag::Reacquire; }
				FORCEINLINE void MarkReacquire(uint32& Mask) { CS_SET_BITFLAG(Mask, EFlag::Reacquire); }
				FORCEINLINE void ClearReacquire(uint32& Mask) { CS_CLEAR_BITFLAG(Mask, EFlag::Reacquire); }
				FORCEINLINE bool HasReacquire(const uint32& Mask) { return CS_TEST_BITFLAG(Mask, EFlag::Reacquire); }
			}
		}
	}
}

#pragma endregion ProjectileTrackingDestinationFlag