// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Projectile/Params/Spread/CsTypes_ProjectileWeapon_Spread.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_ProjectileWeapon_Spread.generated.h"

// FCsProjectileWeapon_Spread_ShapeParams
#pragma region

// NCsWeapon::NProjectile::NSpread::NShape::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NSpread, NShape, FParams)

/**
* Describes any information related to Spread Shape for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Spread_ShapeParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the Spread Shape. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSpreadShape Shape;

	/** Describes the dimensions for the Shape.
		If Shape == ECsProjectileWeaponSpreadShape::Line: 
			Only Extents.X is used for the offset in Left and Right vectors from the default
			Launch Direction
		if Shape == ECsProjectileWeaponSpreadShape::Rectangle:
			Only Extents.X and Extents.Y are used.
			Extents.X is the offset in Left and Right vectors from the default Launch Location.
			Extents.Y is the offset Up and Down from the World Up vector.
		if Shape == ECsProjectileWeaponSpreadShape::Circle:
			Only Extents.X and Extents.Y are used.
			Extents.X is the Inner Radius.
			Extents.Y is the Outer Radius.
			Only Extents.X and Extents.Y are used for the Radius around the default Launch Direction.
			The Radius is represented by the Right vector with respect to the 
			default Launch Direction and World Up vector.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	FVector Extents;

	/** Describes the Axis by which the start locations within a Spread Shape are Distributed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSpreadShapeAxis Axis;

	/** Describes the distribution of start locations within a Spread Shape. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSpreadShapeDistribution Distribution;

	FCsProjectileWeapon_Spread_ShapeParams() :
		Shape(ECsProjectileWeaponSpreadShape::Line),
		Extents(0.0f),
		Axis(ECsProjectileWeaponSpreadShapeAxis::Up),
		Distribution(ECsProjectileWeaponSpreadShapeDistribution::Random)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NSpread::NShape::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NShape
			{
				/**
				* Describes any information related to Spread Shape for a Projectile Weapon.
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				struct CSWP_API FParams
				{
				#define ShapeType NCsWeapon::NProjectile::NSpread::EShape
				#define AxisType NCsWeapon::NProjectile::NSpread::NShape::EAxis
				#define DistributionType NCsWeapon::NProjectile::NSpread::NShape::EDistribution

				private:

					/** Describes the Spread Shape. */
					CS_DECLARE_MEMBER_WITH_PROXY(Shape, ShapeType)
					/** Describes the dimensions for the Shape.
						If Shape == ShapeType::Line (NCsWeapon::NProjectile::NSpread::EShape::Line): 
							Only Extents.X is used for the offset in Left and Right vectors from the default
							Launch Direction
						if Shape == ShapeType::Rectangle (NCsWeapon::NProjectile::NSpread::EShape::Rectangle):
							Only Extents.X and Extents.Y are used.
							Extents.X is the offset in Left and Right vectors from the default Launch Location.
							Extents.Y is the offset Up and Down from the World Up vector.
						if Shape == ShapeType::Circle (NCsWeapon::NProjectile::NSpread::EShape::Circle):
							Only Extents.X and Extents.Y are used.
							Extents.X is the Inner Radius.
							Extents.Y is the Outer Radius.
							Only Extents.X and Extents.Y are used for the Radius around the default Launch Direction.
							The Radius is represented by the Right vector with respect to the
							default Launch Direction and World Up vector.
					*/
					CS_DECLARE_MEMBER_WITH_PROXY(Extents, FVector)
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
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Extents, FVector)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Distribution, DistributionType)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					
					FORCEINLINE bool ShouldPrecalculate() const { return NCsWeapon::NProjectile::NSpread::NShape::NDistribution::ShouldPrecalculate(GetDistribution()); }
					/*
					FORCEINLINE void SetAnglesChecked(const FString& Context, const int32& Count, TArray<float>& OutAngles) const
					{
						NCsWeapon::NProjectile::NSpread::FLibrary::SetAnglesChecked(Context, Count, GetAngleType(), GetAngle(), GetDistribution(), OutAngles);
					}
					*/
					FORCEINLINE FVector GetRandomOffsetChecked(const FString& Context) const
					{
						return NCsWeapon::NProjectile::NSpread::FLibrary::GetRandomOffsetChecked(Context, GetShape(), GetExtents(), GetDistribution());
					}

				#undef ShapeType
				#undef AxisType
				#undef DistributionType
				};
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Spread_ShapeParams

// FCsProjectileWeapon_Spread_AngleParams
#pragma region

// NCsWeapon::NProjectile::NSpread::NAngle::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NSpread, NAngle, FParams)

