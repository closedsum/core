// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Spread/CsTypes_ProjectileWeapon_Spread.h"

// Library
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"

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

// ProjectileWeaponSpreadDistribution
#pragma region

namespace NCsProjectileWeaponSpreadDistribution
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponSpreadDistribution EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedClockwise, "Ordered Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedCounterClockwise, "Ordered Counter-Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongClockwise, "Ordered Ping Pong Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(OrderedPingPongCounterClockwise, "Ordered Ping Pong Counter-Clockwise");
		CSWP_API CS_ADD_TO_ENUM_MAP(Shuffle);
		CSWP_API CS_ADD_TO_ENUM_MAP(Random);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponSpreadDistribution_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
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

#pragma endregion ProjectileWeaponSpreadDistribution

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			#define SpreadAngleType NCsWeapon::NProjectile::NSpread::EAngle
			#define DistributionType NCsWeapon::NProjectile::NSpread::EDistribution

				void FLibrary::GetAnglesChecked( const FString& Context, const int32& Count, const SpreadAngleType& AngleType, const float& Angle, const DistributionType& Distribution, TArray<float>& OutAngles)
				{
					// TODO: Checks

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
						AngleBetween = Count > 1 ? Angle / (Count - 1) : 0.0f;
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

			#undef SpreadAngleType
			#undef DistributionType
		}
	}
}