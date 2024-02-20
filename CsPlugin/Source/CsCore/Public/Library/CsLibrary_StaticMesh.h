// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class UActorComponent;
class UStaticMesh;
class UStaticMeshComponent;
class AStaticMeshActor;

namespace NCsStaticMesh
{
	/**
	* Library of function related to StaticMesh
	*/
	class CSCORE_API FLibrary
	{
	// Load
	#pragma region
	public:

		/**
		* Load the StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the StaticMesh to load.
		* return			StaticMesh.
		*/
		static UStaticMesh* LoadChecked(const FString& Context, const FSoftObjectPath& Path);

		/**
		* Safely load the StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the StaticMesh to load.
		* @param Log
		* return			StaticMesh.
		*/
		static UStaticMesh* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the StaticMesh to load.
		* @param Log
		* return			StaticMesh.
		*/
		static UStaticMesh* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Safely load a StaticMesh at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the StaticMesh to load.
		* @param Log
		* return			StaticMesh.
		*/
		static UStaticMesh* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load

	// Is
	#pragma region
	public:

		static bool IsStaticMeshComponent(const UActorComponent* Component);
		
	#pragma endregion Is

	// Set
	#pragma region
	public:

		/**
		* Set Mesh on the Component.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param Mesh
		*/
		static void SetChecked(const FString& Context, UStaticMeshComponent* Component, UStaticMesh* Mesh);

	#pragma endregion Set

	// Spawn
	#pragma region
	public:

		static AStaticMeshActor* SpawnChecked(const FString& Context, const UObject* WorldContext, const UStaticMeshComponent* Component);
		static AStaticMeshActor* SpawnByActorComponentChecked(const FString& Context, const UObject* WorldContext, const UActorComponent* Component);

	#pragma endregion Spawn

	// Copy
	#pragma region
	public:

		static void CopyChecked(const FString& Context, const UStaticMeshComponent* From, AStaticMeshActor* To);

	#pragma endregion Copy

	// Destroy
	#pragma region
	public:

		static void SimulateDestroyChecked(const FString& Context, UStaticMeshComponent* Component);
		static void SimulateDestroyByActorComponentChecked(const FString& Context, UActorComponent* Component);

	#pragma endregion Destroy
	};
}