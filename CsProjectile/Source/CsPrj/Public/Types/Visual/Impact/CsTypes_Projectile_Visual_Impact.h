// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/FX/CsTypes_FX.h"
#include "Engine/DataTable.h"
// Types
#include "Utility/CsPrjLog.h"

#include "CsTypes_Projectile_Visual_Impact.generated.h"

// ProjectileVisualImpactDirection
#pragma region

/**
* Describes the Direction of the Impact Visual for a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
UENUM(BlueprintType)
enum class ECsProjectileVisualImpactDirection : uint8
{
	None									UMETA(DisplayName = "None"),
	/** Use the Impact Normal to set the Direction / Rotation 
		of the Visual. */
	Normal									UMETA(DisplayName = "Normal"),
	/** Use the Inverse of the Impact Normal to set the Direction / Rotation
		of the Visual. */
	InverseNormal							UMETA(DisplayName = "Inverse Normal"),
	/** Use the Projectile's Velocity Direction to set the 
		Direction / Rotation of the Visual . */
	Velocity								UMETA(DisplayName = "Velocity"),
	/** Use the Inverse of the Projectile's Velocity Direction to set the
		Direction / Rotation of the Visual . */
	InverseVelocity							UMETA(DisplayName = "Inverse Velocity"),
	ECsProjectileVisualImpactDirection_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileVisualImpactDirection final : public TCsEnumMap<ECsProjectileVisualImpactDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileVisualImpactDirection, ECsProjectileVisualImpactDirection)
};

namespace NCsProjectileVisualImpactDirection
{
	typedef ECsProjectileVisualImpactDirection Type;

	namespace Ref
	{
		extern CSPRJ_API const Type None;
		extern CSPRJ_API const Type Normal;
		extern CSPRJ_API const Type InverseNormal;
		extern CSPRJ_API const Type Velocity;
		extern CSPRJ_API const Type InverseVelocity;
		extern CSPRJ_API const Type ECsProjectileVisualImpactDirection_MAX;
	}

	extern CSPRJ_API const uint8 MAX;
}

namespace NCsProjectile
{
	namespace NImpact
	{
		namespace NVisual
		{
			/**
			* Describes the Direction of the Impact Visual for a Projectile.
			*  Projectile is an object that implements the interface: ICsProjectile.
			*/
			enum class EDirection : uint8
			{
				None,
				/** Use the Impact Normal to set the Direction / Rotation 
					of the Visual. */
				Normal,
				/** Use the Inverse of the Impact Normal to set the Direction / Rotation
					of the Visual. */
				InverseNormal,
				/** Use the Projectile's Velocity Direction to set the 
					Direction / Rotation of the Visual . */
				Velocity,
				/** Use the Inverse of the Projectile's Velocity Direction to set the
					Direction / Rotation of the Visual . */
				InverseVelocity,
				EDirection_MAX
			};

			struct CSPRJ_API EMDirection final : public TCsEnumMap<EDirection>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
			};

			namespace NDirection
			{
				typedef EDirection Type;

				namespace Ref
				{
					extern CSPRJ_API const Type None;
					extern CSPRJ_API const Type Normal;
					extern CSPRJ_API const Type InverseNormal;
					extern CSPRJ_API const Type Velocity;
					extern CSPRJ_API const Type InverseVelocity;
					extern CSPRJ_API const Type EDirection_MAX;
				}
			}
		}
	}
}

#pragma endregion ProjectileVisualImpactDirection

// FCsProjectile_FX_ImpactInfo
#pragma region

// NCsProjectile::NImpact::NVisual::NFX::FInfo
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

	/** Describes the Direction of the Impact Visual. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	ECsProjectileVisualImpactDirection Direction;

	/** Whether to Scale the FX by a Damage Range associated with the Projectile.
		 Damage Range is an object that implements the interface: RangeType (NCsDamage::NRange::IRange).
		NOTE: Damage Range MUST exist. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	bool bScaleByDamageRange;

public:

	FCsProjectile_FX_ImpactInfo() :
		bFX(true),
		FX(),
		Direction(ECsProjectileVisualImpactDirection::Normal),
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
				#define DirectionType NCsProjectile::NImpact::NVisual::EDirection

				private:

					/** Whether to spawn FX or not for the Surface Type associated with Impact Object. */
					CS_DECLARE_MEMBER_WITH_PROXY(bFX, bool)
					/** FX to spawn on Impact. */
					CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
					/** Describes the Direction of the Impact Visual. */
					CS_DECLARE_MEMBER_WITH_PROXY(Direction, DirectionType)
					/** Whether to Scale the FX by a Damage Range associated with the Projectile.
						 Damage Range is an object that implements the interface: RangeType (NCsDamage::NRange::IRange).
						NOTE: Damage Range MUST exist. */
					CS_DECLARE_MEMBER_WITH_PROXY(bScaleByDamageRange, bool)

				public:

					FInfo() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bFX, true),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Direction, DirectionType::Normal),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bScaleByDamageRange, false)
					{
						CS_CTOR_SET_MEMBER_PROXY(bFX);
						CS_CTOR_SET_MEMBER_PROXY(FX);
						CS_CTOR_SET_MEMBER_PROXY(Direction);
						CS_CTOR_SET_MEMBER_PROXY(bScaleByDamageRange);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bFX, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Direction, DirectionType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bScaleByDamageRange, bool)

					void Copy(const FInfo& From)
					{
						SetbFX(From.GetbFX());
						SetFX(From.GetFX());
						SetbScaleByDamageRange(From.GetbScaleByDamageRange());
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

				#undef DirectionType
				};
			}
		}
	}
}

#pragma endregion FCsProjectile_FX_ImpactInfo

// FCsProjectile_Visual_ImpactInfo
#pragma region

// NCsProjectile::NImpact::NVisual::FInfo
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