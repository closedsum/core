// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Event/CsLibrary_DamageEvent.h"
#include "CsDmg.h"

// Types
#include "CsMacro_Misc.h"
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
	// Damage
#include "Value/CsLibrary_DamageValue.h"
#include "Range/CsLibrary_DamageRange.h"
	// Common
#include "Object/CsLibrary_Object.h"
#include "Debug/CsTypes_Debug.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsSettings_Damage.h"
// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Data/Shape/Sphere/CsData_DamageSphere.h"
#include "Managers/Damage/Data/Shape/Cone/CsData_DamageCone.h"
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
		namespace NLibrary
		{
			using DataType = NCsDamage::NData::IData;
			using ShapeDataType = NCsDamage::NData::NShape::IShape;
			using ValueLibrary = NCsDamage::NValue::NLibrary::FLibrary;
			using ValueType = NCsDamage::NValue::IValue;
			using ValuePointType = NCsDamage::NValue::NPoint::IPoint;
			using ValueRangeType = NCsDamage::NValue::NRange::IRange;
			using RangeType = NCsDamage::NRange::IRange;

			using EventImplType = NCsDamage::NEvent::NImpl::FImpl;
			using CopyType = NCsDamage::NEvent::NCopy::ICopy;

			FString FLibrary::PrintEvent(const EventType* Event)
			{
				return FString::Printf(TEXT("Event: %s"), *(Event->GetInterfaceMap()->GetRootName().ToString()));
			}

			void FLibrary::LogEvent(const FString& Context, const EventType* Event)
			{
				UE_LOG(LogCsDmg, Warning, TEXT("%s:"), *Context);
				UE_LOG(LogCsDmg, Warning, TEXT("- Damage Event"));

				DataType* Data = Event->GetData();

				// Data
				UE_LOG(LogCsDmg, Warning, TEXT("-- %s"), *CsDamageDataLibrary::PrintDataAndClass(Data));

				// Damage
				const ValueType* Value = Event->GetDamageValue();

				// Point
				if (const ValuePointType* Point = ValueLibrary::GetSafeInterfaceChecked<ValuePointType>(Context, Value))
				{
					UE_LOG(LogCsDmg, Warning, TEXT("-- Damage: %f"), Point->GetValue());
				}
				// Range
				if (const ValueRangeType* Range = ValueLibrary::GetSafeInterfaceChecked<ValueRangeType>(Context, Value))
				{
					UE_LOG(LogCsDmg, Warning, TEXT("-- Damage: %f <-> %f"), Range->GetMinValue(), Range->GetMaxValue());
				}

				UE_LOG(LogCsDmg, Warning, TEXT("-- Type: %s"), Data->GetType().ToChar());
				// Instigator
				UE_LOG(LogCsDmg, Warning, TEXT("- Instigator: %s"), Event->GetInstigator() ? *(Event->GetInstigator()->GetName()) : TEXT("None"));
				// Causer
				UE_LOG(LogCsDmg, Warning, TEXT("- Causer: %s"), Event->GetCauser() ? *(Event->GetCauser()->GetName()) : TEXT("None"));
				// Damage Direction
				UE_LOG(LogCsDmg, Warning, TEXT("- DamageDirection: %s"), *(Event->GetDamageDirection().ToString()));
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
				UE_LOG(LogCsDmg, Warning, TEXT("-- Actor: %s"), HitResult.HasValidHitObjectHandle() ? *(HitResult.GetActor()->GetName()) : TEXT("None"));
				UE_LOG(LogCsDmg, Warning, TEXT("-- Component: %s"), HitResult.Component.IsValid() ? *(HitResult.Component->GetName()) : TEXT("None"));
				UE_LOG(LogCsDmg, Warning, TEXT("-- BoneName: %s"), HitResult.BoneName.IsValid() ? *(HitResult.BoneName.ToString()) : TEXT("None"));
				UE_LOG(LogCsDmg, Warning, TEXT("-- FaceIndex: %d"), HitResult.FaceIndex);
			}

			void FLibrary::Draw(const FString& Context, const EventType* Event)
			{
				CS_IS_PTR_NULL_CHECKED(Event)

				DataType* Data = Event->GetData();

				checkf(Data, TEXT("%s: Event->GetData() is NULL."), *Context);

				const FCsSettings_Damage_Debug& Debug = FCsSettings_Damage_Debug::Get();

				// Shape
				if (const ShapeDataType* ShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
				{
					const RangeType* Range = ShapeData->GetRange();

					checkf(Range, TEXT("%s: Failed to get Range from %s."), *Context, *CsDamageDataLibrary::PrintDataAndClass(Data));

					// Cone
					using ConeDataType = NCsDamage::NData::NShape::NCone::ICone;

					if (const ConeDataType* ConeData = CsDamageDataLibrary::GetSafeInterfaceChecked<ConeDataType>(Context, Data))
					{
						FTransform Transform = FTransform::Identity;
						Transform.SetTranslation(Event->GetHitResult().ImpactPoint);
						Transform.SetRotation(Event->GetDamageDirection().ToOrientationQuat());

						Debug.Pie.Draw(Event->GetInstigator(), FMath::RadiansToDegrees(FMath::Acos(ConeData->GetMinDot())), Transform, Range->GetMaxRange());
					}
					// Sphere
					else
					{
						if (Debug.bSphereAsCircle)
							Debug.Circle.Draw(Event->GetInstigator(), CsMathLibrary::Convert(Event->GetHitResult().ImpactPoint), Range->GetMinRange(), Range->GetMaxRange());
						else
							Debug.Sphere.Draw(Event->GetInstigator(), CsMathLibrary::Convert(Event->GetHitResult().ImpactPoint), Range->GetMinRange(), Range->GetMaxRange());
					}
				}
				// Point
				else
				{

				}
			}

			bool FLibrary::CopyChecked(const FString& Context, const EventType* From, EventType* To)
			{
				GetInterfaceChecked<CopyType>(Context, To)->Copy(From);
				return true;
			}

			bool FLibrary::SetDamageChecked(const FString& Context, EventType* Event)
			{
				// EventImplType (NCsDamage::NEvent::NImpl::FImpl (NCsDamage::NEvent::IEvent))
				{
					if (EventImplType* Impl = SafePureStaticCastChecked<EventImplType>(Context, Event))
					{
						return Impl->SetDamageChecked(Context);
					}
				}
				return false;
			}

			void FLibrary::SetDamageDirectionChecked(const FString& Context, EventType* Event, const FVector& Direction)
			{
				CS_IS_PTR_NULL_CHECKED(Event)

				if (EventImplType* Impl = SafePureStaticCastChecked<EventImplType>(Context, Event))
				{
					Impl->DamageDirection = Direction;
				}
				else
				{
					checkf(0, TEXT("%s: %s is NOT Supported for setting Damage Direction."), *Context, *PrintEvent(Event));
				}
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
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Current Damage Event from %s."), *Context, *(CsObjectLibrary::PrintObjectAndClass(Object))));
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

			FVector FLibrary::GetSafeDamageDirection(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
			{
				const EventType* Event = GetSafeCurrentDamageEvent(Context, Object, Log);

				if (!Event)
					return FVector::ZeroVector;
				return Event->GetDamageDirection();
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

			float FLibrary::GetOrCalculateDamageChecked(const FString& Context, const EventType* Event, const FVector3f& Point)
			{
				CS_IS_PTR_NULL_CHECKED(Event)

				DataType* Data = Event->GetData();

				checkf(Data, TEXT("%s: Event->GetData() is NULL."), *Context);

				if (ShapeDataType* ShapeData = CsDamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
				{
					return ShapeData->CalculateDamage(Event->GetDamageValue(), Event->GetDamageRange(), CsMathLibrary::Convert(Event->GetHitResult().ImpactPoint), Point);
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

				DataType* Data = Event->GetData();

				checkf(Data, TEXT("%s: Data is NULL. No Damage Data found for Event."), *Context);

				using CollisionDataType = NCsDamage::NData::NCollision::ICollision;
				using CollisionInfoType = NCsDamage::NCollision::FInfo;
				using CollisionMethodType = NCsDamage::NCollision::EMethod;

				ShapeDataType* ShapeData			   = CsDamageDataLibrary::GetInterfaceChecked<ShapeDataType>(Context, Data);
				CollisionDataType* CollisionData	   = CsDamageDataLibrary::GetInterfaceChecked<CollisionDataType>(Context, Data);
				const CollisionInfoType& CollisionInfo = CollisionData->GetCollisionInfo();

				checkf(CollisionInfo.GetMethod() == CollisionMethodType::PhysicsSweep, TEXT("%s: GetMethod() is NOT CollisionMethodType::PhysicsSweep."), *Context);

				const RangeType* Range = Event->GetDamageRange();

				checkf(Range, TEXT("%s: Range is NULL. No DamageRange set for Event."), *Context);
				check(CsDamageRangeLibrary::IsValidChecked(Context, Range));

				const FHitResult& Hit = Event->GetHitResult();

				// NOTE: FUTURE: May need flag to exclude Instigator, Causer, ... etc
				//				 For now, exclude Instigator and Causer

				// Max Range
				static TArray<FHitResult> MaxRangeHits;

				const float& MaxRange = Range->GetMaxRange();
				{
					CsTraceRequestType* Request = CsTraceManagerLibrary::AllocateRequestChecked(Context, WorldContext);

					Request->Caller = Event->GetInstigator();
					Request->Type   = ECsTraceType::Sweep;
					Request->Method = ECsTraceMethod::Multi;
					Request->Query  = ECsTraceQuery::ObjectType;

					Request->Start = Hit.ImpactPoint;
					Request->End   = Hit.ImpactPoint;
					Request->Channel = CollisionInfo.GetChannel();

					Request->Shape.SetSphere(MaxRange);

					if (AActor* Instigator = Cast<AActor>(Event->GetInstigator()))
						Request->Params.AddIgnoredActor(Instigator);

					if (AActor* Causer = Cast<AActor>(Event->GetCauser()))
						Request->Params.AddIgnoredActor(Causer);

					Request->ObjectParams.AddObjectTypesToQuery(CollisionInfo.GetChannel());
			
					if (CsTraceResponseType* Response = CsTraceManagerLibrary::TraceChecked(Context, WorldContext, Request))
					{
						MaxRangeHits.Reset(FMath::Max(MaxRangeHits.Max(), Response->OutHits.Num()));
						MaxRangeHits.Append(Response->OutHits);
					}
					else
					{
						MaxRangeHits.Reset(MaxRangeHits.Max());
					}
				}

				if (MaxRangeHits.IsEmpty())
					return;

				// Min Range
				static TArray<FHitResult> MinRangeHits;

				const float& MinRange = Range->GetMinRange();

				if (MinRange > 0.0f)
				{
					CsTraceRequestType* Request = CsTraceManagerLibrary::AllocateRequestChecked(Context, WorldContext);

					Request->Caller = Event->GetInstigator();
					Request->Type   = ECsTraceType::Sweep;
					Request->Method = ECsTraceMethod::Multi;
					Request->Query  = ECsTraceQuery::ObjectType;

					Request->Start = Hit.ImpactPoint;
					Request->End   = Hit.ImpactPoint;
					Request->Channel = CollisionInfo.GetChannel();

					Request->Shape.SetSphere(MinRange);

					if (AActor* Instigator = Cast<AActor>(Event->GetInstigator()))
						Request->Params.AddIgnoredActor(Instigator);

					if (AActor* Causer = Cast<AActor>(Event->GetCauser()))
						Request->Params.AddIgnoredActor(Causer);

					Request->ObjectParams.AddObjectTypesToQuery(CollisionInfo.GetChannel());
			
					if (CsTraceResponseType* Response = CsTraceManagerLibrary::TraceChecked(Context, WorldContext, Request))
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

				// Keep matching
				for (const FHitResult& HitA : MinRangeHits)
				{
					const int32 Count = MaxRangeHits.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						FHitResult& HitB = MaxRangeHits[I];

						if ((HitA.GetActor() && HitB.GetActor() && HitA.GetActor() != HitB.GetActor()) ||
							(HitA.GetComponent() && HitB.GetComponent() && HitB.GetComponent() != HitB.GetComponent()))
						{
							MaxRangeHits.RemoveAt(I, 1, false);
						}
					}
				}

				// Keep facing
				const FVector& Direction = Event->GetDamageDirection();

				const int32 Count = MaxRangeHits.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					FHitResult& HitA = MaxRangeHits[I];

					if (!ShapeData->IsFacing(CsMathLibrary::Convert(Direction), CsMathLibrary::Convert(Hit.Location), CsMathLibrary::Convert(HitA.ImpactPoint)))
					{
						MaxRangeHits.RemoveAt(I, 1, false);
					}
				}

				OutHits.Reset(FMath::Max(OutHits.Max(), MaxRangeHits.Num()));
				OutHits.Append(MaxRangeHits);
			}
		}
	}
}