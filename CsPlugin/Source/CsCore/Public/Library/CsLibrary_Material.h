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
	struct CSCORE_API FLibrary final
	{
	public:

		static bool IsValidChecked(const FString& Context, const TArray<UMaterialInterface*>& Materials);

		/**
		* 
		* 
		* @param Context	The calling context
		* @param Component
		* @param Material
		* @param Index
		*/
		static void SetChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index);

		/**
		* Set the materials on a StaticMeshComponent.
		* 
		* @param Mesh
		* @param Materials
		*/
		static void Set(UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a StaticMeshComponent.
		*
		* @param Mesh
		* @param Materials
		*/
		static void Set(UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials);

		/**
		* Set the materials on a StaticMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Mesh
		* @param Materials
		*/
		static void Set(USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Mesh
		* @param Materials
		*/
		static void Set(USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceConstant*>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Clear the override materials on a StaticMeshComponent.
		* 
		* @param Mesh
		*/
		static void ClearOverride(UStaticMeshComponent* Mesh);
	
		/**
		* Clear the override materials on a SkeletalMeshComponent.
		*
		* @param Mesh
		*/
		static void ClearOverride(USkeletalMeshComponent* Mesh);
	};

	namespace NMID
	{
		struct CSCORE_API FLibrary
		{
		public:

			/**
			*
			*
			* @param Context	The calling context.
			* @param MIDs
			*/
			static bool IsValidChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs);

			/**
			*/
			static void Set(UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

			/**
			*/
			static void Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<FSkeletalMaterial>& Materials);
	
			/**
			*/
			static void Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInstanceConstant*>& Materials);
	
			/**
			*/
			static void Set(USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

			/**
			*/
			static void SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

			/**
			* Apply the MIDs to the Mesh (i.e. call Mesh->SetMaterial(I, MIDs[I]).
			* 
			* @param Context	The calling context.
			* @param Mesh		The StaticMeshComponent to apply the MIDs to.
			* @param MIDs		The array of Material Instance Dynamics to apply to Mesh.
			*/
			static void SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs);

			/**
			*/
			static void SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs, const TArray<UMaterialInterface*>& Materials);

			/**
			* Apply the MIDs to the Mesh (i.e. call Mesh->SetMaterial(I, MIDs[I]).
			* 
			* @param Context	The calling context.
			* @param Mesh		The SkeletalMeshComponent to apply the MIDs to.
			* @param MIDs		The array of Material Instance Dynamics to apply to Mesh.
			*/
			static void SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& MIDs);

			/**
			*/
			static void Destroy(TArray<UMaterialInstanceDynamic*>& MIDs);

			static bool IsVectorParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

			/**
			*/
			static void SetScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float &Value);

			/**
			*/
			static void SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector &Value);

			/**
			*/
			static void SetVectorParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value);

			/**
			*/
			static void SetVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor &Value);
		};
	}
}