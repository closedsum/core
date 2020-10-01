// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEventImpl.h"

const FName NCsStatusEffect::NEvent::FImpl::Name = FName("NCsStatusEffect::NEvent::FImpl");;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		FImpl::FImpl() :
			InterfaceMap(),
			// NCsStatusEffect::NEvent::IEvent
			Data(nullptr),
			Instigator(nullptr),
			Causer(nullptr),
			Receiver(nullptr),
			IgnoreObjects()
		{
			InterfaceMap.SetRootName(FImpl::Name);

			InterfaceMap.Add<IEvent>(static_cast<IEvent*>(this));
			InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
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
			Data = nullptr;
			Instigator = nullptr;
			Causer = nullptr;
			Receiver = nullptr;
			IgnoreObjects.Reset(IgnoreObjects.Max());
		}

		#pragma endregion ICsReset
	}
}