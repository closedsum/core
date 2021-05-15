// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Impl/CsTraceWeapon_Impl_Trace.h"
#include "CsWp.h"

// CVar
#include "Trace/CsCVars_TraceWeapon.h"
// Types
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Collision.h"
// Library
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Library/CsLibrary_Camera.h"
#include "Trace/Data/Params/CsLibrary_Params_TraceWeapon_Trace.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"
#include "Managers/Trace/CsManager_Trace.h"
// Data
#include "Managers/Trace/Data/CsData_Trace.h"
#include "Trace/Data/CsData_TraceWeapon.h"
// Weapon
#include "Trace/CsTraceWeapon.h"
#include "Trace/Impl/CsTraceWeapon_Impl_FX.h"
#include "Trace/Impl/CsTraceWeapon_Impl_Sound.h"
// Component
#include "Components/SkeletalMeshComponent.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NImpl
		{
			namespace NTrace
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NTrace::FImpl, SetTraceData);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NTrace::FImpl, GetStart);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NTrace::FImpl, GetDirection);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NTrace::FImpl, GetEnd);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NTrace::FImpl, OnHit);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NTrace::FImpl, LineTrace);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NTrace::FImpl, Trace);
					}
				}

				FImpl::FImpl() :
					Outer(nullptr),
					Interface(nullptr),
					RootComponent(nullptr),
					Owner(nullptr),
					Component(nullptr),
					TraceData(nullptr),
					FXImpl(nullptr),
					SoundImpl(nullptr),
					GetStartImpl(),
					GetDirectionImpl()
				{
					// ScopedHandles
				#if !UE_BUILD_SHIPPING
					{
						using namespace NCached;

						// TraceScopedHandle
						{
							const FString& ScopeName			= Str::Trace;
							const FECsScopedGroup& ScopedGroup  = NCsScopedGroup::WeaponTrace;
							const FECsCVarLog& ScopeLog			= NCsCVarLog::LogWeaponTraceScopedTimerTrace;

							TraceScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
						}
					}
				#endif // #if !UE_BUILD_SHIPPING
				}

				FImpl::~FImpl()
				{
					CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(TraceScopedHandle);
				}

				void FImpl::SetOuter(UObject* InOuter)
				{
					Outer = InOuter;
					Interface = Cast<ICsTraceWeapon>(Outer);
				}

				void FImpl::SetRootComponent(USceneComponent* InComponent)
				{
					Component = InComponent;
					SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component);
				}
				 
				#define TraceDataType NCsTrace::NData::IData
				void FImpl::SetTraceData(const FString& Context, TraceDataType* Value)
				{
				#undef TraceDataType

					checkf(Value, TEXT("%s: Value is NULL."), *Context);

					TraceData = Value;

					typedef NCsTrace::NData::FLibrary TraceDataLibrary;

					check(TraceDataLibrary::IsValidChecked(Context, TraceData));
				}

				#define TraceDataType NCsTrace::NData::IData
				void FImpl::SetTraceData(TraceDataType* Value)
				{
				#undef TraceDataType

					using namespace NCached;

					const FString& Context = Str::SetTraceData;

					SetTraceData(Context, Value);
				}

				bool FImpl::IsValidChecked(const FString& Context)
				{
					checkf(TraceData, TEXT("%s: TraceData is NULL."), *Context);

					typedef NCsTrace::NData::FLibrary TraceDataLibrary;

					check(TraceDataLibrary::IsValidChecked(Context, TraceData));
					return true;
				}

				#define DataType NCsWeapon::NData::IData
				FVector FImpl::GetStart(DataType* Data)
				{
				#undef DataType

					using namespace NCached;

					const FString& ScopeName		   = Str::GetStart;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTraceGetLocation;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetStart;

					// Get Data Slice
					typedef NCsWeapon::NTrace::NData::IData WeaponDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);
	
					// Get Trace Params

					using namespace NCsWeapon::NTrace::NParams::NTrace;

					const ITrace* TraceParams = WeaponData->GetTraceParams();

					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

					check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

					const FLocationInfo& LocationInfo = TraceParams->GetLocationInfo();
					const ELocation& LocationType	  = LocationInfo.GetType();

					// Self
					if (LocationType == ELocation::Self)
					{
						checkf(RootComponent, TEXT("%s: RootComponent is NULL."), *Context);

						return RootComponent->GetComponentLocation();
					}
					// Owner
					if (LocationType == ELocation::Owner)
					{
						checkf(Owner, TEXT("%s: No Owner found for %s."), *Context, *(PrintOuterNameAndClass()));

						// Actor
						if (AActor* Actor = Cast<AActor>(Owner))
							return Actor->GetActorLocation();
						// Component
						if (USceneComponent* OwnerAsComponent = Cast<USceneComponent>(Owner))
							return OwnerAsComponent->GetComponentLocation();

						checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(PrintOuterNameClassAndOwner()));
					}
					// Bone
					if (LocationType == ELocation::Bone)
					{
						typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

						return SkeletalMeshLibrary::GetBoneLocationChecked(Context, SkeletalMeshComponent, LocationInfo.GetBoneOrSocket());
					}
					// Socket
					if (LocationType == ELocation::Socket)
					{
						typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

						return SkeletalMeshLibrary::GetSocketLocationChecked(Context, SkeletalMeshComponent, LocationInfo.GetBoneOrSocket());
					}
					// Component
					if (LocationType == ELocation::Component)
					{
						checkf(Component, TEXT("%s: Component is NULL."), *Context);

						return Component->GetComponentLocation();
					}
					// Camera
					if (LocationType == ELocation::Camera)
					{
						// Try to get camera through the owner
						if (Owner)
						{
							return FCsLibrary_Camera::GetLocationChecked(Context, Owner);
						}
						checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(PrintOuterNameAndClass()));
					}
					// Custom
					if (LocationType == ELocation::Custom)
					{
						checkf(GetStartImpl.IsBound(), TEXT("%s: NOT IMPLEMENTED. GetStartImpl is NOT Bound."), *Context);

						return GetStartImpl.Execute();
					}
					return FVector::ZeroVector;
				}

				#define DataType NCsWeapon::NData::IData
				FVector FImpl::GetDirection(DataType* Data, const FVector& Start)
				{
				#undef DataType

					using namespace NCached;

					const FString& ScopeName		   = Str::GetDirection;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTraceGetDirection;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetDirection;

					// Get Data Slice
					typedef NCsWeapon::NTrace::NData::IData WeaponDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);
	
					// Get Trace Params
					using namespace NCsWeapon::NTrace::NParams::NTrace;

					const ITrace* TraceParams = WeaponData->GetTraceParams();

					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

					check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

					const FDirectionInfo& DirectionInfo = TraceParams->GetDirectionInfo();
					const EDirection& DirectionType		= DirectionInfo.GetType();
					const int32& DirectionRules			= DirectionInfo.GetRules();

					checkf(DirectionRules != NCsRotationRules::None, TEXT("%s: No DirectionRules set in TraceParams for Data."), *Context);

					// Self
					if (DirectionType == EDirection::Self)
					{
						checkf(RootComponent, TEXT("%s: RootComponent is NULL."), *Context);

						return NCsRotationRules::GetRotation(RootComponent->GetComponentRotation(), DirectionRules).Vector();
					}
					// Owner
					if (DirectionType == EDirection::Owner)
					{
						checkf(Owner, TEXT("%s: No Owner found for %s."), *Context, *(PrintOuterNameAndClass()));
	
						// AActor
						if (AActor* Actor = Cast<AActor>(Owner))
							return NCsRotationRules::GetRotation(Actor, DirectionRules).Vector();
						// USceneComponent
						if (USceneComponent* OwnerAsComponent = Cast<USceneComponent>(Owner))
							return NCsRotationRules::GetRotation(OwnerAsComponent, DirectionRules).Vector();
						checkf(0, TEXT("%s: Failed to get Direction from %s."), *Context, *(PrintOuterNameClassAndOwner()));
					}
					// Bone
					if (DirectionType == EDirection::Bone)
					{
						typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

						return SkeletalMeshLibrary::GetBoneNormalChecked(Context, SkeletalMeshComponent, DirectionInfo.GetBoneOrSocket(), DirectionRules);
					}
					// Socket
					if (DirectionType == EDirection::Socket)
					{
						typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

						return SkeletalMeshLibrary::GetSocketNormalChecked(Context, SkeletalMeshComponent, DirectionInfo.GetBoneOrSocket(), DirectionRules);
					}
					// Component
					if (DirectionType == EDirection::Component)
					{
						checkf(Component, TEXT("%s: Component is NULL."));
		
						const FRotator Rotation = NCsRotationRules::GetRotation(Component, DirectionRules);

						return Rotation.Vector();
					}
					// Camera
					if (DirectionType == EDirection::Camera)
					{
						// Try to get camera through the owner
						if (Owner)
						{
							return FCsLibrary_Camera::GetDirectionChecked(Context, Owner, DirectionRules);
						}
						checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(PrintOuterNameAndClass()));
					}
					// Trace
					if (DirectionType == EDirection::Trace)
					{
						// Try to get camera through the owner and
						// perform a Trace from the Owner's Camera Location in the
						// direction the Owner's Camera is looking
						if (Owner)
						{
							const FVector CameraStart = FCsLibrary_Camera::GetLocationChecked(Context, Owner);
							const FVector Dir		  = FCsLibrary_Camera::GetDirectionChecked(Context, Owner, DirectionRules);
							const FVector End		  = CameraStart + TraceParams->GetDistance() * Dir;

							FHitResult Hit;

							LineTrace(Data, CameraStart, End, Hit);

							if (Hit.bBlockingHit)
							{
								return (Hit.ImpactPoint - Start).GetSafeNormal();
							}
							else
							{
								return (End - Start).GetSafeNormal();
							}
						}
						checkf(0, TEXT("%s: NOT IMPLEMENTED"), *Context);
					}
					return FVector::ZeroVector;
				}

				#define DataType NCsWeapon::NData::IData
				FVector FImpl::GetEnd(DataType* Data, const FVector& Start)
				{
				#undef DataType

					using namespace NCached;

					const FString& Context = Str::GetEnd;

					// Get Data Slice
					typedef NCsWeapon::NTrace::NData::IData WeaponDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);

					// Get Trace Params
					using namespace NCsWeapon::NTrace::NParams::NTrace;

					const ITrace* TraceParams = WeaponData->GetTraceParams();

					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

					check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

					return Start + TraceParams->GetDistance() * GetDirection(Data, Start);
				}

				void FImpl::OnHit(const FHitResult& Hit)
				{
					using namespace NCached;

					const FString& Context = Str::OnHit;

				#if !UE_BUILD_SHIPPING
					if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponTraceTraceCollision))
					{
						UE_LOG(LogCsWp, Warning, TEXT("%s (%s):"), *Context, *(Outer->GetName()));

						// HitResult
						UE_LOG(LogCsWp, Warning, TEXT("- Hit"));
						UE_LOG(LogCsWp, Warning, TEXT("-- bBlockingHit: %s"), Hit.bBlockingHit ? TEXT("True") : TEXT("False"));
						UE_LOG(LogCsWp, Warning, TEXT("-- bStartPenetrating"), Hit.bStartPenetrating ? TEXT("True") : TEXT("False"));
						UE_LOG(LogCsWp, Warning, TEXT("-- Time: %f"), Hit.Time);
						UE_LOG(LogCsWp, Warning, TEXT("-- Location: %s"), *(Hit.Location.ToString()));
						UE_LOG(LogCsWp, Warning, TEXT("-- ImpactPoint: %s"), *(Hit.ImpactPoint.ToString()));
						UE_LOG(LogCsWp, Warning, TEXT("-- Normal: %s"), *(Hit.Normal.ToString()));
						UE_LOG(LogCsWp, Warning, TEXT("-- ImpactNormal: %s"), *(Hit.ImpactNormal.ToString()));
						UE_LOG(LogCsWp, Warning, TEXT("-- TraceStart: %s"), *(Hit.TraceStart.ToString()));
						UE_LOG(LogCsWp, Warning, TEXT("-- TraceEnd: %s"), *(Hit.TraceEnd.ToString()));
						UE_LOG(LogCsWp, Warning, TEXT("-- PenetrationDepth: %f"), Hit.PenetrationDepth);
						UE_LOG(LogCsWp, Warning, TEXT("-- Item: %d"), Hit.Item);
						UE_LOG(LogCsWp, Warning, TEXT("-- PhysMaterial: %s"), Hit.PhysMaterial.IsValid() ? *(Hit.PhysMaterial->GetName()) : TEXT("None"));
						UE_LOG(LogCsWp, Warning, TEXT("-- Actor: %s"), Hit.Actor.IsValid() ? *(Hit.Actor->GetName()) : TEXT("None"));
						UE_LOG(LogCsWp, Warning, TEXT("-- Component: %s"), Hit.Component.IsValid() ? *(Hit.Component->GetName()) : TEXT("None"));
						UE_LOG(LogCsWp, Warning, TEXT("-- BoneName: %s"), Hit.BoneName.IsValid() ? *(Hit.BoneName.ToString()) : TEXT("None"));
						UE_LOG(LogCsWp, Warning, TEXT("-- FaceIndex: %d"), Hit.FaceIndex);
					}
				#endif // #if !UE_BUILD_SHIPPING

					// Get Physics Surface
					UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;
					EPhysicalSurface SurfaceType	= PhysMaterial ? PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

					// ImpactVisualDataType (NCsTrace::NData::NVisual::NImpact::IImpact)
					FXImpl->TryImpact(TraceData, Hit);

					// ImpactSoundDataType (NCsTrace::NData::NSound::NImpact::IImpact)
					SoundImpl->TryImpact(TraceData, Hit);

					// DamageDataType (NCsProjectile::NData::NDamage::IDamage)
					/*
					{
						typedef NCsTrace::NData::NDamage::IDamage DamageDataType;
						typedef NCsTrace::NData::FLibrary TraceDataLibrary;

						if (DamageDataType* DamageData = TraceDataLibrary::GetSafeInterfaceChecked<DamageDataType>(Context, TraceData))
						{
							typedef NCsDamage::NEvent::FResource DamageEventResourceType;

							const DamageEventResourceType* Event = OnHit_CreateDamageEvent(Hit);

							OnBroadcastDamage_Event.Broadcast(Event->Get());
							OnBroadcastDamageContainer_Event.Broadcast(Event);
						}
					}
					*/
				}

				#define DataType NCsWeapon::NData::IData
				void FImpl::LineTrace(DataType* Data, const FVector& Start, const FVector& End, FHitResult& OutHit)
				{
				#undef DataType

					//CS_SCOPED_TIMER(LineTraceScopedHandle);

					using namespace NCached;

					const FString& Context = Str::LineTrace;

					typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
					typedef NCsTrace::NRequest::FRequest RequestType;

					UCsManager_Trace* Manager_Trace = TraceManagerLibrary::GetChecked(Context, Outer);

					RequestType* Request = Manager_Trace->AllocateRequest();
					Request->Start	= Start;
					Request->End	= End;

					// Get collision information related to the trace.
					typedef NCsWeapon::NTrace::NData::IData WeaponTraceDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponTraceDataType* WeaponTraceData = WeaponDataLibrary::GetInterfaceChecked<WeaponTraceDataType>(Context, Data);

					typedef NCsWeapon::NTrace::NParams::NTrace::ITrace TraceParamsType;

					const TraceParamsType* TraceParams = WeaponTraceData->GetTraceParams();

					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

					check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

					Request->Type   = ECsTraceType::Line;
					Request->Method = ECsTraceMethod::Single;
					Request->Query  = ECsTraceQuery::ObjectType;

					const FCollisionShape& Shape = TraceParams->GetShape();

					// For now assume trace via ObjectType
					const TArray<ECollisionChannel>& ObjectTypes = TraceParams->GetObjectTypes();

					for (const ECollisionChannel& ObjectType : ObjectTypes)
					{
						Request->ObjectParams.AddObjectTypesToQuery(ObjectType);
					}

					typedef NCsTrace::NResponse::FResponse ResponseType;

					ResponseType* Response = Manager_Trace->Trace(Request);

					OutHit = Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;

				#if !UE_BUILD_SHIPPING
					if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawWeaponTraceLineTrace))
					{
						UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

						Settings->TraceWeaponImpl.Debug.DrawLineTrace.Draw(Outer->GetWorld(), Start, End, OutHit);
					}
				#endif // #if !UE_BUILD_SHIPPING
				}

				#define DataType NCsWeapon::NData::IData
				void FImpl::Trace(DataType* Data)
				{
				#undef DataType

					CS_SCOPED_TIMER(TraceScopedHandle);

					using namespace NCached;

					const FString& Context = Str::Trace;

					const FVector Start = GetStart(Data);
					const FVector End	= GetEnd(Data, Start);

					typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
					typedef NCsTrace::NRequest::FRequest RequestType;
					
					UCsManager_Trace* Manager_Trace = TraceManagerLibrary::GetChecked(Context, Outer);
	
					RequestType* Request = Manager_Trace->AllocateRequest();
					Request->Start = Start;
					Request->End   = End;

					// Get collision information related to the trace.
					typedef NCsWeapon::NTrace::NData::IData WeaponTraceDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponTraceDataType* WeaponTraceData = WeaponDataLibrary::GetInterfaceChecked<WeaponTraceDataType>(Context, Data);
	
					typedef NCsWeapon::NTrace::NParams::NTrace::ITrace TraceParamsType;

					const TraceParamsType* TraceParams = WeaponTraceData->GetTraceParams();

					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

					check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

					const FCollisionShape& Shape = TraceParams->GetShape();

					// Line
					if (Shape.IsLine())
					{
						Request->Type = ECsTraceType::Line;
					}
					else
					{
						Request->Type = ECsTraceType::Sweep;
					}

					Request->Method = ECsTraceMethod::Single;
					Request->Query  = ECsTraceQuery::ObjectType;

					Request->Shape = Shape;

					// For now assume trace via ObjectType
					const TArray<ECollisionChannel>& ObjectTypes = TraceParams->GetObjectTypes();

					for (const ECollisionChannel& ObjectType : ObjectTypes)
					{
						Request->ObjectParams.AddObjectTypesToQuery(ObjectType);
					}

					typedef NCsTrace::NResponse::FResponse ResponseType;

					ResponseType* Response = Manager_Trace->Trace(Request);
	
				#if !UE_BUILD_SHIPPING
					if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawWeaponTraceTrace))
					{
						UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();
						const FHitResult& Hit		= Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;

						Settings->TraceWeaponImpl.Debug.DrawTrace.Draw(Outer->GetWorld(), Start, End, &Shape, Hit);
					}

				#endif // #if !UE_BUILD_SHIPPING

					// TracerVisualDataType (NCsTrace::NData::NVisual::NTracer::ITracer)
					FXImpl->TryTracer(TraceData, Response->bResult ? Response->OutHits[CS_FIRST].ImpactPoint : End);

					if (Response->bResult)
						OnHit(Response->OutHits[CS_FIRST]);
				}

				FString FImpl::PrintOuterNameAndClass()
				{
					return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(Outer->GetName()), *(Outer->GetClass()->GetName()));
				}

				FString FImpl::PrintOuterNameClassAndOwner()
				{
					return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(Outer->GetName()), *(Outer->GetClass()->GetName()), *(Owner->GetName()));
				}
			}
		}
	}
}