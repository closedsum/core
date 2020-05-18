// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Creep/CsTdCreep.h"
#include "CsTdCreep_UnitTest_A.generated.h"

class UStaticMeshComponent;

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick", "LOD", "Cooking"))
class CSTD_API ACsTdCreep_UnitTest_A : public AActor,
									   public ICsUpdate,
									   public ICsPooledObject,
									   public ICsTdCreep
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region
protected:

	FCsTdCreepPooledCache* Cache;

public:

	ICsPooledObjectCache* GetCache() const;

	void Allocate(ICsPooledObjectPayload* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// ICsTdCreep
#pragma region
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ICsTdCreep")
	FECsTdCreep Type;

	FORCEINLINE const FECsTdCreep& GetType() const 
	{
		return Type;
	}

#pragma endregion ICsTdCreep

// Mesh
#pragma region
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

#pragma endregion Mesh

};