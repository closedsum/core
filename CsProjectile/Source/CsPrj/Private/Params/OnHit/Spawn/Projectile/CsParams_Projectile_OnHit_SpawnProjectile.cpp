// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Params/OnHit/Spawn/Projectile/CsParams_Projectile_OnHit_SpawnProjectile.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_Projectile_OnHit_SpawnProjectile)

// ProjectileOnHitSpawnProjectileDirection
#pragma region

namespace NCsProjectileOnHitSpawnProjectileDirection
{
	namespace Ref
	{
		typedef EMCsProjectileOnHitSpawnProjectileDirection EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Parent);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ParentInverse, "Parent Inverse");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ClosestTarget, "Closest Target");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileOnHitSpawnProjectileDirection_MAX, "MAX");
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
				namespace NDirection
				{
					namespace Ref
					{
						typedef EMDirection EnumMapType;

						CSPRJ_API CS_ADD_TO_ENUM_MAP(Parent);
						CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ParentInverse, "Parent Inverse");
						CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ClosestTarget, "Closest Target");
						CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileOnHitSpawnProjectileDirection

// FCsProjectile_OnHit_SpawnProjectile_DirectionParams
#pragma region

namespace NCsProjectile_OnHit_SpawnProjectile_DirectionParams
{
	using DirectionType = NCsProjectile::NOnHit::NSpawn::NProjectile::EDirection;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Type, DirectionType);
		CS_THIS_COPY_TO_PROXY(Params, Radius);
		CS_THIS_COPY_TO_PROXY(Params, bYaw);
		CS_THIS_COPY_TO_PROXY(Params, Yaw);
		CS_THIS_COPY_TO_PROXY(Params, bPitch);
		CS_THIS_COPY_TO_PROXY(Params, Pitch);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Type, DirectionType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Radius);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bYaw);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Yaw);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bPitch);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Pitch);
	}
}

bool FCsProjectile_OnHit_SpawnProjectile_DirectionParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileOnHitSpawnProjectileDirection, Type)

	if (Type == ECsProjectileOnHitSpawnProjectileDirection::ClosestTarget)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(Radius, 0.0f)
	}
	if (bYaw)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Yaw, -90.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Yaw, 90.0f)
	}
	if (bPitch)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Pitch, -90.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Pitch, 90.0f)
	}
	return true;
}

bool FCsProjectile_OnHit_SpawnProjectile_DirectionParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsProjectileOnHitSpawnProjectileDirection, ECsProjectileOnHitSpawnProjectileDirection, Type)

	if (Type == ECsProjectileOnHitSpawnProjectileDirection::ClosestTarget)
	{
		CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f)
	}
	if (bYaw)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Yaw, -90.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Yaw, 90.0f)
	}
	if (bPitch)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Pitch, -90.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Pitch, 90.0f)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NDirection
				{
					using DirectionMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::EMDirection;

					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_ENUM_VALID_CHECKED(DirectionMapType, GetType())

						if (GetType() == DirectionType::ClosestTarget)
						{
							CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRadius(), 0.0f)
						}
						if (GetbYaw())
						{
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetYaw(), -90.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetYaw(), 90.0f)
						}
						if (GetbPitch())
						{
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetPitch(), -90.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetPitch(), 90.0f)
						}
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						CS_IS_ENUM_VALID(DirectionMapType, DirectionType, GetType())

						if (GetType() == DirectionType::ClosestTarget)
						{
							CS_IS_FLOAT_GREATER_THAN(GetRadius(), 0.0f)
						}
						if (GetbYaw())
						{
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetYaw(), -90.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetYaw(), 90.0f)
						}
						if (GetbPitch())
						{
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetPitch(), -90.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetPitch(), 90.0f)
						}
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectile_DirectionParams

// FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams
#pragma region

namespace NCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams
{
	using ShapeType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EShape;
	using DistributionType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::EDistribution;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Shape, ShapeType);
		CS_THIS_COPY_TO_PROXY(Params, Extents);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Distribution, DistributionType);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Shape, ShapeType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Extents);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Distribution, DistributionType);
	}
}

