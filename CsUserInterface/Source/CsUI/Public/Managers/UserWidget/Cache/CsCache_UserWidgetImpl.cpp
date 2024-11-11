// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Cache/CsCache_UserWidgetImpl.h"

// Types
#include "CsMacro_Interface.h"
#include "CsMacro_Namespace.h"
#include "CsMacro_Misc.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsUserWidget::NCache::NImpl::FImpl);

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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsUserWidget::NCache::NImpl::FImpl, Allocate);
				}
			}

			using PooledPayloadLibrary = NCsPooledObject::NPayload::FLibrary;
			using PayloadType = NCsUserWidget::NPayload::IPayload;

			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// PooledCacheType (NCsPooledObject::NCache::ICache)
				Index(INDEX_NONE),
				bAllocated(false),
				bQueueDeallocate(false),
				State(PooledStateType::Inactive),
				UpdateType(PooledUpdateType::Manager),
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

				InterfaceMap->Add<PooledCacheType>(static_cast<PooledCacheType*>(this));
				InterfaceMap->Add<CacheType>(static_cast<CacheType*>(this));
			}

			FImpl::~FImpl()
			{
				delete InterfaceMap;
			} 

			// NCsPooledObject::NCache::ICache
			#pragma region

			void FImpl::Allocate(PooledPayloadType* Payload)
			{
				using namespace NCsUserWidget::NCache::NImpl::NCached;

				const FString& Context = Str::Allocate;

				// PooledCacheType (NCsPooledObject::NCache::ICache)
				bAllocated = true;
				State	   = PooledStateType::Active;
				UpdateType = Payload->GetUpdateType();
				Instigator = Payload->GetInstigator();
				Owner	   = Payload->GetOwner();
				Parent	   = Payload->GetParent();
				StartTime  = Payload->GetTime();

				PayloadType* WidgetPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

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
				State = PooledStateType::Inactive;
				UpdateType = PooledUpdateType::Manager;
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
}