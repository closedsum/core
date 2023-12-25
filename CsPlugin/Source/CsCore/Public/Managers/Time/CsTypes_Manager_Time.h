// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Manager_Time.generated.h"

// ManagerTimeScaledDeltaTimeApplication
#pragma region

/**
* Describes how to apply a Scaled Delta Time through Manager_Time.
*/
UENUM(BlueprintType)
enum class ECsManagerTimeScaledDeltaTimeApplication : uint8
{
	Set												UMETA(DisplayName = "Set"),
	Reset											UMETA(DisplayName = "Reset"),
	ECsManagerTimeScaledDeltaTimeApplication_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsManagerTimeScaledDeltaTimeApplication : public TCsEnumMap<ECsManagerTimeScaledDeltaTimeApplication>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsManagerTimeScaledDeltaTimeApplication, ECsManagerTimeScaledDeltaTimeApplication)
};

namespace NCsManagerTimeScaledDeltaTimeApplication
{
	namespace Ref
	{
		typedef ECsManagerTimeScaledDeltaTimeApplication Type;

		extern CSCORE_API const Type Set;
		extern CSCORE_API const Type Reset;
		extern CSCORE_API const Type ECsManagerTimeScaledDeltaTimeApplication_MAX;
	}
}

namespace NCsTime
{
	namespace NManager
	{
		namespace NDeltaTime
		{
			namespace NScaled
			{
				enum class EApplication : uint8 
				{
					Set,
					Reset,
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

						extern CSCORE_API const Type Set;
						extern CSCORE_API const Type Reset;
						extern CSCORE_API const Type EApplication_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion ManagerTimeScaledDeltaTimeApplication