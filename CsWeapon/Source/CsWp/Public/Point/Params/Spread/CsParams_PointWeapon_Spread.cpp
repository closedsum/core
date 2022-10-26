// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Params/Spread/CsParams_PointWeapon_Spread.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsPointWeapon_Spread_ShapeParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSpread::NShape::FParams

void FCsPointWeapon_Spread_ShapeParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NPoint::NSpread::EShape ShapeType;

	Params->SetShape((ShapeType*)(&Shape));
	Params->SetExtents(&Extents);

	typedef NCsWeapon::NPoint::NSpread::NShape::EAxis AxisType;

	Params->SetAxis((AxisType*)(&Axis));

	typedef NCsWeapon::NPoint::NSpread::NShape::EDistribution DistributionType;

	Params->SetDistribution((DistributionType*)(&Distribution));
}

void FCsPointWeapon_Spread_ShapeParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NPoint::NSpread::EShape ShapeType;

	Params->SetShape((ShapeType)Shape);
	Params->SetExtents(Extents);

	typedef NCsWeapon::NPoint::NSpread::NShape::EAxis AxisType;

	Params->SetAxis((AxisType)Axis);

	typedef NCsWeapon::NPoint::NSpread::NShape::EDistribution DistributionType;

	Params->SetDistribution((DistributionType)Distribution);
}

#undef ParamsType

bool FCsPointWeapon_Spread_ShapeParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsPointWeaponSpreadShape, Shape)
	CS_IS_VECTOR_ZERO_CHECKED(Extents)
	CS_IS_ENUM_VALID_CHECKED(EMCsPointWeaponSpreadShapeAxis, Axis)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL_CHECKED(Extents, 0.0f)
	CS_IS_ENUM_VALID_CHECKED(EMCsPointWeaponSpreadShapeDistribution, Distribution)

	// Line
	if (Shape == ECsPointWeaponSpreadShape::Line)
	{
		checkf(Extents.X > 0.0f, TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Line, then Extents.X MUST be > 0.0f."), *Context);
	}
	// Rectangle
	else
	if (Shape == ECsPointWeaponSpreadShape::Rectangle)
	{
		checkf(Extents.X > 0.0f, TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context);
		checkf(Extents.Y > 0.0f, TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Rectangle, then Extents.Y MUST be > 0.0f."), *Context);
	}
	// Circle
	else
	if (Shape == ECsPointWeaponSpreadShape::Circle)
	{
		checkf(Extents.Y > 0.0f, TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST be > 0.0f."), *Context);
		checkf(Extents.Y > Extents.X, TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST > Extents.X (Inner Radius)."), *Context);
	}
	return true;
}

bool FCsPointWeapon_Spread_ShapeParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsPointWeaponSpreadShape, ECsPointWeaponSpreadShape, Shape)
	CS_IS_VECTOR_ZERO(Extents)
	CS_IS_ENUM_VALID(EMCsPointWeaponSpreadShapeAxis, ECsPointWeaponSpreadShapeAxis, Axis)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL(Extents, 0.0f)
	CS_IS_ENUM_VALID(EMCsPointWeaponSpreadShapeDistribution, ECsPointWeaponSpreadShapeDistribution, Distribution)

	// Line
	if (Shape == ECsPointWeaponSpreadShape::Line)
	{
		if (Extents.X <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Line, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}
	}
	// Rectangle
	else
	if (Shape == ECsPointWeaponSpreadShape::Rectangle)
	{
		if (Extents.X <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}

		if (Extents.Y <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Rectangle, then Extents.X MUST be > 0.0f."), *Context));
			return false;
		}
	}
	// Circle
	else
	if (Shape == ECsPointWeaponSpreadShape::Circle)
	{
		if (Extents.Y <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST be > 0.0f."), *Context));
			return false;
		}

		if (Extents.Y <= Extents.X)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: if Shape == ECsPointWeaponSpreadShape::Circle, then Extents.Y (Outer Radius) MUST > Extents.X (Inner Radius)."), *Context));
			return false;
		}
	}
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			namespace NShape
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NPoint::NSpread::EMShape ShapeMapType;

					CS_IS_ENUM_VALID_CHECKED(ShapeMapType, GetShape())
					CS_IS_VECTOR_ZERO_CHECKED(GetExtents())

					typedef NCsWeapon::NPoint::NSpread::NShape::EMAxis AxisMapType;

					CS_IS_ENUM_VALID_CHECKED(AxisMapType, GetAxis())

					typedef NCsWeapon::NPoint::NSpread::NShape::EMDistribution DistributionMapType;

					CS_IS_ENUM_VALID_CHECKED(DistributionMapType, GetDistribution())
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NPoint::NSpread::EMShape ShapeMapType;
					typedef NCsWeapon::NPoint::NSpread::EShape ShapeType;

					CS_IS_ENUM_VALID(ShapeMapType, ShapeType, GetShape())
					CS_IS_VECTOR_ZERO(GetExtents())

					typedef NCsWeapon::NPoint::NSpread::NShape::EMAxis AxisMapType;
					typedef NCsWeapon::NPoint::NSpread::NShape::EAxis AxisType;

					CS_IS_ENUM_VALID(AxisMapType, AxisType, GetAxis())

					typedef NCsWeapon::NPoint::NSpread::NShape::EMDistribution DistributionMapType;
					typedef NCsWeapon::NPoint::NSpread::NShape::EDistribution DistributionType;

					CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsPointWeapon_Spread_ShapeParams

// FCsPointWeapon_Spread_AngleParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSpread::NAngle::FParams

void FCsPointWeapon_Spread_AngleParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NPoint::NSpread::EAngle SpreadAngleType;

	Params->SetAngleType((SpreadAngleType*)(&AngleType));
	Params->SetAngle(&Angle);
	Params->SetMin(&Min);
	Params->SetMax(&Max);

	typedef NCsWeapon::NPoint::NSpread::NAngle::EDistribution DistributionType;

	Params->SetDistribution((DistributionType*)(&Distribution));
}

