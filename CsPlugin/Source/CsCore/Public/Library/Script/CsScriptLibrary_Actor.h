// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Actor.generated.h"

class AActor;
class USceneComponent;

UCLASS()
class CSCORE_API UCsScriptLibrary_Actor : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Set the RootComponent for an Actor.
	*
	* @param Context	The calling context.
	* @param Actor
	* @param Component
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context"))
	static void SetRootComponent(const FString& Context, AActor* Actor, USceneComponent* Component);

	/**
	* Sets the value of Role without causing other side effects to this instance.
	*
	* @param Context	The calling context.
	* @param Actor
	* @param Role
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,Role"))
	static void SetRole(const FString& Context, AActor* Actor, const ENetRole& Role);
};