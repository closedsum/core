// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsMacro_Proxy.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Managers/FX/CsTypes_FX.h"
// DataTable
#include "Engine/DataTable.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_PointWeapon_VisualImpact.generated.h"

// PointWeaponVisualImpactDirection
#pragma region

/**
* Describes the Direction of the Impact Visual for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon
*/
UENUM(BlueprintType)
enum class ECsPointWeaponVisualImpactDirection : uint8
{
	None									UMETA(DisplayName = "None"),
	/** Use the Impact Normal to set the Direction / Rotation 
		of the Visual. */
	Normal									UMETA(DisplayName = "Normal"),
	/** Use the Inverse of the Impact Normal to set the Direction / Rotation
		of the Visual. */
	InverseNormal							UMETA(DisplayName = "Inverse Normal"),
	/** Use the Point's Direction (Destination - Start) to set the 
		Direction / Rotation of the Visual . */
	Direction								UMETA(DisplayName = "Direction"),
	/** Use the Inverse of the Point's Direction (Destination - Start) to set the
		Direction / Rotation of the Visual . */
	InverseDirection						UMETA(DisplayName = "Inverse Direction"),
	ECsPointWeaponVisualImpactDirection_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponVisualImpactDirection final : public TCsEnumMap<ECsPointWeaponVisualImpactDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponVisualImpactDirection, ECsPointWeaponVisualImpactDirection)
};

namespace NCsPointWeaponVisualImpactDirection
{
	typedef ECsPointWeaponVisualImpactDirection Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Normal;
		extern CSWP_API const Type InverseNormal;
		extern CSWP_API const Type Direction;
		extern CSWP_API const Type InverseDirection;
		extern CSWP_API const Type ECsPointWeaponVisualImpactDirection_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NImpact
		{
			namespace NVisual
			{
				/**
				* Describes the Direction of the Impact Visual for a Point Weapon.
				*  Weapon is an object that implements the interface: ICsWeapon.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon
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
					/** Use the Point's Direction (Destination - Start) to set the 
						Direction / Rotation of the Visual . */
					Direction,
					/** Use the Inverse of the Point's Direction (Destination - Start) to set the
						Direction / Rotation of the Visual . */
					InverseDirection,
					EDirection_MAX
				};

				struct CSWP_API EMDirection final : public TCsEnumMap<EDirection>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
				};

				namespace NDirection
				{
					typedef EDirection Type;

					namespace Ref
					{
						extern CSWP_API const Type None;
						extern CSWP_API const Type Normal;
						extern CSWP_API const Type InverseNormal;
						extern CSWP_API const Type Direction;
						extern CSWP_API const Type InverseDirection;
						extern CSWP_API const Type EDirection_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileVisualImpactDirection

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

	/** Whether to spawn FX or not for the Surface Type associated with Impact Object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_bFX", InlineEditConditionToggle))
	bool bFX;

	/** FX to spawn on Impact. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (ScriptName = "m_FX", EditCondition = "bFX"))
	FCsFX FX;

	/** Describes the Direction of the Impact Visual. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	ECsPointWeaponVisualImpactDirection Direction;

	/** Whether to Scale the FX by a Damage Range associated with the Point Weapon.
		 Damage Range is an object that implements the interface: NCsDamage::NRange::IRange.
		NOTE: Damage Range MUST exist. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (EditCondition = "bFX"))
	bool bScaleByDamageRange;

public:

	FCsPointWeapon_FX_ImpactInfo() :
		bFX(true),
		FX(),
		Direction(ECsPointWeaponVisualImpactDirection::None),
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

						using DirectionType = NCsWeapon::NPoint::NImpact::NVisual::EDirection;

					private:

						/** Whether to spawn FX or not for the Surface Type associated with Impact Object. */
						CS_DECLARE_MEMBER_WITH_PROXY(bFX, bool)
						/** FX to spawn on Impact. */
						CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
						/** Describes the Direction of the Impact Visual. */
						CS_DECLARE_MEMBER_WITH_PROXY(Direction, DirectionType)
						/** Whether to Scale the FX by a Damage Range associated with the Point.
							 Damage Range is an object that implements the interface: RangeType (NCsDamage::NRange::IRange).
							NOTE: Damage Range MUST exist. */
						CS_DECLARE_MEMBER_WITH_PROXY(bScaleByDamageRange, bool)

					public:

						FInfo() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bFX, true),
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Direction, DirectionType::None),
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
							SetDirection(From.GetDirection());
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