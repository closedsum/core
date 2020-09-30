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
			// NCsPooledObject::NPayload::IPayload
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			// IPayload
			Direction(0.0f),
			Location(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImplPooled::Name);

			InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
			InterfaceMap->Add<NCsProjectile::NPayload::IPayload>(static_cast<NCsProjectile::NPayload::IPayload*>(this));
		}

		FImplPooled::~FImplPooled()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}

		// NCsPooledObject::NPayload::IPayload
		#pragma region

		void FImplPooled::Reset()
		{
			// NCsPooledObject::NPayload::IPayload
			bAllocated = false;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();
			// IPayload
			Direction = FVector::ZeroVector;
			Location = FVector::ZeroVector;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}