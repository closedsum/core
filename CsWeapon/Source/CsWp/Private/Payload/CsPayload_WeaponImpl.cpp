// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_WeaponImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Payload/CsLibrary_Payload_Weapon.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Payload/CsPayload_WeaponImplSlice.h"

using PayloadType = NCsWeapon::NPayload::IPayload;

// FCsPayload_Weapon
#pragma region

void FCsPayload_Weapon::CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const
{
	if (CsWpPayloadLibrary::HasUniqueBasedSlices(Context, Payload))
	{
		typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
		typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadSliceType;

		PooledPayloadSliceType* PooledPayloadSlice = CsWpPayloadLibrary::StaticCastChecked<PooledPayloadSliceType, PooledPayloadType>(Context, Payload);
		PooledPayloadSlice->Instigator = Instigator;
		PooledPayloadSlice->Owner		= Owner;
		PooledPayloadSlice->Parent		= Parent;
		//PooledPayloadSlice->Time = Time;
		PooledPayloadSlice->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

		using PayloadSliceType = NCsWeapon::NPayload::NImplSlice::FImplSlice;

		PayloadSliceType* PayloadSlice = CsWpPayloadLibrary::StaticCastChecked<PayloadSliceType, PayloadType>(Context, Payload);

		PayloadSlice->Type		= Type;
		PayloadSlice->UpdateGroup= UpdateGroup;
		PayloadSlice->Transform	= Transform;
	}
	else
	{
		using PayloadImplType = NCsWeapon::NPayload::NImpl::FImpl;

		PayloadImplType* PayloadImpl = CsWpPayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);
		PayloadImpl->Instigator = Instigator;
		PayloadImpl->Owner		= Owner;
		PayloadImpl->Parent		= Parent;
		//Payload->Time = Time;
		PayloadImpl->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

		PayloadImpl->Type		= Type;
		PayloadImpl->UpdateGroup= UpdateGroup;
		PayloadImpl->Transform	= Transform;
	}
}

bool FCsPayload_Weapon::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsPayload_Weapon::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsPayload_Projectile

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