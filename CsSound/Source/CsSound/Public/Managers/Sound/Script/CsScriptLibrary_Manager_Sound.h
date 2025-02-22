// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

#include "CsScriptLibrary_Manager_Sound.generated.h"

UCLASS()
class CSSOUND_API UCsScriptLibrary_Manager_Sound : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Pool
#pragma region
public:

	/**
	* Find a pooled Sound Object that implements the interface: ICsSoundPooled with the
	* given Type and Index.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type
	* @param Index
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Sound", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type,Index"))
	static UObject* FindObject(const FString& Context, UObject* WorldContextObject, const FECsSound& Type, const int32& Index);

#pragma endregion Pool

public:

	/**
	* Spawn a Sound with the given Payload. 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Payload
	* @param Transform
	* return					Index to spawned Sound in pool.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Sound", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Payload,Transform"))
	static int32 Spawn(const FString& Context, UObject* WorldContextObject, const FCsPayload_Sound& Payload, const FTransform& Transform);
};