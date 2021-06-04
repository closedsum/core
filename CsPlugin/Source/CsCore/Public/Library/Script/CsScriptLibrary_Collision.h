// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Collision.h"

#include "CsScriptLibrary_Collision.generated.h"

class UPrimitiveComponent;

UCLASS()
class CSCORE_API UCsScriptLibrary_Collision : public UObject
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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Collision", meta = (AutoCreateRefTerm = "Context,Preset"))
	static bool Set_CollisionPreset(const FString& Context, UPrimitiveComponent* Component, const FCsCollisionPreset& Preset);

	/**
	* Set any collision information from Object on Component
	*
	* @param Context	The calling context.
	* @param Object
	* @param Component
	* return			Whether the collision information on Object was successfully set on Component.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Collision", meta = (AutoCreateRefTerm = "Context"))
	static bool SetFromObject_CollisionPreset(const FString& Context, UObject* Object, UPrimitiveComponent* Component);
};