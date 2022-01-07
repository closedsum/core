// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEventImpl.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsStatusEffect::NEvent::FImpl::Name = FName("NCsStatusEffect::NEvent::FImpl");;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// EventType (NCsStatusEffect::NEvent::IEvent)
			StatusEffect(),
			Data(nullptr),
			Instigator(nullptr),
			Causer(nullptr),
			Receiver(nullptr),
			IgnoreObjects()
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsStatusEffect::NEvent::IEvent EventType;

			InterfaceMap->Add<EventType>(static_cast<EventType*>(this));
			InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));
		}

		FImpl::~FImpl()
		{
			// ICsGetInterfaceMap
			delete InterfaceMap;
		}

		void FImpl::CopyFrom(const FImpl* From)
		{
			Data = From->Data;
			Instigator = From->Instigator;
			Causer = From->Causer;
			Receiver = From->Receiver;

			IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), From->IgnoreObjects.Max()));

			for (TWeakObjectPtr<UObject> O : From->IgnoreObjects)
			{
				IgnoreObjects.Add(O);
			}
		}

		// ICsReset
		#pragma region

		void FImpl::Reset()
		{
			StatusEffect.Reset();
			Data = nullptr;
			Instigator = nullptr;
			Causer = nullptr;
			Receiver = nullptr;
			IgnoreObjects.Reset(IgnoreObjects.Max());
		}

		#pragma endregion ICsReset
	}
}