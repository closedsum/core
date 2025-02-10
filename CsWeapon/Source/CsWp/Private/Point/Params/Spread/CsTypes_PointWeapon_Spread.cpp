// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Params/Spread/CsTypes_PointWeapon_Spread.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_PointWeapon_Spread)

// PointWeaponSpreadShape
#pragma region

namespace NCsPointWeaponSpreadShape
{
	namespace Ref
	{
		typedef EMCsPointWeaponSpreadShape EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Line);
		CSWP_API CS_ADD_TO_ENUM_MAP(Rectangle);
		CSWP_API CS_ADD_TO_ENUM_MAP(Circle);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponSpreadShape_MAX, "MAX");
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

#pragma endregion PointWeaponSpreadShape

// PointWeaponSpreadShapeDistribution
#pragma region

namespace NCsPointWeaponSpreadShapeDistribution
{
	namespace Ref
	{
		typedef EMCsPointWeaponSpreadShapeDistribution EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Random);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponSpreadShapeDistribution_MAX, "MAX");
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

#pragma endregion PointWeaponSpreadShapeDistribution

// PointWeaponSpreadShapeAxis
#pragma region

namespace NCsPointWeaponSpreadShapeAxis
{
	namespace Ref
	{
		typedef EMCsPointWeaponSpreadShapeAxis EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Up);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(LaunchDirection, "Launch Direction");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponSpreadShapeAxis_MAX, "MAX");
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

#pragma endregion PointWeaponSpreadShapeAxis

// PointWeaponSpreadAngle
#pragma region

namespace NCsPointWeaponSpreadAngle
{
	namespace Ref
	{
		typedef EMCsPointWeaponSpreadAngle EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(DivideByCount, "Divide by Count");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AngleBetween, "Angel Between");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(UniformMinMax, "Uniform: Min / Max");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(RangeMinMax, "Range: Min / Max");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponSpreadAngle_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NPoint
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
					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(UniformMinMax, "Uniform: Min / Max");
					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(RangeMinMax, "Range: Min / Max");
					CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EAngle_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion PointWeaponSpreadAngle

// PointWeaponSpreadAngleDistribution
#pragma region

namespace NCsPointWeaponSpreadAngleDistribution
{
	namespace Ref
	{
		typedef EMCsPointWeaponSpreadAngleDistribution EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedClockwise, "Ordered Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedCounterClockwise, "Ordered Counter-Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongClockwise, "Ordered Ping Pong Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongCounterClockwise, "Ordered Ping Pong Counter-Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP(Shuffle);
		CSWP_API CS_ADD_TO_ENUM_MAP(Random);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponSpreadAngleDistribution_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NPoint
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

#pragma endregion PointWeaponSpreadAngleDistribution

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			using ShapeType = NCsWeapon::NPoint::NSpread::EShape;
			using ShapeMapType = NCsWeapon::NPoint::NSpread::EMShape;
			using DistributionType = NCsWeapon::NPoint::NSpread::NShape::EDistribution;
			using DistributionMapType = NCsWeapon::NPoint::NSpread::NShape::EMDistribution;
			using AngleType = NCsWeapon::NPoint::NSpread::EAngle;
			using AngleMapType = NCsWeapon::NPoint::NSpread::EMAngle;
			using AngleDistributionType = NCsWeapon::NPoint::NSpread::NAngle::EDistribution;
			using AngleDistributionMapType = NCsWeapon::NPoint::NSpread::NAngle::EMDistribution;