void FCsPointWeapon_Spread_AngleParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NPoint::NSpread::EAngle SpreadAngleType;

	Params->SetAngleType((SpreadAngleType)AngleType);
	Params->SetAngle(Angle);
	Params->SetMin(Min);
	Params->SetMax(Max);

	typedef NCsWeapon::NPoint::NSpread::NAngle::EDistribution DistributionType;

	Params->SetDistribution((DistributionType)Distribution);
}

#undef ParamsType

bool FCsPointWeapon_Spread_AngleParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsPointWeaponSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 180.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Max, Min)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Min, -180.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Max, 180.0f)
	CS_IS_ENUM_VALID_CHECKED(EMCsPointWeaponSpreadAngleDistribution, Distribution)
	return true;
}

bool FCsPointWeapon_Spread_AngleParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsPointWeaponSpreadAngle, ECsPointWeaponSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Angle, 180.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Max, Min)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Min, -180.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Max, 180.0f)
	CS_IS_ENUM_VALID(EMCsPointWeaponSpreadAngleDistribution, ECsPointWeaponSpreadAngleDistribution, Distribution)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			namespace NAngle
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NPoint::NSpread::EMAngle SpreadAngleMapType;

					CS_IS_ENUM_VALID_CHECKED(SpreadAngleMapType, GetAngleType())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetAngle(), 0.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetAngle(), 180.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMax(), GetMin())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMin(), -180.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetMax(), 180.0f)

					typedef NCsWeapon::NPoint::NSpread::NAngle::EMDistribution DistributionMapType;

					CS_IS_ENUM_VALID_CHECKED(DistributionMapType, GetDistribution())
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NPoint::NSpread::EMAngle SpreadAngleMapType;
					typedef NCsWeapon::NPoint::NSpread::EAngle SpreadAngleType;

					CS_IS_ENUM_VALID(SpreadAngleMapType, SpreadAngleType, GetAngleType())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetAngle(), 0.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetAngle(), 180.0f)
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMax(), GetMin())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMin(), -180.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetMax(), 180.0f)

					typedef NCsWeapon::NPoint::NSpread::NAngle::EMDistribution DistributionMapType;
					typedef NCsWeapon::NPoint::NSpread::NAngle::EDistribution DistributionType;

					CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsPointWeapon_Spread_AngleParams

// FCsPointWeapon_SpreadParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSpread::FParams

void FCsPointWeapon_SpreadParams::CopyToParams(ParamsType* Params)
{
	Params->SetbShape(&bShape);
	ShapeParams.CopyToParams(Params->GetShapeParamsPtr());
	Params->SetbYaw(&bYaw);
	YawParams.CopyToParams(Params->GetYawParamsPtr());
	Params->SetbPitch(&bPitch);
	PitchParams.CopyToParams(Params->GetPitchParamsPtr());
}

void FCsPointWeapon_SpreadParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbShape(bShape);
	ShapeParams.CopyToParamsAsValue(Params->GetShapeParamsPtr());
	Params->SetbYaw(bYaw);
	YawParams.CopyToParamsAsValue(Params->GetYawParamsPtr());
	Params->SetbPitch(bPitch);
	PitchParams.CopyToParamsAsValue(Params->GetPitchParamsPtr());
}

#undef ParamsType

bool FCsPointWeapon_SpreadParams::IsValidChecked(const FString& Context) const
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

bool FCsPointWeapon_SpreadParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
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
	namespace NPoint
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

#pragma endregion FCsPointWeapon_SpreadParams