// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Instanced/CsSettings_Manager_InstancedStaticMeshComponent.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

// FCsSettings_Manager_InstancedStaticMeshComponent
#pragma region

/*static*/ const FCsSettings_Manager_InstancedStaticMeshComponent& FCsSettings_Manager_InstancedStaticMeshComponent::Get()
{
	return GetMutableDefault<UCsDeveloperSettings>()->Manager_InstancedStaticMeshComponent;
}

bool FCsSettings_Manager_InstancedStaticMeshComponent::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 4)
	return true;
}

bool FCsSettings_Manager_InstancedStaticMeshComponent::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 4)
	return true;
}

#pragma endregion FCsSettings_Manager_InstancedStaticMeshComponent