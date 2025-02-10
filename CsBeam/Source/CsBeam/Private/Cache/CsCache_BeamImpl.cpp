// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Cache/CsCache_BeamImpl.h"

// Types
#include "CsMacro_Interface.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Conatiner
#include "Containers/CsInterfaceMap.h"
// Data
#include "Data/CsData_Beam.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsBeam::NCache::NImpl::FImpl);

namespace NCsBeam
{
	namespace NCache
	{
		namespace NImpl
		{
			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// PooledCacheType (NCsPooledObject::NCache::ICache)
				Index(INDEX_NONE),
				bAllocated(false),
				bQueueDeallocate(false),
				State(StateType::Inactive),
				UpdateType(NCsPooledObject::EUpdate::Manager),
				Instigator(),
				Owner(),
				Parent(),
				WarmUpTime(0.0f),
				LifeTime(0.0f),
				StartTime(),
				ElapsedTime(),
				Data(nullptr)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FImpl);

				CS_INTERFACE_MAP_ADD(PooledCacheType);
				CS_INTERFACE_MAP_ADD(CacheType);
			}

			FImpl::~FImpl()
			{
				delete InterfaceMap;
			}

			using DataType = NCsBeam::NData::IData;

			// PooledCacheType (NCsPooledObject::NCache::ICache)s
			#pragma region

			void FImpl::Allocate(PooledPayloadType* Payload)
			{
				bAllocated = true;
				State	   = StateType::Active;
				UpdateType = Payload->GetUpdateType();
				Instigator = Payload->GetInstigator();
				Owner	   = Payload->GetOwner();
				Parent	   = Payload->GetParent();
				StartTime  = Payload->GetTime();
			}

			void FImpl::Deallocate()
			{
				Reset();
			}

			bool FImpl::HasLifeTimeExpired() const
			{
				return LifeTime > 0.0f && ElapsedTime.Time > LifeTime;
			}

			void FImpl::Reset()
			{
				bAllocated = false;
				bQueueDeallocate = false;
				State = StateType::Inactive;
				UpdateType = NCsPooledObject::EUpdate::Manager;
				Instigator.Reset();
				Owner.Reset();
				Parent.Reset();
				WarmUpTime = 0.0f;
				LifeTime = 0.0f;
				StartTime.Reset();
				ElapsedTime.Reset();
			}

			#pragma endregion PooledCacheType (NCsPooledObject::NCache::ICache)

			void FImpl::Update(const FCsDeltaTime& DeltaTime)
			{
				ElapsedTime += DeltaTime;
			}

			void FImpl::SetData(DataType* InData)
			{
				Data	 = InData;
				LifeTime = Data->GetLifeTime();
			}
		}
	}
}