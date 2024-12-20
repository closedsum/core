// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

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
	class CSCORELIBRARY_API FLibrary
	{
	private:

		CS_DECLARE_STATIC_LOG_LEVEL

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
		static UStaticMesh* SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
		static UStaticMesh* SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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

using CsStaticMeshLibrary = NCsStaticMesh::FLibrary;