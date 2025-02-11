// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Spread/CsParams_ProjectileWeapon_Spread.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_ProjectileWeapon_Spread)

// FCsProjectileWeapon_Spread_ShapeParams
#pragma region

namespace NCsProjectileWeapon_Spread_ShapeParams
{
	using ShapeType = NCsWeapon::NProjectile::NSpread::EShape;
	using AxisType = NCsWeapon::NProjectile::NSpread::NShape::EAxis;
	using DistributionType = NCsWeapon::NProjectile::NSpread::NShape::EDistribution;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Shape, ShapeType);
		CS_THIS_COPY_TO_PROXY(Params, Extents);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Axis, AxisType);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Distribution, DistributionType);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Shape, ShapeType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Extents);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Axis, AxisType);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Distribution, DistributionType);
	}
}

bool FCsProjectileWeapon_Spread_ShapeParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponSpreadShape, Shape)
	CS_IS_VECTOR_ZERO_CHECKED(Extents)
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponSpreadShapeAxis, Axis)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL_CHECKED(Extents, 0.0f)
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponSpreadShapeDistribution, Distribution)

	// Line
	if (Shape == ECsProjectileWeaponSpreadShape::Line)
	{
		checkf(Extents.X > 0.0f, TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Line, then Extents.X MUST be > 0.0f."), *Context);
	}
	// Rectangle
	else
	if (Shape == ECsProjectileWeaponSpreadShape::Rectangle)
	{
		checkf(Extents.X > 0.0f, TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context);
		checkf(Extents.Y > 0.0f, TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Rectangle, then Extents.Y MUST be > 0.0f."), *Context);
	}
	// Circle
	else
	if (Shape == ECsProjectileWeaponSpreadShape::Circle)
	{
		checkf(Extents.Y > 0.0f, TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST be > 0.0f."), *Context);
		checkf(Extents.Y > Extents.X, TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST > Extents.X (Inner Radius)."), *Context);
	}
	return true;
}

bool FCsProjectileWeapon_Spread_ShapeParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsProjectileWeaponSpreadShape, ECsProjectileWeaponSpreadShape, Shape)
	CS_IS_VECTOR_ZERO(Extents)
	CS_IS_ENUM_VALID(EMCsProjectileWeaponSpreadShapeAxis, ECsProjectileWeaponSpreadShapeAxis, Axis)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL(Extents, 0.0f)
	CS_IS_ENUM_VALID(EMCsProjectileWeaponSpreadShapeDistribution, ECsProjectileWeaponSpreadShapeDistribution, Distribution)

	// Line
	if (Shape == ECsProjectileWeaponSpreadShape::Line)
	{
		if (Extents.X <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Line, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}
	}
	// Rectangle
	else
	if (Shape == ECsProjectileWeaponSpreadShape::Rectangle)
	{
		if (Extents.X <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}

		if (Extents.Y <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}
	}
	// Circle
	else
	if (Shape == ECsProjectileWeaponSpreadShape::Circle)
	{
		if (Extents.Y <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST be > 0.0f."), *Context));
			return false;
		}

		if (Extents.Y <= Extents.X)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsProjectileWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST > Extents.X (Inner Radius)."), *Context));
			return false;
		}
	}
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NShape
			{
				using ShapeMapType = NCsWeapon::NProjectile::NSpread::EMShape;
				using AxisMapType = NCsWeapon::NProjectile::NSpread::NShape::EMAxis;
				using DistributionMapType = NCsWeapon::NProjectile::NSpread::NShape::EMDistribution;

				bool FParams::IsValidChecked(const FString& Context) const
				{
					CS_IS_ENUM_VALID_CHECKED(ShapeMapType, GetShape())
					CS_IS_VECTOR_ZERO_CHECKED(GetExtents())
					CS_IS_ENUM_VALID_CHECKED(AxisMapType, GetAxis())
					CS_IS_ENUM_VALID_CHECKED(DistributionMapType, GetDistribution())
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					CS_IS_ENUM_VALID(ShapeMapType, ShapeType, GetShape())
					CS_IS_VECTOR_ZERO(GetExtents())
					CS_IS_ENUM_VALID(AxisMapType, AxisType, GetAxis())
					CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Spread_ShapeParams

// FCsProjectileWeapon_Spread_AngleParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NSpread::NAngle::FParams

void FCsProjectileWeapon_Spread_AngleParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NProjectile::NSpread::EAngle SpreadAngleType;

	Params->SetAngleType((SpreadAngleType*)(&AngleType));
	Params->SetAngle(&Angle);
	Params->SetMin(&Min);
	Params->SetMax(&Max);

	typedef NCsWeapon::NProjectile::NSpread::NAngle::EDistribution DistributionType;

	Params->SetDistribution((DistributionType*)(&Distribution));
}

void FCsProjectileWeapon_Spread_AngleParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NProjectile::NSpread::EAngle SpreadAngleType;

	Params->SetAngleType((SpreadAngleType)AngleType);
	Params->SetAngle(Angle);
	Params->SetMin(Min);
	Params->SetMax(Max);

	typedef NCsWeapon::NProjectile::NSpread::NAngle::EDistribution DistributionType;

	Params->SetDistribution((DistributionType)Distribution);
}

#undef ParamsType

bool FCsProjectileWeapon_Spread_AngleParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 180.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Max, Min)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Min, -180.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Max, 180.0f)
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponSpreadAngleDistribution, Distribution)
	return true;
}

