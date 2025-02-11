// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Impl/CsBeamWeapon_Impl_Beam.h"
#include "CsWp.h"

// CVar
#include "Beam/CsCVars_BeamWeapon.h"
// Types
#include "Types/CsTypes_Math_Library.h"
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
	// Data
#include "Beam/Data/CsLibrary_Data_BeamWeapon.h"
#include "Data/CsLibrary_Data_Beam.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Beam/Params/CsLibrary_Params_BeamWeapon_Beam.h"
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
#include "Managers/Beam/CsManager_Beam.h"
// Data
#include "Beam/Data/CsData_BeamWeapon.h"
// Weapon
#include "CsWeapon.h"
#include "Beam/CsBeamWeapon.h"
#include "Beam/Impl/CsBeamWeapon_Impl_FX.h"
#include "Beam/Impl/CsBeamWeapon_Impl_Sound.h"
// Beam
#include "Payload/CsPayload_BeamImpl.h"
#include "Types/CsGetBeamType.h"
// Update
#include "Managers/Time/CsGetUpdateGroup.h"
// Component
#include "Components/SkeletalMeshComponent.h"

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NImpl
		{
			namespace NBeam
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, SetOuter);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, SetBeamData);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, GetLocation);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, GetDirection);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, GetEnd);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, OnHit);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, LineBeam);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NBeam::FImpl, Beam);
					}
				}

				FImpl::FImpl() :
					Outer(nullptr),
					GetUpdateGroup(nullptr),
					WeaponInterface(nullptr),
					BeamWeaponInterface(nullptr),
					GetBeamType(nullptr),
					RootComponent(nullptr),
					Owner(nullptr),
					Component(nullptr),
					Data(nullptr),
					BeamData(nullptr),
					FXImpl(nullptr),
					SoundImpl(nullptr),
					GetStartImpl(),
					GetDirectionImpl(),
					Beams()
				{
					// ScopedHandles
				#if !UE_BUILD_SHIPPING
					{
						using namespace NCached;

						// BeamScopedHandle
						{
							const FString& ScopeName			= Str::Beam;
							const FECsScopedGroup& ScopedGroup  = NCsScopedGroup::WeaponBeam;
							const FECsCVarLog& ScopeLog			= NCsCVarLog::LogWeaponBeamScopedTimerBeam;

							BeamScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
						}
					}
				#endif // #if !UE_BUILD_SHIPPING
				}

				FImpl::~FImpl()
				{
					if (UCsManager_Beam* Manager_Beam = CsBeamManagerLibrary::GetSafe(Outer))
					{
						for (ICsBeam* Beam : Beams)
						{
							Manager_Beam->Destroy(Beam);
						}
					}
					Beams.Reset();

					CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(BeamScopedHandle)
				}

				void FImpl::SetOuter(UObject* InOuter)
				{
					using namespace NCsWeapon::NBeam::NImpl::NBeam::NCached;

					const FString& Context = Str::SetOuter;

					Outer = InOuter;

					GetUpdateGroup = CS_INTERFACE_CAST_CHECKED(Outer, UObject, ICsGetUpdateGroup);
					WeaponInterface = CS_INTERFACE_CAST_CHECKED(Outer, UObject, ICsWeapon);
					BeamWeaponInterface = CS_INTERFACE_CAST_CHECKED(Outer, UObject, ICsBeamWeapon);
					GetBeamType = CS_INTERFACE_CAST_CHECKED(Outer, UObject, ICsGetBeamType);
				}

				void FImpl::SetRootComponent(USceneComponent* InComponent)
				{
					Component = InComponent;
					SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component);
				}

				#define BeamDataType NCsWeapon::NBeam::NData::IData
				void FImpl::SetBeamData(BeamDataType* Value)
				{
				#undef BeamDataType

					using namespace NCsWeapon::NBeam::NImpl::NBeam::NCached;

					const FString& Context = Str::SetBeamData;

					BeamData = Value;

					typedef NCsWeapon::NBeam::NParams::NBeam::FLibrary BeamParamsLibrary;
					typedef NCsWeapon::NBeam::NParams::NBeam::IBeam BeamParamsType;

					BeamParams = const_cast<BeamParamsType*>(BeamData->GetBeamParams());

					check(BeamParamsLibrary::IsValidChecked(Context, BeamParams));
				}

				#define DataType NCsWeapon::NData::IData

				FVector3f FImpl::GetLocation()
				{
					using namespace NCached;

					const FString& ScopeName		   = Str::GetLocation;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponBeam;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponBeamScopedTimerBeamGetLocation;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetLocation;
	
					using namespace NCsWeapon::NBeam::NParams::NBeam;

					const FLocationInfo& LocationInfo = BeamParams->GetLocationInfo();
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

				FVector3f FImpl::GetDirection(const FVector3f& Start)
				{
					using namespace NCached;

					const FString& ScopeName		   = Str::GetDirection;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponBeam;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponBeamScopedTimerBeamGetDirection;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetDirection;

					using namespace NCsWeapon::NBeam::NParams::NBeam;

					const FDirectionInfo& DirectionInfo = BeamParams->GetDirectionInfo();
					const EDirection& DirectionType		= DirectionInfo.GetType();
					const int32& DirectionRules			= DirectionInfo.GetRules();

					checkf(DirectionRules != NCsRotationRules::None, TEXT("%s: No DirectionRules set in BeamParams for Data."), *Context);

					// Self
					if (DirectionType == EDirection::Self)
					{
						CS_IS_PTR_NULL_CHECKED(RootComponent)

						return NCsRotationRules::GetRotation(CsMathLibrary::Convert(RootComponent->GetComponentRotation()), DirectionRules).Vector();
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
						// perform a Beam from the Owner's Camera Location in the
						// direction the Owner's Camera is looking
						if (Owner)
						{
							const FVector3f CameraStart = CsCameraLibrary::GetLocation3fChecked(Context, Owner);
							const FVector3f Dir		  = CsCameraLibrary::GetDirection3fChecked(Context, Owner, DirectionRules);
							// TODO: Fix
							const FVector3f End		  = CameraStart + 10000.0f * Dir;
							//const FVector3f End		  = CameraStart + BeamParams->GetDistance() * Dir;

							FHitResult Hit;

							LineTrace(CameraStart, End, Hit);

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

				void FImpl::LineTrace(const FVector3f& Start, const FVector3f& End, FHitResult& OutHit)
				{
					//CS_SCOPED_TIMER(LineBeamScopedHandle);

					using namespace NCached;

					const FString& Context = Str::LineBeam;
					/*
					typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
					typedef NCsTrace::NRequest::FRequest RequestType;

					UCsManager_Trace* Manager_Trace = TraceManagerLibrary::GetChecked(Context, Outer);

					RequestType* Request = Manager_Trace->AllocateRequest();
					Request->Start	= Start;
					Request->End	= End;

					// Get collision information related to the trace.
					
					typedef NCsWeapon::NBeam::NData::IData WeaponBeamDataType;

					WeaponBeamDataType* WeaponBeamData = CsWeaponDataLibrary::GetInterfaceChecked<WeaponBeamDataType>(Context, Data);

					typedef NCsWeapon::NBeam::NParams::NBeam::IBeam BeamParamsType;
					typedef NCsWeapon::NBeam::NParams::NBeam::FLibrary BeamParamsLibrary;

					const BeamParamsType* BeamParams = WeaponBeamData->GetBeamParams();

					check(BeamParamsLibrary::IsValidChecked(Context, BeamParams));

					Request->Type   = ECsTraceType::Line;
					Request->Method = ECsTraceMethod::Single;
					Request->Query  = ECsTraceQuery::ObjectType;

					const FCollisionShape& Shape = BeamParams->GetShape();

					// For now assume trace via ObjectType
					const TArray<ECollisionChannel>& ObjectTypes = BeamParams->GetObjectTypes();

					for (const ECollisionChannel& ObjectType : ObjectTypes)
					{
						Request->ObjectParams.AddObjectTypesToQuery(ObjectType);
					}

					typedef NCsBeam::NResponse::FResponse ResponseType;

					ResponseType* Response = Manager_Beam->Beam(Request);

					OutHit = Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;
					*/
				#if !UE_BUILD_SHIPPING
					if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawWeaponBeamLineBeam))
					{
						UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

						//Settings->BeamWeaponImpl.Debug.DrawLineBeam.Draw(Outer->GetWorld(), Start, End, OutHit);
					}
				#endif // #if !UE_BUILD_SHIPPING

					checkf(0, TEXT("NOT IMPLEMENTED"));
				}

				void FImpl::Emit()
				{
					CS_SCOPED_TIMER(BeamScopedHandle);

					using namespace NCached;

					const FString& Context = Str::Beam;

					if (!BeamParams->IsAttached())
					{
						const FVector3f Location  = GetLocation();
						const FVector3f Direction = GetDirection(Location);
					}

					typedef NCsBeam::NPayload::FImpl PayloadType;

					UCsManager_Beam* Manager_Beam = CsBeamManagerLibrary::GetChecked(Context, Outer);

					const FECsBeam& Type = GetBeamType->GetBeamType();
					PayloadType* Payload	 = Manager_Beam->AllocatePayload<PayloadType>(Context, Type);

					// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
					const bool IsAttached = BeamParams->IsAttached();

					if (IsAttached)
					{
						typedef NCsPooledObject::EUpdate UpdateType;

						Payload->UpdateType = NCsPooledObject::EUpdate::Owner;
					}

					Payload->Instigator = Owner;
					Payload->Owner = Outer;
					
					//Payload->Parent = IsAttached ? Component : nullptr;

					Payload->Time = CsTimeManagerLibrary::GetTimeChecked(Context, Outer, GetUpdateGroup->GetUpdateGroup());

					//Payload->PreserveChangesFromDefaultMask;

					// BeamPayloadType (NCsBeam::NPayload::IPayload)
					Payload->Type = Type;
					//Payload->Location;
					//Payload->Direction;
					//Payload->Scale;

					const FCsBeamPooled* BeamPooled = Manager_Beam->Spawn(Type, Payload);

					// If the Beam is attached, change the 
					//if (IsAttached)
					//typedef N
					//BeamPooled->GetCache()
				}

				void FImpl::AfterShot()
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::ELifeCycle LifeCycleType;

					if (BeamParams->GetLifeCycle() == LifeCycleType::AfterShot)
					{
						for (ICsBeam* Beam : Beams)
						{
							Beam->Off();
						}
					}
				}

				void FImpl::AfterBeamsPerShot()
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::ELifeCycle LifeCycleType;

					if (BeamParams->GetLifeCycle() == LifeCycleType::AfterBeamsPerShot)
					{
						for (ICsBeam* Beam : Beams)
						{
							Beam->Off();
						}
					}
				}

				void FImpl::AfterStopFire()
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::ELifeCycle LifeCycleType;

					if (BeamParams->GetLifeCycle() == LifeCycleType::AfterStopFire)
					{
						for (ICsBeam* Beam : Beams)
						{
							Beam->Off();
						}
					}
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