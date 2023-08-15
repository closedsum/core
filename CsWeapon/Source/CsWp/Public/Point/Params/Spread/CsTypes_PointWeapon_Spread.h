// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_PointWeapon_Spread.generated.h"

// PointWeaponSpreadShape
#pragma region

/**
* Describes the Spread Shape for a Point Weapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponSpreadShape : uint8
{
	/** The "area" is the line Right and Left vectors
		with respect to the the default Direction of the Point. */
	Line							UMETA(DisplayName = "Line"),
	/** The area is the extents Right and Left vectors
		with respect to the default Direction of the Point and World Up vector. */
	Rectangle						UMETA(DisplayName = "Rectangle"),
	/** The area is a radius around the default Direction of the Point.
		The area is represented by Right vector with respect to the default Direction and 
		World Up vector. */
	Circle							UMETA(DisplayName = "Circle"),
	ECsPointWeaponSpreadShape_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponSpreadShape : public TCsEnumMap<ECsPointWeaponSpreadShape>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponSpreadShape, ECsPointWeaponSpreadShape)
};

namespace NCsPointWeaponSpreadShape
{
	typedef ECsPointWeaponSpreadShape Type;

	namespace Ref
	{
		extern CSWP_API const Type Line;
		extern CSWP_API const Type Rectangle;
		extern CSWP_API const Type Circle;
		extern CSWP_API const Type ECsPointWeaponSpreadShape_MAX;
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			/**
			* Describes the Spread Shape for a Point Weapon.
			*  Point Weapon is an object that implements the interface: ICsPointWeapon.
			*/
			enum class EShape : uint8
			{
				/** The "area" is the line Right and Left vectors
					with respect to the the default Direction of the Point. */
				Line,
				/** The area is the extents Right and Left vectors
					with respect to the default Direction of the Point and World Up vector. */
				Rectangle,
				/** The area is a radius around the default Direction of the Point.
					The area is represented by Right vector with respect to the default Direction and 
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

#pragma endregion PointWeaponSpreadShape

// PointWeaponSpreadShapeDistribution
#pragma region

/**
* Describes the distribution of start locations within a Spread Shape for a Point Weapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponSpreadShapeDistribution : uint8
{
	Random										UMETA(DisplayName = "Random"),
	ECsPointWeaponSpreadShapeDistribution_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponSpreadShapeDistribution : public TCsEnumMap<ECsPointWeaponSpreadShapeDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponSpreadShapeDistribution, ECsPointWeaponSpreadShapeDistribution)
};

namespace NCsPointWeaponSpreadShapeDistribution
{
	typedef ECsPointWeaponSpreadShapeDistribution Type;

	namespace Ref
	{
		extern CSWP_API const Type Random;
		extern CSWP_API const Type ECsPointWeaponSpreadShapeDistribution_MAX;
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			namespace NShape
			{
				/**
				* Describes the distribution of start locations within a Spread Shape for a Point Weapon.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon.
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

#pragma endregion PointWeaponSpreadShapeDistribution

// PointWeaponSpreadShapeAxis
#pragma region

/**
* Describes the Axis by which the start locations within a Spread Shape are Distributed for a Point Weapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponSpreadShapeAxis: uint8
{
	/** Up Vector */
	Up									UMETA(DisplayName = "Up"),
	/** In the direction of the Projectile is fired. */
	LaunchDirection						UMETA(DisplayName = "Launch Direction"),
	ECsPointWeaponSpreadShapeAxis_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponSpreadShapeAxis : public TCsEnumMap<ECsPointWeaponSpreadShapeAxis>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponSpreadShapeAxis, ECsPointWeaponSpreadShapeAxis)
};

namespace NCsPointWeaponSpreadShapeAxis
{
	typedef ECsPointWeaponSpreadShapeAxis Type;

