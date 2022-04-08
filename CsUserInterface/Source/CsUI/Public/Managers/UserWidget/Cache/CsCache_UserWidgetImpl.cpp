// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Cache/CsCache_UserWidgetImpl.h"

// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"

const FName NCsUserWidget::NCache::FImpl::Name = FName("NCsUserWidget::NCache::FImpl");

namespace NCsUserWidget
{
	namespace NCache
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsUserWidget::NCache::FImpl, Allocate);
				}
			}
		}

		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledCacheType (NCsPooledObject::NCache::ICache)
			Index(INDEX_NONE),
			bAllocated(false),
			bQueueDeallocate(false),
			State(NCsPooledObject::EState::Inactive),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(),
			Owner(),
			Parent(),
			WarmUpTime(0.0f),
			LifeTime(0.0f),
			StartTime(),
			ElapsedTime()
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NCache::ICache PooledCacheType;
			typedef NCsUserWidget::NCache::ICache WidgetCacheType;

			InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
			InterfaceMap->Add<WidgetCacheType>(static_cast<WidgetCacheType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		} 

		// NCsPooledObject::NCache::ICache
		#pragma region

		#define PayloadType NCsPooledObject::NPayload::IPayload
		void FImpl::Allocate(PayloadType* Payload)
		{
		#undef PayloadType

			using namespace NCsUserWidget::NCache::NImpl::NCached;

			const FString& Context = Str::Allocate;

			// PooledCacheType (NCsPooledObject::NCache::ICache)
			bAllocated = true;
			State	   = NCsPooledObject::EState::Active;
			UpdateType = Payload->GetUpdateType();
			Instigator = Payload->GetInstigator();
			Owner	   = Payload->GetOwner();
			Parent	   = Payload->GetParent();
			StartTime  = Payload->GetTime();

			typedef NCsPooledObject::NPayload::FLibrary PayloadLibrary;
			typedef NCsUserWidget::NPayload::IPayload WidgetPayloadType;

			WidgetPayloadType* WidgetPayload = PayloadLibrary::GetInterfaceChecked<WidgetPayloadType>(Context, Payload);

			LifeTime = WidgetPayload->GetLifeTime();
		}

		void FImpl::Deallocate()
		{
			Reset();
		}

		void FImpl::Reset()
		{
			// PooledCacheType (NCsPooledObject::NCache::ICache)
			bAllocated = false;
			bQueueDeallocate = false;
			State = NCsPooledObject::EState::Inactive;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator.Reset();
			Owner.Reset();
			Parent.Reset();
			WarmUpTime = 0.0f;
			LifeTime = 0.0f;
			StartTime.Reset();
			ElapsedTime.Reset();
		}

		#pragma endregion NCsPooledObject::NCache::ICache
	}
}