// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectileImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Payload/CsLibrary_Payload_Projectile.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectileImplSlice.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPayload_ProjectileImpl)

using PayloadType = NCsProjectile::NPayload::IPayload;

// FCsPayload_Projectile
#pragma region

void FCsPayload_Projectile::CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const
{
	if (CsPrjPayloadLibrary::HasUniqueBasedSlices(Context, Payload))
	{
		typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
		typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadSliceType;

		PooledPayloadSliceType* PooledPayloadSlice = CsPrjPayloadLibrary::StaticCastChecked<PooledPayloadSliceType, PooledPayloadType>(Context, Payload);
		PooledPayloadSlice->Instigator = Instigator;
		PooledPayloadSlice->Owner		= Owner;
		PooledPayloadSlice->Parent		= Parent;
		//PooledPayloadSlice->Time = Time;
		PooledPayloadSlice->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

		using PayloadSliceType = NCsProjectile::NPayload::NImplSlice::FImplSlice;

		PayloadSliceType* PayloadSlice = CsPrjPayloadLibrary::StaticCastChecked<PayloadSliceType, PayloadType>(Context, Payload);

		PayloadSlice->Type		= Type;
		PayloadSlice->Generation = Generation;
		PayloadSlice->Location	= Location;
		PayloadSlice->Direction	= Direction;
	}
	else
	{
		using PayloadImplType = NCsProjectile::NPayload::NImpl::FImpl;

		PayloadImplType* PayloadImpl = CsPrjPayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);
		PayloadImpl->Instigator = Instigator;
		PayloadImpl->Owner		= Owner;
		PayloadImpl->Parent		= Parent;
		//Payload->Time = Time;
		PayloadImpl->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

		PayloadImpl->Type		= Type;
		PayloadImpl->Generation = Generation;
		PayloadImpl->Location	= Location;
		PayloadImpl->Direction	= Direction;
	}
}

bool FCsPayload_Projectile::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsPayload_Projectile::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	return true;
}

#pragma endregion FCsPayload_Projectile

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NPayload::NImpl::FImpl);

namespace NCsProjectile
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
				// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
				Type(),
				Generation(0),
				Direction(0.0f),
				Location(0.0f)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FImpl);

				CS_INTERFACE_MAP_ADD(PooledPayloadType);
				CS_INTERFACE_MAP_ADD(PayloadType);
			}

			FImpl::~FImpl()
			{
				// ICsGetInterfaceMap
				delete InterfaceMap;
			}

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			#pragma region

			void FImpl::Reset()
			{
				// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
				bAllocated	= false;
				UpdateType	= NCsPooledObject::EUpdate::Manager;
				Instigator	= nullptr;
				Owner		= nullptr;
				Parent		= nullptr;

				Time.Reset();
				// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
				Type		= EMCsProjectile::Get().GetMAX();
				Generation	= 0;
				Direction	= FVector::ZeroVector;
				Location	= FVector::ZeroVector;
			}

			#pragma endregion NCsPooledObject::NPayload::IPayload
		}
	}
}