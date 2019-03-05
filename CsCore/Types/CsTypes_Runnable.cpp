// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Runnable.h"
#include "CsCore.h"

EMCsThreadPriority* EMCsThreadPriority::Instance;

EMCsThreadPriority& EMCsThreadPriority::Get()
{
	if (!Instance)
		Instance = new EMCsThreadPriority();
	return *Instance;
}

namespace ECsThreadPriority
{
	namespace Ref
	{
		CSCORE_API const Type TPri_Normal = EMCsThreadPriority::Get().Add(Type::TPri_Normal, TEXT("TPri_Normal"), TEXT("Normal"));
		CSCORE_API const Type TPri_AboveNormal = EMCsThreadPriority::Get().Add(Type::TPri_AboveNormal, TEXT("TPri_AboveNormal"), TEXT("Above Normal"));
		CSCORE_API const Type TPri_BelowNormal = EMCsThreadPriority::Get().Add(Type::TPri_BelowNormal, TEXT("TPri_BelowNormal"), TEXT("Below Normal"));
		CSCORE_API const Type TPri_Highest = EMCsThreadPriority::Get().Add(Type::TPri_Highest, TEXT("TPri_Highest"), TEXT("Highest"));
		CSCORE_API const Type TPri_Lowest = EMCsThreadPriority::Get().Add(Type::TPri_Lowest, TEXT("TPri_Lowest"), TEXT("Lowest"));
		CSCORE_API const Type TPri_SlightlyBelowNormal = EMCsThreadPriority::Get().Add(Type::TPri_SlightlyBelowNormal, TEXT("TPri_SlightlyBelowNormal"), TEXT("Slightly Below Normal"));
		CSCORE_API const Type TPri_TimeCritical = EMCsThreadPriority::Get().Add(Type::TPri_TimeCritical, TEXT("TPri_TimeCritical"), TEXT("Time Critical"));
		CSCORE_API const Type ECsThreadPriority_MAX = EMCsThreadPriority::Get().Add(Type::ECsThreadPriority_MAX, TEXT("ECsThreadPriority_MAX"), TEXT("MAX"));
	}
}