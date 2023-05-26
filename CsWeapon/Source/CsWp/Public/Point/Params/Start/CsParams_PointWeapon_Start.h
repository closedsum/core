// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Point/Params/Start/CsTypes_PointWeapon_Start.h"
#include "Point/Params/Spread/CsParams_PointWeapon_Spread.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointWeapon_Start.generated.h"

// FCsPointWeapon_StartParams
#pragma region

// NCsWeapon::NPoint::NStart::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NPoint, NStart, FParams)

/**
* Describes any information related to the Start location for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_StartParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes how to determine the Start location. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponStart Type;

	/** What position offset to apply to the Start location. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FVector Offset;

	// Whether to use Spread Params or not.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_bSpreadParams", InlineEditConditionToggle))
	bool bSpreadParams;

	/** Describes any spread information related to the Start location. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point", meta = (ScriptName = "m_SpreadParams", editcondition = "bSpreadParams"))
	FCsPointWeapon_SpreadParams SpreadParams;

	FCsPointWeapon_StartParams() :
		Type(ECsPointWeaponStart::Destination),
		Offset(0.0f),
		bSpreadParams(false),
		SpreadParams()
	{
	}

#define ParamsType NCsWeapon::NPoint::NStart::FParams
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
		namespace NStart
		{
			/**
			* Describes any information related to the Start location for a Point Weapon.
			*  Weapon is an object that implements the interface: ICsWeapon.
			*  Point Weapon is an object that implements the interface: ICsPointWeapon.
			*/
			struct CSWP_API FParams
			{
			#define StartType NCsWeapon::NPoint::EStart
			#define SpreadParamsType NCsWeapon::NPoint::NSpread::FParams

			private:

				/** Describes how to determine the Start location. */
				CS_DECLARE_MEMBER_WITH_PROXY(Type, StartType)
				/** What position offset to apply to the Start location. */
				CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector)
				// Whether to use Spread Params or not.
				CS_DECLARE_MEMBER_WITH_PROXY(bSpreadParams, bool)
				/** Describes any spread information related to the Start location. */
				SpreadParamsType SpreadParams;

			public:

				FParams() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, StartType::Destination),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bSpreadParams, false),
					SpreadParams()
				{
					CS_CTOR_SET_MEMBER_PROXY(Offset);
					CS_CTOR_SET_MEMBER_PROXY(bSpreadParams);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, StartType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSpreadParams, bool)
				FORCEINLINE const SpreadParamsType& GetSpreadParams() const { return SpreadParams; }
				FORCEINLINE SpreadParamsType* GetSpreadParamsPtr() { return &SpreadParams; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

			#undef StartType
			#undef SpreadParamsType
			};
		}
	}
}

#pragma endregion FCsPointWeapon_StartParams