// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsDmgLog.h"

class ICsGetCurrentDamageEvent;

namespace NCsDamage
{
	namespace NEvent
	{
	#define EventType NCsDamage::NEvent::IEvent

		/**
		* Library for interface: (EventType) NCsDamage::NEvent::IEvent
		*/
		struct CSDMG_API FLibrary final : public NCsInterfaceMap::TLibrary<EventType>
		{
		public:

			static void LogEvent(const FString& Context, const EventType* Event);

			/**
			* Copy the values from From to To with checks.
			* Currently supports To types of:
			*  NCsDamage::NEvent::FImpl (NCsDamage::NEvent::IEvent)
			*
			* @param Context	The calling context.
			* @param From		What to copy.
			* @param To			What to copy to.
			* return			Whether the copy was performed successfully.
			*/
			static bool CopyChecked(const FString& Context, const EventType* From, EventType* To);

			/**
			* Set the damage on the Event with checks.
			*
			* @param Context	The calling context.
			* @param Event
			* return			Whether the damage was set successfully.
			*/
			static bool SetDamageChecked(const FString& Context, EventType* Event);

			/**
			* Safely try to get the Current Damage Event (EventType: NCsDamage::NEvent::IEvent) from Object.
			* Assumes Object implements the interfaces:
			* - ICsReceiveDamage
			* - ICsGetCurrentDamageEvent
			* This should be called immediately after the following events:
			* - Damage_ScriptEvent gets broadcasted during Character->Damage and after current damage event is set.
			* - RecieveDamage (bRecieveDamage must be true) is called.
			* - OverrideDamage (bOverrideDamage must be true) is called.
			* 
			* @param Context	The calling context.
			* @param Object
			* @param Log		(optional)
			* return
			*/
			static const EventType* GetSafeCurrentDamageEvent(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			static float GetSafeDamage(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			static UObject* GetSafeInstigator(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			static UObject* GetSafeCauser(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			static const FECsHitType& GetSafeHitType(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			static const FHitResult& GetSafeOrigin(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			static const FHitResult& GetSafeHitResult(const FString& Context, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			static bool GetSafeIgnoreObjects(const FString& Context, UObject* Object, TArray<UObject*>& OutObjects, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);
		};

	#undef EventType
	}
}