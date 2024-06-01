// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Time/CsTypes_Manager_Time.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Manager_Time)

// ManagerTimeScaledDeltaTimeApplication
#pragma region

namespace NCsManagerTimeScaledDeltaTimeApplication
{
	namespace Ref
	{
		typedef EMCsManagerTimeScaledDeltaTimeApplication EnumMapType;

		CSTIME_API CS_ADD_TO_ENUM_MAP(Set);
		CSTIME_API CS_ADD_TO_ENUM_MAP(Reset);
		CSTIME_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsManagerTimeScaledDeltaTimeApplication_MAX, "MAX");
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
				namespace NApplication
				{
					namespace Ref
					{
						typedef EMApplication EnumMapType;

						CSTIME_API CS_ADD_TO_ENUM_MAP(Set);
						CSTIME_API CS_ADD_TO_ENUM_MAP(Reset);
						CSTIME_API CS_ADD_TO_ENUM_MAP_CUSTOM(EApplication_MAX, "MAX");
					}
				}
			}
		}
	}
}
#pragma endregion ManagerTimeScaledDeltaTimeApplication