// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_WeaponImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsWeapon::NPayload::FImpl::Name = FName("NCsWeapon::NPayload::FImpl");

namespace NCsWeapon
{
	namespace NPayload
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// PayloadType (NCsWeapon::NPayload::IPayload)
			Type(),
			UpdateGroup(),
			Transform(FTransform::Identity)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsWeapon::NPayload::IPayload PayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<PayloadType>(static_cast<PayloadType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region

		void FImpl::Reset()
		{
			bAllocated = false;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner	   = nullptr;
			Parent	   = nullptr;

			Time.Reset();

			PreserveChangesFromDefaultMask = 0;

			// PayloadType NCsWeapon::NPayload::IPayload
			Type		= EMCsWeapon::Get().GetMAX();
			UpdateGroup = EMCsUpdateGroup::Get().GetMAX();
			Transform	= FTransform3f::Identity;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
	}
}