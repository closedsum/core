// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsGetLevelSetupData.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsGetLevelSetupData : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Level_Setup;

/**
*/
class CSCORE_API ICsGetLevelSetupData
{
	GENERATED_IINTERFACE_BODY()

	virtual ICsData_Level_Setup* GetLevelSetupData() const = 0;
};