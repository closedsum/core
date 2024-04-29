// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
#include "Point/Params/Spread/CsTypes_PointWeapon_Spread.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointWeapon_Spread.generated.h"

// FCsPointWeapon_Spread_ShapeParams
#pragma region

// NCsWeapon::NPoint::NSpread::NShape::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NSpread, NShape, FParams)

/**
* Describes any information related to Spread Shape for a Point Weapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_Spread_ShapeParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the Spread Shape. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponSpreadShape Shape;

	/** Describes the dimensions for the Shape.
		If Shape == ECsPointWeaponSpreadShape::Line: 
			Only Extents.X is used for the offset in Left and Right vectors from the default
			Launch Direction
		if Shape == ECsPointWeaponSpreadShape::Rectangle:
			Only Extents.X and Extents.Y are used.
			Extents.X is the offset in Left and Right vectors from the default Location.
			Extents.Y is the offset Up and Down from the World Up vector.
		if Shape == ECsPointWeaponSpreadShape::Circle:
			Only Extents.X and Extents.Y are used.
			Extents.X is the Inner Radius.
			Extents.Y is the Outer Radius.
			Only Extents.X and Extents.Y are used for the Radius around the default Direction.
			The Radius is represented by the Right vector with respect to the 
			default Direction and World Up vector.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FVector3f Extents;

	/** Describes the Axis by which the start locations within a Spread Shape are Distributed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponSpreadShapeAxis Axis;

	/** Describes the distribution of start locations within a Spread Shape. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponSpreadShapeDistribution Distribution;

	FCsPointWeapon_Spread_ShapeParams() :
		Shape(ECsPointWeaponSpreadShape::Line),
		Extents(0.0f),
		Axis(ECsPointWeaponSpreadShapeAxis::Up),
		Distribution(ECsPointWeaponSpreadShapeDistribution::Random)
	{
	}

#define ParamsType NCsWeapon::NPoint::NSpread::NShape::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			namespace NShape
			{
				/**
				* Describes any information related to Spread Shape for a Point Weapon.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon.
				*/
				struct CSWP_API FParams
				{
				#define ShapeType NCsWeapon::NPoint::NSpread::EShape
				#define AxisType NCsWeapon::NPoint::NSpread::NShape::EAxis
				#define DistributionType NCsWeapon::NPoint::NSpread::NShape::EDistribution

				private:

					/** Describes the Spread Shape. */
					CS_DECLARE_MEMBER_WITH_PROXY(Shape, ShapeType)
					/** Describes the dimensions for the Shape.
						If Shape == ShapeType::Line (NCsWeapon::NPoint::NSpread::EShape::Line): 
							Only Extents.X is used for the offset in Left and Right vectors from the default
							Direction
						if Shape == ShapeType::Rectangle (NCsWeapon::NPoint::NSpread::EShape::Rectangle):
							Only Extents.X and Extents.Y are used.
							Extents.X is the offset in Left and Right vectors from the default Location.
							Extents.Y is the offset Up and Down from the World Up vector.
						if Shape == ShapeType::Circle (NCsWeapon::NPoint::NSpread::EShape::Circle):
							Only Extents.X and Extents.Y are used.
							Extents.X is the Inner Radius.
							Extents.Y is the Outer Radius.
							Only Extents.X and Extents.Y are used for the Radius around the default Direction.
							The Radius is represented by the Right vector with respect to the
							default Direction and World Up vector.
					*/
					CS_DECLARE_MEMBER_WITH_PROXY(Extents, FVector3f)
					/** Describes the Axis by which the start locations within a Spread Shape are Distributed. */
					CS_DECLARE_MEMBER_WITH_PROXY(Axis, AxisType)
					/** Describes the distribution of start locations within a Spread Shape. */
					CS_DECLARE_MEMBER_WITH_PROXY(Distribution, DistributionType)

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Shape, ShapeType::Line),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Extents, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Axis, AxisType::Up),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Distribution, DistributionType::Random)
					{
						CS_CTOR_SET_MEMBER_PROXY(Shape);
						CS_CTOR_SET_MEMBER_PROXY(Axis);
						CS_CTOR_SET_MEMBER_PROXY(Extents);
						CS_CTOR_SET_MEMBER_PROXY(Distribution);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Shape, ShapeType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Axis, AxisType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Extents, FVector3f)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Distribution, DistributionType)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					
					FORCEINLINE bool ShouldPrecalculate() const { return NCsWeapon::NPoint::NSpread::NShape::NDistribution::ShouldPrecalculate(GetDistribution()); }
					/*
					FORCEINLINE void SetAnglesChecked(const FString& Context, const int32& Count, TArray<float>& OutAngles) const
					{
						NCsWeapon::NPoint::NSpread::FLibrary::SetAnglesChecked(Context, Count, GetAngleType(), GetAngle(), GetDistribution(), OutAngles);
					}
					*/
					FORCEINLINE FVector3f GetRandomOffsetChecked(const FString& Context) const
					{
						return NCsWeapon::NPoint::NSpread::FLibrary::GetRandomOffsetChecked(Context, GetShape(), GetExtents(), GetDistribution());
					}

				#undef ShapeType
				#undef AxisType
				#undef DistributionType
				};
			}
		}
	}
}

