// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_ProjectileWeapon_Spread.generated.h"

// ProjectileWeaponSpreadShape
#pragma region

/**
* Describes the Spread Shape for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponSpreadShape : uint8
{
	/** The "area" is the line Right and Left vectors
		with respect to the the default Launch Direction of the Projectile. */
	Line								UMETA(DisplayName = "Line"),
	/** The area is the extents Right and Left vectors
		with respect to the default Launch Direction of the Projectile and World Up vector. */
	Rectangle							UMETA(DisplayName = "Rectangle"),
	/** The area is a radius around the default Launch Direction of the Projectile.
		The area is represented by Right vector with respect to the default Launch Direction and 
		World Up vector. */
	Circle								UMETA(DisplayName = "Circle"),
	ECsProjectileWeaponSpreadShape_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponSpreadShape : public TCsEnumMap<ECsProjectileWeaponSpreadShape>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponSpreadShape, ECsProjectileWeaponSpreadShape)
};

namespace NCsProjectileWeaponSpreadShape
{
	typedef ECsProjectileWeaponSpreadShape Type;

	namespace Ref
	{
		extern CSWP_API const Type Line;
		extern CSWP_API const Type Rectangle;
		extern CSWP_API const Type Circle;
		extern CSWP_API const Type ECsProjectileWeaponSpreadShape_MAX;
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			/**
			* Describes the Spread Shape for a Projectile Weapon.
			*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
			*/
			enum class EShape : uint8
			{
				/** The "area" is the line Right and Left vectors
					with respect to the the default Launch Direction of the Projectile. */
				Line,
				/** The area is the extents Right and Left vectors
					with respect to the default Launch Direction of the Projectile and World Up vector. */
				Rectangle,
				/** The area is a radius around the default Launch Direction of the Projectile.
					The area is represented by Right vector with respect to the default Launch Direction and 
					World Up vector. */
				Circle,
				EShape_MAX
			};

			struct CSWP_API EMShape : public TCsEnumMap<EShape>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMShape, EShape)
			};

			namespace NShape
			{
				namespace Ref
				{
					typedef EShape Type;

					extern CSWP_API const Type Line;
					extern CSWP_API const Type Rectangle;
					extern CSWP_API const Type Circle;
					extern CSWP_API const Type EShape_MAX;
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadShape

// ProjectileWeaponSpreadShapeDistribution
#pragma region

/**
* Describes the distribution of start locations within a Spread Shape for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponSpreadShapeDistribution : uint8
{
	Random											UMETA(DisplayName = "Random"),
	ECsProjectileWeaponSpreadShapeDistribution_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponSpreadShapeDistribution : public TCsEnumMap<ECsProjectileWeaponSpreadShapeDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponSpreadShapeDistribution, ECsProjectileWeaponSpreadShapeDistribution)
};

namespace NCsProjectileWeaponSpreadShapeDistribution
{
	typedef ECsProjectileWeaponSpreadShapeDistribution Type;

	namespace Ref
	{
		extern CSWP_API const Type Random;
		extern CSWP_API const Type ECsProjectileWeaponSpreadShapeDistribution_MAX;
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NShape
			{
				/**
				* Describes the distribution of start locations within a Spread Shape for a Projectile Weapon.
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				enum class EDistribution : uint8
				{
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

						extern CSWP_API const Type Random;
						extern CSWP_API const Type EDistribution_MAX;
					}

					FORCEINLINE bool ShouldPrecalculate(const EDistribution& InType) { return InType != EDistribution::Random; }
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadShapeDistribution

// ProjectileWeaponSpreadShapeAxis
#pragma region

/**
* Describes the Axis by which the start locations within a Spread Shape are Distributed for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponSpreadShapeAxis: uint8
{
	/** Up Vector */
	Up										UMETA(DisplayName = "Up"),
	/** In the direction of the Projectile is fired. */
	LaunchDirection							UMETA(DisplayName = "Launch Direction"),
	ECsProjectileWeaponSpreadShapeAxis_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponSpreadShapeAxis : public TCsEnumMap<ECsProjectileWeaponSpreadShapeAxis>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponSpreadShapeAxis, ECsProjectileWeaponSpreadShapeAxis)
};

namespace NCsProjectileWeaponSpreadShapeAxis
{
	typedef ECsProjectileWeaponSpreadShapeAxis Type;

	namespace Ref
	{
		extern CSWP_API const Type Up;
		extern CSWP_API const Type LaunchDirection;
		extern CSWP_API const Type ECsProjectileWeaponSpreadShapeAxis_MAX;
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NShape
			{
				/**
				* Describes the distribution of start locations within a Spread Shape for a Projectile Weapon.
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				enum class EAxis : uint8
				{
					/** Up Vector */
					Up,
					/** In the direction of the Projectile is fired. */
					LaunchDirection,
					EAxis_MAX
				};