	namespace Ref
	{
		extern CSWP_API const Type Up;
		extern CSWP_API const Type LaunchDirection;
		extern CSWP_API const Type ECsPointWeaponSpreadShapeAxis_MAX;
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			namespace NShape
			{
				/**
				* Describes the distribution of start locations within a Spread Shape for a Point Weapon.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon.
				*/
				enum class EAxis : uint8
				{
					/** Up Vector */
					Up,
					/** In the direction of the Point is fired. */
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

#pragma endregion PointWeaponSpreadShapeAxis

// PointWeaponSpreadAngle
#pragma region

/**
* Describes how the Spread Angle should be interpreted for a Point Weapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponSpreadAngle : uint8
{
	/** The angle between each point is the Spread Angle divide by the 
		number Points per Shot. */
	DivideByCount					UMETA(DisplayName = "Divide by Count"),
	/** The Spread Angle is the angle between each point in a Shot.
		(i.e. if Points per Shot is 3 and the Spread Angle is 60, then angle between
			  each Point is 60.) */
	AngleBetween					UMETA(DisplayName = "Angle Between"),
	/** The Spread Angle represents the absolute angle delta (+/-) from the Direction.
		(i.e. If the Spread Angle is 60, then the Points are fired at angles between
		      60 and -60 degrees from the Direction, usually the Weapon Forward.) */
	UniformMinMax					UMETA(DisplayName = "Uniform: Min / Max"),
	/** The Spread Angle is represented by a Min and a Max angle from the Direction.
		(i.e. If the Min Angle is -20 and the Max Angle is 60, then the Points are fired at
				angles between -20 and 60 degrees from the Direction, usually the Weapon Forward). */
	RangeMinMax						UMETA(DisplayName = "Range: Min / Max"),
	ECsPointWeaponSpreadAngle_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponSpreadAngle : public TCsEnumMap<ECsPointWeaponSpreadAngle>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponSpreadAngle, ECsPointWeaponSpreadAngle)
};

namespace NCsPointWeaponSpreadAngle
{
	typedef ECsPointWeaponSpreadAngle Type;

	namespace Ref
	{
		extern CSWP_API const Type DivideByCount;
		extern CSWP_API const Type AngleBetween;
		extern CSWP_API const Type UniformMinMax;
		extern CSWP_API const Type RangeMinMax;
		extern CSWP_API const Type ECsPointWeaponSpreadAngle_MAX;
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			/**
			* Describes how the Spread Angle should be interpreted for a Point Weapon.
			*  Point Weapon is an object that implements the interface: ICsPointWeapon.
			*/
			enum class EAngle : uint8
			{
				/** The angle between each point the Spread Angle divide by the 
					number Points per Shot. */
				DivideByCount,
				/** The Spread Angle is the angle between each point in a Shot.
					(i.e. if Points per Shot is 3 and the Spread Angle is 60, then angle between
						  each Point is 60.) */
				AngleBetween,
				/** The Spread Angle represents the absolute angle delta (+/-) from the Direction.
					(i.e. If the Spread Angle is 60, then the Points are fired at angles between
						  60 and -60 degrees from the Direction, usually the Weapon Forward.) */
				UniformMinMax,
				/** The Spread Angle is represented by a Min and a Max angle from the Direction. 
					(i.e. If the Min Angle is -20 and the Max Angle is 60, then the Points are fired at
						  angles between -20 and 60 degrees from the Direction, usually the Weapon Forward). */
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

#pragma endregion PointWeaponSpreadAngle

// PointWeaponSpreadAngleDistribution
#pragma region

/**
* Describes the direction of points fired from a Point Weapon using
*  the Spread Angle and Spread Angle Type (ECsPointWeaponSpreadAngle or NCsWeapon::NPoint::NSpread::EAngle).
*  The distribution is for a "shot" of points and reset / determined again for each shot.
*  If PointsPerShot.Interval is 0.0f, then ORDERED distributions are the SAME.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponSpreadAngleDistribution : uint8
{
	/** Points are spawned in order and clockwise from the default Direction,
		usually the Weapon Forward. */
	OrderedClockwise							UMETA(DisplayName = "Ordered Clockwise"),
	/** Points are spawned in order and counter-clockwise from the default Direction,
		usually the Weapon Forward.  */
	OrderedCounterClockwise						UMETA(DisplayName = "Ordered Counter-Clockwise"),
	/** Points are spawn in order and alternate from clockwise to counter-clockwise from the 
		default Direction, usually the Weapon Forward. The clockwise direction is chosen first
		before counter-clockwise (i.e. c, cc, c, cc, c, cc, ... etc). */
	OrderedPingPongClockwise					UMETA(DisplayName = "Ordered Ping Ping Clockwise"),
	/** Points are spawn in order and alternate from counter-clockwise to clockwise from the 
		default Direction, usually the Weapon Forward. The counter-clockwise direction is chosen first
		before clockwise (i.e. cc, c, cc, c, cc, c, ... etc). */
	OrderedPingPongCounterClockwise				UMETA(DisplayName = "Ordered Ping Ping Counter-Clockwise"),
	/** Points are spawned from a random shuffle of predetermined angles from the default
		Direction, usually the Weapon Forward. */
	Shuffle										UMETA(DisplayName = "Shuffle"),
	/** Points are spawned at random angles from the default Direction, 
		usually the Weapon Forward. 
		NOTE: Spread Angle Type MUST = ECsPointWeaponSpreadAngle::UniformMinMax. */
	Random										UMETA(DisplayName = "Random"),
	ECsPointWeaponSpreadAngleDistribution_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponSpreadAngleDistribution : public TCsEnumMap<ECsPointWeaponSpreadAngleDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponSpreadAngleDistribution, ECsPointWeaponSpreadAngleDistribution)
};

namespace NCsPointWeaponSpreadAngleDistribution
{
	typedef ECsPointWeaponSpreadAngleDistribution Type;

