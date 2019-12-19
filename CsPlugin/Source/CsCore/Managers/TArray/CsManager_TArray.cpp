// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/TArray/CsManager_TArray.h"
#include "CsCore.h"
#include "CsCVars.h"

FCsManager_TArray::FCsManager_TArray()
{
}

FCsManager_TArray::~FCsManager_TArray()
{
	Manager_TArray_bool.Reserve((uint8)ECsManagerTArraySize::ECsManagerTArraySize_MAX);
	Manager_TArray_bool[(uint8)ECsManagerTArraySize::S_8] = &Manager_TArray_bool_8;
}

TArray<bool>& FCsManager_TArray::AllocateRef_TArray_bool(const ECsManagerTArraySize& Size)
{
	int32 Max = 8;
	TArray<bool>* Ptr = nullptr;

	// 8
	if (Size == ECsManagerTArraySize::S_8)
	{
		Max = 8;
		Ptr	= Manager_TArray_bool_8.AllocateResource();
	}

	checkf(Ptr->Max() == Max, TEXT(""));

	Ptr->Reset(Ptr->Max());

	return *Ptr;
}

TArray<bool>& FCsManager_TArray::ForceAllocateRef_TArray_bool(const ECsManagerTArraySize& Size)
{
	// 8
	if (Size == ECsManagerTArraySize::S_8)
	{
		if (Manager_TArray_bool_8.IsExhausted())
			Manager_TArray_bool_8.DellocateHead();
	}
	return AllocateRef_TArray_bool(Size);
}

void FCsManager_TArray::DeallocateAll_TArray_bool(const ECsManagerTArraySize& Size)
{
	// 8
	if (Size == ECsManagerTArraySize::S_8)
		Manager_TArray_bool_8.DeallocateAll();
}