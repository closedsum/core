// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObjectImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsPooledObject::NPayload::FImpl::Name = FName("NCsPooledObject::NPayload::FImpl");

namespace NCsPooledObject
{
	namespace NPayload
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// IPayload
			bAllocated(false),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0)
		{
			// ICsGetInterfaceMap
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			InterfaceMap->Add<IPayload>(static_cast<IPayload*>(this));
		}

		FImpl::~FImpl()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}

		// IPayload
		#pragma region

		void FImpl::Reset()
		{
			// IPayload
			bAllocated = false;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();
		}

		#pragma endregion IPayload
	}
}