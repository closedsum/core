// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_World.generated.h"

class AActor;

UCLASS()
class CSCORE_API UCsScriptLibrary_World : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Removes the passed in actor to from special network actor list
	*
	* @param Actor	Actor to remove
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|World", meta = (AutoCreateRefTerm = "Context"))
	static void RemoveNetworkActor(const FString& Context, AActor* Actor);
};