// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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