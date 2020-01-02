// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_Weapon.h"
#include "CsData_Weapon.generated.h"

class UMaterialInstanceConstant;
class USkeletalMeshComponent;
class ASkeletalMeshActor;
class USkeletalMesh;

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API UCsData_Weapon : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const FName& GetItemShortCode();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const bool& UseInventory();

#pragma endregion Stats

// Mesh
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual const bool& UseMesh();

	virtual USkeletalMesh* GetMesh(const ECsViewType& ViewType, const bool& IsLow = false);
	virtual USkeletalMesh* GetMesh();

	virtual void SetMesh(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow = false);
	virtual void SetMesh(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow = false);
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual void SetMesh(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow = false);

	virtual void SetMesh(USkeletalMeshComponent* InMesh);
	virtual void SetMesh(ASkeletalMeshActor* InActor);
	virtual void SetMesh(UObject* InObject);

	virtual void GetDefaultMaterials(TArray<UMaterialInstanceConstant*>& OutMaterials, const ECsViewType& ViewType, const bool& IsLow = false);
	virtual void GetDefaultMaterials(TArray<UMaterialInstanceConstant*>& OutMaterials);

#pragma endregion Mesh

// Anims
#pragma region
public:

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow = false);
	virtual void SetAnimBlueprint(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow = false);
	UFUNCTION(BlueprintCallable, Category = Animation)
	virtual void SetAnimBlueprint(UObject* InActor, const ECsViewType& ViewType, const bool& IsLow = false);

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh);
	virtual void SetAnimBlueprint(ASkeletalMeshActor* InActor);
	virtual void SetAnimBlueprint(UObject* InActor);

#pragma endregion Anims
};