bool FCsProjectileWeapon_Spread_AngleParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsProjectileWeaponSpreadAngle, ECsProjectileWeaponSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Angle, 180.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Max, Min)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Min, -180.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Max, 180.0f)
	CS_IS_ENUM_VALID(EMCsProjectileWeaponSpreadAngleDistribution, ECsProjectileWeaponSpreadAngleDistribution, Distribution)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NAngle
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NProjectile::NSpread::EMAngle SpreadAngleMapType;

					CS_IS_ENUM_VALID_CHECKED(SpreadAngleMapType, GetAngleType())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetAngle(), 0.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetAngle(), 180.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMax(), GetMin())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMin(), -180.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetMax(), 180.0f)

					typedef NCsWeapon::NProjectile::NSpread::NAngle::EMDistribution DistributionMapType;

					CS_IS_ENUM_VALID_CHECKED(DistributionMapType, GetDistribution())
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NProjectile::NSpread::EMAngle SpreadAngleMapType;
					typedef NCsWeapon::NProjectile::NSpread::EAngle SpreadAngleType;

					CS_IS_ENUM_VALID(SpreadAngleMapType, SpreadAngleType, GetAngleType())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetAngle(), 0.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetAngle(), 180.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMax(), GetMin())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMin(), -180.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetMax(), 180.0f)

					typedef NCsWeapon::NProjectile::NSpread::NAngle::EMDistribution DistributionMapType;
					typedef NCsWeapon::NProjectile::NSpread::NAngle::EDistribution DistributionType;

					CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Spread_AngleParams

// FCsProjectileWeapon_SpreadParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NSpread::FParams

void FCsProjectileWeapon_SpreadParams::CopyToParams(ParamsType* Params)
{
	Params->SetbShape(&bShape);
	ShapeParams.CopyToParams(Params->GetShapeParamsPtr());
	Params->SetbYaw(&bYaw);
	YawParams.CopyToParams(Params->GetYawParamsPtr());
	Params->SetbPitch(&bPitch);
	PitchParams.CopyToParams(Params->GetPitchParamsPtr());
}

void FCsProjectileWeapon_SpreadParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbShape(bShape);
	ShapeParams.CopyToParamsAsValue(Params->GetShapeParamsPtr());
	Params->SetbYaw(bYaw);
	YawParams.CopyToParamsAsValue(Params->GetYawParamsPtr());
	Params->SetbPitch(bPitch);
	PitchParams.CopyToParamsAsValue(Params->GetPitchParamsPtr());
}

#undef ParamsType

bool FCsProjectileWeapon_SpreadParams::IsValidChecked(const FString& Context) const
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

bool FCsProjectileWeapon_SpreadParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
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

namespace NCsWeapon
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

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
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

#pragma endregion FCsProjectileWeapon_SpreadParams