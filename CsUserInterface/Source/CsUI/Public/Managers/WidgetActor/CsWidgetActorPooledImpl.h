// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
// Interfaces
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "CsWidgetActorPooledImpl.generated.h"

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class UCsWidgetComponent;
struct FCsUserWidgetPooled;

UCLASS()
class CSUI_API ACsWidgetActorPooledImpl : public AActor,
										  public ICsUpdate,
										  public ICsPooledObject,
										  public ICsWidgetActor
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
protected:

	virtual void BeginPlay() override;

#pragma endregion AActor Interface

// AActor Interface
#pragma region
public:

	virtual void FellOutOfWorld(const UDamageType& DmgType) override;

	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region
public:

	FORCEINLINE NCsPooledObject::NCache::ICache* GetCache() const
	{
		return Cache;
	}
	
	void Allocate(NCsPooledObject::NPayload::IPayload* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	void Deallocate_Internal();

	NCsPooledObject::NCache::ICache* Cache;

	void ConstructCache();

// ICsWidgetActor
#pragma region
public:

	FORCEINLINE UCsWidgetComponent* GetWidgetComponent() const
	{
		return WidgetComponent;
	}

#pragma endregion ICsWidgetActor

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCsWidgetComponent* WidgetComponent;

	FCsUserWidgetPooled* UserWidgetPooled;
};