// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsLibrary_DamageEvent.h"
#include "CsDmg.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/CsReceiveDamage.h"
#include "Managers/Damage/Event/CsGetCurrentDamageEvent.h"
#include "Managers/Damage/Event/Copy/CsDamageEvent_Copy.h"
#include "Managers/Damage/Event/CsDamageEventImpl.h"
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"
#include "Managers/Damage/Value/Range/CsDamageValueRange.h"
// Material
#include "PhysicalMaterials/PhysicalMaterial.h"

namespace NCsDamage
{
	namespace NEvent
	{
	#define EventType NCsDamage::NEvent::IEvent

		void FLibrary::LogEvent(const FString& Context, const EventType* Event)
		{
			UE_LOG(LogCsDmg, Warning, TEXT("%s:"), *Context);
			UE_LOG(LogCsDmg, Warning, TEXT("- Damage Event"));

			typedef NCsDamage::NData::FLibrary DataLibrary;
			typedef NCsDamage::NData::IData DataType;

			DataType* Data = Event->GetData();

			// Data
			UE_LOG(LogCsDmg, Warning, TEXT("-- %s"), *DataLibrary::PrintDataAndClass(Data));

			// Damage
			{
				typedef NCsDamage::NValue::FLibrary ValueLibrary;
				typedef NCsDamage::NValue::IValue ValueType;

				const ValueType* Value = Event->GetDamageValue();

				// Point
				{
					typedef NCsDamage::NValue::NPoint::IPoint PointType;

					if (const PointType* Point = ValueLibrary::GetSafeInterfaceChecked<PointType>(Context, Value))
					{
						UE_LOG(LogCsDmg, Warning, TEXT("-- Damage: %f"), Point->GetValue());
					}
				}
				// Range
				{
					typedef NCsDamage::NValue::NRange::IRange RangeType;

					if (const RangeType* Range = ValueLibrary::GetSafeInterfaceChecked<RangeType>(Context, Value))
					{
						UE_LOG(LogCsDmg, Warning, TEXT("-- Damage: %f <-> %f"), Range->GetMinValue(), Range->GetMaxValue());
					}
				}
			}

			UE_LOG(LogCsDmg, Warning, TEXT("-- Type: %s"), Data->GetType().ToChar());
			// Instigator
			UE_LOG(LogCsDmg, Warning, TEXT("- Instigator: %s"), Event->GetInstigator() ? *(Event->GetInstigator()->GetName()) : TEXT("None"));
			// Causer
			UE_LOG(LogCsDmg, Warning, TEXT("- Causer: %s"), Event->GetCauser() ? *(Event->GetCauser()->GetName()) : TEXT("None"));
			// HitResult
			const FHitResult& HitResult = Event->GetHitResult();

			UE_LOG(LogCsDmg, Warning, TEXT("- HitResult"));
			UE_LOG(LogCsDmg, Warning, TEXT("-- bBlockingHit: %s"), HitResult.bBlockingHit ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCsDmg, Warning, TEXT("-- bStartPenetrating"), HitResult.bStartPenetrating ? TEXT("True") : TEXT("False"));
			UE_LOG(LogCsDmg, Warning, TEXT("-- Time: %f"), HitResult.Time);
			UE_LOG(LogCsDmg, Warning, TEXT("-- Location: %s"), *(HitResult.Location.ToString()));
			UE_LOG(LogCsDmg, Warning, TEXT("-- ImpactPoint: %s"), *(HitResult.ImpactPoint.ToString()));
			UE_LOG(LogCsDmg, Warning, TEXT("-- Normal: %s"), *(HitResult.Normal.ToString()));
			UE_LOG(LogCsDmg, Warning, TEXT("-- ImpactNormal: %s"), *(HitResult.ImpactNormal.ToString()));
			UE_LOG(LogCsDmg, Warning, TEXT("-- TraceStart: %s"), *(HitResult.TraceStart.ToString()));
			UE_LOG(LogCsDmg, Warning, TEXT("-- TraceEnd: %s"), *(HitResult.TraceEnd.ToString()));
			UE_LOG(LogCsDmg, Warning, TEXT("-- PenetrationDepth: %f"), HitResult.PenetrationDepth);
			UE_LOG(LogCsDmg, Warning, TEXT("-- Item: %d"), HitResult.Item);
			UE_LOG(LogCsDmg, Warning, TEXT("-- PhysMaterial: %s"), HitResult.PhysMaterial.IsValid() ? *(HitResult.PhysMaterial->GetName()) : TEXT("None"));
			UE_LOG(LogCsDmg, Warning, TEXT("-- Actor: %s"), HitResult.Actor.IsValid() ? *(HitResult.Actor->GetName()) : TEXT("None"));
			UE_LOG(LogCsDmg, Warning, TEXT("-- Component: %s"), HitResult.Component.IsValid() ? *(HitResult.Component->GetName()) : TEXT("None"));
			UE_LOG(LogCsDmg, Warning, TEXT("-- BoneName: %s"), HitResult.BoneName.IsValid() ? *(HitResult.BoneName.ToString()) : TEXT("None"));
			UE_LOG(LogCsDmg, Warning, TEXT("-- FaceIndex: %d"), HitResult.FaceIndex);
		}

		bool FLibrary::CopyChecked(const FString& Context, const EventType* From, EventType* To)
		{
			typedef NCsDamage::NEvent::NCopy::ICopy CopyType;

			CopyType* Copy = GetInterfaceChecked<CopyType>(Context, To);

			Copy->Copy(From);
			return true;
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

		float FLibrary::GetSafeDamage(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return 0.0f;
			return Event->GetDamage();
		}

		UObject* FLibrary::GetSafeInstigator(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return nullptr;
			return Event->GetInstigator();
		}

		UObject* FLibrary::GetSafeCauser(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return nullptr;
			return Event->GetCauser();
		}

		const FECsHitType& FLibrary::GetSafeHitType(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return EMCsHitType::Get().GetMAX();
			return Event->GetHitType();
		}

		const FHitResult& FLibrary::GetSafeOrigin(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return NCsCollision::NHit::Default;
			return Event->GetOrigin();
		}

		const FHitResult& FLibrary::GetSafeHitResult(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

			if (!Event)
				return NCsCollision::NHit::Default;
			return Event->GetHitResult();
		}

		bool FLibrary::GetSafeIgnoreObjects(const FString& Context, UObject* Object, TArray<UObject*>& OutObjects, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
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