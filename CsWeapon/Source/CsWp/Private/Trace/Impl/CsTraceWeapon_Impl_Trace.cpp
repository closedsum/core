// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Impl/CsTraceWeapon_Impl_Trace.h"
#include "CsWp.h"

// CVar
#include "Trace/CsCVars_TraceWeapon.h"
// Types
#include "Types/CsTypes_Math_Library.h"
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
	// Data
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Trace/Data/Params/CsLibrary_Params_TraceWeapon_Trace.h"
	// Common
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Camera/CsLibrary_Camera.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
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
// Materials
#include "PhysicalMaterials/PhysicalMaterial.h"
// World
#include "Engine/World.h"

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
					CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(TraceScopedHandle)
				}

				using DataType = NCsWeapon::NData::IData;
				using TraceDataType = NCsTrace::NData::IData;

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

				void FImpl::SetTraceData(const FString& Context, TraceDataType* Value)
				{
					CS_IS_PTR_NULL_CHECKED(Value)

					TraceData = Value;

					check(CsTraceDataLibrary::IsValidChecked(Context, TraceData));
				}

				void FImpl::SetTraceData(TraceDataType* Value)
				{
					using namespace NCached;

					const FString& Context = Str::SetTraceData;

					SetTraceData(Context, Value);
				}

				bool FImpl::IsValidChecked(const FString& Context)
				{
					CS_IS_PTR_NULL_CHECKED(TraceData)
					check(CsTraceDataLibrary::IsValidChecked(Context, TraceData));
					return true;
				}

				FVector3f FImpl::GetStart(DataType* Data)
				{
					using namespace NCached;

					const FString& ScopeName		   = Str::GetStart;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTraceGetLocation;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetStart;

					// Get Data Slice
					typedef NCsWeapon::NTrace::NData::IData WeaponDataType;

					WeaponDataType* WeaponData = CsWeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);
	
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
						CS_IS_PTR_NULL_CHECKED(RootComponent)

						return CsMathLibrary::Convert(RootComponent->GetComponentLocation());
					}
					// Owner
					if (LocationType == ELocation::Owner)
					{
						checkf(Owner, TEXT("%s: No Owner found for %s."), *Context, *(PrintOuterNameAndClass()));

						// Actor
						if (AActor* Actor = Cast<AActor>(Owner))
							return CsMathLibrary::Convert(Actor->GetActorLocation());
						// Component
						if (USceneComponent* OwnerAsComponent = Cast<USceneComponent>(Owner))
							return CsMathLibrary::Convert(OwnerAsComponent->GetComponentLocation());

						checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(PrintOuterNameClassAndOwner()));
					}
					// Bone
					if (LocationType == ELocation::Bone)
					{
						return CsSkeletalMeshLibrary::GetBoneLocation3fChecked(Context, SkeletalMeshComponent, LocationInfo.GetBoneOrSocket());
					}
					// Socket
					if (LocationType == ELocation::Socket)
					{
						return CsSkeletalMeshLibrary::GetSocketLocation3fChecked(Context, SkeletalMeshComponent, LocationInfo.GetBoneOrSocket());
					}
					// Component
					if (LocationType == ELocation::Component)
					{
						CS_IS_PTR_NULL_CHECKED(Component)

						return CsMathLibrary::Convert(Component->GetComponentLocation());
					}
					// Camera
					if (LocationType == ELocation::Camera)
					{
						// Try to get camera through the owner
						if (Owner)
						{
							return CsCameraLibrary::GetLocation3fChecked(Context, Owner);
						}
						checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(PrintOuterNameAndClass()));
					}
					// Custom
					if (LocationType == ELocation::Custom)
					{
						checkf(GetStartImpl.IsBound(), TEXT("%s: NOT IMPLEMENTED. GetStartImpl is NOT Bound."), *Context);

						return GetStartImpl.Execute();
					}
					return FVector3f::ZeroVector;
				}

				FVector3f FImpl::GetDirection(DataType* Data, const FVector3f& Start)
				{
					using namespace NCached;

					const FString& ScopeName		   = Str::GetDirection;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTraceGetDirection;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetDirection;

					// Get Data Slice
					typedef NCsWeapon::NTrace::NData::IData WeaponDataType;

					WeaponDataType* WeaponData = CsWeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);
	
					// Get Trace Params
					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;
					using namespace NCsWeapon::NTrace::NParams::NTrace;

					const ITrace* TraceParams = WeaponData->GetTraceParams();

					check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

					const FDirectionInfo& DirectionInfo = TraceParams->GetDirectionInfo();
					const EDirection& DirectionType		= DirectionInfo.GetType();
					const int32& DirectionRules			= DirectionInfo.GetRules();

					checkf(DirectionRules != NCsRotationRules::None, TEXT("%s: No DirectionRules set in TraceParams for Data."), *Context);

					// Self
					if (DirectionType == EDirection::Self)
					{
						CS_IS_PTR_NULL_CHECKED(RootComponent)

						return NCsRotationRules::GetRotation3f(RootComponent->GetComponentRotation(), DirectionRules).Vector();
					}
					// Owner
					if (DirectionType == EDirection::Owner)
					{
						checkf(Owner, TEXT("%s: No Owner found for %s."), *Context, *(PrintOuterNameAndClass()));
	
						// AActor
						if (AActor* Actor = Cast<AActor>(Owner))
							return NCsRotationRules::GetRotation3f(Actor, DirectionRules).Vector();
						// USceneComponent
						if (USceneComponent* OwnerAsComponent = Cast<USceneComponent>(Owner))
							return NCsRotationRules::GetRotation3f(OwnerAsComponent, DirectionRules).Vector();
						checkf(0, TEXT("%s: Failed to get Direction from %s."), *Context, *(PrintOuterNameClassAndOwner()));
					}
					// Bone
					if (DirectionType == EDirection::Bone)
					{
						return CsSkeletalMeshLibrary::GetBoneNormal3fChecked(Context, SkeletalMeshComponent, DirectionInfo.GetBoneOrSocket(), DirectionRules);
					}
					// Socket
					if (DirectionType == EDirection::Socket)
					{
						return CsSkeletalMeshLibrary::GetSocketNormal3fChecked(Context, SkeletalMeshComponent, DirectionInfo.GetBoneOrSocket(), DirectionRules);
					}
					// Component
					if (DirectionType == EDirection::Component)
					{
						CS_IS_PTR_NULL_CHECKED(Component)
		
						const FRotator3f Rotation = NCsRotationRules::GetRotation3f(Component, DirectionRules);

						return Rotation.Vector();
					}
					// Camera
					if (DirectionType == EDirection::Camera)
					{
						// Try to get camera through the owner
						if (Owner)
						{
							return CsCameraLibrary::GetDirection3fChecked(Context, Owner, DirectionRules);
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
							const FVector3f CameraStart = CsCameraLibrary::GetLocation3fChecked(Context, Owner);
							const FVector3f Dir		  = CsCameraLibrary::GetDirection3fChecked(Context, Owner, DirectionRules);
							const FVector3f End		  = CameraStart + TraceParams->GetDistance() * Dir;

							FHitResult Hit;

							LineTrace(Data, CameraStart, End, Hit);

							if (Hit.bBlockingHit)
							{
								return (CsMathLibrary::Convert(Hit.ImpactPoint) - Start).GetSafeNormal();
							}
							else
							{
								return (End - Start).GetSafeNormal();
							}
						}
						checkf(0, TEXT("%s: NOT IMPLEMENTED"), *Context);
					}
					return FVector3f::ZeroVector;
				}

				FVector3f FImpl::GetEnd(DataType* Data, const FVector3f& Start)
				{
					using namespace NCached;

					const FString& Context = Str::GetEnd;

					// Get Data Slice
					typedef NCsWeapon::NTrace::NData::IData WeaponDataType;

					WeaponDataType* WeaponData = CsWeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);

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
					if (CS_CVAR_LOG_IS_SHOWING(LogWeaponTraceTraceCollision))
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
						UE_LOG(LogCsWp, Warning, TEXT("-- Actor: %s"), Hit.HasValidHitObjectHandle() ? *(Hit.GetActor()->GetName()) : TEXT("None"));
						UE_LOG(LogCsWp, Warning, TEXT("-- Component: %s"), Hit.Component.IsValid() ? *(Hit.Component->GetName()) : TEXT("None"));
						UE_LOG(LogCsWp, Warning, TEXT("-- BoneName: %s"), Hit.BoneName.IsValid() ? *(Hit.BoneName.ToString()) : TEXT("None"));
						UE_LOG(LogCsWp, Warning, TEXT("-- FaceIndex: %d"), Hit.FaceIndex);
					}
				#endif // #if !UE_BUILD_SHIPPING
					
					// Get Physics Surface
					UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;
					EPhysicalSurface SurfaceType	= PhysMaterial ? (EPhysicalSurface)PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

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

				void FImpl::LineTrace(DataType* Data, const FVector3f& Start, const FVector3f& End, FHitResult& OutHit)
				{
					//CS_SCOPED_TIMER(LineTraceScopedHandle);

					using namespace NCached;

					const FString& Context = Str::LineTrace;

					UCsManager_Trace* Manager_Trace = CsTraceManagerLibrary::GetChecked(Context, Outer);

					CsTraceRequestType* Request = Manager_Trace->AllocateRequest();
					Request->Start	= CsMathLibrary::Convert(Start);
					Request->End	= CsMathLibrary::Convert(End);

					// Get collision information related to the trace.
					typedef NCsWeapon::NTrace::NData::IData WeaponTraceDataType;

					WeaponTraceDataType* WeaponTraceData = CsWeaponDataLibrary::GetInterfaceChecked<WeaponTraceDataType>(Context, Data);

					typedef NCsWeapon::NTrace::NParams::NTrace::ITrace TraceParamsType;
					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

					const TraceParamsType* TraceParams = WeaponTraceData->GetTraceParams();

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

					CsTraceResponseType* Response = Manager_Trace->Trace(Request);

					OutHit = Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;

				#if !UE_BUILD_SHIPPING
					if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawWeaponTraceLineTrace))
					{
						UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

						Settings->TraceWeaponImpl.Debug.DrawLineTrace.Draw(Outer->GetWorld(), Start, End, OutHit);
					}
				#endif // #if !UE_BUILD_SHIPPING
				}

				void FImpl::Trace(DataType* Data)
				{
					CS_SCOPED_TIMER(TraceScopedHandle);

					using namespace NCached;

					const FString& Context = Str::Trace;

					const FVector3f Start = GetStart(Data);
					const FVector3f End	  = GetEnd(Data, Start);
					
					UCsManager_Trace* Manager_Trace = CsTraceManagerLibrary::GetChecked(Context, Outer);
	
					CsTraceRequestType* Request = Manager_Trace->AllocateRequest();
					Request->Start = CsMathLibrary::Convert(Start);
					Request->End   = CsMathLibrary::Convert(End);

					// Get collision information related to the trace.
					typedef NCsWeapon::NTrace::NData::IData WeaponTraceDataType;
					typedef NCsWeapon::NTrace::NParams::NTrace::ITrace TraceParamsType;
					typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

					WeaponTraceDataType* WeaponTraceData = CsWeaponDataLibrary::GetInterfaceChecked<WeaponTraceDataType>(Context, Data);
					const TraceParamsType* TraceParams   = WeaponTraceData->GetTraceParams();

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

					CsTraceResponseType* Response = Manager_Trace->Trace(Request);
	
				#if !UE_BUILD_SHIPPING
					if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawWeaponTraceTrace))
					{
						UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();
						const FHitResult& Hit		= Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;

						Settings->TraceWeaponImpl.Debug.DrawTrace.Draw(Outer->GetWorld(), Start, End, &Shape, Hit);
					}

				#endif // #if !UE_BUILD_SHIPPING

					// TracerVisualDataType (NCsTrace::NData::NVisual::NTracer::ITracer)
					FXImpl->TryTracer(TraceData, Response->bResult ? CsMathLibrary::Convert(Response->OutHits[CS_FIRST].ImpactPoint) : End);

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