/**
* Describes any information related to spread along an angle axis for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Spread_AngleParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes how the Spread Angle should be interpreted. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSpreadAngle AngleType;

	/** The angle in degrees to use for spread. 
		NOTE: NOT used if AngleType == ECsProjectileWeaponSpreadAngle::RangeMinMax. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0"))
	float Angle;

	/** The minimum angle in degrees to use for spread.
		NOTE: ONLY used if AngleType == ECsProjectileWeaponSpreadAngle::RangeMinMax. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (UIMin = "-180.0", ClampMin = "-180.0", UIMax = "0.0", ClampMax = "0.0"))
	float Min;

	/** The maximum angle in degrees to use for spread.
		NOTE: ONLY used if AngleType == ECsProjectileWeaponSpreadAngle::RangeMinMax. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0"))
	float Max;

	/** How to populate the list of angles for the spread. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSpreadAngleDistribution Distribution;

	FCsProjectileWeapon_Spread_AngleParams() :
		AngleType(ECsProjectileWeaponSpreadAngle::DivideByCount),
		Angle(0.0f),
		Min(0.0f),
		Max(0.0f),
		Distribution(ECsProjectileWeaponSpreadAngleDistribution::Shuffle)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NSpread::NAngle::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NAngle
			{
				/**
				* Describes any information related to spread along an angle axis for a Projectile Weapon.
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				struct CSWP_API FParams
				{
				#define SpreadAngleType NCsWeapon::NProjectile::NSpread::EAngle
				#define DistributionType NCsWeapon::NProjectile::NSpread::NAngle::EDistribution

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

					FORCEINLINE bool ShouldPrecalculate() const { return NCsWeapon::NProjectile::NSpread::NAngle::NDistribution::ShouldPrecalculate(GetDistribution()); }

					FORCEINLINE void SetAnglesChecked(const FString& Context, const int32& Count, TArray<float>& OutAngles) const
					{
						NCsWeapon::NProjectile::NSpread::FLibrary::SetAnglesChecked(Context, Count, GetAngleType(), GetAngle(), GetDistribution(), OutAngles);
					}

					FORCEINLINE float GetRandomAngleChecked(const FString& Context) const
					{
						return NCsWeapon::NProjectile::NSpread::FLibrary::GetRandomAngleChecked(Context, GetAngleType(), GetAngle(), GetDistribution());
					}

				#undef SpreadAngleType
				#undef DistributionType
				};
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Spread_AngleParams

// FCsProjectileWeapon_SpreadParams
#pragma region

// NCsWeapon::NProjectile::NSpread::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NProjectile, NSpread, FParams)

/**
* Describes any information related to spread for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_SpreadParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (InlineEditConditionToggle))
	bool bShape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (editcondition = "bShape"))
	FCsProjectileWeapon_Spread_ShapeParams ShapeParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (InlineEditConditionToggle))
	bool bYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (editcondition = "bYaw"))
	FCsProjectileWeapon_Spread_AngleParams YawParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (InlineEditConditionToggle))
	bool bPitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (editcondition = "bPitch"))
	FCsProjectileWeapon_Spread_AngleParams PitchParams;

	FCsProjectileWeapon_SpreadParams() :
		bShape(false),
		ShapeParams(),
		bYaw(true),
		YawParams(),
		bPitch(false),
		PitchParams()
	{
	}

#define ParamsType NCsWeapon::NProjectile::NSpread::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			/**
			* Describes any information related to spread for a Projectile Weapon.
			*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
			*/
			struct CSWP_API FParams
			{
			#define ShapeParamsType NCsWeapon::NProjectile::NSpread::NShape::FParams
			#define AngleParamsType NCsWeapon::NProjectile::NSpread::NAngle::FParams

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(bShape, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(bYaw, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(bPitch, bool)

			public:

				ShapeParamsType ShapeParams;

				AngleParamsType YawParams;
				AngleParamsType PitchParams;

				FParams() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bYaw, true),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bPitch, false),
					YawParams(),
					PitchParams()
				{
					CS_CTOR_SET_MEMBER_PROXY(bYaw);
					CS_CTOR_SET_MEMBER_PROXY(bPitch);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bShape, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bYaw, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPitch, bool)
				FORCEINLINE const ShapeParamsType& GetShapeParams() const { return ShapeParams; }
				FORCEINLINE ShapeParamsType* GetShapeParamsPtr() { return &ShapeParams; }
				FORCEINLINE const AngleParamsType& GetYawParams() const { return YawParams; }
				FORCEINLINE AngleParamsType* GetYawParamsPtr() { return &YawParams; }
				FORCEINLINE const AngleParamsType& GetPitchParams() const { return PitchParams; }
				FORCEINLINE AngleParamsType* GetPitchParamsPtr() { return &PitchParams; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

			#undef ShapeParamsType
			#undef AngleParamsType
			};
		}
	}
}

#pragma endregion FCsProjectileWeapon_SpreadParams