bool FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileOnHitSpawnProjectileSpreadShape, Shape)
	CS_IS_VECTOR_ZERO_CHECKED(Extents)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL_CHECKED(Extents, 0.0f)
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileOnHitSpawnProjectileSpreadShapeDistribution, Distribution)

	// Line
	if (Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Line)
	{
		checkf(Extents.X > 0.0f, TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Line, then Extents.X MUST be > 0.0f."), *Context);
	}
	// Rectangle
	else
	if (Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle)
	{
		checkf(Extents.X > 0.0f, TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context);
		checkf(Extents.Y > 0.0f, TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle, then Extents.Y MUST be > 0.0f."), *Context);
	}
	// Circle
	else
	if (Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle)
	{
		checkf(Extents.Y > 0.0f, TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle, then Extents.Y (Outer Radius) MUST be > 0.0f."), *Context);
		checkf(Extents.Y > Extents.X, TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle, then Extents.Y (Outer Radius) MUST > Extents.X (Inner Radius)."), *Context);
	}
	return true;
}

bool FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsProjectileOnHitSpawnProjectileSpreadShape, ECsProjectileOnHitSpawnProjectileSpreadShape, Shape)
	CS_IS_VECTOR_ZERO(Extents)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL(Extents, 0.0f)
	CS_IS_ENUM_VALID(EMCsProjectileOnHitSpawnProjectileSpreadShapeDistribution, ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution, Distribution)

	// Line
	if (Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Line)
	{
		if (Extents.X <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Line, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}
	}
	// Rectangle
	else
	if (Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle)
	{
		if (Extents.X <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}

		if (Extents.Y <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}
	}
	// Circle
	else
	if (Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle)
	{
		if (Extents.Y <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle, then Extents.Y (Outer Radius) MUST be > 0.0f."), *Context));
			return false;
		}

		if (Extents.Y <= Extents.X)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle, then Extents.Y (Outer Radius) MUST > Extents.X (Inner Radius)."), *Context));
			return false;
		}
	}
	return true;
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
						using ShapeMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EMShape;
						using DistributionMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::EMDistribution;

						bool FParams::IsValidChecked(const FString& Context) const
						{
							CS_IS_ENUM_VALID_CHECKED(ShapeMapType, GetShape())
							CS_IS_VECTOR_ZERO_CHECKED(GetExtents())
							CS_IS_ENUM_VALID_CHECKED(DistributionMapType, GetDistribution())
							return true;
						}

						bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
						{
							CS_IS_ENUM_VALID(ShapeMapType, ShapeType, GetShape())
							CS_IS_VECTOR_ZERO(GetExtents())
							CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
							return true;
						}
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Spread_ShapeParams

// FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams
#pragma region

namespace NCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams
{
	using SpreadAngleType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EAngle;
	using DistributionType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::EDistribution;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Params, AngleType, SpreadAngleType);
		CS_THIS_COPY_TO_PROXY(Params, Angle);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Distribution, DistributionType);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, AngleType, SpreadAngleType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Angle);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Distribution, DistributionType);
	}
}

bool FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileOnHitSpawnProjectileSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 180.0f)
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileOnHitSpawnProjectileSpreadAngleDistribution, Distribution)
	return true;
}

bool FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsProjectileOnHitSpawnProjectileSpreadAngle, ECsProjectileOnHitSpawnProjectileSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Angle, 180.0f)
	CS_IS_ENUM_VALID(EMCsProjectileOnHitSpawnProjectileSpreadAngleDistribution, ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution, Distribution)
	return true;
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
						using SpreadAngleMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EMAngle;
						using DistributionMapType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::EMDistribution;

						bool FParams::IsValidChecked(const FString& Context) const
						{
							CS_IS_ENUM_VALID_CHECKED(SpreadAngleMapType, GetAngleType())
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetAngle(), 0.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetAngle(), 180.0f)
							CS_IS_ENUM_VALID_CHECKED(DistributionMapType, GetDistribution())
							return true;
						}

						bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
						{
							CS_IS_ENUM_VALID(SpreadAngleMapType, SpreadAngleType, GetAngleType())
							CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetAngle(), 0.0f)
							CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetAngle(), 180.0f)
							CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
							return true;
						}
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams

// FCsProjectile_OnHit_SpawnProjectile_SpreadParams
#pragma region

namespace NCsProjectile_OnHit_SpawnProjectile_SpreadParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, bShape);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, ShapeParams);
		CS_THIS_COPY_TO_PROXY(Params, bYaw);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, YawParams);
		CS_THIS_COPY_TO_PROXY(Params, bPitch);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, PitchParams);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bShape);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, ShapeParams);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bYaw);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, YawParams);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bPitch);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, PitchParams);
	}
}

bool FCsProjectile_OnHit_SpawnProjectile_SpreadParams::IsValidChecked(const FString& Context) const
{
	if (bShape)
	{
		CS_IS_VALID_CHECKED(ShapeParams);
	}

	if (bYaw)
	{
		CS_IS_VALID_CHECKED(YawParams);
	}

	if (bPitch)
	{
		CS_IS_VALID_CHECKED(PitchParams);
	}
	return true;
}

