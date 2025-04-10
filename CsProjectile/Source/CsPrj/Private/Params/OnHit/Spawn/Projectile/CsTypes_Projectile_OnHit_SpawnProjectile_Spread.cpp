// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Params/OnHit/Spawn/Projectile/CsTypes_Projectile_OnHit_SpawnProjectile_Spread.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Projectile_OnHit_SpawnProjectile_Spread)

// ProjectileOnHitSpawnProjectileSpreadShape
#pragma region

namespace NCsProjectileOnHitSpawnProjectileSpreadShape
{
	namespace Ref
	{
		typedef EMCsProjectileOnHitSpawnProjectileSpreadShape EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Line);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Rectangle);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Circle);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileOnHitSpawnProjectileSpreadShape_MAX, "MAX");
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
						namespace Ref
						{
							typedef EMShape EnumMapType;

							CSPRJ_API CS_ADD_TO_ENUM_MAP(Line);
							CSPRJ_API CS_ADD_TO_ENUM_MAP(Rectangle);
							CSPRJ_API CS_ADD_TO_ENUM_MAP(Circle);
							CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EShape_MAX, "MAX");
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

namespace NCsProjectileOnHitSpawnProjectileSpreadShapeDistribution
{
	namespace Ref
	{
		typedef EMCsProjectileOnHitSpawnProjectileSpreadShapeDistribution EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Random);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution_MAX, "MAX");
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
						namespace NDistribution
						{
							namespace Ref
							{
								typedef EMDistribution EnumMapType;

								CSPRJ_API CS_ADD_TO_ENUM_MAP(Random);
								CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDistribution_MAX, "MAX");
							}
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

namespace NCsProjectileOnHitSpawnProjectileSpreadAngle
{
	namespace Ref
	{
		typedef EMCsProjectileOnHitSpawnProjectileSpreadAngle EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(DivideByCount, "Divide by Count");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(AngleBetween, "Angel Between");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(MinMax, "Min / Max");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileOnHitSpawnProjectileSpreadAngle_MAX, "MAX");
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
					namespace NAngle
					{
						namespace Ref
						{
							typedef EMAngle EnumMapType;

							CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(DivideByCount, "Divide by Count");
							CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(AngleBetween, "Angel Between");
							CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(MinMax, "Min / Max");
							CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EAngle_MAX, "MAX");
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileOnHitSpawnProjectileSpreadAngle

// ProjectileOnHitSpawnProjectileSpreadAngleDistribution
#pragma region

namespace NCsProjectileOnHitSpawnProjectileSpreadAngleDistribution
{
	namespace Ref
	{
		typedef EMCsProjectileOnHitSpawnProjectileSpreadAngleDistribution EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedClockwise, "Ordered Clockwise");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedCounterClockwise, "Ordered Counter-Clockwise");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongClockwise, "Ordered Ping Pong Clockwise");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongCounterClockwise, "Ordered Ping Pong Counter-Clockwise");
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Shuffle);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Random);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution_MAX, "MAX");
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
					namespace NAngle
					{
						namespace NDistribution
						{
							namespace Ref
							{
								typedef EMDistribution EnumMapType;

								CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedClockwise, "Ordered Clockwise");
								CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedCounterClockwise, "Ordered Counter-Clockwise");
								CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongClockwise, "Ordered Ping Pong Clockwise");
								CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongCounterClockwise, "Ordered Ping Pong Counter-Clockwise");
								CSPRJ_API CS_ADD_TO_ENUM_MAP(Shuffle);
								CSPRJ_API CS_ADD_TO_ENUM_MAP(Random);
								CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDistribution_MAX, "MAX");
							}
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
					using ShapeType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EShape;
					using ShapeMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EMShape;
					using DistributionType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::EDistribution;
					using DistributionMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::EMDistribution;
					using AngleType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EAngle;
					using AngleMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EMAngle;
					using AngleDistributionType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::EDistribution;
					using AngleDistributionMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::EMDistribution;

					FVector FLibrary::GetRandomOffsetChecked(const FString& Context, const ShapeType& Shape, const FVector& Extents, const DistributionType& Distribution)
					{
						CS_IS_ENUM_VALID_CHECKED(ShapeMapType, Shape)
						CS_IS_VECTOR_ZERO_CHECKED(Extents)

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
						// MinMax
						else 
						if (Type == AngleType::MinMax)
						{
							AngleBetween = Count > 1 ? (2.0f * Angle) / Count : 0.0f;
						}

						// Ordered Clockwise
						if (Distribution == AngleDistributionType::OrderedClockwise)
						{
							for (int32 I = 0; I < Count; ++I)
							{
								OutAngles[I] = I * (360.0f - AngleBetween);
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
									OutAngles[I] = I * (360.0f - AngleBetween);
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
									OutAngles[I] = I * (360.0f - AngleBetween);
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

						checkf(Type == AngleType::MinMax, TEXT("%s: Type (%s) != AngleType::MinMax."), *Context, AngleMapType::Get().ToChar(Type));

						CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
						CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 360.0f)
						CS_IS_ENUM_VALID_CHECKED(AngleDistributionMapType, Distribution)

						checkf(Distribution == AngleDistributionType::Random, TEXT("%s: Distribution (%s) != DistributionType::Random."), *Context, AngleDistributionMapType::Get().ToChar(Distribution));

						return FMath::FRandRange(Angle, 360.0f - Angle);
					}
				}
			}
		}
	}
}