#pragma endregion FCsPointWeapon_Spread_ShapeParams

// FCsPointWeapon_Spread_AngleParams
#pragma region

// NCsWeapon::NPoint::NSpread::NAngle::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NSpread, NAngle, FParams)

/**
* Describes any information related to spread along an angle axis for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_Spread_AngleParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes how the Spread Angle should be interpreted. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponSpreadAngle AngleType;

	/** The angle in degrees to use for spread. 
		NOTE: NOT used if AngleType == ECsProjectileWeaponSpreadAngle::RangeMinMax. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0"))
	float Angle;

	/** The minimum angle in degrees to use for spread.
		NOTE: ONLY used if AngleType == ECsProjectileWeaponSpreadAngle::RangeMinMax. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "-180.0", ClampMin = "-180.0", UIMax = "180.0", ClampMax = "180.0"))
	float Min;

	/** The maximum angle in degrees to use for spread.
		NOTE: ONLY used if AngleType == ECsProjectileWeaponSpreadAngle::RangeMinMax. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (UIMin = "-180.0", ClampMin = "-180.0", UIMax = "180.0", ClampMax = "180.0"))
	float Max;

	/** How to populate the list of angles for the spread. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponSpreadAngleDistribution Distribution;

	FCsPointWeapon_Spread_AngleParams() :
		AngleType(ECsPointWeaponSpreadAngle::DivideByCount),
		Angle(0.0f),
		Min(0.0f),
		Max(0.0f),
		Distribution(ECsPointWeaponSpreadAngleDistribution::Shuffle)
	{
	}

#define ParamsType NCsWeapon::NPoint::NSpread::NAngle::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			namespace NAngle
			{
				/**
				* Describes any information related to spread along an angle axis for a Point Weapon.
				*  Weapon is an object that implements the interface: ICsWeapon.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon.
				*/
				struct CSWP_API FParams
				{
				#define SpreadAngleType NCsWeapon::NPoint::NSpread::EAngle
				#define DistributionType NCsWeapon::NPoint::NSpread::NAngle::EDistribution

				private:

					/** Describes how the Spread Angle should be interpreted. */
					CS_DECLARE_MEMBER_WITH_PROXY(AngleType, SpreadAngleType)
					/** The angle in degrees to use for spread. 
						NOTE: NOT used if AngleType == SpreadAngleType::RangeMinMax. */
					CS_DECLARE_MEMBER_WITH_PROXY(Angle, float)
					/** The minimum angle in degrees to use for spread.
						NOTE: ONLY used if AngleType == SpreadAngleType::RangeMinMax. */
					CS_DECLARE_MEMBER_WITH_PROXY(Min, float)
					/** The maximum angle in degrees to use for spread.
						NOTE: ONLY used if AngleType == SpreadAngleType::RangeMinMax. */
					CS_DECLARE_MEMBER_WITH_PROXY(Max, float)
					/** How to populate the list of angles for the spread. */
					CS_DECLARE_MEMBER_WITH_PROXY(Distribution, DistributionType)

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(AngleType, SpreadAngleType::DivideByCount),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Angle, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Min, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Max, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Distribution, DistributionType::Shuffle)
					{
						CS_CTOR_SET_MEMBER_PROXY(AngleType);
						CS_CTOR_SET_MEMBER_PROXY(Angle);
						CS_CTOR_SET_MEMBER_PROXY(Min);
						CS_CTOR_SET_MEMBER_PROXY(Max);
						CS_CTOR_SET_MEMBER_PROXY(Distribution);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AngleType, SpreadAngleType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Angle, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Min, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Max, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Distribution, DistributionType)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					FORCEINLINE bool ShouldPrecalculate() const { return NCsWeapon::NPoint::NSpread::NAngle::NDistribution::ShouldPrecalculate(GetDistribution()); }

					FORCEINLINE void SetAnglesChecked(const FString& Context, const int32& Count, TArray<float>& OutAngles) const
					{
						NCsWeapon::NPoint::NSpread::FLibrary::SetAnglesChecked(Context, Count, GetAngleType(), GetAngle(), GetDistribution(), OutAngles);
					}

					FORCEINLINE float GetRandomAngleChecked(const FString& Context) const
					{
						// UniformMinMax
						if (GetAngleType() == SpreadAngleType::UniformMinMax)
							return NCsWeapon::NPoint::NSpread::FLibrary::GetRandomAngleChecked(Context, GetAngleType(), GetAngle(), GetDistribution());
						// RangeMinMax
						return NCsWeapon::NPoint::NSpread::FLibrary::GetRandomAngleChecked(Context, GetAngleType(), GetMin(), GetMax(), GetDistribution());
					}

				#undef SpreadAngleType
				#undef DistributionType
				};
			}
		}
	}
}

