// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_PointWeapon_Start.generated.h"

// PointWeaponStart
#pragma region

/**
* Describes how to determine the Start location for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
UENUM(BlueprintType)
enum class ECsPointWeaponStart : uint8
{
	/** Use the Owner of the Point Weapon as the Start location. */
	Owner					UMETA(DisplayName = "Owner"),
	/** Use the Destination of the Point Weapon as the Start location. */
	Destination				UMETA(DisplayName = "Destination"),
	Custom					UMETA(DisplayName = "Custom"),
	ECsPointWeaponStart_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsPointWeaponStart : public TCsEnumMap<ECsPointWeaponStart>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPointWeaponStart, ECsPointWeaponStart)
};

namespace NCsPointWeaponStart
{
	typedef ECsPointWeaponStart Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Destination;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsPointWeaponStart_MAX;
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		/**
		* Describes how to determine the Start location for a Point Weapon.
		*  Weapon is an object that implements the interface: ICsWeapon.
		*  Point Weapon is an object that implements the interface: ICsPointWeapon.
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

#pragma endregion PointWeaponStart