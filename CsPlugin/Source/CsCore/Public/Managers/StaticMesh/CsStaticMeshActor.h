// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsStaticMeshActor.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsStaticMeshActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMeshComponent;

/**
* Interface for a StaticMeshActor.
*/
class CSCORE_API ICsStaticMeshActor
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
	virtual UStaticMeshComponent* GetMeshComponent() const = 0;
};