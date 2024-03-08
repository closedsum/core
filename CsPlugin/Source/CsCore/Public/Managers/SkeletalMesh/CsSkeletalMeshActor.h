// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsSkeletalMeshActor.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsSkeletalMeshActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class USkeletalMeshComponent;

/**
* Interface for a SkeletalMeshActor.
*/
class CSCORE_API ICsSkeletalMeshActor
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
	/**
	* 
	*
	* return
	*/
	virtual USkeletalMeshComponent* GetMeshComponent() const = 0;
};