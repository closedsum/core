// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UPrimitiveComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UMaterialInterface;
class UMaterialInstanceConstant;
class UMaterialInstanceDynamic;
struct FSkeletalMaterial;

namespace NCsMaterial
{
	/**
	*/
	class CSCORE_API FLibrary
	{
	public:

		/**
		* 
		* 
		* @param Context	The calling context
		* @param Component
		* @param Material
		* @param Index
		*/
		static void SetMaterialChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index);

		static bool IsValidChecked(const FString& Context, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a StaticMeshComponent.
		* 
		* @param Mesh
		* @param Materials
		*/
		static void SetMaterials(UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a StaticMeshComponent.
		*
		* @param Mesh
		* @param Materials
		*/
		static void SetMaterials(UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials);

		/**
		* Set the materials on a StaticMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetMaterialsChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Mesh
		* @param Materials
		*/
		static void SetMaterials(USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Mesh
		* @param Materials
		*/
		static void SetMaterials(USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetMaterialsChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Clear the override materials on a StaticMeshComponent.
		* 
		* @param Mesh
		*/
		static void ClearOverrideMaterials(UStaticMeshComponent* Mesh);
	
		/**
		* Clear the override materials on a SkeletalMeshComponent.
		*
		* @param Mesh
		*/
		static void ClearOverrideMaterials(USkeletalMeshComponent* Mesh);

	// MID
	#pragma region
	public:

		/**
		*/
		static void SetMIDs(UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static void SetMIDsChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static void SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials);
	
		/**
		*/
		static void SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials);
	
		/**
		*/
		static void SetMIDs(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static void DestroyMIDs(TArray<UMaterialInstanceDynamic*>& MIDs);

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
}