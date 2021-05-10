// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Material/CsTypes_Material_Anim.h"
#include "Coroutine/CsRoutineHandle.h"
// Log
#include "Utility/CsLog.h"

class UStaticMesh;
class USkeletalMesh;
class UPrimitiveComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UMaterialInterface;
class UMaterialInstanceConstant;
class UMaterialInstanceDynamic;
struct FSkeletalMaterial;
struct FCsRoutine;

namespace NCsMaterial
{
	/**
	* Library of functions related to MaterialInterface
	*/
	struct CSCORE_API FLibrary final
	{
	// Load
	#pragma region
	public:

		/**
		* Load the Material Interface at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Material Interface to load.
		* @param Log
		* return			NiagaraSystem.
		*/
		static UMaterialInterface* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a Material Interface at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Material Interface to load.
		* @param Log
		* return			Material Interface.
		*/
		static UMaterialInterface* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load

	public:

		/**
		*/
		static bool IsValidChecked(const FString& Context, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static bool IsValid(const FString& Context, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) = &FCsLog::Warning);
		 
		/**
		*/
		static bool IsValidChecked(const FString& Context, UStaticMesh* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static bool IsValid(const FString& Context, UStaticMesh* Mesh, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		*/
		static bool IsValidChecked(const FString& Context, USkeletalMesh* Mesh, const TArray<UMaterialInterface*>& Materials);

		/**
		*/
		static bool IsValid(const FString& Context, USkeletalMesh* Mesh, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) = &FCsLog::Warning);

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
		* @param Log
		*/
		static void SetSafe(const FString& Context, UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning);
		
		/**
		* Safely set the Material at the given Index on Component
		*
		* @param Component
		* @param Material
		* @param Index
		*/
		static void SetSafe(UPrimitiveComponent* Component, UMaterialInterface* Material, const int32& Index);

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
		* @param Log
		*/
		static void SetSafe(const FString& Context, UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) = &FCsLog::Warning);
		
		/**
		* Safely set the Materials on Component
		*
		* @param Component
		* @param Materials
		*/
		static void SetSafe(UPrimitiveComponent* Component, const TArray<UMaterialInterface*>& Materials);

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
		* Clear the override materials on Component.
		*
		* @param Context	The calling context.
		* @param Component
		*/
		static void ClearOverrideChecked(const FString& Context, UPrimitiveComponent* Component);

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
		/**
		* Library of functions related to MaterialInstanceDynamic
		*/
		struct CSCORE_API FLibrary
		{
		private:
			FLibrary();

			FLibrary(const FLibrary&) = delete;
			FLibrary(FLibrary&&) = delete;
		public:
			~FLibrary();

			FORCEINLINE static FLibrary& Get()
			{
				static FLibrary Instance;
				return Instance;
			}

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
			static bool IsScalarParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Check whether there is a Scalar Parameter Value with name: ParamName for MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value.
			* return			Whether there IS a Scalar Parameter Value with name: ParamName or NOT.
			*/
			static bool IsScalarParameterValid(UMaterialInstanceDynamic* MID, const FName& ParamName);

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
			static void SetScalarParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MID.
			*
			* @param Context	The calling context.
			* @param MIDs		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* @param Log
			*/
			static void SetSafeScalarParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MID.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetSafeScalarParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const float& Value);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			* @param Log
			*/
			static void SetSafeScalarParameterValue(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the Scalar Parameter Value with name: ParamName with value Value on MIDs.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetSafeScalarParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const float& Value);

			/**
			* Get the value of the Scalar Parameter Value with name: ParamName on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Scalar Parameter Value.
			* return			The value of the Scalar Parameter Value with name: ParamName.
			*/
			static float GetScalarParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName);

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
			static bool IsVectorParameterValid(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static void SetVectorParameterValueChecked(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value);

			/**
			* Set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetVectorParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param Context	The calling context.
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* @param Log
			*/
			static void SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FVector& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* @param Log
			*/
			static void SetSafeVectorParameterValue(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetSafeVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FVector& Value);

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
			* @param Log
			*/
			static void SetSafeVectorParameterValue(const FString& Context, UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MID.
			*
			* @param MID		Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetSafeVectorParameterValue(UMaterialInstanceDynamic* MID, const FName& ParamName, const FLinearColor& Value);

			/**
			* Set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetVectorParameterValueChecked(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param Context	The calling context.
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			* @param Log
			*/
			static void SetSafeVectorParameterValue(const FString& Context, TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the Vector Parameter Value with name: ParamName with value: Value on MIDs.
			*
			* @param MIDs		Array of Material Instance Dynamic.
			* @param ParamName	Name of the Vector Parameter Value to set.
			* @param Value		The value to set.
			*/
			static void SetSafeVectorParameterValue(TArray<UMaterialInstanceDynamic*>& MIDs, const FName& ParamName, const FLinearColor& Value);

		#pragma endregion Vector

		// Anim
		#pragma region
		private:

		#define ParamsManagerType NCsMaterial::NAnim::NParams::FManager
		#define ParamsResourceType NCsMaterial::NAnim::NParams::FResource
		#define ParamsType NCsMaterial::NAnim::NParams::FParams

			ParamsManagerType Manager_AnimParams;

		public:

			FORCEINLINE ParamsResourceType* AllocateAnimParams() { return Manager_AnimParams.Allocate(); }

			FORCEINLINE void DeallocateAnimParams(ParamsResourceType* Resource) { Manager_AnimParams.Deallocate(Resource); }

		public:

			/**
			* Animate any number of parameters on a MaterialInstanceDynamic with the given Params.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Params			Information describing how to animate any number of parameters on a MaterialInstanceDynamic.
			* return				Handle to the movement coroutine.
			*/
			static FCsRoutineHandle PlayAnimChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params);

			/**
			* Safely animate any number of parameters on a MaterialInstanceDynamic with the given Params.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Params			Information describing how to animate any number of parameters on a MaterialInstanceDynamic.
			* @param Log
			* return				Handle to the movement coroutine.
			*/
			static FCsRoutineHandle SafePlayAnim(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) = &FCsLog::Warning);

		private:

			static char PlayAnim_Internal(FCsRoutine* R);

			static void PlayAnim_Internal_OnEnd(FCsRoutine* R);

		#undef ParamsManagerType
		#undef ParamsResourceType
		#undef ParamsType

		#pragma endregion Anim
		};
	}
}