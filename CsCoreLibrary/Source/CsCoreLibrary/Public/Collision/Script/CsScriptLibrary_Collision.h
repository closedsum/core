// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Collision/CsTypes_Collision.h"

#include "CsScriptLibrary_Collision.generated.h"

class UPrimitiveComponent;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_Collision : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Set any collision information from Preset on Component
	*
	* @param Context	The calling context.
	* @param Component
	* @param Preset
	* return			Whether the collision Preset was successfully set on Component.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Collision", meta = (AutoCreateRefTerm = "Context,Preset"))
	static bool Set_CollisionPreset(const FString& Context, UPrimitiveComponent* Component, const FCsCollisionPreset& Preset);

	/**
	* Set any collision information from Object on Component
	*
	* @param Context	The calling context.
	* @param Object
	* @param Component
	* return			Whether the collision information on Object was successfully set on Component.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Collision", meta = (AutoCreateRefTerm = "Context"))
	static bool SetFromObject_CollisionPreset(const FString& Context, UObject* Object, UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Collision", meta = (AutoCreateRefTerm = "Context"))
	static FCollisionResponseContainer SetCollisionResponse(const FCollisionResponseContainer& Container, const ECollisionChannel& Channel, const ECollisionResponse& NewResponse);
};