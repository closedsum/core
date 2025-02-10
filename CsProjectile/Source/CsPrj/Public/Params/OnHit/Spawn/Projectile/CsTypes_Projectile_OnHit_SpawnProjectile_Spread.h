// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Projectile_OnHit_SpawnProjectile_Spread.generated.h"

// ProjectileOnHitSpawnProjectileSpreadShape
#pragma region

/**
* Describes the Spread Shape for a Projectile spawned On Hit from another Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
UENUM(BlueprintType)
enum class ECsProjectileOnHitSpawnProjectileSpreadShape : uint8
{
	/** The "area" is the line Right and Left vectors
		with respect to the movement Direction of the Projectile. */
	Line												UMETA(DisplayName = "Line"),
	/** The area is the extents Right and Left vectors
		with respect to the movement Direction of the Projectile and World Up vector. */
	Rectangle											UMETA(DisplayName = "Rectangle"),
	/** The area is a radius around the movement Direction of the Projectile.
		The area is represented by Right vector with respect to the movement Direction and 
		World Up vector. */
	Circle												UMETA(DisplayName = "Circle"),
	ECsProjectileOnHitSpawnProjectileSpreadShape_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileOnHitSpawnProjectileSpreadShape : public TCsEnumMap<ECsProjectileOnHitSpawnProjectileSpreadShape>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileOnHitSpawnProjectileSpreadShape, ECsProjectileOnHitSpawnProjectileSpreadShape)
};

namespace NCsProjectileOnHitSpawnProjectileSpreadShape
{
	typedef ECsProjectileOnHitSpawnProjectileSpreadShape Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Line;
		extern CSPRJ_API const Type Rectangle;
		extern CSPRJ_API const Type Circle;
		extern CSPRJ_API const Type ECsProjectileOnHitSpawnProjectileSpreadShape_MAX;
	}
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					/**
					* Describes the Spread Shape for a Projectile spawned On Hit from another Projectile.
					*  Projectile is an object that implements the interface: ICsProjectile.
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

					struct CSPRJ_API EMShape : public TCsEnumMap<EShape>
					{
						CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMShape, EShape)
					};

					namespace NShape
					{
						namespace Ref
						{
							typedef EShape Type;

							extern CSPRJ_API const Type Line;
							extern CSPRJ_API const Type Rectangle;
							extern CSPRJ_API const Type Circle;
							extern CSPRJ_API const Type EShape_MAX;
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileOnHitSpawnProjectileSpreadShape

// ProjectileOnHitSpawnProjectileSpreadShapeDistribution
#pragma region

/**
* Describes the distribution of start locations within a Spread Shape for a Projectile spawned
* OnHit from another Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
UENUM(BlueprintType)
enum class ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution : uint8
{
	Random															UMETA(DisplayName = "Random"),
	ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileOnHitSpawnProjectileSpreadShapeDistribution : public TCsEnumMap<ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileOnHitSpawnProjectileSpreadShapeDistribution, ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution)
};

namespace NCsProjectileOnHitSpawnProjectileSpreadShapeDistribution
{
	typedef ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Random;
		extern CSPRJ_API const Type ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution_MAX;
	}
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					namespace NShape
					{
						/**
						* Describes the distribution of start locations within a Spread Shape for a Projectile spawned
						* OnHit from another Projectile.
						*  Projectile is an object that implements the interface: ICsProjectile.
						*/
						enum class EDistribution : uint8
						{
							Random,
							EDistribution_MAX
						};

						struct CSPRJ_API EMDistribution : public TCsEnumMap<EDistribution>
						{
							CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDistribution, EDistribution)
						};

						namespace NDistribution
						{
							namespace Ref
							{
								typedef EDistribution Type;

								extern CSPRJ_API const Type Random;
								extern CSPRJ_API const Type EDistribution_MAX;
							}

							FORCEINLINE bool ShouldPrecalculate(const EDistribution& InType) { return InType != EDistribution::Random; }
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileOnHitSpawnProjectileSpreadShapeDistribution

// ProjectileOnHitSpawnProjectileSpreadAngle
#pragma region

/**
* Describes how the Spread Angle should be interpreted for a Projectile spawned OnHit
* from another Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
UENUM(BlueprintType)
enum class ECsProjectileOnHitSpawnProjectileSpreadAngle : uint8
{
	/** The angle between each projectile is the Spread Angle divide by the 
		number Projectiles per Spawn. */
	DivideByCount										UMETA(DisplayName = "Divide by Count"),
	/** The Spread Angle is the angle between each projectile in a Spawn.
		(i.e. if Projectiles per Spawn is 3 and the Spread Angle is 60, then angle between
			  each Projectile is 60.) */
	AngleBetween										UMETA(DisplayName = "Angle Between"),
	/** The Spread Angle represents the absolute angle delta (+/-) from the movement direction
		of the parent Projectile.
		(i.e. If the Spread Angel is 60, then the Projectiles are fired at angles between
		      60 and -60 degrees from the movement direction.) */
	MinMax												UMETA(DisplayName = "Min / Max"),
	ECsProjectileOnHitSpawnProjectileSpreadAngle_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileOnHitSpawnProjectileSpreadAngle : public TCsEnumMap<ECsProjectileOnHitSpawnProjectileSpreadAngle>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileOnHitSpawnProjectileSpreadAngle, ECsProjectileOnHitSpawnProjectileSpreadAngle)
};

