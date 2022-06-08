// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Projectile/Params/Spread/CsTypes_ProjectileWeapon_Spread.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_ProjectileWeapon_Spread.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSpreadAngle AngleType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0"))
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponSpreadDistribution Distribution;

	FCsProjectileWeapon_Spread_AngleParams() :
		AngleType(ECsProjectileWeaponSpreadAngle::DivideByCount),
		Angle(0.0f),
		Distribution(ECsProjectileWeaponSpreadDistribution::Shuffle)
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
				#define DistributionType NCsWeapon::NProjectile::NSpread::EDistribution

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(AngleType, SpreadAngleType)
					CS_DECLARE_MEMBER_WITH_PROXY(Angle, float)
					CS_DECLARE_MEMBER_WITH_PROXY(Distribution, DistributionType)

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(AngleType, SpreadAngleType::DivideByCount),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Angle, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Distribution, DistributionType::Shuffle)
					{
						CS_CTOR_SET_MEMBER_PROXY(AngleType);
						CS_CTOR_SET_MEMBER_PROXY(Angle);
						CS_CTOR_SET_MEMBER_PROXY(Distribution);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AngleType, SpreadAngleType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Angle, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Distribution, DistributionType)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

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
	bool bYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (editcondition = "bYaw"))
	FCsProjectileWeapon_Spread_AngleParams YawParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (InlineEditConditionToggle))
	bool bPitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (editcondition = "bPitch"))
	FCsProjectileWeapon_Spread_AngleParams PitchParams;

	FCsProjectileWeapon_SpreadParams() :
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
			#define AngleParamsType NCsWeapon::NProjectile::NSpread::NAngle::FParams

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(bYaw, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(bPitch, bool)

			public:

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

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bYaw, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPitch, bool)
				FORCEINLINE const AngleParamsType& GetYawParams() const { return YawParams; }
				FORCEINLINE AngleParamsType* GetYawParamsPtr() { return &YawParams; }
				FORCEINLINE const AngleParamsType& GetPitchParams() const { return PitchParams; }
				FORCEINLINE AngleParamsType* GetPitchParamsPtr() { return &PitchParams; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

			#undef AngleParamsType
			};
		}
	}
}

#pragma endregion FCsProjectileWeapon_SpreadParams