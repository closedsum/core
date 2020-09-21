// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Runnable/CsTypes_Runnable.h"
#include "CsCore.h"

// ThreadPriority
#pragma region

namespace NCsThreadPriority
{
	namespace Ref
	{
		typedef EMCsThreadPriority EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_Normal, "Normal");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_AboveNormal, "Above Normal");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_BelowNormal, "Below Normal");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_Highest, "Highest");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_Lowest, "Lowest");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_SlightlyBelowNormal, "Slightly Below Normal");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TPri_TimeCritical, "Time Critical");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsThreadPriority_MAX, "MAX");
	}
}

#pragma endregion ThreadPriority

const FCsRunnableHandle FCsRunnableHandle::Invalid;