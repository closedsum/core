// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEventImpl.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Library
#include "Event/CsLibrary_StatusEffectEvent.h"

const FName NCsStatusEffect::NEvent::FImpl::Name = FName("NCsStatusEffect::NEvent::FImpl");;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::NEvent::FImpl, Copy);
				}
			}
		}

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

		// CopyType (NCsStatusEffect::NEvent::NCopy::ICopy)
		#pragma region

		#define EventType NCsStatusEffect::NEvent::IEvent
		void FImpl::Copy(const EventType* From)
		{
		#undef EventType

			using namespace NCsStatusEffect::NEvent::NImpl::NCached;

			const FString& Context = Str::Copy;

			typedef NCsStatusEffect::NEvent::FLibrary SeEventLibrary;

			const FImpl* FromImpl = SeEventLibrary::PureStaticCastChecked<FImpl>(Context, From);

			StatusEffect.Copy(FromImpl->StatusEffect);

			Data	   = FromImpl->Data;
			Instigator = FromImpl->Instigator;
			Causer	   = FromImpl->Causer;
			Receiver   = FromImpl->Receiver;

			IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), FromImpl->IgnoreObjects.Max()));

			for (TWeakObjectPtr<UObject> O : FromImpl->IgnoreObjects)
			{
				IgnoreObjects.Add(O);
			}
		}

		#pragma endregion CopyType (NCsStatusEffect::NEvent::NCopy::ICopy)

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