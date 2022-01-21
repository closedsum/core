// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Modifier.generated.h"

// IntegralValueModifierApplication
#pragma region

UENUM(BlueprintType)
enum class ECsIntegralValueModifierApplication : uint8
{
	Multiply								UMETA(DisplayName = "Multiply"),
	Add										UMETA(DisplayName = "Add"),
	Replace									UMETA(DisplayName = "Replace"),
	ReplaceOnlyIfGreater					UMETA(DisplayName = "Replace Only If Greater"),
	ECsIntegralValueModifierApplication_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsIntegralValueModifierApplication : public TCsEnumMap<ECsIntegralValueModifierApplication>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsIntegralValueModifierApplication, ECsIntegralValueModifierApplication)
};

namespace NCsIntegralValueModifierApplication
{
	typedef ECsIntegralValueModifierApplication Type;

	namespace Ref
	{
		extern CSCORE_API const Type Multiply;
		extern CSCORE_API const Type Add;
		extern CSCORE_API const Type Replace;
		extern CSCORE_API const Type ReplaceOnlyIfGreater;
		extern CSCORE_API const Type ECsIntegralValueModifierApplication_MAX;
	}
}

namespace NCsModifier
{
	namespace NValue
	{
		namespace NIntegral
		{
			enum class EApplication : uint8
			{
				Multiply,
				Add,
				Replace,
				ReplaceOnlyIfGreater,
				EApplication_MAX
			};

			struct CSCORE_API EMApplication : public TCsEnumMap<EApplication>
			{
				CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMApplication, EApplication)
			};

			namespace NApplication
			{
				namespace Ref
				{
					typedef EApplication Type;

					extern CSCORE_API const Type Multiply;
					extern CSCORE_API const Type Add;
					extern CSCORE_API const Type Replace;
					extern CSCORE_API const Type ReplaceOnlyIfGreater;
					extern CSCORE_API const Type EApplication_MAX;
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

#pragma endregion IntegralValueModifierApplication