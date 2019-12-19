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
	Sizes.Reserve((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);
	Sizes.Add(8);
	Sizes.Add(64);
	Sizes.Add(128);
	Sizes.Add(512);

	//std::is
}

TArray<bool>& FCsManager_TArray::AllocateRef_TArray_bool(const ECsManagerTArraySize& Size)
{
	return Pool_bool.AllocateRef_TArray(Size);
}

TArray<bool>& FCsManager_TArray::ForceAllocateRef_TArray_bool(const ECsManagerTArraySize& Size)
{
	return Pool_bool.ForceAllocateRef_TArray(Size);
}

void FCsManager_TArray::DeallocateAll_TArray_bool(const ECsManagerTArraySize& Size)
{
	Pool_bool.DeallocateAll_TArray(Size);
}