bool FCsProjectile_OnHit_SpawnProjectile_SpreadParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (bShape)
	{
		CS_IS_VALID(ShapeParams);
	}

	if (bYaw)
	{
		CS_IS_VALID(YawParams)
	}

	if (bPitch)
	{
		CS_IS_VALID(PitchParams)
	}
	return true;
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
					bool FParams::IsValidChecked(const FString& Context) const
					{
						if (GetbShape())
						{
							CS_IS_VALID_CHECKED(ShapeParams);
						}

						if (GetbYaw())
						{
							CS_IS_VALID_CHECKED(YawParams);
						}

						if (GetbPitch())
						{
							CS_IS_VALID_CHECKED(PitchParams);
						}

						checkf(GetbShape() || GetbYaw() || GetbPitch(), TEXT("%s: GetbShape() or GetbYaw() or GetbPitch() must be true."), *Context);
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						if (GetbShape())
						{
							CS_IS_VALID(ShapeParams)
						}

						if (GetbYaw())
						{
							CS_IS_VALID(YawParams)
						}

						if (GetbPitch())
						{
							CS_IS_VALID(PitchParams)
						}

						if (GetbShape() || (!GetbYaw() && !GetbPitch()))
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetbShape() or GetbYaw() or GetbPitch() must be true."), *Context));
							return false;
						}
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_SpreadParams

// FCsProjectile_OnHit_SpawnProjectileParams
#pragma region

namespace NCsProjectile_OnHit_SpawnProjectileParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_PTR_TO_PROXY(Params, Projectile);
		CS_THIS_COPY_TO_PROXY(Params, ProjectilesPerSpawn);
		CS_THIS_COPY_TO_PROXY(Params, TimeBetweenProjectilesPerSpawn);
		CS_THIS_COPY_TO_PROXY(Params, bUntilGenerationCount);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, DirectionParams);
		CS_THIS_COPY_TO_PROXY(Params, bSpreadParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, SpreadParams);
		CS_THIS_COPY_TO_PROXY(Params, bInheritModifiers);
		CS_THIS_COPY_INFO_TO_PROXY_PTR(Params, CreateModifiers);
		CS_THIS_COPY_INFO_TO_PROXY_PTR(Params, Modifiers);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_PTR_TO_PROXY_AS_VALUE(Params, Projectile);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ProjectilesPerSpawn);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, TimeBetweenProjectilesPerSpawn);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bUntilGenerationCount);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, DirectionParams);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bSpreadParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, SpreadParams);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bInheritModifiers);
		CS_THIS_COPY_INFO_TO_PROXY_PTR_AS_VALUE(Params, CreateModifiers);
		CS_THIS_COPY_INFO_TO_PROXY_PTR_AS_VALUE(Params, Modifiers);
	}
}

bool FCsProjectile_OnHit_SpawnProjectileParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Projectile);
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(ProjectilesPerSpawn, 1)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TimeBetweenProjectilesPerSpawn, 0.0f)
	
	if (bUntilGenerationCount)
	{
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GenerationCount, 1)
	}
	
	CS_IS_VALID_CHECKED(DirectionParams);

	if (bSpreadParams)
	{
		CS_IS_VALID_CHECKED(SpreadParams);
	}
	CS_IS_VALID_CHECKED(CreateModifiers);
	CS_IS_VALID_CHECKED(Modifiers);
	return true;
}

bool FCsProjectile_OnHit_SpawnProjectileParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(Projectile)
	CS_IS_INT_GREATER_THAN_OR_EQUAL(ProjectilesPerSpawn, 1)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(TimeBetweenProjectilesPerSpawn, 0.0f)
	
	if (bUntilGenerationCount)
	{
		CS_IS_INT_GREATER_THAN_OR_EQUAL(GenerationCount, 1)
	}
	
	CS_IS_VALID(DirectionParams)

	if (bSpreadParams)
	{
		CS_IS_VALID(SpreadParams)
	}
	CS_IS_VALID(CreateModifiers)
	CS_IS_VALID(Modifiers)
	return true;
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, GetProjectile())
					CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetProjectilesPerSpawn(), 1)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTimeBetweenProjectilesPerSpawn(), 0.0f)
	
					if (GetbUntilGenerationCount())
					{
						CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetGenerationCount(), 1)
					}

					CS_IS_VALID_CHECKED(DirectionParams);

					if (GetbSpreadParams())
					{
						CS_IS_VALID_CHECKED(SpreadParams);
					}
					CS_IS_VALID_CHECKED(CreateModifiers);
					CS_IS_VALID_CHECKED(Modifiers);
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, GetProjectile())
					CS_IS_INT_GREATER_THAN_OR_EQUAL(GetProjectilesPerSpawn(), 1)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTimeBetweenProjectilesPerSpawn(), 0.0f)
	
					if (GetbUntilGenerationCount())
					{
						CS_IS_INT_GREATER_THAN_OR_EQUAL(GetGenerationCount(), 1)
					}

					CS_IS_VALID(DirectionParams)

					if (GetbSpreadParams())
					{
						CS_IS_VALID(SpreadParams)
					}
					CS_IS_VALID(CreateModifiers)
					CS_IS_VALID(Modifiers)
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectileParams