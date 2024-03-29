// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsStaticMeshActor.generated.h"

UINTERFACE(BlueprintType)
class CSSTATICMESH_API UCsStaticMeshActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

/**
* Interface for a StaticMeshActor.
*/
class CSSTATICMESH_API ICsStaticMeshActor
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
	
	/**
	* Get the StaticMeshComponent for the actor. 
	*
	* return StaticMeshComponent
	*/
	virtual UStaticMeshComponent* GetMeshComponent() const = 0;

	/**
	* Get the Material Instance Dynamic(s) or MIDs associated with the 
	* Static Mesh on GetMeshComponent() (GetMeshComponent()->GetStaticMesh()).
	* 
	* return MIDs
	*/
	virtual const TArray<UMaterialInstanceDynamic*>& GetMIDs() const = 0;
};