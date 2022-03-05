// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsLibrary_DamageEvent.h"
#include "CsDmg.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Value/CsLibrary_DamageValue.h"
#include "Range/CsLibrary_DamageRange.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Collision/CsData_DamageCollision.h"
// Damage
#include "Managers/Damage/CsReceiveDamage.h"
#include "Event/CsGetCurrentDamageEvent.h"
#include "Event/Copy/CsDamageEvent_Copy.h"
#include "Event/CsDamageEventImpl.h"
#include "Value/Point/CsDamageValuePoint.h"
#include "Value/Range/CsDamageValueRange.h"
#include "Range/CsDamageRange.h"
// Material
#include "PhysicalMaterials/PhysicalMaterial.h"
// Trace
#include "Managers/Trace/CsTraceRequest.h"
// Component
#include "Components/PrimitiveComponent.h"
// Engine
#include "GameFramework/Actor.h"

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

		float FLibrary::GetOrCalculateDamageChecked(const FString& Context, const EventType* Event, const FVector& Point)
		{
			CS_IS_PTR_NULL_CHECKED(Event)

			typedef NCsDamage::NData::IData DataType;

			DataType* Data = Event->GetData();

			checkf(Data, TEXT("%s: Event->GetData() is NULL."), *Context);

			typedef NCsDamage::NData::FLibrary DamageDataLibrary;
			typedef NCsDamage::NData::NShape::IShape ShapeDataType;

			if (ShapeDataType* ShapeData = DamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
			{
				return ShapeData->CalculateDamage(Event->GetDamageValue(), Event->GetDamageRange(), Event->GetHitResult().ImpactPoint, Point);
			}
			return Event->GetDamage();
		}

		UObject* FLibrary::Implements_ICsReceiveDamage(const FString& Context, const FHitResult& Hit, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			// Actor
			if (AActor* Actor = Hit.GetActor())
			{
				// Check if Actor implements interface: ICsReceiveDamage
				UClass* Class = Actor->GetClass();
			
				if (Class->ImplementsInterface(UCsReceiveDamage::StaticClass()))
				{
					return Actor;
				}
			}
			// Component
			if (UPrimitiveComponent* Component = Hit.GetComponent())
			{
				// Check if Component implements interface: ICsReceiveDamage
				UClass* Class = Component->GetClass();

				if (Class->ImplementsInterface(UCsReceiveDamage::StaticClass()))
				{
					return Component;
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Hit.GetActor() or Hit.GetComponent() do NOT implement the interface: ICsReceiveDamage."), *Context));
			return nullptr;
		}

		void FLibrary::SweepChecked(const FString& Context, const UObject* WorldContext, const EventType* Event, TArray<FHitResult>& OutHits)
		{
			CS_IS_PTR_NULL_CHECKED(Event)

			typedef NCsDamage::NData::IData DataType;

			DataType* Data = Event->GetData();

			checkf(Data, TEXT("%s: Data is NULL. No Damage Data found for Event."), *Context);

			typedef NCsDamage::NData::FLibrary DamageDataLibrary;
			typedef NCsDamage::NData::NShape::IShape ShapeDataType;
			typedef NCsDamage::NData::NCollision::ICollision CollisionDataType;

			ShapeDataType* ShapeData		 = DamageDataLibrary::GetInterfaceChecked<ShapeDataType>(Context, Data);
			CollisionDataType* CollisionData = DamageDataLibrary::GetInterfaceChecked<CollisionDataType>(Context, Data);

			typedef NCsDamage::NCollision::EMethod CollisionMethodType;

			checkf(CollisionData->GetCollisionMethod() == CollisionMethodType::PhysicsSweep, TEXT("%s: GetCollisionMethod() is NOT CollisionMethodType::PhysicsSweep."), *Context);

			typedef NCsDamage::NRange::FLibrary RangeLibrary;
			typedef NCsDamage::NRange::IRange RangeType;

			const RangeType* Range = Event->GetDamageRange();

			checkf(Range, TEXT("%s: Range is NULL. No DamageRange set for Event."), *Context);
			check(RangeLibrary::IsValidChecked(Context, Range));

			// NOTE: FUTURE: May need flag to exclude Instigator, Causer, ... etc
			//				 For now, exclude Instigator and Causer

			typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
			typedef NCsTrace::NRequest::FRequest RequestType;

			// Max Range
			static TArray<FHitResult> MaxRangeHits;

			const float& MaxRange = Range->GetMaxRange();
			{
				RequestType* Request = TraceManagerLibrary::AllocateRequestChecked(Context, WorldContext);

				Request->Caller = Event->GetInstigator();
				Request->Type   = ECsTraceType::Sweep;
				Request->Method = ECsTraceMethod::Multi;
				Request->Query  = ECsTraceQuery::ObjectType;

				const FHitResult& Hit = Event->GetHitResult();

				Request->Start = Hit.ImpactPoint;
				Request->End   = Hit.ImpactPoint;
				Request->Channel = CollisionData->GetCollisionChannel();

				Request->Shape.SetSphere(MaxRange);

				if (AActor* Instigator = Cast<AActor>(Event->GetInstigator()))
					Request->Params.AddIgnoredActor(Instigator);

				if (AActor* Causer = Cast<AActor>(Event->GetCauser()))
					Request->Params.AddIgnoredActor(Causer);

				Request->ObjectParams.AddObjectTypesToQuery(CollisionData->GetCollisionChannel());
			
				typedef NCsTrace::NResponse::FResponse ResponseType;

				if (ResponseType* Response = TraceManagerLibrary::TraceChecked(Context, WorldContext, Request))
				{
					MaxRangeHits.Reset(FMath::Max(MaxRangeHits.Max(), Response->OutHits.Num()));
					MaxRangeHits.Append(Response->OutHits);
				}
				else
				{
					MaxRangeHits.Reset(MaxRangeHits.Max());
				}
			}

			if (MaxRangeHits.Num() == CS_EMPTY)
				return;

			// Min Range
			static TArray<FHitResult> MinRangeHits;

			const float& MinRange = Range->GetMinRange();

			if (MinRange > 0.0f)
			{
				RequestType* Request = TraceManagerLibrary::AllocateRequestChecked(Context, WorldContext);

				Request->Caller = Event->GetInstigator();
				Request->Type   = ECsTraceType::Sweep;
				Request->Method = ECsTraceMethod::Multi;
				Request->Query  = ECsTraceQuery::ObjectType;

				const FHitResult& Hit = Event->GetHitResult();

				Request->Start = Hit.ImpactPoint;
				Request->End   = Hit.ImpactPoint;
				Request->Channel = CollisionData->GetCollisionChannel();

				Request->Shape.SetSphere(MinRange);

				if (AActor* Instigator = Cast<AActor>(Event->GetInstigator()))
					Request->Params.AddIgnoredActor(Instigator);

				if (AActor* Causer = Cast<AActor>(Event->GetCauser()))
					Request->Params.AddIgnoredActor(Causer);

				Request->ObjectParams.AddObjectTypesToQuery(CollisionData->GetCollisionChannel());
			
				typedef NCsTrace::NResponse::FResponse ResponseType;

				if (ResponseType* Response = TraceManagerLibrary::TraceChecked(Context, WorldContext, Request))
				{
					MinRangeHits.Reset(FMath::Max(MinRangeHits.Max(), Response->OutHits.Num()));
					MinRangeHits.Append(Response->OutHits);
				}
				else
				{
					MinRangeHits.Reset(MinRangeHits.Max());
				}
			}
			else
			{
				MinRangeHits.Reset(MinRangeHits.Max());
			}

			for (const FHitResult& HitA : MinRangeHits)
			{
				const int32 Count = MaxRangeHits.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					FHitResult& HitB = MaxRangeHits[I];

					if ((HitA.GetActor() && HitA.GetActor() == HitB.GetActor()) ||
						(HitA.GetComponent() && HitB.GetComponent() == HitB.GetComponent()))
					{
						MaxRangeHits.RemoveAt(I, 1, false);
					}
				}
			}

			OutHits.Reset(FMath::Max(OutHits.Max(), MaxRangeHits.Num()));
			OutHits.Append(MaxRangeHits);
		}

	#undef EventType
	}
}