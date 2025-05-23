// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Cached.h"
#include "CsMacro_Log.h"
#include "Managers/StaticMesh/Payload/CsTypes_Payload_StaticMeshActor.h"

#include "CsScriptLibrary_Manager_StaticMeshActor.generated.h"

CS_FWD_DECLARE_CACHED_FUNCTION_NAME(CsScriptLibrary_Manager_StaticMeshActor)

UCLASS()
class CSSTATICMESH_API UCsScriptLibrary_Manager_StaticMeshActor : public UObject
{ 
	GENERATED_UCLASS_BODY() 

private:

	CS_USING_CACHED_FUNCTION_NAME(CsScriptLibrary_Manager_StaticMeshActor);

	CS_DECLARE_STATIC_LOG_WARNING

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