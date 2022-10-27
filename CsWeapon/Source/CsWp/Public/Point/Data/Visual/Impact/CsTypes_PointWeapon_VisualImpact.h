// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/FX/CsTypes_FX.h"
#include "Engine/DataTable.h"
// Types
#include "Utility/CsWpLog.h"

#include "CsTypes_PointWeapon_VisualImpact.generated.h"

// FCsPointWeapon_FX_ImpactInfo
#pragma region

// NCsWeapon::NPoint::NImpact::NVisual::NFX::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NImpact, NVisual, NFX, FInfo)

/**
* Container holding Impact Visual FX information for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_FX_ImpactInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsFX FX;

	/** Whether to Scale the FX by a Damage Range associated with the Point Weapon.
		 Damage Range is an object that implements the interface: NCsDamage::NRange::IRange.
		NOTE: Damage Range MUST exist. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	bool bScaleByDamageRange;

public:

	FCsPointWeapon_FX_ImpactInfo() :
		FX(),
		bScaleByDamageRange(false)
	{
	}

#define InfoType NCsWeapon::NPoint::NImpact::NVisual::NFX::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NImpact
		{
			namespace NVisual
			{
				namespace NFX
				{
					struct CSWP_API FInfo
					{
					private:

						CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
						CS_DECLARE_MEMBER_WITH_PROXY(bScaleByDamageRange, bool)

					public:

						FInfo() :
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bScaleByDamageRange, false)
						{
							CS_CTOR_SET_MEMBER_PROXY(FX);
							CS_CTOR_SET_MEMBER_PROXY(bScaleByDamageRange);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bScaleByDamageRange, bool)

						void Copy(const FInfo& From)
						{
							SetFX(From.GetFX());
							SetbScaleByDamageRange(From.GetbScaleByDamageRange());
						}

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsPointWeapon_FX_ImpactInfo

// FCsPointWeapon_Visual_ImpactInfo
#pragma region

// NCsWeapon::NPoint::NImpact::NVisual::NFInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NImpact, NVisual, FInfo)

/**
* Container holding any Impact Visual information for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_Visual_ImpactInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	TEnumAsByte<EPhysicalSurface> Surface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (DisplayName = "FX Info"))
	FCsPointWeapon_FX_ImpactInfo FXInfo;

public:

	FCsPointWeapon_Visual_ImpactInfo() :
		Surface(EPhysicalSurface::SurfaceType_Default),
		FXInfo()
	{
	}

#define InfoType NCsWeapon::NPoint::NImpact::NVisual::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NImpact
		{
			namespace NVisual
			{
				struct CSWP_API FInfo
				{
				#define ImpactFXInfoType NCsWeapon::NPoint::NImpact::NVisual::NFX::FInfo

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(Surface, EPhysicalSurface)

					ImpactFXInfoType FXInfo;

				public:

					FInfo() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Surface, EPhysicalSurface::SurfaceType_Default),
						FXInfo()
					{
						CS_CTOR_SET_MEMBER_PROXY(Surface);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Surface, EPhysicalSurface)

					FORCEINLINE const ImpactFXInfoType& GetFXInfo() const { return FXInfo; }
					FORCEINLINE ImpactFXInfoType& GetFXInfo() { return FXInfo; }
					FORCEINLINE ImpactFXInfoType* GetFXInfoPtr() { return &FXInfo; }

					void Copy(const FInfo& From)
					{
						SetSurface(From.GetSurface());
						FXInfo.Copy(From.GetFXInfo());
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef ImpactFXInfoType
				};
			}
		}
	}
}

#pragma endregion FCsPointWeapon_Visual_ImpactInfo