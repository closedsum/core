// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Managers/Pool/CsOnConstructObject.h"
#include "Managers/Time/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"

#include "CsUserWidgetPooledImpl.generated.h"

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsUserWidget::NCache::NImpl::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsUserWidget, NCache, NImpl, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsUserWidget::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NPayload, IPayload)

class UUserWidget;

UCLASS()
class CSUI_API UCsUserWidgetPooledImpl : public UObject,
										 public ICsOnConstructObject,
										 public ICsUpdate,
										 public ICsShutdown,
										 public ICsPooledObject,
										 public ICsUserWidgetPooled
{
	GENERATED_UCLASS_BODY()

using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
using CacheType = NCsPooledObject::NCache::ICache;
using CacheImplType = NCsUserWidget::NCache::NImpl::FImpl;
using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
using PayloadType = NCsUserWidget::NPayload::IPayload;

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

// ICsShutdown
#pragma region
public:

	void Shutdown();

	FORCEINLINE bool HasShutdown() const { return bShutdown; }

#pragma endregion ICsShutdown

// Shutdown
#pragma region
private:

	bool bShutdown;

#pragma endregion Shutdown

// ICsPooledObject
#pragma region
public:

	FORCEINLINE CacheType* GetCache() const { return Cache; }
	
	void Allocate(PooledPayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	CacheType* Cache;

	CacheImplType* CacheImpl;

	void ConstructCache();

	uint32 PreserveChangesToDefaultMask;
	uint32 ChangesToDefaultMask;

// ICsUserWidgetPooled
#pragma region
public:

	FORCEINLINE UUserWidget* GetUserWidget() const { return UserWidget; }

#pragma endregion ICsUserWidgetPooled

public:

	template<typename T>
	FORCEINLINE T* GetUserWidget() const { return Cast<T>(GetUserWidget()); }

protected:

	UPROPERTY()
	UUserWidget* UserWidget;

	void Handle_AddToViewport(PayloadType* Payload);
};