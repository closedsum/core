// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_ProjectileModifier_Speed.generated.h"

// ProjectileSpeedModifierApplication
#pragma region

UENUM(BlueprintType)
enum class ECsProjectileSpeedModifierApplication : uint8
{
	Multiply									UMETA(DisplayName = "Multiply"),
	Add											UMETA(DisplayName = "Add"),
	Replace										UMETA(DisplayName = "Replace"),
	ReplaceOnlyIfGreater						UMETA(DisplayName = "Replace Only If Greater"),
	ECsProjectileSpeedModifierApplication_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileSpeedModifierApplication : public TCsEnumMap<ECsProjectileSpeedModifierApplication>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileSpeedModifierApplication, ECsProjectileSpeedModifierApplication)
};

namespace NCsProjectileSpeedModifierApplication
{
	typedef ECsProjectileSpeedModifierApplication Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Multiply;
		extern CSPRJ_API const Type Add;
		extern CSPRJ_API const Type Replace;
		extern CSPRJ_API const Type ReplaceOnlyIfGreater;
		extern CSPRJ_API const Type ECsProjectileSpeedModifierApplication_MAX;
	}
}

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
			enum class EApplication : uint8
			{
				Multiply,
				Add,
				Replace,
				ReplaceOnlyIfGreater,
				EApplication_MAX
			};

			struct CSPRJ_API EMApplication : public TCsEnumMap<EApplication>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMApplication, EApplication)
			};

			namespace NApplication
			{
				namespace Ref
				{
					typedef EApplication Type;

					extern CSPRJ_API const Type Multiply;
					extern CSPRJ_API const Type Add;
					extern CSPRJ_API const Type Replace;
					extern CSPRJ_API const Type ReplaceOnlyIfGreater;
					extern CSPRJ_API const Type EApplication_MAX;
				}

				FORCEINLINE void Modify(float& ValueToModify, const float& Modifier, const EApplication& Type)
				{
					if (Type == EApplication::Multiply)
					{
						ValueToModify *= Modifier;
					}
					else
					if (Type == EApplication::Add)
					{
						ValueToModify += Modifier;
					}
					else
					if (Type == EApplication::Replace)
					{
						ValueToModify = Modifier;
					}
					else
					if (Type == EApplication::ReplaceOnlyIfGreater)
					{
						if (Modifier > ValueToModify)
							ValueToModify = Modifier;
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileSpeedModifierApplication