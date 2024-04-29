// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointSequenceWeapon_VisualFire.generated.h"

// PointSequenceWeaponVisualFireAttach
#pragma region

/**
* Describes how the Visual Fire FX should be attached to the weapon.
*/
UENUM(BlueprintType)
enum class ECsPointSequenceWeaponVisualFireAttach : uint8
{
	None										UMETA(DisplayName = "None"),
	Owner										UMETA(DisplayName = "Owner"),
	Component									UMETA(DisplayName = "Component"),
	Custom										UMETA(DisplayName = "Custom"),
	ECsPointSequenceWeaponVisualFireAttach_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointSequenceWeaponVisualFireAttach : public TCsEnumMap<ECsPointSequenceWeaponVisualFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointSequenceWeaponVisualFireAttach, ECsPointSequenceWeaponVisualFireAttach)
};

namespace NCsPointSequenceWeaponVisualFireAttach
{
	typedef ECsPointSequenceWeaponVisualFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsPointSequenceWeaponVisualFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NFire
			{
				namespace NVisual
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
							extern CSWP_API const Type Custom;
							extern CSWP_API const Type EAttach_MAX;
						}
					}
				}
			}
		}
	}
}

#pragma endregion PointSequenceWeaponVisualFireAttach

// FCsPointSequenceWeapon_Visual_FireParams
#pragma region

// NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NSequence, NFire, NVisual, FParams)

/**
* Describes any Visual information related to the Fire action for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_Visual_FireParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Which FX to spawn when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FCsFX FX;

	/** How the FX should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointSequenceWeaponVisualFireAttach Attach;

	/** Whether the Destination of the Point Weapon should be used as location 
		where the FX should be spawned.
		NOTE: If this is TRUE and the Orientation parameter is used, it will be
			  inverted. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	bool bDestinationAsStart;

	/** Whether to pass a value to a Distance parameter or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_bDistanceParameter", InlineEditConditionToggle))
	bool bDistanceParameter;

	/** The name of the Distance parameter to pass the distance between the 
		Start and Destination positions for the Point Weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_DistanceParameter", EditCondition = "bDistanceParameter"))
	FName DistanceParameter;

	/** Whether to pass a value to a Orientation parameter or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_bOrientationParameter", InlineEditConditionToggle))
	bool bOrientationParameter;

	/** The name of the Orientation parameter to pass the direction from the 
		Start to the Destination positions for the Point Weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_OrientationParameter", EditCondition = "bOrientationParameter"))
	FName OrientationParameter;

	FCsPointSequenceWeapon_Visual_FireParams() :
		FX(),
		Attach(ECsPointSequenceWeaponVisualFireAttach::Component),
		bDestinationAsStart(false),
		bDistanceParameter(false),
		DistanceParameter(NAME_None),
		bOrientationParameter(false),
		OrientationParameter(NAME_None)
	{
	}

#define ParamsType NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams
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
		namespace NSequence
		{
			namespace NFire
			{
				namespace NVisual
				{
					/**
					* Describes any Visual information related to the Fire action for a Point Weapon.
					*  Point Weapon is an object that implements the interface: ICsPointWeapon.
					*/
					struct CSWP_API FParams
					{
					#define AttachType NCsWeapon::NPoint::NSequence::NFire::NVisual::EAttach

					private:

						/** Which FX to spawn when the Fire action is executed. */
						CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
						/** How the FX should be attached. */
						CS_DECLARE_MEMBER_WITH_PROXY(Attach, AttachType)
						/** Whether the Destination of the Point Weapon should be used as location 
							where the FX should be spawned.
							NOTE: If this is TRUE and the Orientation parameter is used, it will be
								  inverted. */
						CS_DECLARE_MEMBER_WITH_PROXY(bDestinationAsStart, bool)
						/** Whether to pass a value to a Distance parameter or not. */
						CS_DECLARE_MEMBER_WITH_PROXY(bDistanceParameter, bool)
						/** The name of the Distance parameter to pass the distance between the 
							Start and Destination positions for the Point Weapon. */
						CS_DECLARE_MEMBER_WITH_PROXY(DistanceParameter, FName)
						/** Whether to pass a value to a Orientation parameter or not. */
						CS_DECLARE_MEMBER_WITH_PROXY(bOrientationParameter, bool)
						/** The name of the Orientation parameter to pass the direction from the 
							Start to the Destination positions for the Point Weapon. */
						CS_DECLARE_MEMBER_WITH_PROXY(OrientationParameter, FName)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Attach, AttachType::None),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bDestinationAsStart, false),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bDistanceParameter, false),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(DistanceParameter, NAME_None),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bOrientationParameter, false),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(OrientationParameter, NAME_None)
						{
							CS_CTOR_SET_MEMBER_PROXY(FX);
							CS_CTOR_SET_MEMBER_PROXY(Attach);
							CS_CTOR_SET_MEMBER_PROXY(bDestinationAsStart);
							CS_CTOR_SET_MEMBER_PROXY(bDistanceParameter);
							CS_CTOR_SET_MEMBER_PROXY(DistanceParameter);
							CS_CTOR_SET_MEMBER_PROXY(bOrientationParameter);
							CS_CTOR_SET_MEMBER_PROXY(OrientationParameter);
						}

					public:
						
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Attach, AttachType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bDestinationAsStart, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bDistanceParameter, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DistanceParameter, FName)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bOrientationParameter, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(OrientationParameter, FName)

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef AttachType
					};
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Visual_FireParams