				struct CSWP_API EMAxis : public TCsEnumMap<EAxis>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMAxis, EAxis)
				};

				namespace NAxis
				{
					namespace Ref
					{
						typedef EAxis Type;

						extern CSWP_API const Type Up;
						extern CSWP_API const Type LaunchDirection;
						extern CSWP_API const Type EAxis_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadShapeAxis

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
		(i.e. If the Spread Angle is 60, then the Projectiles are fired at angles between
		      60 and -60 degrees from the Launch Direction, usually the Weapon Forward.) */
	UniformMinMax						UMETA(DisplayName = "Uniform: Min / Max"),
	/** The Spread Angle is represented by a Min and a Max angle from the Launch Direction.
		(i.e. If the Min Angle is -20 and the Max Angle is 60, then the Projectiles are fired at
				angles between -20 and 60 degrees from the Launch Direction, usually the Weapon Forward). */
	RangeMinMax							UMETA(DisplayName = "Range: Min / Max"),
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
		extern CSWP_API const Type UniformMinMax;
		extern CSWP_API const Type RangeMinMax;
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
					(i.e. If the Spread Angle is 60, then the Projectiles are fired at angles between
						  60 and -60 degrees from the Launch Direction, usually the Weapon Forward.) */
				UniformMinMax,
				/** The Spread Angle is represented by a Min and a Max angle from the Launch Direction. 
					(i.e. If the Min Angle is -20 and the Max Angle is 60, then the Projectiles are fired at
						  angles between -20 and 60 degrees from the Launch Direction, usually the Weapon Forward). */
				RangeMinMax,
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
					extern CSWP_API const Type UniformMinMax;
					extern CSWP_API const Type RangeMinMax;
					extern CSWP_API const Type EAngle_MAX;
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadAngle

// ProjectileWeaponSpreadAngleDistribution
#pragma region

/**
* Describes the direction of projectiles fired from a Projectile Weapon using
*  the Spread Angle and Spread Angle Type (ECsProjectileWeaponSpreadAngle or NCsWeapon::NProjectile::NSpread::EAngle).
*  The distribution is for a "shot" of projectiles and reset / determined again for each shot.
*  If ProjectilesPerShot.Interval is 0.0f, then ORDERED distributions are the SAME.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponSpreadAngleDistribution : uint8
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
		usually the Weapon Forward. 
		NOTE: Spread Angle Type MUST = ECsProjectileWeaponSpreadAngle::UniformMinMax. */
	Random											UMETA(DisplayName = "Random"),
	ECsProjectileWeaponSpreadAngleDistribution_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponSpreadAngleDistribution : public TCsEnumMap<ECsProjectileWeaponSpreadAngleDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponSpreadAngleDistribution, ECsProjectileWeaponSpreadAngleDistribution)
};

namespace NCsProjectileWeaponSpreadAngleDistribution
{
	typedef ECsProjectileWeaponSpreadAngleDistribution Type;

	namespace Ref
	{
		extern CSWP_API const Type OrderedClockwise;
		extern CSWP_API const Type OrderedCounterClockwise;
		extern CSWP_API const Type OrderedPingPongClockwise;
		extern CSWP_API const Type OrderedPingPongCounterClockwise;
		extern CSWP_API const Type Shuffle;
		extern CSWP_API const Type Random;
		extern CSWP_API const Type ECsProjectileWeaponSpreadAngleDistribution_MAX;
	}

	FORCEINLINE bool ShouldPrecalculate(const Type& InType) { return InType != Type::Random; }
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NAngle
			{
				/**
				* Describes the direction of projectiles fired from a Projectile Weapon using
				*  the Spread Angle and Spread Angle Type (NCsWeapon::NProjectile::NSpread::EAngle).
				*  The distribution is for a "shot" of projectiles and reset / determined again for each shot.
				*  If ProjectilesPerShot.Interval is 0.0f, then ORDERED distributions are the SAME.
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
						usually the Weapon Forward. 
						NOTE: Spread Angle Type MUST = NCsWeapon::NProjectile::NSpread::EAngle::MinMax. */
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

					FORCEINLINE bool ShouldPrecalculate(const EDistribution& InType) { return InType != EDistribution::Random; }
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadAngleDistribution

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			struct CSWP_API FLibrary
			{
			public:

			#define ShapeType NCsWeapon::NProjectile::NSpread::EShape
			#define DistributionType NCsWeapon::NProjectile::NSpread::NShape::EDistribution

				static FVector GetRandomOffsetChecked(const FString& Context, const ShapeType& Shape, const FVector& Extents, const DistributionType& Distribution);

			#undef ShapeType
			#undef DistributionType

			#define SpreadAngleType NCsWeapon::NProjectile::NSpread::EAngle
			#define DistributionType NCsWeapon::NProjectile::NSpread::NAngle::EDistribution

				static void SetAnglesChecked(const FString& Context, const int32& Count, const SpreadAngleType& AngleType, const float& Angle, const DistributionType& Distribution, TArray<float>& OutAngles);

				static float GetRandomAngleChecked(const FString& Context, const SpreadAngleType& AngleType, const float& Angle, const DistributionType& Distribution);

				static float GetRandomAngleChecked(const FString& Context, const SpreadAngleType& AngleType, const float& Min, const float& Max, const DistributionType& Distribution);

			#undef SpreadAngleType
			#undef DistributionType
			};
		}
	}
}