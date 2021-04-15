// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/FX/Payload/CsTypes_Payload_FX.h"

#include "CsScriptLibrary_Manager_FX.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_FX : public UObject
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
	* @param WorldContextObject
	* @param Type
	* @param Index
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|FX", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Index"))
	static UObject* FindObject(const FString& Context, UObject* WorldContextObject, const FECsFX& Type, const int32& Index);

#pragma endregion Pool

public:

	/**
	* Spawn a FX with the given Payload. 
	*
	* @param Context			The calling context.
	* @param WorldContextObject
	* @param Payload
	* return					Index to spawned FX in pool.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|FX", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Payload"))
	static int32 Spawn(const FString& Context, UObject* WorldContextObject, const FCsPayload_FX& Payload);
};