// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointWeapon_VisualFire.generated.h"

// PointWeaponVisualFireAttach
#pragma region

/**
* Describes how the Visual Fire FX should be attached to the weapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponVisualFireAttach : uint8
{
	None								UMETA(DisplayName = "None"),
	Owner								UMETA(DisplayName = "Owner"),
	Component							UMETA(DisplayName = "Component"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsPointWeaponVisualFireAttach_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponVisualFireAttach : public TCsEnumMap<ECsPointWeaponVisualFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponVisualFireAttach, ECsPointWeaponVisualFireAttach)
};

namespace NCsPointWeaponVisualFireAttach
{
	typedef ECsPointWeaponVisualFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsPointWeaponVisualFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NPoint
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

#pragma endregion PointWeaponVisualFireAttach

// NCsWeapon::NPoint::NData::NVisual::NFire::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NData, NVisual, NFire, FParams)

/**
* Describes any Visual information related to the Fire action for a Point Weapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_VisualFire_Params
{
	GENERATED_USTRUCT_BODY()

public:

	/** Which FX to spawn when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FCsFX FX;

	/** How the FX should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponVisualFireAttach Attach;

	FCsPointWeapon_VisualFire_Params() :
		FX(),
		Attach(ECsPointWeaponVisualFireAttach::Component)
	{
	}

	FORCEINLINE void UpdateInternalPtrs()
	{
		FX.UpdateInternalPtrs();
	}

#define ParamsType NCsWeapon::NPoint::NData::NVisual::NFire::FParams
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
					#define AttachType NCsWeapon::NPoint::NData::NVisual::NFire::EAttach

					private:

						/** Which FX to spawn when the Fire action is executed. */
						CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
						/** How the FX should be attached. */
						CS_DECLARE_MEMBER_WITH_PROXY(Attach, AttachType)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Attach, AttachType::None)
						{
							CS_CTOR_SET_MEMBER_PROXY(FX);
							CS_CTOR_SET_MEMBER_PROXY(Attach);
						}

					public:
						
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Attach, AttachType)

						FORCEINLINE void SetAttach(const ECsPointWeaponVisualFireAttach& Value) 
						{
							Attach	     = (AttachType)Value;
							Attach_Proxy = &Attach;
						}
						FORCEINLINE void SetAttach(ECsPointWeaponVisualFireAttach* Value) { Attach_Proxy = (AttachType*)Value; }
						
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef AttachType
					};
				}
			}
		}
	}
}