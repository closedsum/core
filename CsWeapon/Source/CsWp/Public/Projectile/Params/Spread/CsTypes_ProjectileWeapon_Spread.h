// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_ProjectileWeapon_Spread.generated.h"

// ProjectileWeaponSpreadAngle
#pragma region

/**
* Describes how the Spread Angle should be interpreted for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponSpreadAngle : uint8
{
	/** The angle between each projectile is the Spread Angle divide by the 
		number Projectiles per Shot. */
	DivideByCount						UMETA(DisplayName = "Divide by Count"),
	/** The Spread Angle is the angle between each projectile in a Shot.
		(i.e. if Projectiles per Shot is 3 and the Spread Angle is 60, then angle between
			  each Projectile is 60.) */
	AngleBetween						UMETA(DisplayName = "Angle Between"),
	/** The Spread Angle represents the absolute angle delta (+/-) from the Launch Direction.
		(i.e. If the Spread Angel is 60, then the Projectiles are fired at angles between
		      60 and -60 degrees from the Launch Direction, usually the Weapon Forward.) */
	MinMax								UMETA(DisplayName = "Min / Max"),
	ECsProjectileWeaponSpreadAngle_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponSpreadAngle : public TCsEnumMap<ECsProjectileWeaponSpreadAngle>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponSpreadAngle, ECsProjectileWeaponSpreadAngle)
};

namespace NCsProjectileWeaponSpreadAngle
{
	typedef ECsProjectileWeaponSpreadAngle Type;

	namespace Ref
	{
		extern CSWP_API const Type DivideByCount;
		extern CSWP_API const Type AngleBetween;
		extern CSWP_API const Type MinMax;
		extern CSWP_API const Type ECsProjectileWeaponSpreadAngle_MAX;
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			/**
			* Describes how the Spread Angle should be interpreted for a Projectile Weapon.
			*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
			*/
			enum class EAngle : uint8
			{
				/** The angle between each projectile the Spread Angle divide by the 
					number Projectiles per Shot. */
				DivideByCount,
				/** The Spread Angle is the angle between each projectile in a Shot.
					(i.e. if Projectiles per Shot is 3 and the Spread Angle is 60, then angle between
						  each Projectile is 60.) */
				AngleBetween,
				/** The Spread Angle represents the absolute angle delta (+/-) from the Launch Direction.
					(i.e. If the Spread Angel is 60, then the Projectiles are fired at angles between
						  60 and -60 degrees from the Launch Direction, usually the Weapon Forward.) */
				MinMax,
				EAngle_MAX
			};

			struct CSWP_API EMAngle : public TCsEnumMap<EAngle>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMAngle, EAngle)
			};

			namespace NAngle
			{
				namespace Ref
				{
					typedef EAngle Type;

					extern CSWP_API const Type DivideByCount;
					extern CSWP_API const Type AngleBetween;
					extern CSWP_API const Type MinMax;
					extern CSWP_API const Type EAngle_MAX;
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadAngle


// ProjectileWeaponSpreadDistribution
#pragma region

/**
* Describes the direction of projectiles fired from a Projectile Weapon using
*  the Spread Angle and Spread Angle Type (ECsProjectileWeaponSpreadAngle or NCsWeapon::NProjectile::NSpread::EAngle).
*  The distribution is for a "shot" of projectiles and reset / determined again for each shot.
*  If TimeBetweenProjectilesPerShot is 0.0f, then ORDERED distributions are the SAME.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponSpreadDistribution : uint8
{
	/** Projectiles are spawned in order and clockwise from the default Launch Direction,
		usually the Weapon Forward. */
	OrderedClockwise								UMETA(DisplayName = "Ordered Clockwise"),
	/** Projectiles are spawned in order and counter-clockwise from the default Launch Direction,
		usually the Weapon Forward.  */
	OrderedCounterClockwise							UMETA(DisplayName = "Ordered Counter-Clockwise"),
	/** Projectiles are spawn in order and alternate from clockwise to counter-clockwise from the 
		default Launch Direction, usually the Weapon Forward. The clockwise direction is chosen first
		before counter-clockwise (i.e. c, cc, c, cc, c, cc, ... etc). */
	OrderedPingPongClockwise						UMETA(DisplayName = "Ordered Ping Ping Clockwise"),
	/** Projectiles are spawn in order and alternate from counter-clockwise to clockwise from the 
		default Launch Direction, usually the Weapon Forward. The counter-clockwise direction is chosen first
		before clockwise (i.e. cc, c, cc, c, cc, c, ... etc). */
	OrderedPingPongCounterClockwise					UMETA(DisplayName = "Ordered Ping Ping Counter-Clockwise"),
	/** Projectiles are spawned from a random shuffle of predetermined angles from the default
		Launch Direction, usually the Weapon Forward. */
	Shuffle											UMETA(DisplayName = "Shuffle"),
	/** Projectiles are spawned at random angles from the default Launch Direction, 
		usually the Weapon Forward. */
	Random											UMETA(DisplayName = "Random"),
	ECsProjectileWeaponSpreadDistribution_MAX		UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponSpreadDistribution : public TCsEnumMap<ECsProjectileWeaponSpreadDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponSpreadDistribution, ECsProjectileWeaponSpreadDistribution)
};

