// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UStaticMeshComponent;
class USkeletalMeshComponent;
class UMaterialInterface;
class UMaterialInstanceConstant;
class UMaterialInstanceDynamic;
struct FSkeletalMaterial;

/**
*/
class CSCORE_API FCsLibrary_Material
{
public:

	/**
	*/
	static void SetMaterials(UStaticMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials);

	/**
	*/
	static void SetMaterials(USkeletalMeshComponent* InMesh, const TArray<UMaterialInterface*>& Materials);

	/**
	*/
	static void SetMaterials(USkeletalMeshComponent* InMesh, const TArray<UMaterialInstanceConstant*>& Materials);

	/**
	*/
	static void ClearOverrideMaterials(UStaticMeshComponent* InMesh);
	
	/**
	*/
	static void ClearOverrideMaterials(USkeletalMeshComponent* InMesh);

// MID
#pragma region
public:

	/**
	*/
	static void DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs);

	/**
	*/
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials);
	
	/**
	*/
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials);
	
	/**
	*/
	static void SetMIDs(USkeletalMeshComponent* InMesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

	/**
	*/
	static void MIDs_SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value);

	/**
	*/
	static void MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value);

	/**
	*/
	static void MIDs_SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value);

#pragma endregion MID
};