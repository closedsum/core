// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Coroutine/CsRoutineHandle.h"
#include "Types/CsTypes_Movement.h"
// Log
#include "Utility/CsLog.h"

class AActor;
class UObject;
struct FCsRoutine;
class USceneComponent;
class UPrimitiveComponent;
class UMaterialInterface;

namespace NCsActor
{
	/**
	* Library of functions related to Actor
	*/
	struct CSCORE_API FLibrary final
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

	// Get
	#pragma region
	public:

		/**
		* Get an Actor with the given Tag (checks AActor->Tags)
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		static AActor* GetWithTagChecked(const FString& Context, UObject* WorldContext, const FName& Tag);

		/**
		* Get an Actor (casted to type T) with the given Tag (checks AActor->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		template<typename T>
		FORCEINLINE static T* GetWithTagChecked(const FString& Context, UObject* WorldContext, const FName& Tag)
		{
			T* A = Cast<T>(GetWithTagChecked(Context, WorldContext, Tag));

			checkf(A, TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName()));

			return A;
		}

		/**
		* Get an Actor with the given Name.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static AActor* GetByNameChecked(const FString& Context, UObject* WorldContext, const FName& Name);

		/**
		* Get an Actor with the given Name.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log
		* return
		*/
		static AActor* GetSafeByName(const FString& Context, UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Actor with the given Name.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static AActor* GetSafeByName(UObject* WorldContext, const FName& Name);

		/**
		* Get an Actor with the given Label.
		* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
		*		  Actor found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Level
		* return
		*/
		static AActor* GetByLabelChecked(const FString& Context, UObject* WorldContext, const FString& Label);

		/**
		* Get an Actor with the given Label.
		* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
		*		  Actor found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log
		* return
		*/
		static AActor* GetSafeByLabel(const FString& Context, UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Actor with the given Label.
		* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
		*		  Actor found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static AActor* GetSafeByLabel(UObject* WorldContext, const FString& Label);

	#pragma endregion Get

	// RootComponent
	#pragma region
	public:

		/**
		* Get the Root Component from an Actor.
		* 
		* @param Context	The calling context.
		* @param Actor
		* return			RootComponent.
		*/
		static USceneComponent* GetRootComponentChecked(const FString& Context, AActor* Actor);

		/**
		* Get the Root Component from an Actor.
		*
		* @param Context	The calling context.
		* @param Actor
		* @param Log
		* return			RootComponent.
		*/
		static USceneComponent* GetSafeRootComponent(const FString& Context, AActor* Actor, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get the Root Component from an Actor.
		*
		* @param Actor
		* return			RootComponent.
		*/
		static USceneComponent* GetSafeRootComponent(AActor* Actor);

		/**
		* Get the Root Component from an Actor.
		*
		* @param Context	The calling context.
		* @param Actor
		* return			RootComponent.
		*/
		static UPrimitiveComponent* GetRootPrimitiveComponentChecked(const FString& Context, AActor* Actor);

		/**
		* Get the Root Component from an Actor.
		*
		* @param Context	The calling context.
		* @param Actor
		* @param Log
		* return			RootComponent.
		*/
		static UPrimitiveComponent* GetSafeRootPrimitiveComponent(const FString& Context, AActor* Actor, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get the Root Component from an Actor.
		*
		* @param Actor
		* return			RootComponent.
		*/
		static UPrimitiveComponent* GetSafeRootPrimitiveComponent(AActor* Actor);

	#pragma endregion RootComponent

	// Move
	#pragma region

		// Interp
	#pragma region
	private:

	#define ParamsManagerType NCsMovement::NTo::NInterp::NParams::FManager
	#define ParamsResourceType NCsMovement::NTo::NInterp::NParams::FResource
	#define ParamsType NCsMovement::NTo::NInterp::NParams::FParams

		ParamsManagerType Manager_MoveByInterpParams;

	public:

		FORCEINLINE ParamsResourceType* AllocateMoveByInterpParams() { return Manager_MoveByInterpParams.Allocate(); }

		FORCEINLINE void DeallocateMoveByInterpParams(ParamsResourceType* Resource) { Manager_MoveByInterpParams.Deallocate(Resource); }

	public:

		/**
		* Move an Object via interpolation (i.e. an simple easing function) with the given Params.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Params			Information describing how to interpolate the Object.
		* return				Handle to the movement coroutine.
		*/
		static FCsRoutineHandle MoveByInterpChecked(const FString& Context, UObject* WorldContext, ParamsResourceType* Params);

		static FCsRoutineHandle SafeMoveByInterp(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) = &FCsLog::Warning);

		static char MoveByInterp_Internal(FCsRoutine* R);

		static void MoveByInterp_Internal_OnEnd(FCsRoutine* R);

	#undef ParamsManagerType
	#undef ParamsResourceType
	#undef ParamsType

	#pragma endregion Interp

	#pragma endregion Move

	// Material
	#pragma region
	public:

		/**
		* Set the Material at the given Index for the RootComponent, of type UPrimitiveComponent, on Actor.
		* 
		* @param Context	The calling context.
		* @param Actor		Actor whose RootComponent would have the Material set at Index.
		* @param Material
		* @param Index
		*/
		static void SetMaterialChecked(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index);

		/**
		* Safely set the Material at the given Index for the RootComponent, of type UPrimitiveComponent, on Actor.
		*
		* @param Context	The calling context.
		* @param Actor		Actor whose RootComponent would have the Material set at Index.
		* @param Material
		* @param Index
		* @param Log
		*/
		static void SetSafeMaterial(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely set the Material at the given Index for the RootComponent, of type UPrimitiveComponent, on Actor.
		*
		* @param Actor		Actor whose RootComponent would have the Material set at Index.
		* @param Material
		* @param Index
		*/
		static void SetSafeMaterial(AActor* Actor, UMaterialInterface* Material, const int32& Index);

		/**
		* Set the Materials for the RootComponent, of type UPrimitiveComponent, on Actor.
		*
		* @param Context	The calling context.
		* @param Actor		Actor whose RootComponent would have the Material set at Index.
		* @param Materials
		*/
		static void SetMaterialsChecked(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials);

		/**
		* Safely set the Materials for the RootComponent, of type UPrimitiveComponent, on Actor.
		*
		* @param Context	The calling context.
		* @param Actor		Actor whose RootComponent would have the Material set at Index.
		* @param Materials
		* @param Log
		*/
		static void SetSafeMaterials(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Material
	};
}