namespace NCsProjectileWeaponSpreadDistribution
{
	typedef ECsProjectileWeaponSpreadDistribution Type;

	namespace Ref
	{
		extern CSWP_API const Type OrderedClockwise;
		extern CSWP_API const Type OrderedCounterClockwise;
		extern CSWP_API const Type OrderedPingPongClockwise;
		extern CSWP_API const Type OrderedPingPongCounterClockwise;
		extern CSWP_API const Type Shuffle;
		extern CSWP_API const Type Random;
		extern CSWP_API const Type ECsProjectileWeaponSpreadDistribution_MAX;
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			/**
			* Describes the direction of projectiles fired from a Projectile Weapon using
			*  the Spread Angle and Spread Angle Type (ECsProjectileWeaponSpreadAngle or NCsWeapon::NProjectile::NSpread::EAngle).
			*  The distribution is for a "shot" of projectiles and reset / determined again for each shot.
			*  If TimeBetweenProjectilesPerShot is 0.0f, then ORDERED distributions are the SAME.
			*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
			*/
			enum class EDistribution : uint8
			{
				/** Projectiles are spawned in order and clockwise from the default Launch Direction,
					usually the Weapon Forward. */
				OrderedClockwise,
				/** Projectiles are spawned in order and counter-clockwise from the default Launch Direction,
					usually the Weapon Forward.  */
				OrderedCounterClockwise,
				/** Projectiles are spawn in order and alternate from clockwise to counter-clockwise from the 
					default Launch Direction, usually the Weapon Forward. The clockwise direction is chosen first
					before counter-clockwise (i.e. c, cc, c, cc, c, cc, ... etc). */
				OrderedPingPongClockwise,
				/** Projectiles are spawn in order and alternate from counter-clockwise to clockwise from the 
					default Launch Direction, usually the Weapon Forward. The counter-clockwise direction is chosen first
					before clockwise (i.e. cc, c, cc, c, cc, c, ... etc). */
				OrderedPingPongCounterClockwise,
				/** Projectiles are spawned from a random shuffle of predetermined angles from the default
					Launch Direction, usually the Weapon Forward. */
				Shuffle,
				/** Projectiles are spawned at random angles from the default Launch Direction, 
					usually the Weapon Forward. */
				Random,
				EDistribution_MAX
			};

			struct CSWP_API EMDistribution : public TCsEnumMap<EDistribution>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDistribution, EDistribution)
			};

			namespace NDistribution
			{
				namespace Ref
				{
					typedef EDistribution Type;

					extern CSWP_API const Type OrderedClockwise;
					extern CSWP_API const Type OrderedCounterClockwise;
					extern CSWP_API const Type OrderedPingPongClockwise;
					extern CSWP_API const Type OrderedPingPongCounterClockwise;
					extern CSWP_API const Type Shuffle;
					extern CSWP_API const Type Random;
					extern CSWP_API const Type EDistribution_MAX;
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadDistribution