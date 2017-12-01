// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "CsData_Interactive.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Interactive : public ACsData
{
	GENERATED_UCLASS_BODY()

// Mesh
#pragma region

	virtual class UStaticMesh* GetStaticMesh();
	virtual class USkeletalMesh* GetSkeletalMesh();

	virtual TArray<class UMaterialInstanceConstant*>* GetMaterials();

	void SetMeshAndMaterials(UStaticMeshComponent* InMesh);
	void SetMeshAndMaterials(USkeletalMeshComponent* InMesh);

#pragma endregion Mesh
};