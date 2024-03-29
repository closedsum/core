// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
		typedef EMCsManagerTArraySize EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Small);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Medium);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Large);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VeryLarge, "Very Large");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsManagerTArraySize_MAX, "MAX");
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