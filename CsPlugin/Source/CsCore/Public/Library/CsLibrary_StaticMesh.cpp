// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_StaticMesh.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Math.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Mesh
#include "Engine/StaticMesh.h"
// Component
#include "Components/StaticMeshComponent.h"

namespace NCsStaticMesh
{
	// Load
	#pragma region

	UStaticMesh* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::LoadChecked<UStaticMesh>(Context, Path);
	}

	UStaticMesh* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UStaticMesh>(Context, Path, Log);
	}

	UStaticMesh* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::LoadChecked<UStaticMesh>(Context, Path);
	}

	UStaticMesh* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UStaticMesh>(Context, Path, Log);
	}

	#pragma endregion Load

	// Set
	#pragma region

	void FLibrary::SetChecked(const FString& Context, UStaticMeshComponent* Component, UStaticMesh* Mesh)
	{
		CS_IS_PTR_NULL_CHECKED(Component)
		CS_IS_PTR_NULL_CHECKED(Mesh)

		Component->SetStaticMesh(Mesh);
	}

	#pragma endregion Set
}