	namespace Ref
	{
		extern CSWP_API const Type OrderedClockwise;
		extern CSWP_API const Type OrderedCounterClockwise;
		extern CSWP_API const Type OrderedPingPongClockwise;
		extern CSWP_API const Type OrderedPingPongCounterClockwise;
		extern CSWP_API const Type Shuffle;
		extern CSWP_API const Type Random;
		extern CSWP_API const Type ECsPointWeaponSpreadAngleDistribution_MAX;
	}

	FORCEINLINE bool ShouldPrecalculate(const Type& InType) { return InType != Type::Random; }
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			namespace NAngle
			{
				/**
				* Describes the direction of points fired from a Point Weapon using
				*  the Spread Angle and Spread Angle Type (NCsWeapon::NPoint::NSpread::EAngle).
				*  The distribution is for a "shot" of points and reset / determined again for each shot.
				*  If PointsPerShot.Interval is 0.0f, then ORDERED distributions are the SAME.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon.
				*/
				enum class EDistribution : uint8
				{
					/** Points are spawned in order and clockwise from the default Direction,
						usually the Weapon Forward. */
					OrderedClockwise,
					/** Points are spawned in order and counter-clockwise from the default Direction,
						usually the Weapon Forward.  */
					OrderedCounterClockwise,
					/** Points are spawn in order and alternate from clockwise to counter-clockwise from the 
						default Direction, usually the Weapon Forward. The clockwise direction is chosen first
						before counter-clockwise (i.e. c, cc, c, cc, c, cc, ... etc). */
					OrderedPingPongClockwise,
					/** Points are spawn in order and alternate from counter-clockwise to clockwise from the 
						default Direction, usually the Weapon Forward. The counter-clockwise direction is chosen first
						before clockwise (i.e. cc, c, cc, c, cc, c, ... etc). */
					OrderedPingPongCounterClockwise,
					/** Points are spawned from a random shuffle of predetermined angles from the default
						Direction, usually the Weapon Forward. */
					Shuffle,
					/** Points are spawned at random angles from the default Direction, 
						usually the Weapon Forward. 
						NOTE: Spread Angle Type MUST = NCsWeapon::NPoint::NSpread::EAngle::MinMax. */
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

#pragma endregion PointWeaponSpreadAngleDistribution

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			struct CSWP_API FLibrary
			{
			public:

			#define ShapeType NCsWeapon::NPoint::NSpread::EShape
			#define DistributionType NCsWeapon::NPoint::NSpread::NShape::EDistribution

				static FVector3f GetRandomOffsetChecked(const FString& Context, const ShapeType& Shape, const FVector3f& Extents, const DistributionType& Distribution);

			#undef ShapeType
			#undef DistributionType

			#define SpreadAngleType NCsWeapon::NPoint::NSpread::EAngle
			#define DistributionType NCsWeapon::NPoint::NSpread::NAngle::EDistribution

				static void SetAnglesChecked(const FString& Context, const int32& Count, const SpreadAngleType& AngleType, const float& Angle, const DistributionType& Distribution, TArray<float>& OutAngles);

				static float GetRandomAngleChecked(const FString& Context, const SpreadAngleType& AngleType, const float& Angle, const DistributionType& Distribution);

				static float GetRandomAngleChecked(const FString& Context, const SpreadAngleType& AngleType, const float& Min, const float& Max, const DistributionType& Distribution);

			#undef SpreadAngleType
			#undef DistributionType
			};
		}
	}
}