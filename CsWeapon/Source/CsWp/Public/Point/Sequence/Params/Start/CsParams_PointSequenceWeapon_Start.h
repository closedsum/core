// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Point/Sequence/Params/Start/CsTypes_PointSequenceWeapon_Start.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointSequenceWeapon_Start.generated.h"

// FCsPointSequenceWeapon_StartParams
#pragma region

// NCsWeapon::NPoint::NSequence::NStart::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NSequence, NStart, FParams)

/**
* Describes any information related to the Start location for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_StartParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes how to determine the Start location. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointSequenceWeaponStart Type;

	/** What position offset to apply to the Start location. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FVector3f Offset;

	FCsPointSequenceWeapon_StartParams() :
		Type(ECsPointSequenceWeaponStart::Destination),
		Offset(0.0f)
	{
	}

#define ParamsType NCsWeapon::NPoint::NSequence::NStart::FParams
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
			namespace NStart
			{
				/**
				* Describes any information related to the Start location for a Point Sequence Weapon.
				*  Weapon is an object that implements the interface: ICsWeapon.
				*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
				*/
				struct CSWP_API FParams
				{
				#define StartType NCsWeapon::NPoint::NSequence::EStart

				private:

					/** Describes how to determine the Start location. */
					CS_DECLARE_MEMBER_WITH_PROXY(Type, StartType)
					/** What position offset to apply to the Start location. */
					CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector3f)

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, StartType::Destination),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, 0.0f)
					{
						CS_CTOR_SET_MEMBER_PROXY(Offset);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, StartType)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector3f)

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

				#undef StartType
				};
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_StartParams