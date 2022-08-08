// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetSafeByTag;
			}
		}
	}

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
		static AActor* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

		/**
		* Get an Actor (casted to type T) with the given Tag (checks AActor->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		template<typename T>
		FORCEINLINE static T* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
		{
			T* A = Cast<T>(GetByTagChecked(Context, WorldContext, Tag));

			checkf(A, TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName()));

			return A;
		}

		/**
		* Safely get an Actor with the given Tag (checks AActor->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* @param Log
		* return				Actor
		*/
		static AActor* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely get an Actor (casted to type T) with the given Tag (checks AActor->Tags)
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* @param Log
		* return				Actor
		*/
		template<typename T>
		FORCEINLINE static T* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			T* A = Cast<T>(GetSafeByTag(Context, WorldContext, Tag, Log));

			if (!A)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName())));
			}
			return A;
		}

		/**
		* Safely get an Actor with the given Tag (checks AActor->Tags)
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return				Actor
		*/
		FORCEINLINE static AActor* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeByTag;

			return GetSafeByTag(Context, WorldContext, Tag, nullptr);
		}

		/**
		* Safely get an Actor (casted to type T) with the given Tag (checks AActor->Tags)
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return				Actor
		*/
		template<typename T>
		FORCEINLINE static T* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeByTag;

			return GetSafeByTag<T>(Context, WorldContext, Tag, nullptr);
		}

		/**
		* Get a list of Actors with the given Tag (checks AActor->Tags).
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param OutActors		(out)
		*/
		static void GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors);

		/**
		* Safely get a list of Actors with the given Tag (checks AActor->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param OutActors		(out)
		* @param Log			(optional)
		* return				Whether any actors were found with Tags.
		*/
		static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Actor with the given Name.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static AActor* GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

		/**
		* Get an Actor with the given Name.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log
		* return
		*/
		static AActor* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Actor with the given Name.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static AActor* GetSafeByName(const UObject* WorldContext, const FName& Name);

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
		static AActor* GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label);

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
		static AActor* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &FCsLog::Warning);

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
		static AActor* GetSafeByLabel(const UObject* WorldContext, const FString& Label);

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

	// Visibility
	#pragma region
	public:

		static void SetSafeHiddenInGame(const FString& Context, AActor* A, const bool& NewHidden, const bool& ApplyToAttachChildren, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Visibility

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
		static FCsRoutineHandle MoveByInterpChecked(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params);

		/**
		* Safely move an Object via interpolation (i.e. an simple easing function) with the given Params.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Params			Information describing how to interpolate the Object.
		* @param Log
		* return				Handle to the movement coroutine.
		*/
		static FCsRoutineHandle SafeMoveByInterp(const FString& Context, const UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) = &FCsLog::Warning);

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

	// Spawn
	#pragma region
	public:

		/**
		* Safely spawn an Actor in the World with the given Path.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Path			SoftObjectPath to the Actor class to load and then spawn.
		* @param Log
		* return				Spawned Actor.
		*/
		static AActor* SafeSpawn(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path, void (*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely spawn an Actor in the World with the given Path.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Path			String path to the Actor class to load and then spawn.
		* @param Log
		* return				Spawned Actor.
		*/
		static AActor* SafeSpawn(const FString& Context, const UObject* WorldContext, const FString& Path, void (*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Spawn

	// Distance
	#pragma region
	public:

		/**
		* Safely get the distance squared between A and B.
		* 
		* @param Context	The calling context.
		* @param A
		* @param B
		* @param Log		(optional)
		* return			Distance squared between A and B.
		*/
		static float GetSafeDistanceSq(const FString& Context, const AActor* A, const AActor* B, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get the distance squared 2D between A and B.
		*
		* @param Context	The calling context.
		* @param A
		* @param B
		* return			Distance squared 2D between A and B.
		*/
		static float GetDistanceSq2DChecked(const FString& Context, const AActor* A, const AActor* B);

		/**
		* Safely get the distance squared 2D between A and B.
		*
		* @param Context	The calling context.
		* @param A
		* @param B
		* @param Log		(optional)
		* return			Distance squared 2D between A and B.
		*/
		static float GetSafeDistanceSq2D(const FString& Context, const AActor* A, const AActor* B, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Check if the distance squared 2D between A and B is Less Than or Equal to R^2 (R squared).
		*
		* @param Context	The calling context.
		* @param A
		* @param B
		* @param R
		* @param Log		(optional)
		* return
		*/
		static bool SafeIsDistanceSq2D_LessThanOrEqual(const FString& Context, AActor* A, AActor* B, const float& R, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Distance

	// Normal
	#pragma region
	public:

		/**
		* Safely gets the normal between A and B (AB or B - A)
		* 
		* @param Context		The calling context.
		* @param A
		* @param B
		* @param OutNormal
		* @param OutDistanceSq	The distance squared between A and B
		* @param OutDistance
		* @param Log			(optional)
		* return
		*/
		static bool GetSafeNormalAtoB(const FString& Context, const AActor* A, const AActor* B, FVector& OutNormal, float& OutDistanceSq, float& OutDistance, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Gets the normal 2d between A and B (AB or B - A)
		*
		* @param Context		The calling context.
		* @param A
		* @param B
		* @param OutNormal
		* @param OutDistanceSq	The distance squared between A and B
		* @param OutDistance
		*/
		static void GetNormal2DAtoBChecked(const FString& Context, const AActor* A, const AActor* B, FVector& OutNormal, float& OutDistanceSq, float& OutDistance);

		/**
		* Safely gets the normal 2d between A and B (AB or B - A)
		*
		* @param Context		The calling context.
		* @param A
		* @param B
		* @param OutNormal
		* @param OutDistanceSq	The distance squared between A and B
		* @param OutDistance
		* @param Log			(optional)
		* return
		*/
		static bool GetSafeNormal2DAtoB(const FString& Context, const AActor* A, const AActor* B, FVector& OutNormal, float& OutDistanceSq, float& OutDistance, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Gets the normal 2d between A and B (AB or B - A)
		*
		* @param Context		The calling context.
		* @param A
		* @param B
		* @param OutNormal
		* @param OutDistanceSq	The distance squared between A and B
		* @param OutDistance
		*/
		static void GetNormal2DAtoBChecked(const FString& Context, const AActor* A, const FVector& B, FVector& OutNormal, float& OutDistanceSq, float& OutDistance);

		/**
		* Safely gets the normal 2d between A and B (AB or B - A)
		*
		* @param Context		The calling context.
		* @param A
		* @param B
		* @param OutNormal
		* @param OutDistanceSq	The distance squared between A and B
		* @param OutDistance
		* @param Log			(optional)
		* return
		*/
		static bool GetSafeNormal2DAtoB(const FString& Context, const AActor* A, const FVector& B, FVector& OutNormal, float& OutDistanceSq, float& OutDistance, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Normal
	};
}