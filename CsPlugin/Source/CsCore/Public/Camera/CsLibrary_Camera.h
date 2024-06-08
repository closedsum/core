// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

class UObject;
class UActorComponent;
class ACameraActor;
class UCameraComponent;

namespace NCsCamera
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetLocation;
				extern CSCORE_API const FString GetLocationChecked;
				extern CSCORE_API const FString GetRotation;
				extern CSCORE_API const FString GetRotationChecked;
				extern CSCORE_API const FString GetDirectionChecked;
			}
		}
	}

	/**
	* Library of function related to Camera
	*/
	class CSCORE_API FLibrary final
	{
	// Get
	#pragma region
	public:

		/**
		* Get an Camera with the given Tag (checks ACameraActor->Tags)
		*  NOTE: Find the FIRST Camera the given Tag.
		*  NOTE: There should be only ONE Camera with given Tag.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		static ACameraActor* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

	#pragma endregion Get
	
	// Is
	#pragma region
	public:

		static bool IsCameraComponent(const UActorComponent* Component);
		
	#pragma endregion Is

	// Spawn
	#pragma region
	public:

		static ACameraActor* SpawnChecked(const FString& Context, const UObject* WorldContext, const UCameraComponent* Component);

	#pragma endregion Spawn

	// Copy
	#pragma region

		static void CopyChecked(const FString& Context, const UCameraComponent* From, ACameraActor* To);

	#pragma endregion Copy

	// Destroy
	#pragma region
	public:

		static void SimulateDestroyChecked(const FString& Context, UCameraComponent* Component);
		static void SimulateDestroyByActorComponentChecked(const FString& Context, UActorComponent* Component);

	#pragma endregion Destroy

	// Location
	#pragma region
	public:

		/**
		* Get the current camera location from Object.
		*
		* @param Object	Object to get camera related information from.
		* return		Current camera location.
		*/
		static FVector3f GetLocation(UObject* Object);

		/**
		* Get the current camera location from Object with 
		* rules (see ECsLocationRules).
		*
		* @param Object	Object to get camera related information from.
		* @param Rules	Mask of bits to determine which location axis to take.
		*				Omitted axes will default to 0.0f.
		* return		Current camera location.
	`	*/
		static FVector3f GetLocation(UObject* Object, const int32& Rules);

		/**
		* Get the current camera location from Object with checks.
		*
		* @param Context	The calling context.
		* @param Object		Object to get camera related information from.
		* return			Current camera location
		*/
		static FVector3f GetLocationChecked(const FString& Context, UObject* Object);

		/**
		* Get the current camera location from Object with checks.
		*
		* @param Object	Object to get camera related information from.
		* return		Current camera location
		*/
		static FVector3f GetLocationChecked(UObject* Object);

	#pragma endregion Location

	// Rotation
	#pragma region
	public:

		/**
		* Get the current camera rotation from Object.
		*
		* @param Object	Object to get camera related information from.
		* return		Current camera rotation.
		*/
		static FRotator3f GetRotation(UObject* Object);

		/**
		* Get the current camera rotation from Object with
		* rules (see ECsRotationRules).
		*
		* @param Object	Object to get camera related information from.
		* @param Rules	Mask of bits to determine which rotation axis to take.
		*				Omitted axes will default to 0.0f.
		* return		Current camera rotation.
		*/
		static FRotator3f GetRotation(UObject* Object, const int32& Rules);

		/**
		*/
		static FRotator3f GetRotationChecked(const FString& Context, UObject* Object);

		/**
		*/
		static FRotator3f GetRotationChecked(UObject* Object);

		/**
	*/
		static FRotator3f GetRotationChecked(const FString& Context, UObject* Object, const int32& Rules);

		/**
		*/
		static FRotator3f GetRotationChecked(UObject* Object, const int32& Rules);


	#pragma endregion Rotation

	// Direction
	#pragma region
	public:

		/**
		* Get the current camera direction from Object.
		*
		* @param Object	Object to get camera related information from.
		* return		Current camera direction.	
		*/
		FORCEINLINE static FVector3f GetDirection(UObject* Object)
		{
			return GetRotation(Object).Vector();
		}

		/**
		* Get the current camera direction from Object with
		* rules (see ECsRotationRules).
		*
		* @param Object	Object to get camera related information from.
		* @param Rules	Mask of bits to determine which location axis to take.
		*				Omitted axes will default to 0.0f.
		* @param		Current camera direction.
		*/
		FORCEINLINE static FVector3f GetDirection(UObject* Object, const int32& Rules)
		{
			return GetRotation(Object, Rules).Vector();
		}

		/**
		*/
		FORCEINLINE static FVector3f GetDirectionChecked(const FString& Context, UObject* Object)
		{
			return GetRotationChecked(Context, Object).Vector();
		}

		/**
		*/
		FORCEINLINE static FVector3f GetDirectionChecked(UObject* Object)
		{
			using namespace NCsCamera::NLibrary::NCached;

			const FString& Context = Str::GetDirectionChecked;

			return GetRotationChecked(Context, Object).Vector();
		}

		/**
		*/
		FORCEINLINE static FVector3f GetDirectionChecked(const FString& Context, UObject* Object, const int32& Rules)
		{
			return GetRotationChecked(Context, Object, Rules).Vector();
		}

		/**
		*/
		FORCEINLINE static FVector3f GetDirectionChecked(UObject* Object, const int32& Rules)
		{
			using namespace NCsCamera::NLibrary::NCached;

			const FString& Context = Str::GetDirectionChecked;

			return GetRotationChecked(Context, Object, Rules).Vector();
		}

	#pragma endregion Direction
	};
}