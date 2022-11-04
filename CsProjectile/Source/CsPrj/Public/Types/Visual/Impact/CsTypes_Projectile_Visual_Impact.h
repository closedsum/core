// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/FX/CsTypes_FX.h"
#include "Engine/DataTable.h"
// Types
#include "Utility/CsPrjLog.h"

#include "CsTypes_Projectile_Visual_Impact.generated.h"

// FCsProjectile_FX_ImpactInfo
#pragma region

CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NImpact, NVisual, NFX, FInfo)

/**
* Container holding Impact Visual FX information for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_FX_ImpactInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** Whether to spawn FX or not for the Surface Type associated with Impact Object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_bFX", InlineEditConditionToggle))
	bool bFX;

	/** FX to spawn on Impact. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_FX", EditCondition = "bFX"))
	FCsFX FX;

	/** Whether to Scale the FX by a Damage Range associated with the Projectile.
		 Damage Range is an object that implements the interface: RangeType (NCsDamage::NRange::IRange).
		NOTE: Damage Range MUST exist. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	bool bScaleByDamageRange;

public:

	FCsProjectile_FX_ImpactInfo() :
		bFX(true),
		FX(),
		bScaleByDamageRange(false)
	{
	}

#define InfoType NCsProjectile::NImpact::NVisual::NFX::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NImpact
	{
		namespace NVisual
		{
			namespace NFX
			{
				struct CSPRJ_API FInfo
				{
				private:

					/** Whether to spawn FX or not for the Surface Type associated with Impact Object. */
					CS_DECLARE_MEMBER_WITH_PROXY(bFX, bool)
					/** FX to spawn on Impact. */
					CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
					/** Whether to Scale the FX by a Damage Range associated with the Projectile.
						 Damage Range is an object that implements the interface: RangeType (NCsDamage::NRange::IRange).
						NOTE: Damage Range MUST exist. */
					CS_DECLARE_MEMBER_WITH_PROXY(bScaleByDamageRange, bool)

				public:

					FInfo() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bFX, true),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bScaleByDamageRange, false)
					{
						CS_CTOR_SET_MEMBER_PROXY(bFX);
						CS_CTOR_SET_MEMBER_PROXY(FX);
						CS_CTOR_SET_MEMBER_PROXY(bScaleByDamageRange);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bFX, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bScaleByDamageRange, bool)

					void Copy(const FInfo& From)
					{
						SetbFX(From.GetbFX());
						SetFX(From.GetFX());
						SetbScaleByDamageRange(From.GetbScaleByDamageRange());
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
				};
			}
		}
	}
}

#pragma endregion FCsProjectile_FX_ImpactInfo

// FCsProjectile_Visual_ImpactInfo
#pragma region

CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NImpact, NVisual, FInfo)

/**
* Container holding any Impact Visual information for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_Visual_ImpactInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	TEnumAsByte<EPhysicalSurface> Surface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (DisplayName = "FX Info"))
	FCsProjectile_FX_ImpactInfo FXInfo;

public:

	FCsProjectile_Visual_ImpactInfo() :
		Surface(EPhysicalSurface::SurfaceType_Default),
		FXInfo()
	{
	}

#define InfoType NCsProjectile::NImpact::NVisual::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NImpact
	{
		namespace NVisual
		{
			struct CSPRJ_API FInfo
			{
			#define ImpactFXInfoType NCsProjectile::NImpact::NVisual::NFX::FInfo

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Surface, EPhysicalSurface)

			public:
	
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
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef ImpactFXInfoType
			};
		}
	}
}

#pragma endregion FCsProjectile_Visual_ImpactInfo