// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"

// Types
#include "Types/CsTypes_Macro.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Library
#include "Event/CsLibrary_StatusEffectEvent.h"

const FName NCsStatusEffect::NEvent::NDamage::FImpl::Name = FName("NCsStatusEffect::NEvent::NDamage::FImpl");;

namespace NCsStatusEffect
{
	namespace NEvent
	{
		namespace NDamage
		{
			namespace NImpl
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::NEvent::NDamage::FImpl, Copy);
					}
				}
			}

			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(),
				// EventType (NCsStatusEffect::NEvent::IEvent)
				StatusEffect(),
				Data(nullptr),
				Instigator(nullptr),
				Causer(nullptr),
				Receiver(nullptr),
				IgnoreObjects(),
				// DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)
				DamageEvent()
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FImpl>(this);

				typedef NCsStatusEffect::NEvent::IEvent EventType;
				typedef NCsStatusEffect::NEvent::NDamage::IDamage DamageSeEventType;
				typedef NCsStatusEffect::NEvent::NCopy::ICopy CopyType;
		
				InterfaceMap->Add<EventType>(static_cast<EventType*>(this));
				InterfaceMap->Add<ICsGetStatusEffectEventType>(static_cast<ICsGetStatusEffectEventType*>(this));
				InterfaceMap->Add<DamageSeEventType>(static_cast<DamageSeEventType*>(this));
				InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
				InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));
			}

			FImpl::~FImpl()
			{
				delete InterfaceMap;
			}

			// CopyType (NCsStatusEffect::NEvent::NCopy::ICopy)
			#pragma region

			#define EventType NCsStatusEffect::NEvent::IEvent
			void FImpl::Copy(const EventType* From)
			{
			#undef EventType
				
				using namespace NCsStatusEffect::NEvent::NDamage::NImpl::NCached;

				const FString& Context = Str::Copy;

				typedef NCsStatusEffect::NEvent::FLibrary SeEventLibrary;

				const FImpl* FromImpl = SeEventLibrary::PureStaticCastChecked<FImpl>(Context, From);

				// EventType(NCsStatusEffect::NEvent::IEvent)

				StatusEffect.Copy(FromImpl->StatusEffect);

				Data		= FromImpl->Data;
				Instigator  = FromImpl->Instigator;
				Causer		= FromImpl->Causer;
				Receiver	= FromImpl->Receiver;

				IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), FromImpl->IgnoreObjects.Max()));

				for (TWeakObjectPtr<UObject> O : FromImpl->IgnoreObjects)
				{
					IgnoreObjects.Add(O);
				}

				// DamageSeEventType (NCsStatusEffect::NEvent::NDamage::IDamage)

				DamageEvent.Copy(FromImpl->DamageEvent);
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
				DamageEvent.Reset();
			}

			#pragma endregion ICsReset
		}
	}
}