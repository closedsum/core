// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Speed/CsTypes_ProjectileModifier_Speed.h"

// ProjectileSpeedModifierApplication
#pragma region

namespace NCsProjectileSpeedModifierApplication
{
	namespace Ref
	{
		typedef EMCsProjectileSpeedModifierApplication EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(Multiply);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Add);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Replace);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileSpeedModifierApplication_MAX, "MAX");
	}
}

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
			namespace NApplication
			{
				namespace Ref
				{
					typedef EMApplication EnumMapType;

					CSPRJ_API CS_ADD_TO_ENUM_MAP(Multiply);
					CSPRJ_API CS_ADD_TO_ENUM_MAP(Add);
					CSPRJ_API CS_ADD_TO_ENUM_MAP(Replace);
					CSPRJ_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
					CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EApplication_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion ProjectileSpeedModifierApplication