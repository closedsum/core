// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Projectile_Tracking.h"

// ProjectileTrackingDestination
#pragma region

namespace NCsProjectileTrackingDestination
{
	namespace Ref
	{
		typedef EMCsProjectileTrackingDestination EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Object);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Bone);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Location);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Custom);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileTrackingDestination_MAX, "MAX");
	}
}

namespace NCsProjectile
{
	namespace NTracking
	{
		namespace NDestination
		{
			namespace Ref
			{
				typedef EMDestination EnumMapType;

				CSPRJ_API CS_ADD_TO_ENUM_MAP(Object);
				CSPRJ_API CS_ADD_TO_ENUM_MAP(Bone);
				CSPRJ_API CS_ADD_TO_ENUM_MAP(Location);
				CSPRJ_API CS_ADD_TO_ENUM_MAP(Custom);
				CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDestination_MAX, "MAX");
			}
		}
	}
}

#pragma endregion ProjectileTrackingDestination