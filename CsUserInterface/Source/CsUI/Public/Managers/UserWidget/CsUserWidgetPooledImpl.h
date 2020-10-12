// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Managers/Pool/CsOnConstructObject.h"
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"

#include "CsUserWidgetPooledImpl.generated.h"

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class UUserWidget;

UCLASS()
class CSUI_API UCsUserWidgetPooledImpl : public UObject,
										 public ICsOnConstructObject,
										 public ICsUpdate,
										 public ICsPooledObject,
										 public ICsUserWidgetPooled
{
	GENERATED_UCLASS_BODY()

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
#define CacheType NCsPooledObject::NCache::ICache
#define PayloadType NCsPooledObject::NPayload::IPayload

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region
public:

	void OnConstructObject(const ConstructParamsType& Params);

#pragma endregion ICsOnConstructObject

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region
public:

	FORCEINLINE CacheType* GetCache() const
	{
		return Cache;
	}
	
	void Allocate(PayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	CacheType* Cache;

	void ConstructCache();

// ICsUserWidgetPooled
#pragma region
public:

	FORCEINLINE UUserWidget* GetUserWidget() const 
	{
		return UserWidget;
	}

#pragma endregion ICsUserWidgetPooled

protected:

	UPROPERTY()
	UUserWidget* UserWidget;

#undef ConstructParamsType
#undef CacheType
#undef PayloadType
};