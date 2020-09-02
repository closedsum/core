// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/TArray/CsManager_TArray.h"
#include "CsCore.h"
#include "CsCVars.h"

// Enums
#pragma region

	// ManagerTArraySize
#pragma region

namespace NCsManagerTArraySize
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsManagerTArraySize, Small);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsManagerTArraySize, Medium);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsManagerTArraySize, Large);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsManagerTArraySize, VeryLarge, "Very Large");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsManagerTArraySize, ECsManagerTArraySize_MAX, "MAX");
	}
}

#pragma endregion ManagerTArraySize

#pragma endregion Enums

FCsManager_TArray::FCsManager_TArray()
{
}

FCsManager_TArray::~FCsManager_TArray()
{
}