namespace NCsProjectileOnHitSpawnProjectileSpreadAngle
{
	typedef ECsProjectileOnHitSpawnProjectileSpreadAngle Type;

	namespace Ref
	{
		extern CSPRJ_API const Type DivideByCount;
		extern CSPRJ_API const Type AngleBetween;
		extern CSPRJ_API const Type MinMax;
		extern CSPRJ_API const Type ECsProjectileOnHitSpawnProjectileSpreadAngle_MAX;
	}
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					/**
					* Describes how the Spread Angle should be interpreted for a Projectile spawned OnHit
					* from another Projectile.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					enum class EAngle : uint8
					{
						/** The angle between each projectile the Spread Angle divide by the 
							number Projectiles per Spawn. */
						DivideByCount,
						/** The Spread Angle is the angle between each projectile in a Spawn.
							(i.e. if Projectiles per Spawn is 3 and the Spread Angle is 60, then angle between
								  each Projectile is 60.) */
						AngleBetween,
						/** The Spread Angle represents the absolute angle delta (+/-) from the movement direction
							of the parent Projectile.
							(i.e. If the Spread Angel is 60, then the Projectiles are fired at angles between
								  60 and -60 degrees from the movement direction.) */
						MinMax,
						EAngle_MAX
					};

					struct CSPRJ_API EMAngle : public TCsEnumMap<EAngle>
					{
						CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMAngle, EAngle)
					};

					namespace NAngle
					{
						namespace Ref
						{
							typedef EAngle Type;

							extern CSPRJ_API const Type DivideByCount;
							extern CSPRJ_API const Type AngleBetween;
							extern CSPRJ_API const Type MinMax;
							extern CSPRJ_API const Type EAngle_MAX;
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadAngle

// ProjectileOnHitSpawnProjectileSpreadAngleDistribution
#pragma region

/**
* Describes the direction of projectiles fired from a Projectile On Hit using
*  the Spread Angle and Spread Angle Type (ECsProjectileOnHitSpawnProjectileSpreadAngle or 
*  NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EAngle).
*  The distribution is for a spawn of projectiles and reset / determined again for each spawn.
*  If TimeBetweenProjectilesPerSpawn is 0.0f, then ORDERED distributions are the SAME.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
UENUM(BlueprintType)
enum class ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution : uint8
{
	/** Projectiles are spawned in order and clockwise from the movement direction of the 
		parent Projectile. */
	OrderedClockwise												UMETA(DisplayName = "Ordered Clockwise"),
	/** Projectiles are spawned in order and counter-clockwise from the movement direction of the
		parent Projectile. */
	OrderedCounterClockwise											UMETA(DisplayName = "Ordered Counter-Clockwise"),
	/** Projectiles are spawn in order and alternate from clockwise to counter-clockwise from the 
		movement direction of the parent Projectile. The clockwise direction is chosen first
		before counter-clockwise (i.e. c, cc, c, cc, c, cc, ... etc). */
	OrderedPingPongClockwise										UMETA(DisplayName = "Ordered Ping Ping Clockwise"),
	/** Projectiles are spawn in order and alternate from counter-clockwise to clockwise from the 
		movement direction of the parent Projectile. The counter-clockwise direction is chosen first
		before clockwise (i.e. cc, c, cc, c, cc, c, ... etc). */
	OrderedPingPongCounterClockwise									UMETA(DisplayName = "Ordered Ping Ping Counter-Clockwise"),
	/** Projectiles are spawned from a random shuffle of predetermined angles from the
		movement direction of the parent Projectile. */
	Shuffle															UMETA(DisplayName = "Shuffle"),
	/** Projectiles are spawned at random angles from the movement direction of the parent
		Projectile. 
		NOTE: Spread Angle Type MUST = ECsProjectileOnHitSpawnProjectileSpreadAngle::MinMax. */
	Random															UMETA(DisplayName = "Random"),
	ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileOnHitSpawnProjectileSpreadAngleDistribution : public TCsEnumMap<ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileOnHitSpawnProjectileSpreadAngleDistribution, ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution)
};

