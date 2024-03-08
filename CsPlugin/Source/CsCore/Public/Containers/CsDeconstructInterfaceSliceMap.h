// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsDeconstructInterfaceSliceMap.generated.h"

UINTERFACE()
class CSCORE_API UCsDeconstructInterfaceSliceMap : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsDeconstructInterfaceSliceMap
{
	GENERATED_IINTERFACE_BODY()

	virtual void AddSlice(const FName& SliceName, void* Slice) = 0;

	virtual void AddDeconstructSliceImpl(const FName& SliceName, void(*DeconstructImpl)(void*)) = 0;
};