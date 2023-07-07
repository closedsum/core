// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_PointSequenceWeapon_Start.generated.h"

// PointSequenceWeaponStart
#pragma region

/**
* Describes how to determine the Start location for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointSequenceWeaponStart : uint8
{
	/** Use the Owner of the Point Weapon as the Start location. */
	Owner							UMETA(DisplayName = "Owner"),
	/** Use the Destination of the Point Weapon as the Start location. */
	Destination						UMETA(DisplayName = "Destination"),
	Custom							UMETA(DisplayName = "Custom"),
	ECsPointSequenceWeaponStart_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointSequenceWeaponStart : public TCsEnumMap<ECsPointSequenceWeaponStart>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointSequenceWeaponStart, ECsPointSequenceWeaponStart)
};

namespace NCsPointSequenceWeaponStart
{
	typedef ECsPointSequenceWeaponStart Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Destination;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsPointSequenceWeaponStart_MAX;
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			/**
			* Describes how to determine the Start location for a Point Sequence Weapon.
			*  Weapon is an object that implements the interface: ICsWeapon.
			*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
			*/
			enum class EStart : uint8
			{
				/** Use the Owner of the Point Weapon as the Start location. */
				Owner,
				/** Use the Destination of the Point Weapon as the Start location. */
				Destination,
				Custom,
				EStart_MAX
			};

			struct CSWP_API EMStart : public TCsEnumMap<EStart>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMStart, EStart)
			};

			namespace NStart
			{
				namespace Ref
				{
					typedef EStart Type;

					extern CSWP_API const Type Owner;
					extern CSWP_API const Type Destination;
					extern CSWP_API const Type Custom;
					extern CSWP_API const Type EStart_MAX;
				}
			}
		}
	}
}

#pragma endregion PointSequenceWeaponStart