namespace NCsProjectileOnHitSpawnProjectileSpreadAngleDistribution
{
	typedef ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution Type;

	namespace Ref
	{
		extern CSPRJ_API const Type OrderedClockwise;
		extern CSPRJ_API const Type OrderedCounterClockwise;
		extern CSPRJ_API const Type OrderedPingPongClockwise;
		extern CSPRJ_API const Type OrderedPingPongCounterClockwise;
		extern CSPRJ_API const Type Shuffle;
		extern CSPRJ_API const Type Random;
		extern CSPRJ_API const Type ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution_MAX;
	}

	FORCEINLINE bool ShouldPrecalculate(const Type& InType) { return InType != Type::Random; }
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					namespace NAngle
					{
						/**
						* Describes the direction of projectiles fired from a Projectile On Hit using
						*  the Spread Angle and Spread Angle Type (NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EAngle).
						*  The distribution is for a spawn of projectiles and reset / determined again for each spawn.
						*  If TimeBetweenProjectilesPerSpawn is 0.0f, then ORDERED distributions are the SAME.
						*  Projectile is an object that implements the interface: ICsProjectile.
						*/
						enum class EDistribution : uint8
						{
							/** Projectiles are spawned in order and clockwise from the movement direction of the
								parent Projectile. */
							OrderedClockwise,
							/** Projectiles are spawned in order and counter-clockwise from the movement direction of the
								parent Projectile. */
							OrderedCounterClockwise,
							/** Projectiles are spawn in order and alternate from clockwise to counter-clockwise from the
								movement direction of the parent Projectile. The clockwise direction is chosen first
								before counter-clockwise (i.e. c, cc, c, cc, c, cc, ... etc). */
							OrderedPingPongClockwise,
							/** Projectiles are spawn in order and alternate from counter-clockwise to clockwise from the
								movement direction of the parent Projectile. The counter-clockwise direction is chosen first
								before clockwise (i.e. cc, c, cc, c, cc, c, ... etc). */
							OrderedPingPongCounterClockwise,
							/** Projectiles are spawned from a random shuffle of predetermined angles from the
								movement direction of the parent Projectile. */
							Shuffle,
							/** Projectiles are spawned at random angles from the movement direction of the parent
								Projectile.
								NOTE: Spread Angle Type MUST = ECsProjectileOnHitSpawnProjectileSpreadAngle::MinMax. */
							Random,
							EDistribution_MAX
						};

						struct CSPRJ_API EMDistribution : public TCsEnumMap<EDistribution>
						{
							CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDistribution, EDistribution)
						};

						namespace NDistribution
						{
							namespace Ref
							{
								typedef EDistribution Type;

								extern CSPRJ_API const Type OrderedClockwise;
								extern CSPRJ_API const Type OrderedCounterClockwise;
								extern CSPRJ_API const Type OrderedPingPongClockwise;
								extern CSPRJ_API const Type OrderedPingPongCounterClockwise;
								extern CSPRJ_API const Type Shuffle;
								extern CSPRJ_API const Type Random;
								extern CSPRJ_API const Type EDistribution_MAX;
							}

							FORCEINLINE bool ShouldPrecalculate(const EDistribution& InType) { return InType != EDistribution::Random; }
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileOnHitSpawnProjectileSpreadAngleDistribution

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					struct CSPRJ_API FLibrary
					{
					private:

						using ShapeType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EShape;
						using DistributionType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::EDistribution;
						using AngleType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EAngle;
						using AngleDistributionType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::EDistribution;

					public:		

						static FVector3f GetRandomOffsetChecked(const FString& Context, const ShapeType& Shape, const FVector3f& Extents, const DistributionType& Distribution);

						static void SetAnglesChecked(const FString& Context, const int32& Count, const AngleType& Type, const float& Angle, const AngleDistributionType& Distribution, TArray<float>& OutAngles);

						static float GetRandomAngleChecked(const FString& Context, const AngleType& Type, const float& Angle, const AngleDistributionType& Distribution);
					};
				}
			}
		}
	}
}