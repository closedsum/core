// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/FX/Payload/CsTypes_Payload_FX.h"

#include "CsScriptLibrary_Manager_FX.generated.h"

UCLASS()
class CSFX_API UCsScriptLibrary_Manager_FX : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Pool
#pragma region
public:

	/**
	* Find a pooled FX Object that implements the interface: ICsFXActorPooled with the
	* given Type and Index.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Index
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFX|Library|Manager|FX", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Index"))
	static UObject* FindObject(const FString& Context, UObject* WorldContextObject, const FECsFX& Type, const int32& Index);

#pragma endregion Pool

public:

	/**
	* Spawn a FX with the given Payload. 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* @param Transform
	* return					Index to spawned FX in pool.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsFX|Library|Manager|FX", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Payload,Transform"))
	static int32 Spawn(const FString& Context, UObject* WorldContextObject, const FCsPayload_FX& Payload, const FTransform& Transform);
};