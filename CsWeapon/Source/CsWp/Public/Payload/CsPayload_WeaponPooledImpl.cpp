// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_WeaponPooledImpl.h"

#include "Containers/CsInterfaceMap.h"

namespace NCsWeapon
{
	namespace NPayload
	{
		FImplPooled::FImplPooled() :
			InterfaceMap(nullptr),
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time()
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
			InterfaceMap->Add<NPayload::IPayload>(static_cast<NPayload::IPayload*>(this));
		}

		FImplPooled::~FImplPooled()
		{
			delete InterfaceMap;
		}

		// NCsPooledObject::NPayload::IPayload
		#pragma region

		void FImplPooled::Reset()
		{
			bAllocated = false;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}