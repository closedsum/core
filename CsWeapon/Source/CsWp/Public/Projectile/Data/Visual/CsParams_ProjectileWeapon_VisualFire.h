// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_ProjectileWeapon_VisualFire.generated.h"
#pragma once

// ProjectileWeaponVisualFireAttach
#pragma region

/**
* Describes how the Visual Fire FX should be attached to the weapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponVisualFireAttach : uint8
{
	None									UMETA(DisplayName = "None"),
	Owner									UMETA(DisplayName = "Owner"),
	Component								UMETA(DisplayName = "Component"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponVisualFireAttach_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponVisualFireAttach : public TCsEnumMap<ECsProjectileWeaponVisualFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponVisualFireAttach, ECsProjectileWeaponVisualFireAttach)
};

namespace NCsProjectileWeaponVisualFireAttach
{
	typedef ECsProjectileWeaponVisualFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsProjectileWeaponVisualFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					/**
					* Describes how the Visual Fire FX should be attached to the weapon.
					*/
					enum class EAttach : uint8
					{
						None,
						Owner,
						Component,
						Custom,
						EAttach_MAX
					};

					struct CSWP_API EMAttach : public TCsEnumMap<EAttach>
					{
						CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMAttach, EAttach)
					};

					namespace NAttach
					{
						namespace Ref
						{
							typedef EAttach Type;

							extern CSWP_API const Type None;
							extern CSWP_API const Type Owner;
							extern CSWP_API const Type Component;
							extern CSWP_API const Type EAttach_MAX;
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponVisualFireAttach

// NCsWeapon::NProjectile::NData::NVisual::NFire::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NData, NVisual, NFire, FParams)

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_VisualFire_Params
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsFX FX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponVisualFireAttach Attach;

	FCsProjectileWeapon_VisualFire_Params() :
		FX(),
		Attach(ECsProjectileWeaponVisualFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NData::NVisual::NFire::FParams
	void CopyParams(ParamsType* Params);
	void CopyParamsAsValue(ParamsType* Params) const;
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					/**
					*/
					struct CSWP_API FParams
					{
					#define AttachType NCsWeapon::NProjectile::NData::NVisual::NFire::EAttach

					private:

						FCsFX FX;
						FCsFX* FX_Emu;

						AttachType Attach;
						AttachType* Attach_Emu;

					public:

						FParams() :
							FX(),
							FX_Emu(nullptr),
							Attach(AttachType::None),
							Attach_Emu(nullptr)
						{
							FX_Emu = &FX;
							Attach_Emu = &Attach;
						}

					public:
						
						CS_DEFINE_SET_GET_MEMBER_WITH_EMU(FX, FCsFX)
						CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Attach, AttachType)

						FORCEINLINE void SetAttach(const ECsProjectileWeaponVisualFireAttach& Value) 
						{
							Attach	   = (AttachType)Value;
							Attach_Emu = &Attach;
						}
						FORCEINLINE void SetAttach(ECsProjectileWeaponVisualFireAttach* Value) { Attach_Emu = (AttachType*)Value; }
						
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef AttachType
					};
				}
			}
		}
	}
}