// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "CsData_Debug.generated.h"

/* Current Order of Categories

*/

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Debug : public ACsData
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