// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Beam
#include "Payload/CsPayload_BeamImpl.h"

#include "CsScriptLibrary_Manager_Beam.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class ICsBeam;

UCLASS()
class CSBEAM_API UCsScriptLibrary_Manager_Beam : public UObject
{
	GENERATED_UCLASS_BODY()

// Settings
#pragma region
public:

	/**
	*
	*
	* @param WorldContextObject
	* @param Beam
	* @param Key
	* @param Value
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Manager|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Key,Value"))
	static void SetTypeMapKeyValue(const FString& Context, const UObject* WorldContextObject, const FECsBeam& Key, const FECsBeam& Value);

#pragma endregion Settings

// Spawn
#pragma region
public:

	/**
	* 
	*
	* @param WorldContextObject
	* @param Beam
	* @param Payload
	* return					Object of type ICsBeam
	*/
	UFUNCTION(BlueprintCallable, Category = "CsBeam|Library|Manager|Beam", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Beam,Payload"))
	static int32 Spawn(const FString& Context, const UObject* WorldContextObject, const FECsBeam& Beam, const FCsPayload_Beam& Payload);

#pragma endregion Spawn
};