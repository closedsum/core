// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_WeaponImpl.h"

// Types
#include "CsMacro_Interface.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsWeapon::NPayload::NImpl::FImpl);

namespace NCsWeapon
{
	namespace NPayload
	{
		namespace NImpl
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

				CS_INTERFACE_MAP_SET_ROOT(FImpl);

				CS_INTERFACE_MAP_ADD(PooledPayloadType);
				CS_INTERFACE_MAP_ADD(PayloadType);
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
				Transform	= FTransform::Identity;
			}

			#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		}
	}
}