#pragma endregion FCsPointWeapon_Spread_AngleParams

// FCsPointWeapon_SpreadParams
#pragma region

// NCsWeapon::NPoint::NSpread::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NPoint, NSpread, FParams)

/**
* Describes any information related to spread for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_SpreadParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes any information related to Spread Shape. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FCsPointWeapon_Spread_ShapeParams ShapeParams;

	/** Whether to use Angle Params or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (InlineEditConditionToggle))
	bool bAngle;

	/** Describes any Angle information related to spread */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (editcondition = "bAngle"))
	FCsPointWeapon_Spread_AngleParams AngleParams;

	FCsPointWeapon_SpreadParams() :
		ShapeParams(),
		bAngle(false),
		AngleParams()
	{
	}

#define ParamsType NCsWeapon::NPoint::NSpread::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSpread
		{
			/**
			* Describes any information related to spread for a Point Weapon.
			*  Weapon is an object that implements the interface: ICsWeapon.
			*  Point Weapon is an object that implements the interface: ICsPointWeapon.
			*/
			struct CSWP_API FParams
			{
			#define ShapeParamsType NCsWeapon::NPoint::NSpread::NShape::FParams
			#define AngleParamsType NCsWeapon::NPoint::NSpread::NAngle::FParams

			private:

				/** Describes any information related to Spread Shape. */
				ShapeParamsType ShapeParams;
				/** Whether to use Angle Params or not. */
				CS_DECLARE_MEMBER_WITH_PROXY(bAngle, bool)
				/** Describes any Angle information related to spread */
				AngleParamsType AngleParams;

			public:

				FParams() :
					ShapeParams(),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bAngle, false),
					AngleParams()
				{
					CS_CTOR_SET_MEMBER_PROXY(bAngle);
				}

				FORCEINLINE const ShapeParamsType& GetShapeParams() const { return ShapeParams; }
				FORCEINLINE ShapeParamsType* GetShapeParamsPtr() { return &ShapeParams; }
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bAngle, bool)
				FORCEINLINE const AngleParamsType& GetAngleParams() const { return AngleParams; }
				FORCEINLINE AngleParamsType* GetAngleParamsPtr() { return &AngleParams; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

			#undef ShapeParamsType
			#undef AngleParamsType
			};
		}
	}
}

#pragma endregion FCsPointWeapon_SpreadParams