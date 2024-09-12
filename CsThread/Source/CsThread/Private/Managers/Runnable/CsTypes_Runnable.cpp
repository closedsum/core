// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Runnable/CsTypes_Runnable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Runnable)

// ThreadPriority
#pragma region

namespace NCsThreadPriority
{
	namespace Ref
	{
		typedef EMCsThreadPriority EnumMapType;

		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_Normal, "Normal");
		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_AboveNormal, "Above Normal");
		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_BelowNormal, "Below Normal");
		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_Highest, "Highest");
		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_Lowest, "Lowest");
		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_SlightlyBelowNormal, "Slightly Below Normal");
		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_TimeCritical, "Time Critical");
		CSTHREAD_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsThreadPriority_MAX, "MAX");
	}
}

#pragma endregion ThreadPriority

const FCsRunnableHandle FCsRunnableHandle::Invalid;