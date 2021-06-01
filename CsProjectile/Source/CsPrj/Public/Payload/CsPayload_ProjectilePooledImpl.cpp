// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectilePooledImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::FImplPooled::Name = FName("NCsProjectile::NPayload::FImplPooled");;

namespace NCsProjectile
{
	namespace NPayload
	{
		FImplPooled::FImplPooled() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
			Direction(0.0f),
			Location(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImplPooled::Name);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsProjectile::NPayload::IPayload ProjectilePayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<ProjectilePayloadType>(static_cast<ProjectilePayloadType*>(this));
		}

		FImplPooled::~FImplPooled()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region

		void FImplPooled::Reset()
		{
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated = false;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();
			// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
			Direction = FVector::ZeroVector;
			Location = FVector::ZeroVector;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}