			FVector3f FLibrary::GetRandomOffsetChecked(const FString& Context, const ShapeType& Shape, const FVector3f& Extents, const DistributionType& Distribution)
			{
				CS_IS_ENUM_VALID_CHECKED(ShapeMapType, Shape)
				CS_IS_VECTOR_ZERO_CHECKED(Extents)

				checkf(Distribution == DistributionType::Random, TEXT("%s: Distribution (%s) != DistributionType::Random."), *Context, DistributionMapType::Get().ToChar(Distribution));

				FVector3f Offset = FVector3f::ZeroVector;

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

			void FLibrary::SetAnglesChecked(const FString& Context, const int32& Count, const AngleType& Type, const float& Angle, const AngleDistributionType& Distribution, TArray<float>& OutAngles)
			{
				CS_IS_INT_GREATER_THAN_CHECKED(Count, 0)
				CS_IS_ENUM_VALID_CHECKED(AngleMapType, Type)
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
				CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 360.0f)
				CS_IS_ENUM_VALID_CHECKED(AngleDistributionMapType, Distribution)

				checkf(Distribution != AngleDistributionType::Random, TEXT("%s: Distribution == AngleDistributionType::Random is NOT supported."), *Context);

				CS_IS_TARRAY_SIZE_CHECKED(OutAngles, float, Count)

				float AngleBetween = Angle;

				// DivideByCount
				if (Type == AngleType::DivideByCount)
				{
					AngleBetween = Angle / Count;
				}
				// UniformMinMax
				else 
				if (Type == AngleType::UniformMinMax)
				{
					AngleBetween = Count > 1 ? (2.0f * Angle) / Count : 0.0f;
				}

				// Ordered Clockwise
				if (Distribution == AngleDistributionType::OrderedClockwise)
				{
					for (int32 I = 0; I < Count; ++I)
					{
						OutAngles[I] = 360.0f - (I * AngleBetween);
					}
				}
				// Ordered Counter-Clockwise
				else
				if (Distribution == AngleDistributionType::OrderedCounterClockwise)
				{
					for (int32 I = 0; I < Count; ++I)
					{
						OutAngles[I] = I * AngleBetween;
					}
				}
				// Ordered Ping Pong Clockwise
				else
				if (Distribution == AngleDistributionType::OrderedPingPongClockwise)
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
							OutAngles[I] = 360.0f - (I * AngleBetween);
						else
							OutAngles[I] = I * AngleBetween;

						Direction *= -1;
					}
				}
				// Ordered Ping Pong Counter-Clockwise
				else
				if (Distribution == AngleDistributionType::OrderedPingPongCounterClockwise)
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
							OutAngles[I] = 360.0f - (I * AngleBetween);
						else
							OutAngles[I] = I * AngleBetween;

						Direction *= -1;
					}
				}
				// Shuffle
				else
				if (Distribution == AngleDistributionType::Shuffle)
				{
					for (int32 I = 0; I < Count; ++I)
					{
						OutAngles[I] = I * AngleBetween;
					}
					CsArrayLibrary::Shuffle<float>(OutAngles);
				}
			}

			float FLibrary::GetRandomAngleChecked(const FString& Context, const AngleType& Type, const float& Angle, const AngleDistributionType& Distribution)
			{
				CS_IS_ENUM_VALID_CHECKED(AngleMapType, Type)

				checkf(Type == AngleType::UniformMinMax, TEXT("%s: AngleType (%s) != AngleType::UniformMinMax."), *Context, AngleMapType::Get().ToChar(Type));

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
				CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 180.0f)
				CS_IS_ENUM_VALID_CHECKED(AngleDistributionMapType, Distribution)

				checkf(Distribution == AngleDistributionType::Random, TEXT("%s: Distribution (%s) != AngleDistributionType::Random."), *Context, AngleDistributionMapType::Get().ToChar(Distribution));

				return FMath::FRandRange(-Angle, Angle);
			}

			float FLibrary::GetRandomAngleChecked(const FString& Context, const AngleType& Type, const float& Min, const float& Max, const AngleDistributionType& Distribution)
			{
				CS_IS_ENUM_VALID_CHECKED(AngleMapType, Type)

				checkf(Type == AngleType::RangeMinMax, TEXT("%s: Type (%s) != AngleType::RangeMinMax."), *Context, AngleMapType::Get().ToChar(Type));

				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Max, Min)
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Min, -180.0f)
				CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Max, 180.0f)
				CS_IS_ENUM_VALID_CHECKED(AngleDistributionMapType, Distribution)

				checkf(Distribution == AngleDistributionType::Random, TEXT("%s: Distribution (%s) != AngleDistributionType::Random."), *Context, AngleDistributionMapType::Get().ToChar(Distribution));

				return FMath::FRandRange(Min, Max);
			}
		}
	}
}