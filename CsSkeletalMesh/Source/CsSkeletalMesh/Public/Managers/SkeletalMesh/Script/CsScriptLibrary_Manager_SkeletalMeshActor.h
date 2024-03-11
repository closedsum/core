// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/SkeletalMesh/Payload/CsTypes_Payload_SkeletalMeshActor.h"

#include "CsScriptLibrary_Manager_SkeletalMeshActor.generated.h"

UCLASS()
class CSSKELETALMESH_API UCsScriptLibrary_Manager_SkeletalMeshActor : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Pool
#pragma region
public:

	/**
	* Find a pooled SkeletalMeshActor that implements the interface: ICsSkeletalMeshActorPooled with the
	* given Type and Index.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Index
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|SkeletalMesh", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Index"))
	static UObject* FindObject(const FString& Context, UObject* WorldContextObject, const FECsSkeletalMeshActor& Type, const int32& Index);

#pragma endregion Pool

public:

	/**
	* Spawn a SkeletalMeshActor with the given Payload. 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* return					Index to spawned SkeletalMeshActor in pool.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|SkeletalMesh", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Payload"))
	static int32 SpawnByAnimSequenceOneShot(const FString& Context, UObject* WorldContextObject, const FCsPayload_SkeletalMesh_AnimSequence_OneShot& Payload);

	/**
	* Spawn a SkeletalMeshActor with the given Payload. 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* return					Index to spawned SkeletalMeshActor in pool.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|SkeletalMesh", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Payload"))
	static int32 SpawnByAnimMontageOneShot(const FString& Context, UObject* WorldContextObject, const FCsPayload_SkeletalMesh_AnimMontage_OneShot& Payload);
};