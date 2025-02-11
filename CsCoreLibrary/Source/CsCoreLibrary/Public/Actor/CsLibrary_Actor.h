// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Templates/SubclassOf.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class AActor;
class UObject;
class UActorComponent;
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
				extern CSCORELIBRARY_API const FString GetSafeByTag;
				extern CSCORELIBRARY_API const FString SetScaleChecked;
				extern CSCORELIBRARY_API const FString SetSafeScale;
				// Orientation
				extern CSCORELIBRARY_API const FString GetRotationChecked;
				extern CSCORELIBRARY_API const FString GetSafeRotation;
				extern CSCORELIBRARY_API const FString GetQuatChecked;
				extern CSCORELIBRARY_API const FString SetRotationChecked;
				// Movement
				extern CSCORELIBRARY_API const FString GetLocationChecked;
				extern CSCORELIBRARY_API const FString SetLocationChecked;
				extern CSCORELIBRARY_API const FString SetLocationAndRotationChecked;
				extern CSCORELIBRARY_API const FString GetForwardChecked;
			}
		}
	}

	/**
	* Library of functions related to Actor
	*/
	struct CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

		static FString PrintActorAndClass(const AActor* Actor);

	// Get
	#pragma region
	public:

		static void GetAllChecked(const FString& Context, const UObject* WorldContext, TArray<AActor*>& OutActors);

		/**
		*
		*
		* @param Context		The calling context.
		* @param WorldContxt
		* @param ActorClass
		* @param OutActors		(out)
		*/
		static void GetAllOfClassChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, TArray<AActor*>& OutActors);

		/**
		*
		*
		* @param Context		The calling context.
		* @param WorldContxt
		* @param ActorClass
		* @param OutActors		(out)
		* @param Log			(optional)
		* return
		*/
		static bool GetSafeAllOfClass(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, TArray<AActor*>& OutActors, LogLevel);

		static AActor* GetByClassChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass);

		template<typename T>
		FORCEINLINE static T* GetByClassChecked(const FString& Context, const UObject* WorldContext)
		{
			T* A = Cast<T>(GetByClassChecked(Context, WorldContext, T::StaticClass()));

			checkf(A, TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName()));
			return A;
		}

		static AActor* GetSafeByClass(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, LogLevel);

		template<typename T>
		FORCEINLINE static T* GetSafeByClass(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			T* A = Cast<T>(GetSafeByClass(Context, WorldContext, T::StaticClass(), Log));

			if (!A)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName())));
			}
			return A;
		}

		static AActor* GetByClassAndTagChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const FName& Tag);

		static AActor* GetSafeByClassAndTag(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const FName& Tag, LogLevel);

		static AActor* GetByClassAndInterfaceChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const UClass* InterfaceClass);

		static AActor* GetByClassAndInterfaceAndTagChecked(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const UClass* InterfaceClass, const FName& Tag);

		static AActor* GetSafeByClassAndInterfaceAndTag(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, const UClass* InterfaceClass, const FName& Tag, LogLevel);

		static AActor* GetByInterfaceChecked(const FString& Context, const UObject* WorldContext, const UClass* InterfaceClass);

		static void GetAllByInterfaceChecked(const FString& Context, const UObject* WorldContext, const UClass* InterfaceClass, TArray<AActor*>& OutActors);

		static bool GetSafeAllByInterface(const FString& Context, const UObject* WorldContext, const UClass* InterfaceClass, TArray<AActor*>& OutActors, LogLevel);

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
		static AActor* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogLevel);

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
		FORCEINLINE static T* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogLevel)
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
		static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors, LogLevel);

		/**
		* Get an Actor with the given Tags (checks AActor->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* returns				Actor
		*/
		static AActor* GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags);

		/**
		* Safely get an Actor with the given Tags (checks AActor->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param Log			(optional)
		* return				Actor
		*/
		static AActor* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, LogLevel);

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
		static AActor* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, LogLevel);

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
		static AActor* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, LogLevel);

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

	// Has
	#pragma region
	public:

		static bool HasTagsChecked(const FString& Context, const AActor* A, const TArray<FName>& Tags);

		static bool SafeHasTags(const FString& Context, const AActor* A, const TArray<FName>& Tags, LogLevel);

		static bool SafeHasTags(const FString& Context, const AActor* A, const TArray<FName>& Tags, bool& OutSuccess, LogLevel);

		static bool HasTagChecked(const FString& Context, const AActor* A, const FName& Tag);

		static bool SafeHasTag(const FString& Context, const AActor* A, const FName& Tag, LogLevel);

		static bool SafeHasTag(const FString& Context, const AActor* A, const FName& Tag, bool& OutSuccess, LogLevel);

	#pragma endregion Has

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
		static USceneComponent* GetSafeRootComponent(const FString& Context, AActor* Actor, LogLevel);

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
		static UPrimitiveComponent* GetSafeRootPrimitiveComponent(const FString& Context, AActor* Actor, LogLevel);

		/**
		* Get the Root Component from an Actor.
		*
		* @param Actor
		* return			RootComponent.
		*/
		static UPrimitiveComponent* GetSafeRootPrimitiveComponent(AActor* Actor);

	#pragma endregion RootComponent

	// Component
	#pragma region
	public:

		/**
		* Safely get a Component with Tag from Actor.
		*
		* @param Context	The calling context.
		* @param A			Actor
		* @param Tag
		* @param Log		(optional)
		* return			Component.
		*/
		static UActorComponent* GetSafeComponentByTag(const FString& Context, const AActor* A, const FName& Tag, LogLevel);

	#pragma endregion Component

	// Visibility
	#pragma region
	public:

		/**
		* Set an Actor to be hidden or visible with option to set the visibility of any attached children.
		*
		* @param Context				The calling context.
		* @param Actor
		* @param NewHidden				True = Hide. False = Visible.
		* @param ApplyToAttachChildren
		*/
		static void SetHiddenInGameChecked(const FString& Context, AActor* A, const bool& NewHidden, const bool& ApplyToAttachChildren);

		/**
		* Safely set an Actor to be hidden or visible with option to set the visibility of any attached children.
		*
		* @param Context				The calling context.
		* @param Actor
		* @param NewHidden				True = Hide. False = Visible.
		* @param ApplyToAttachChildren
		* @param Log					(optional)
		* return						Whether the visibility change was successfully set.
		*/
		static bool SetSafeHiddenInGame(const FString& Context, AActor* A, const bool& NewHidden, const bool& ApplyToAttachChildren, LogLevel);

	#pragma endregion Visibility

	public:

		static void SetScaleChecked(const FString& Context, AActor* A, const FVector3f& Scale);
		FORCEINLINE static void SetScaleChecked(AActor* A, const FVector3f& Scale)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::SetScaleChecked;

			SetScaleChecked(Context, A, Scale);
		}

		static bool SetSafeScale(const FString& Context, AActor* A, const FVector3f& Scale, LogLevel);
		FORCEINLINE static bool SetSafeScale(AActor* A, const FVector3f& Scale, LogLevel)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::SetSafeScale;

			return SetSafeScale(Context, A, Scale, Log);
		}

	// Orientation
	#pragma region
	public:

		static FRotator3f GetRotationChecked(const FString& Context, const AActor* A);
		FORCEINLINE static FRotator3f GetRotationChecked(const AActor* A)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetRotationChecked;

			return GetRotationChecked(Context, A);
		}

		static FRotator3f GetSafeRotation(const FString& Context, const AActor* A, LogLevel);
		FORCEINLINE static FRotator3f GetSafeRotation(const AActor* A, LogLevel)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetSafeRotation;

			return GetSafeRotation(Context, A, Log);
		}

		static FQuat4f GetQuatChecked(const FString& Context, const AActor* A);
		FORCEINLINE static FQuat4f GetQuatChecked(const AActor* A)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetQuatChecked;

			return GetQuatChecked(Context, A);
		}

		static void SetRotationChecked(const FString& Context, AActor* A, const FRotator3f& Rotation);
		FORCEINLINE static void SetRotationChecked(AActor* A, const FRotator3f& Rotation)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::SetRotationChecked;

			SetRotationChecked(Context, A, Rotation);
		}

		static void SetRotationChecked(const FString& Context, AActor* A, const FQuat4f& Rotation);
		FORCEINLINE static void SetRotationChecked(AActor* A, const FQuat4f& Rotation)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::SetRotationChecked;

			SetRotationChecked(Context, A, Rotation);
		}

	#pragma endregion Orientation

	// Movement
	#pragma region
	public:

		static bool GetSafeLocation(const FString& Context, const AActor* A, FVector3f& OutLocation, LogLevel);
	
		static FVector3f GetLocationChecked(const FString& Context, const AActor* A);
		FORCEINLINE static FVector3f GetLocationChecked(const AActor* A)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetLocationChecked;

			return GetLocationChecked(Context, A);
		}

		static void SetLocationChecked(const FString& Context, AActor* A, const FVector3f& Location);
		FORCEINLINE static void SetLocationChecked(AActor* A, const FVector3f& Location)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::SetLocationChecked;

			SetLocationChecked(Context, A, Location);
		}

		static bool SetLocationAndRotationChecked(const FString& Context, AActor* A, const FVector3f& Location, const FRotator3f& Rotation);
		FORCEINLINE static bool SetLocationAndRotationChecked(AActor* A, const FVector3f& Location, const FRotator3f& Rotation)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::SetLocationAndRotationChecked;

			return SetLocationAndRotationChecked(Context, A, Location, Rotation);
		}

		static bool SetLocationAndRotationChecked(const FString& Context, AActor* A, const FVector3f& Location, const FQuat4f& Rotation);
		FORCEINLINE static bool SetLocationAndRotationChecked(AActor* A, const FVector3f& Location, const FQuat4f& Rotation)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::SetLocationAndRotationChecked;

			return SetLocationAndRotationChecked(Context, A, Location, Rotation);
		}

		static FVector3f GetForwardChecked(const FString& Context, const AActor* A);
		FORCEINLINE static FVector3f GetForwardChecked(const AActor* A)
		{
			using namespace NCsActor::NLibrary::NCached;

			const FString& Context = Str::GetForwardChecked;

			return GetForwardChecked(Context, A);
		}

		/**
		 * Used for adding actors to levels or teleporting them to a new location.
		 * The result of this function is independent of the actor's current location and rotation.
		 * If the actor doesn't fit exactly at the location specified, tries to slightly move it out of walls and such if bNoCheck is false.
		 *
		 * @param DestLocation The target destination point
		 * @param DestRotation The target rotation at the destination
		 * @param bIsATest is true if this is a test movement, which shouldn't cause any notifications (used by AI pathfinding, for example)
		 * @param bNoCheck is true if we should skip checking for encroachment in the world or other actors
		 * @return true if the actor has been successfully moved, or false if it couldn't fit.
		 */
		static bool TeleportToChecked(const FString& Context, AActor* A, const FVector3f& DestLocation, const FRotator3f& DestRotation, const bool& bIsATest = false, const bool& bNoCheck = false);

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
		static void SetSafeMaterial(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index, LogLevel);

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
		static void SetSafeMaterials(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials, LogLevel);

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
		static AActor* SafeSpawn(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path, LogLevel);

		/**
		* Safely spawn an Actor in the World with the given Path.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Path			String path to the Actor class to load and then spawn.
		* @param Log
		* return				Spawned Actor.
		*/
		static AActor* SafeSpawn(const FString& Context, const UObject* WorldContext, const FString& Path, LogLevel);

		/**
		* Safely spawn an Actor in the World with the given ActorClass.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Path			String path to the Actor class to load and then spawn.
		* @param Log
		* return				Spawned Actor.
		*/
		static AActor* SafeSpawn(const FString& Context, const UObject* WorldContext, const TSubclassOf<AActor>& ActorClass, LogLevel);

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
		static float GetSafeDistanceSq(const FString& Context, const AActor* A, const AActor* B, LogLevel);

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
		static float GetSafeDistanceSq2D(const FString& Context, const AActor* A, const AActor* B, LogLevel);

		/**
		* Check if the distance squared 2D between A and B is Less Than or Equal to R^2 (R squared).
		*
		* @param Context	The calling context.
		* @param A
		* @param B
		* @param R
		* return
		*/
		static bool IsDistanceSq2D_LessThanOrEqualChecked(const FString& Context, const AActor* A, const AActor* B, const float& R);

		/**
		* Safely check if the distance squared 2D between A and B is Less Than or Equal to R^2 (R squared).
		*
		* @param Context	The calling context.
		* @param A
		* @param B
		* @param R
		* @param Log		(optional)
		* return
		*/
		static bool SafeIsDistanceSq2D_LessThanOrEqual(const FString& Context, const AActor* A, const AActor* B, const float& R, LogLevel);

		/**
		* Check if the distance squared 2D between A and Location is Less Than or Equal to R^2 (R squared).
		*
		* @param Context	The calling context.
		* @param A
		* @param Location
		* @param R
		* return
		*/
		static bool IsDistanceSq2D_LessThanOrEqualChecked(const FString& Context, const AActor* A, const FVector3f& Location, const float& R);

		/**
		* Safely check if the distance squared 2D between A and Location is Less Than or Equal to R^2 (R squared).
		*
		* @param Context	The calling context.
		* @param A
		* @param Location
		* @param R
		* @param Log		(optional)
		* return
		*/
		static bool SafeIsDistanceSq2D_LessThanOrEqual(const FString& Context, const AActor* A, const FVector3f& Location, const float& R, LogLevel);

		/**
		* Check if the distance squared 2D between A and Location is Greater Than R^2 (R squared).
		*
		* @param Context	The calling context.
		* @param A
		* @param Location
		* @param R
		* return
		*/
		static bool IsDistanceSq2D_GreaterThanChecked(const FString& Context, const AActor* A, const FVector3f& Location, const float& R);

		/**
		* Safely check if the distance squared 2D between A and Location is Greater Than R^2 (R squared).
		*
		* @param Context	The calling context.
		* @param A
		* @param Location
		* @param R
		* return
		*/
		static bool SafeIsDistanceSq2D_GreaterThan(const FString& Context, const AActor* A, const FVector3f& Location, const float& R, LogLevel);

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
		static bool GetSafeNormalAtoB(const FString& Context, const AActor* A, const AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance, LogLevel);

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
		static void GetNormal2DAtoBChecked(const FString& Context, const AActor* A, const AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance);

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
		static bool GetSafeNormal2DAtoB(const FString& Context, const AActor* A, const AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance, LogLevel);

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
		static void GetNormal2DAtoBChecked(const FString& Context, const AActor* A, const FVector3f& B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance);

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
		static bool GetSafeNormal2DAtoB(const FString& Context, const AActor* A, const FVector3f& B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance, LogLevel);

	#pragma endregion Normal

	// Tag
	#pragma region
	public:

		static void ClearTagsChecked(const FString& Context, AActor* A, const bool& bClearComponentTags = true);

	#pragma endregion Tag

	// Tick
	#pragma region
	public:

		static void SetTickEnabledChecked(const FString& Context, AActor* A, const bool& bEnabled, const bool& bComponentsEnabled = true);

	#pragma endregion Tick

	#undef LogLevel
	};
}

using CsActorLibrary = NCsActor::FLibrary;