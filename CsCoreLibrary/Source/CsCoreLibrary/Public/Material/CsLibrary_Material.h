// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Material/CsTypes_Material_Anim.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UStaticMesh;
class USkeletalMesh;
class UPrimitiveComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UMaterial;
class UMaterialInstance;
class UMaterialInterface;
class UMaterialInstanceConstant;
class UMaterialInstanceDynamic;
struct FSkeletalMaterial;
class UTexture;
class UObject;

struct FScalarParameterValue;
struct FVectorParameterValue;

// TEMP
class FMaterialInstanceResource;
struct FMaterialParameterInfo;

namespace NCsMaterial
{
	/**
	* Library of functions related to MaterialInterface
	*/
	struct CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	// Load
	#pragma region
	public:

		/**
		* Safely load the Material Interface at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Material Interface to load.
		* @param Log		(optional)
		* return			Material Interface.
		*/
		static UMaterialInterface* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

		/**
		* Safely load a Material Interface at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Material Interface to load.
		* @param Log		(optional)
		* return			Material Interface.
		*/
		static UMaterialInterface* SafeLoad(const FString& Context, const FString& Path, LogLevel);

		/**
		* Safely load Material Interfaces for the given Paths.
		*
		* @param Context		The calling context.
		* @param Paths			FString paths to the Material Interfaces to load.
		* @param OutMaterials	(out) 
		* @param Log			(optional)
		* return				Material Interface.
		*/
		static bool SafeLoad(const FString& Context, const TArray<FString>& Paths, TArray<UMaterialInterface*>& OutMaterials, LogLevel);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static UMaterialInterface* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, FString& OutPath, bool& OutSuccess, LogLevel);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, TArray<TSoftObjectPtr<UMaterialInterface>>& OutArray, bool& OutSuccess, LogLevel);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, TArray<FString>& OutArray, bool& OutSuccess, LogLevel);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, TArray<UMaterialInterface*>& OutArray, bool& OutSuccess, LogLevel);

	#pragma endregion Get

	// Valid
	#pragma region
	public:

		/**
		*/
		static bool IsValidChecked(const FString& Context, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static bool IsValid(const FString& Context, const TArray<UMaterialInterface*>& Materials, LogLevel);
		 
		/**
		*/
		static bool IsValidChecked(const FString& Context, UStaticMesh* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static bool IsValid(const FString& Context, UStaticMesh* Mesh, const TArray<UMaterialInterface*>& Materials, LogLevel);

		/**
		*/
		static bool IsValidChecked(const FString& Context, USkeletalMesh* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static bool IsValid(const FString& Context, USkeletalMesh* Mesh, const TArray<UMaterialInterface*>& Materials, LogLevel);

		/**
		* Check if Index is a valid Material Index for Mesh.
		* 
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		* return
		*/
		static bool IsValidChecked(const FString& Context, USkeletalMesh* Mesh, const int32& Index);

		/**
		* Check if Index is a valid Material Index for Mesh.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		* return
		*/
		static bool IsValidChecked(const FString& Context, UStaticMesh* Mesh, const int32& Index);

		/**
		* Check if Index is a valid Material Index for Mesh.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		* return
		*/
		static bool IsValidChecked(const FString& Context, UPrimitiveComponent* Mesh, const int32& Index);

		/**
		* Check if Index is a valid Material Index for Mesh.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		* @param Log		(optional)
		* return
		*/
		static bool IsValid(const FString& Context, UPrimitiveComponent* Mesh, const int32& Index, LogLevel);

		static bool IsValidChecked_ArrayIndex(const FString& Context, UMaterialInterface* Material, const int32& Index);

		static bool IsValid_ArrayIndex(const FString& Context, UMaterialInterface* Material, const int32& Index, LogLevel);

	#pragma endregion Valid

	// Set
	#pragma region
	public:

		/**
		* Set the Material at ALL indices on Component
		*
		* @param Context	The calling context
		* @param Component
		* @param Material
		*/
		static void SetChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material);

		/**
		* Safely set the Material at ALL Indices on Component
		*
		* @param Context	The calling context
		* @param Component
		* @param Material
		* @param Log		(optional)
		* return			Whether the material was successful set or not.
		*/
		static bool SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, LogLevel);

		/**
		* Set the Material at the given Index on Component
		* 
		* @param Context	The calling context
		* @param Component	
		* @param Material
		* @param Index
		*/
		static void SetChecked(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index);

		/**
		* Safely set the Material at the given Index on Component
		*
		* @param Context	The calling context
		* @param Component
		* @param Material
		* @param Index
		* @param Log		(optional)
		* return			Whether the material was successful set or not.
		*/
		static bool SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index, LogLevel);
		
		/**
		* Safely set the Material at the given Index on Component
		*
		* @param Component
		* @param Material
		* @param Index
		* return			Whether the material was successful set or not.
		*/
		static bool SetSafe(UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index);

		/**
		* Set the Materials on Component
		*
		* @param Context	The calling context
		* @param Component
		* @param Materials
		*/
		static void SetChecked(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials);

		/**
		* Safely set the Materials on Component
		*
		* @param Context	The calling context
		* @param Component
		* @param Materials
		* @param Log		(optional)
		* return			Whether the materials were successful set or not.
		*/
		static bool SetSafe(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials, LogLevel);
		
		/**
		* Safely set the Materials on Component
		*
		* @param Component
		* @param Materials
		* return			Whether the materials were successful set or not.
		*/
		static bool SetSafe(UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a StaticMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a StaticMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<TObjectPtr<UMaterialInterface>>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		* Set the materials on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Materials
		*/
		static void SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<TObjectPtr<UMaterialInterface>>& Materials);

	#pragma endregion Set

	// Override
	#pragma region
	public:

		/**
		* Clear the override material at Index on Component.
		*
		* @param Context	The calling context.
		* @param Component
		* @param Index
		*/
		static void ClearOverrideChecked(const FString& Context, UPrimitiveComponent* Component, const int32& Index);

		/**
		* Safely clear the override material at Index on Component.
		*
		* @param Context	The calling context.
		* @param Component
		* @param Index
		* @param Log		(optional)
		* return
		*/
		static bool SafeClearOverride(const FString& Context, UPrimitiveComponent* Component, const int32& Index, LogLevel);

		/**
		* Clear the override materials on Component.
		*
		* @param Context	The calling context.
		* @param Component
		*/
		static void ClearOverrideChecked(const FString& Context, UPrimitiveComponent* Component);

		/**
		* Safely clear the override materials on Component.
		*
		* @param Context	The calling context.
		* @param Component
		* @param Log		(optional)
		* return
		*/
		static bool SafeClearOverride(const FString& Context, UPrimitiveComponent* Component, LogLevel);

		/**
		* Clear the override material at Index on a StaticMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		*/
		static void ClearOverrideChecked(const FString& Context, UStaticMeshComponent* Mesh, const int32& Index);

		/**
		* Clear the override material at Index on a StaticMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		* @param Log		(optional)
		*/
		static bool SafeClearOverride(const FString& Context, UStaticMeshComponent* Mesh, const int32& Index, LogLevel);

		/**
		* Clear the override materials on a StaticMeshComponent.
		* 
		* @param Context	The calling context.
		* @param Mesh
		*/
		static void ClearOverrideChecked(const FString& Context, UStaticMeshComponent* Mesh);
	
		/**
		* Safely clear the override materials on a StaticMeshComponent.
		* 
		* @param Context	The calling context.
		* @param Mesh
		* @param Log		(optional)
		*/
		static bool SafeClearOverride(const FString& Context, UStaticMeshComponent* Mesh, LogLevel);

		/**
		* Clear the override material at Index on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		*/
		static void ClearOverrideChecked(const FString& Context, USkeletalMeshComponent* Mesh, const int32& Index);

		/**
		* Safely clear the override material at Index on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Index
		* @param Log		(optional)
		*/
		static bool SafeClearOverride(const FString& Context, USkeletalMeshComponent* Mesh, const int32& Index, LogLevel);

		/**
		* Clear the override materials on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		*/
		static void ClearOverrideChecked(const FString& Context, USkeletalMeshComponent* Mesh);

		/**
		* Safely clear the override materials on a SkeletalMeshComponent.
		*
		* @param Context	The calling context.
		* @param Mesh
		* @param Log		(optional)
		*/
		static bool SafeClearOverride(const FString& Context, USkeletalMeshComponent* Mesh, LogLevel);

		#pragma endregion Override

	// Scalar
	#pragma region
	public:

		/**
		* Check whether there is a Scalar Parameter Value with name: ParamName for MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Scalar Parameter Value.
		* return			Whether there IS a Scalar Parameter Value with name: ParamName or NOT.
		*/
		static bool IsScalarParameterValidChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName);

		/**
		* Check whether there is a Scalar Parameter Value with name: ParamName for MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Scalar Parameter Value.
		* @param Log
		* return			Whether there IS a Scalar Parameter Value with name: ParamName or NOT.
		*/
		static bool IsScalarParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, LogLevel);

		/**
		* Check whether there is a Scalar Parameter Value with name: ParamName for MID.
		*
		* @param Material	Material Interface.
		* @param ParamName	Name of the Scalar Parameter Value.
		* return			Whether there IS a Scalar Parameter Value with name: ParamName or NOT.
		*/
		static bool IsScalarParameterValid(UMaterialInterface* Material, const FName& ParamName);

		/**
		* Get the value of the Scalar Parameter Value with name: ParamName on MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Scalar Parameter Value.
		* return			The value of the Scalar Parameter Value with name: ParamName.
		*/
		static float GetScalarParameterValueChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName);

	#pragma endregion Scalar

	// Vector
	#pragma region
	public:

		/**
		* Check whether there is a Vector Parameter Value with name: ParamName for MID.
		* 
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Vector Parameter Value.
		* return			Whether there IS a Vector Parameter Value with name: ParamName or NOT.
		*/
		static bool IsVectorParameterValidChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName);

		/**
		* Check whether there is a Vector Parameter Value with name: ParamName for MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Vector Parameter Value.
		* @param Log
		* return			Whether there IS a Vector Parameter Value with name: ParamName or NOT.
		*/
		static bool IsVectorParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, LogLevel);

		/**
		* Check whether there is a Vector Parameter Value with name: ParamName for MID.
		*
		* @param Material	Material Interface.
		* @param ParamName	Name of the Vector Parameter Value.
		* return			Whether there IS a Vector Parameter Value with name: ParamName or NOT.
		*/
		static bool IsVectorParameterValid(UMaterialInterface* Material, const FName& ParamName);

		/**
		* Get the value of the Vector Parameter Value with name: ParamName on MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Vector Parameter Value.
		* return			The value of the Vector Parameter Value with name: ParamName.
		*/
		static FLinearColor GetVectorParameterValueChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName);

	#pragma endregion Vector

	// Texture
	#pragma region
	public:

		/**
		* Check whether there is a Texture Parameter Value with name: ParamName for MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Texture Parameter Value.
		* return			Whether there IS a Texture Parameter Value with name: ParamName or NOT.
		*/
		static bool IsTextureParameterValidChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName);

		/**
		* Check whether there is a Texture Parameter Value with name: ParamName for MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Texture Parameter Value.
		* @param Log
		* return			Whether there IS a Texture Parameter Value with name: ParamName or NOT.
		*/
		static bool IsTextureParameterValid(const FString& Context, UMaterialInterface* Material, const FName& ParamName, LogLevel);

		/**
		* Check whether there is a Texture Parameter Value with name: ParamName for MID.
		*
		* @param Material	Material Interface.
		* @param ParamName	Name of the Texture Parameter Value.
		* return			Whether there IS a Texture Parameter Value with name: ParamName or NOT.
		*/
		static bool IsTextureParameterValid(UMaterialInterface* Material, const FName& ParamName);

		/**
		* Get the value of the Texture Parameter Value with name: ParamName on MID.
		*
		* @param Context	The calling context.
		* @param Material	Material Interface.
		* @param ParamName	Name of the Texture Parameter Value.
		* return			The value of the Texture Parameter Value with name: ParamName.
		*/
		static UTexture* GetTextureParameterValueChecked(const FString& Context, UMaterialInterface* Material, const FName& ParamName);

	#pragma endregion Texture

	#undef LogLevel
	};

	namespace NMID
	{
		/**
		* Library of functions related to MaterialInstanceDynamic
		*/
		struct CSCORELIBRARY_API FLibrary
		{
		#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

		public:

			/**
			*
			*
			* @param Context	The calling context.
			* @param MIDs
			*/
			static bool IsValidChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs);

			/**
			* Create and apply the OutMID to the Mesh (i.e. call Mesh->SetMaterial(Index, OutMID).
			*
			* @param Context	The calling context.
			* @param Mesh		The PrimitiveComponent to apply OutMID at Index.
			* @param Material
			* @param Index
			* @param OutMID		(out) The Material Instance Dynamics applied to Mesh at Index.
			*/
			static void SetChecked(const FString& Context, UPrimitiveComponent* Mesh, UMaterialInterface* Material, const int32& Index, UMaterialInstanceDynamic*& OutMID);

			/**
			* Safely create and apply the OutMID to the Mesh (i.e. call Mesh->SetMaterial(Index, OutMID).
			*
			* @param Context	The calling context.
			* @param Mesh		The PrimitiveComponent to apply OutMID at Index.
			* @param Material
			* @param Index
			* @param OutMID		(out) The Material Instance Dynamics applied to Mesh at Index.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafe(const FString& Context, UPrimitiveComponent* Mesh, UMaterialInterface* Material, const int32& Index, UMaterialInstanceDynamic*& OutMID, LogLevel);

			/**
			* Create and apply the MIDs to the Mesh (i.e. call Mesh->SetMaterial(I, MIDs[I]).
			*
			* @param Context	The calling context.
			* @param Mesh		The PrimitiveComponent to apply the MIDs to.
			* @param Materials
			* @param OutMIDs	(out) The array of Material Instance Dynamics to apply to Mesh.
			*/
			static void SetChecked(const FString& Context, UPrimitiveComponent* Mesh, const TArray<UMaterialInterface*>& Materials, TArray<UMaterialInstanceDynamic*>& OutMIDs);

			/**
			* Safely create and apply the MIDs to the Mesh (i.e. call Mesh->SetMaterial(I, MIDs[I]).
			*
			* @param Context	The calling context.
			* @param Mesh		The PrimitiveComponent to apply the MIDs to.
			* @param Materials
			* @param OutMIDs	(out) The array of Material Instance Dynamics to apply to Mesh.
			* @param Log		(optional)
			*/
			static bool SetSafe(const FString& Context, UPrimitiveComponent* Mesh, const TArray<UMaterialInterface*>& Materials, TArray<UMaterialInstanceDynamic*>& OutMIDs, LogLevel);

			/**
			*/
			static void SetChecked(const FString& Context, UStaticMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& OutMIDs, const TArray<UMaterialInterface*>& Materials);

			/**
			* Apply the MIDs to the Mesh (i.e. call Mesh->SetMaterial(I, MIDs[I]).
			* 
			* @param Context	The calling context.
			* @param Mesh		The StaticMeshComponent to apply the MIDs to.
			* @param MIDs		The array of Material Instance Dynamics to apply to Mesh.
			*/
			static void SetChecked(const FString& Context, UStaticMeshComponent* Mesh, const TArray<UMaterialInstanceDynamic*>& MIDs);

			/**
			* Create and apply the MIDs to the Mesh (i.e. call Mesh->SetMaterial(I, MIDs[I]).
			*
			* @param Context	The calling context.
			* @param Mesh		The SkeletalMeshComponent to apply the MIDs to.
			* @param OutMIDs	(out) The array of Material Instance Dynamics to apply to Mesh.
			* @param Materials
			*/
			static void SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, TArray<UMaterialInstanceDynamic*>& OutMIDs, const TArray<UMaterialInterface*>& Materials);

			/**
			* Apply the MIDs to the Mesh (i.e. call Mesh->SetMaterial(I, MIDs[I]).
			* 
			* @param Context	The calling context.
			* @param Mesh		The SkeletalMeshComponent to apply the MIDs to.
			* @param MIDs		The array of Material Instance Dynamics to apply to Mesh.
			*/
			static void SetChecked(const FString& Context, USkeletalMeshComponent* Mesh, const TArray<UMaterialInstanceDynamic*>& MIDs);

			/**
			*/
			static void Destroy(TArray<UMaterialInstanceDynamic*>& OutMIDs);

		// Scalar
		#pragma region
		public:

			/**
			* Check whether there is a Scalar Parameter Value with name: ParamName for MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value.
			* return			Whether there IS a Scalar Parameter Value with name: ParamName or NOT.
			*/
			static bool IsScalarParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

			/**
			* Check whether there is a Scalar Parameter Value with name: ParamName for MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value.
			* @param Log
			* return			Whether there IS a Scalar Parameter Value with name: ParamName or NOT.
			*/
			static bool IsScalarParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, LogLevel);

			/**
			* Check whether there is a Scalar Parameter Value with name: ParamName for MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value.
			* return			Whether there IS a Scalar Parameter Value with name: ParamName or NOT.
			*/
			static bool IsScalarParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName);

			/**
			* Check whether there are Scalar Parameter Values with names: ParamNames for MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamNames	Name of the Scalar Parameter Value.
			* return			Whether there ARE Scalar Parameter Values with names: ParamNames or NOT.
			*/
			static bool AreScalarParametersValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const TArray<FName>& ParamNames);

			/**
			* Set the Scalar Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value);

			/**
			* Set the Scalar Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetScalarParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MID.
			*
			* @param Context	The calling context.
			* @param MIDs		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value, LogLevel);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MID.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeScalarParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeScalarParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value, LogLevel);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MIDs.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeScalarParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			*
			* @param Context	The calling context.
			* @param MIDs		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeScalarParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeScalarParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeScalarParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeScalarParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value);

			/**
			* Get the value of the Scalar Parameter Value with name: ParamName on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value.
			* return			The value of the Scalar Parameter Value with name: ParamName.
			*/
			static float GetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

			// Batch
		#pragma region
		public:

			static void PopulateScalarParameterValuesChecked(const FString& Context, UMaterialInstanceDynamic* MID, const TArray<FName>& Names, TArray<FScalarParameterValue*>& Values);

		#pragma endregion Batch

		#pragma endregion Scalar

		// Vector
		#pragma region
		public:

			/**
			* Check whether there is a Vector Parameter Value with name: ParamName for MID.
			* 
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value.
			* return			Whether there IS a Vector Parameter Value with name: ParamName or NOT.
			*/
			static bool IsVectorParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

			/**
			* Check whether there is a Vector Parameter Value with name: ParamName for MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value.
			* @param Log
			* return			Whether there IS a Vector Parameter Value with name: ParamName or NOT.
			*/
			static bool IsVectorParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, LogLevel);

			/**
			* Check whether there is a Vector Parameter Value with name: ParamName for MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value.
			* return			Whether there IS a Vector Parameter Value with name: ParamName or NOT.
			*/
			static bool IsVectorParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName);

			/**
			* Set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value);

			/**
			* Set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetVectorParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value, LogLevel);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeVectorParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value, LogLevel);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector3f& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector3f& Value);

			/**
			* Set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value, LogLevel);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value);

			/**
			* Set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetVectorParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeVectorParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value, LogLevel);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeVectorParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value);

			/**
			* Get the value of the Vector Parameter Value with name: ParamName on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value.
			* return			The value of the Vector Parameter Value with name: ParamName.
			*/
			static FLinearColor GetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

			// Batch
		#pragma region

			static void PopulateVectorParameterValuesChecked(const FString& Context, UMaterialInstanceDynamic* MID, const TArray<FName>& Names, TArray<FVectorParameterValue*>& Values);

		#pragma endregion Batch

		#pragma endregion Vector

		// Texture
		#pragma region
		public:

			/**
			* Check whether there is a Texture Parameter Value with name: ParamName for MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value.
			* return			Whether there IS a Texture Parameter Value with name: ParamName or NOT.
			*/
			static bool IsTextureParameterValidChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

			/**
			* Check whether there is a Texture Parameter Value with name: ParamName for MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value.
			* @param Log
			* return			Whether there IS a Texture Parameter Value with name: ParamName or NOT.
			*/
			static bool IsTextureParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, LogLevel);

			/**
			* Check whether there is a Texture Parameter Value with name: ParamName for MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value.
			* return			Whether there IS a Texture Parameter Value with name: ParamName or NOT.
			*/
			static bool IsTextureParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName);

			/**
			* Set the Texture Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetTextureParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value);

			/**
			* Set the Texture Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetTextureParameterValueChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MID.
			*
			* @param Context	The calling context.
			* @param MIDs		Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeTextureParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value, LogLevel);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MID.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeTextureParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* @param Log		(optional)
			* return
			*/
			static bool SetSafeTextureParameterValue(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value, LogLevel);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MIDs.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeTextureParameterValue(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param Context	The calling context.
			* @param MIDs		Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeTextureParameterValue_MinChecks(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MID.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeTextureParameterValue_MinChecks(UMaterialInstanceDynamic* MID, const FName& ParamName, UTexture* Value);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeTextureParameterValue_MinChecks(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value);

			/**
			* Safely set the Texture Parameter Value with name: ParamName with value Value on MIDs.
			*  No Log
			*  Minimum Checks in terms of exiting early due Param Name not existing for the MID.
			* 
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value to set.
			* @param Value		The value to set.
			* return
			*/
			static bool SetSafeTextureParameterValue_MinChecks(const TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, UTexture* Value);

			/**
			* Get the value of the Texture Parameter Value with name: ParamName on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Texture Parameter Value.
			* return			The value of the Texture Parameter Value with name: ParamName.
			*/
			static UTexture* GetTextureParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

		#pragma endregion Texture

		#undef LogLevel
		};
	}
}

using CsMaterialLibrary = NCsMaterial::FLibrary;
using CsMIDLibrary = NCsMaterial::NMID::FLibrary;