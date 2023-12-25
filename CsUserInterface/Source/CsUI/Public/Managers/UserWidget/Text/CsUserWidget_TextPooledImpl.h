// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Blueprint/UserWidget.h"
// Interfaces
#include "Managers/Pool/CsOnConstructObject.h"
#include "Managers/Time/CsUpdate.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#include "CsUserWidget_TextPooledImpl.generated.h"

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsUserWidget::NCache::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NCache, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsUserWidget::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NPayload, IPayload)

class UTextBlock;

UCLASS()
class CSUI_API UCsUserWidget_TextPooledImpl : public UUserWidget,
											  public ICsOnConstructObject,
											  public ICsUpdate,
											  public ICsShutdown,
											  public ICsPooledObject,
											  public ICsUserWidgetPooled
{
	GENERATED_UCLASS_BODY()

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
#define CacheType NCsPooledObject::NCache::ICache
#define CacheImplType NCsUserWidget::NCache::FImpl
#define PayloadType NCsPooledObject::NPayload::IPayload
#define UserWidgetPayloadType NCsUserWidget::NPayload::IPayload

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
	
	void Allocate(PayloadType* Payload);

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

	FORCEINLINE UUserWidget* GetUserWidget() const { return const_cast<UCsUserWidget_TextPooledImpl*>(this); }

#pragma endregion ICsUserWidgetPooled

protected:

	int32 SetPositionInViewport_ID;

	int32 CurrentZOrder;

	void Handle_AddToViewport(UserWidgetPayloadType* Payload);

	void Handle_RemoveFromViewport();

private:

	FORCEINLINE const UObject* GetWorldContext() const { return this; }

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

#undef ConstructParamsType
#undef CacheType
#undef CacheImplType
#undef PayloadType
#undef UserWidgetPayloadType
};