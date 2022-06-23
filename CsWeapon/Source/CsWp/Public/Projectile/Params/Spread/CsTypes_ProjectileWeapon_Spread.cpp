// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Spread/CsTypes_ProjectileWeapon_Spread.h"

// Library
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"

// ProjectileWeaponSpreadShape
#pragma region

namespace NCsProjectileWeaponSpreadShape
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponSpreadShape EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Line);
		CSWP_API CS_ADD_TO_ENUM_MAP(Rectangle);
		CSWP_API CS_ADD_TO_ENUM_MAP(Circle);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponSpreadShape_MAX, "MAX");
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
				namespace Ref
				{
					typedef EMShape EnumMapType;

					CSWP_API CS_ADD_TO_ENUM_MAP(Line);
					CSWP_API CS_ADD_TO_ENUM_MAP(Rectangle);
					CSWP_API CS_ADD_TO_ENUM_MAP(Circle);
					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EShape_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadShape

// ProjectileWeaponSpreadShapeDistribution
#pragma region

namespace NCsProjectileWeaponSpreadShapeDistribution
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponSpreadShapeDistribution EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Random);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponSpreadShapeDistribution_MAX, "MAX");
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
				namespace NDistribution
				{
					namespace Ref
					{
						typedef EMDistribution EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(Random);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDistribution_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadShapeDistribution

// ProjectileWeaponSpreadShapeAxis
#pragma region

namespace NCsProjectileWeaponSpreadShapeAxis
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponSpreadShapeAxis EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Up);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(LaunchDirection, "Launch Direction");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponSpreadShapeAxis_MAX, "MAX");
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
				namespace NAxis
				{
					namespace Ref
					{
						typedef EMAxis EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(Up);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(LaunchDirection, "Launch Direction");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EAxis_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadShapeAxis

// ProjectileWeaponSpreadAngle
#pragma region

namespace NCsProjectileWeaponSpreadAngle
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponSpreadAngle EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(DivideByCount, "Divide by Count");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AngleBetween, "Angel Between");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(MinMax, "Min / Max");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponSpreadAngle_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NAngle
			{
				namespace Ref
				{
					typedef EMAngle EnumMapType;

					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(DivideByCount, "Divide by Count");
					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AngleBetween, "Angel Between");
					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(MinMax, "Min / Max");
					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EAngle_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponSpreadAngle

// ProjectileWeaponSpreadAngleDistribution
#pragma region

namespace NCsProjectileWeaponSpreadAngleDistribution
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponSpreadAngleDistribution EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedClockwise, "Ordered Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedCounterClockwise, "Ordered Counter-Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongClockwise, "Ordered Ping Pong Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongCounterClockwise, "Ordered Ping Pong Counter-Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP(Shuffle);
		CSWP_API CS_ADD_TO_ENUM_MAP(Random);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponSpreadAngleDistribution_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NAngle
			{
				namespace NDistribution
				{
					namespace Ref
					{
						typedef EMDistribution EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedClockwise, "Ordered Clockwise");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedCounterClockwise, "Ordered Counter-Clockwise");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongClockwise, "Ordered Ping Pong Clockwise");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongCounterClockwise, "Ordered Ping Pong Counter-Clockwise");
						CSWP_API CS_ADD_TO_ENUM_MAP(Shuffle);
						CSWP_API CS_ADD_TO_ENUM_MAP(Random);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDistribution_MAX, "MAX");
					}
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
			#define ShapeType NCsWeapon::NProjectile::NSpread::EShape
			#define DistributionType NCsWeapon::NProjectile::NSpread::NShape::EDistribution

			FVector FLibrary::GetRandomOffsetChecked(const FString& Context, const ShapeType& Shape, const FVector& Extents, const DistributionType& Distribution)
			{
				typedef NCsWeapon::NProjectile::NSpread::EMShape ShapeMapType;

				CS_IS_ENUM_VALID_CHECKED(ShapeMapType, Shape)

				CS_IS_VECTOR_ZERO_CHECKED(Extents)

				typedef NCsWeapon::NProjectile::NSpread::NShape::EMDistribution DistributionMapType;

				checkf(Distribution == DistributionType::Random, TEXT("%s: Distribution (%s) != DistributionType::Random."), *Context, DistributionMapType::Get().ToChar(Distribution));

				FVector Offset = FVector::ZeroVector;

				// Line
				if (Shape == ShapeType::Line)
				{
					Offset.X = (FMath::RandRange(0, 1) == 0 ? 1 : -1) * FMath::FRandRange(0.0f, 1.0f) * Extents.X;
				}
				// Rectangle
				else
				if (Shape == ShapeType::Rectangle)
				{
					Offset.X = (FMath::RandRange(0, 1) == 0 ? 1 : -1) * FMath::FRandRange(0.0f, 1.0f) * Extents.X;
					Offset.Y = (FMath::RandRange(0, 1) == 0 ? 1 : -1) * FMath::FRandRange(0.0f, 1.0f) * Extents.Y;
				}
				// Circle
				else
				if (Shape == ShapeType::Circle)
				{
					const float& MinRadius = Extents.X;
					const float& MaxRadius = Extents.Y;

					const float MaxRadiusSq = MaxRadius * MaxRadius;
					const float MinRadiusSq = MinRadius * MinRadius;

					const float Radius = FMath::Sqrt((FMath::RandRange(0.0f, 1.0f) * (MaxRadiusSq - MinRadiusSq)) + MinRadiusSq);
					const float Theta  = FMath::RandRange(0.0f, 1.0f) * 2.0f * PI;
					
					Offset.X = Radius * FMath::Cos(Theta);
					Offset.Y = Radius * FMath::Sin(Theta);
				}
				return Offset;
			}

			#undef ShapeType
			#undef DistributionType

			#define SpreadAngleType NCsWeapon::NProjectile::NSpread::EAngle
			#define DistributionType NCsWeapon::NProjectile::NSpread::NAngle::EDistribution

			void FLibrary::SetAnglesChecked(const FString& Context, const int32& Count, const SpreadAngleType& AngleType, const float& Angle, const DistributionType& Distribution, TArray<float>& OutAngles)
			{
				CS_IS_INT_GREATER_THAN_CHECKED(Count, 0)

				typedef NCsWeapon::NProjectile::NSpread::EMAngle SpreadAngleMapType;

				CS_IS_ENUM_VALID_CHECKED(SpreadAngleMapType, AngleType)

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
				CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 360.0f)

				typedef NCsWeapon::NProjectile::NSpread::NAngle::EMDistribution DistributionMapType;

				CS_IS_ENUM_VALID_CHECKED(DistributionMapType, Distribution)

				checkf(Distribution != DistributionType::Random, TEXT("%s: Distribution == DistributionType::Random is NOT supported."), *Context);

				CS_IS_ARRAY_SIZE_CHECKED(OutAngles, float, Count)

				float AngleBetween = Angle;

				// DivideByCount
				if (AngleType == SpreadAngleType::DivideByCount)
				{
					AngleBetween = Angle / Count;
				}
				// MinMax
				else 
				if (AngleType == SpreadAngleType::MinMax)
				{
					AngleBetween = Count > 1 ? (2.0f * Angle) / Count : 0.0f;
				}

				// Ordered Clockwise
				if (Distribution == DistributionType::OrderedClockwise)
				{
					for (int32 I = 0; I < Count; ++I)
					{
						OutAngles[I] = I * (360.0f - AngleBetween);
					}
				}
				// Ordered Counter-Clockwise
				else
				if (Distribution == DistributionType::OrderedCounterClockwise)
				{
					for (int32 I = 0; I < Count; ++I)
					{
						OutAngles[I] = I * AngleBetween;
					}
				}
				// Ordered Ping Pong Clockwise
				else
				if (Distribution == DistributionType::OrderedPingPongClockwise)
				{
					int32 StartIndex = 0;

					// Odd
					if (Count % 2 == 1)
					{
						OutAngles[CS_FIRST] = 0.0f;

						StartIndex = 1;
					}

					static const int32 CLOCKWISE		 = -1;
					static const int32 COUNTER_CLOCKWISE = 1;

					int32 Direction = CLOCKWISE;

					for (int32 I = StartIndex; I < Count; ++I)
					{
						if (Direction == CLOCKWISE)
							OutAngles[I] = I * (360.0f - AngleBetween);
						else
							OutAngles[I] = I * AngleBetween;

						Direction *= -1;
					}
				}
				// Ordered Ping Pong Counter-Clockwise
				else
				if (Distribution == DistributionType::OrderedPingPongCounterClockwise)
				{
					int32 StartIndex = 0;

					// Odd
					if (Count % 2 == 1)
					{
						OutAngles[CS_FIRST] = 0.0f;

						StartIndex = 1;
					}

					static const int32 CLOCKWISE		 = -1;
					static const int32 COUNTER_CLOCKWISE = 1;

					int32 Direction = COUNTER_CLOCKWISE;

					for (int32 I = StartIndex; I < Count; ++I)
					{
						if (Direction == CLOCKWISE)
							OutAngles[I] = I * (360.0f - AngleBetween);
						else
							OutAngles[I] = I * AngleBetween;

						Direction *= -1;
					}
				}
				// Shuffle
				else
				if (Distribution == DistributionType::Shuffle)
				{
					for (int32 I = 0; I < Count; ++I)
					{
						OutAngles[I] = I * AngleBetween;
					}
						
					typedef NCsArray::FLibrary ArrayLibrary;

					ArrayLibrary::Shuffle<float>(OutAngles);
				}
			}

			float FLibrary::GetRandomAngleChecked(const FString& Context, const SpreadAngleType& AngleType, const float& Angle, const DistributionType& Distribution)
			{
				typedef NCsWeapon::NProjectile::NSpread::EMAngle SpreadAngleMapType;

				CS_IS_ENUM_VALID_CHECKED(SpreadAngleMapType, AngleType)

				checkf(AngleType == SpreadAngleType::MinMax, TEXT("%s: AngleType (%s) != SpreadAngleType::MinMax."), *Context, SpreadAngleMapType::Get().ToChar(AngleType));

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
				CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 360.0f)

				typedef NCsWeapon::NProjectile::NSpread::NAngle::EMDistribution DistributionMapType;

				CS_IS_ENUM_VALID_CHECKED(DistributionMapType, Distribution)

				checkf(Distribution == DistributionType::Random, TEXT("%s: Distribution (%s) != DistributionType::Random."), *Context, DistributionMapType::Get().ToChar(Distribution));

				return FMath::FRandRange(Angle, 360.0f - Angle);
			}

			#undef SpreadAngleType
			#undef DistributionType
		}
	}
}