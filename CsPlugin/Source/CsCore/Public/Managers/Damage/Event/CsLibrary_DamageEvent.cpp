// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"

namespace NCsDamage
{
	namespace NEvent
	{
	#define EventType NCsDamage::NEvent::IEvent

		bool FLibrary::CopyChecked(const FString& Context, const EventType* From, EventType* To)
		{
			// NCsDamage::NEvent::FImpl (NCsDamage::NEvent::IEvent)
			{
				typedef NCsDamage::NEvent::FImpl ImplType;

				if (ImplType* ToImpl = SafePureStaticCastChecked<ImplType>(Context, To))
				{
					const ImplType* FromImpl = PureStaticCastChecked<ImplType>(Context, From);

					ToImpl->CopyFrom(FromImpl);
					return true;
				}
			}
			return false;
		}

		bool FLibrary::SetDamageChecked(const FString& Context, EventType* Event)
		{
			// NCsDamage::NEvent::FImpl (NCsDamage::NEvent::IEvent)
			{
				typedef NCsDamage::NEvent::FImpl ImplType;

				if (ImplType* Impl = SafePureStaticCastChecked<ImplType>(Context, Event))
				{
					return Impl->SetDamageChecked(Context);
				}
			}
			return false;
		}

	#undef EventType

	#define EventResourceType NCsDamage::NEvent::FResource
	#define DamageDataType NCsDamage::NData::IData

		const EventResourceType* FLibrary::CreateContainerChecked(const FString& Context, const FHitResult& HitResult, const DamageDataType* Data)
		{
			return nullptr;
		}

	#undef EventResourceType
	#undef DamageDataType
	}
}