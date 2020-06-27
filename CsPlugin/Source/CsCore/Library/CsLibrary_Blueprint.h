// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Kismet/BlueprintFunctionLibrary.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Types/CsTypes_Sound.h"
#include "Types/CsTypes.h"

#include "CsLibrary_Blueprint.generated.h"
#pragma once

class USoundCue;
class UParticleSystem;
class UDataTable;
class USkeletalMesh;
class UTexture;

UCLASS()
class CSCORE_API UCsLibrary_Blueprint : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// TSoftObjectPtr
#pragma region
public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Name", BlueprintThreadSafe), Category = "Utilities")
	static FString GetName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get FName", BlueprintThreadSafe), Category = "Utilities")
	static FName GetFName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject);

	// Container
#pragma region
public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (SoundCue)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static USoundCue* Conv_CsSoundCueToInternal(const FCsSoundCue& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (ParticleSystem)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static UParticleSystem* Conv_CsParticleSystemToInternal(const FCsParticleSystem& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (DataTable)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static UDataTable* Conv_CsDataTableToInternal(const FCsDataTable& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (Actor)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static AActor* Conv_CsActorToInternal(const FCsActor& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (Class)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static UClass* Conv_CsActorToClass(const FCsActor& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (SubclassOf)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static TSubclassOf<AActor> Conv_CsActorToSubclassOf(const FCsActor& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (SkeletalMesh)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static USkeletalMesh* Conv_CsSkeletalMeshToInternal(const FCsSkeletalMesh& Container);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get (Texture)", CompactNodeTitle = "->", BlueprintThreadSafe), Category = "Utilities")
	static UTexture* Conv_CsTextureToInternal(const FCsTexture& Container);

#pragma endregion Container

#pragma endregion TSoftObjectPtr

	
// TSoftClassPtr
#pragma region
public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Name", BlueprintThreadSafe), Category = "Utilities")
	static FString GetName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get FName", BlueprintThreadSafe), Category = "Utilities")
	static FName GetFName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass);

#pragma endregion TSoftClassPtr
};