// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes.h"
#include "CsData_Debug.generated.h"

/* Current Order of Categories

*/

UCLASS(Blueprintable)
class CSCORE_API UCsData_Debug : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsTArrayBlueprint Blueprints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsTArraySkeletalMesh SkeletalMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsTArrayStaticMesh StaticMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01 Common")
	FCsTArrayMaterialInstanceConstant Materials;
};