// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/CsReceiveDamage.h"
#include "Managers/Damage/Event/CsGetCurrentDamageEvent.h"
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

		const EventType* FLibrary::GetSafeCurrentDamageEvent(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Object)

			CS_DOES_OBJ_IMPLEMENT_RET_NULL(Object, UObject, ICsReceiveDamage)

			ICsGetCurrentDamageEvent* GetCurrentDamageEvent = CS_INTERFACE_CAST(Object, UObject, ICsGetCurrentDamageEvent);

			if (!GetCurrentDamageEvent)
				return nullptr;

			const EventType* Event = GetCurrentDamageEvent->GetCurrentDamageEvent();

			if (!Event)
			{
				typedef NCsObject::FLibrary ObjectLibrary;

				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Current Damage Event from %s."), *Context, *(ObjectLibrary::PrintObjectAndClass(Object))));
			}
			return Event;
		}

		float FLibrary::GetSafeDamage(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return 0.0f;
			return Event->GetDamage();
		}

		UObject* FLibrary::GetSafeInstigator(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return nullptr;
			return Event->GetInstigator();
		}

		UObject* FLibrary::GetSafeCauser(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return nullptr;
			return Event->GetCauser();
		}

		const FECsHitType& FLibrary::GetSafeHitType(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return EMCsHitType::Get().GetMAX();
			return Event->GetHitType();
		}

		const FHitResult& FLibrary::GetSafeOrigin(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return NCsCollision::NHit::Default;
			return Event->GetOrigin();
		}

		const FHitResult& FLibrary::GetSafeHitResult(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return NCsCollision::NHit::Default;
			return Event->GetHitResult();
		}

		bool FLibrary::GetSafeIgnoreObjects(const FString& Context, UObject* Object, TArray<UObject*>& OutObjects, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return false;
			OutObjects = Event->GetIgnoreObjects();
			return true;
		}

	#undef EventType
	}
}