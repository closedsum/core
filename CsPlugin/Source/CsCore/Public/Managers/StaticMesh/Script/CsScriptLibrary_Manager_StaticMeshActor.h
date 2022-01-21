// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/StaticMesh/Payload/CsTypes_Payload_StaticMeshActor.h"

#include "CsScriptLibrary_Manager_StaticMeshActor.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_StaticMeshActor : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Pool
#pragma region
public:

	/**
	* Find a pooled StaticMeshActor that implements the interface: ICsStaticMeshActorPooled with the
	* given Type and Index.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Index
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|StaticMesh", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Index"))
	static UObject* FindObject(const FString& Context, const UObject* WorldContextObject, const FECsStaticMeshActor& Type, const int32& Index);

#pragma endregion Pool

public:

	/**
	* Spawn a StaticMeshActor with the given Payload. 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* return					Index to spawned StaticMeshActor in pool.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|StaticMesh", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Payload"))
	static int32 Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_StaticMesh& Payload);
};