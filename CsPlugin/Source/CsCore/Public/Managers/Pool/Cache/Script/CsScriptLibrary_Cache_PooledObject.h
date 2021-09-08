// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Cache_PooledObject.generated.h"

class UObject;

UCLASS()
class CSCORE_API UCsScriptLibrary_Cache_PooledObject : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Get the Index of the Object, which implements the interface:
	* ICsPooledObject, in the pool it resides in.
	*
	* @param Context	The calling context.
	* @param Object		Implements the interface: ICsPooledObject.
	* return			Index
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Pool|Cache", meta = (AutoCreateRefTerm = "Context"))
	static int32 GetIndex(const FString& Context, UObject* Object);

	/**
	* Check whether the Object, which implements the interface:
	* ICsPooledObject, is allocated from the pool it resides in.
	*
	* @param Context	The calling context.
	* @param Object		Implements the interface: ICsPooledObject.
	* 
	* return			Whether the Object is allocated or not.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Pool|Cache", meta = (AutoCreateRefTerm = "Context"))
	static bool IsAllocated(const FString& Context, UObject* Object);

	/**
	* Queue the Object, which implements the interface: ICsPooledObject,
	* for deallocation. This is the preferably way to deallocate a 
	* pooled object. Usually the Object will be deallocated the next frame.
	* 
	* @param Context	The calling context.
	* @param Object		Implements the interface: ICsPooledObject.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Pool|Cache", meta = (AutoCreateRefTerm = "Context"))
	static void QueueDeallocate(const FString& Context, UObject* Object);
};