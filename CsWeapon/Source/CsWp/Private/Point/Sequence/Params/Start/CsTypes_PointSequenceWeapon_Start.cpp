// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Params/Start/CsTypes_PointSequenceWeapon_Start.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_PointSequenceWeapon_Start)

// PointSequenceWeaponStart
#pragma region

namespace NCsPointSequenceWeaponStart
{
	namespace Ref
	{
		typedef EMCsPointSequenceWeaponStart EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Destination);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointSequenceWeaponStart_MAX, "MAX");
	}
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NStart
		{
			namespace Ref
			{
				typedef EMStart EnumMapType;

				CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
				CSWP_API CS_ADD_TO_ENUM_MAP(Destination);
				CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
				CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EStart_MAX, "MAX");
			}
		}
		}
	}
}

#pragma endregion PointSequenceWeaponStart