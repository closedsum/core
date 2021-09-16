// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Impl/CsBeamWeapon_Impl_Beam.h"
#include "CsWp.h"

// CVar
#include "Beam/CsCVars_BeamWeapon.h"
// Types
#include "Types/CsTypes_Math.h"
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Data/CsLibrary_Data_Beam.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Beam/Data/Params/CsLibrary_Params_BeamWeapon_Trace.h"
#include "Library/CsLibrary_SkeletalMesh.h"
#include "Library/CsLibrary_Camera.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"
#include "Managers/Trace/CsManager_Trace.h"
// Data
#include "Beam/Data/CsData_BeamWeapon.h"
// Weapon
#include "Beam/CsBeamWeapon.h"
#include "Beam/Impl/CsBeamWeapon_Impl_FX.h"
#include "Beam/Impl/CsBeamWeapon_Impl_Sound.h"
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
					Interface(nullptr),
					RootComponent(nullptr),
					Owner(nullptr),
					Component(nullptr),
					BeamData(nullptr),
					FXImpl(nullptr),
					SoundImpl(nullptr),
					GetStartImpl(),
					GetDirectionImpl()
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
					CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(BeamScopedHandle);
				}

				void FImpl::SetOuter(UObject* InOuter)
				{
					Outer = InOuter;
					Interface = Cast<ICsBeamWeapon>(Outer);
				}

				void FImpl::SetRootComponent(USceneComponent* InComponent)
				{
					Component = InComponent;
					SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component);
				}
				 
				#define BeamDataType NCsBeam::NData::IData

				void FImpl::SetBeamData(const FString& Context, BeamDataType* Value)
				{
					CS_IS_PTR_NULL_CHECKED(Value)

					BeamData = Value;

					typedef NCsBeam::NData::FLibrary BeamDataLibrary;

					check(BeamDataLibrary::IsValidChecked(Context, BeamData));
				}

				void FImpl::SetBeamData(BeamDataType* Value)
				{
					using namespace NCached;

					const FString& Context = Str::SetBeamData;

					SetBeamData(Context, Value);
				}

				#undef BeamDataType

				bool FImpl::IsValidChecked(const FString& Context)
				{
					CS_IS_PTR_NULL_CHECKED(BeamData)

					typedef NCsBeam::NData::FLibrary BeamDataLibrary;

					check(BeamDataLibrary::IsValidChecked(Context, BeamData));
					return true;
				}

				#define DataType NCsWeapon::NData::IData

				FVector FImpl::GetLocation(DataType* Data)
				{
					using namespace NCached;

					const FString& ScopeName		   = Str::GetLocation;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponBeam;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponBeamScopedTimerBeamGetLocation;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetLocation;

					// Get Data Slice
					typedef NCsWeapon::NBeam::NData::IData WeaponDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);
	
					// Get Beam Params

					using namespace NCsWeapon::NBeam::NParams::NBeam;

					const IBeam* BeamParams = WeaponData->GetBeamParams();

					typedef NCsWeapon::NBeam::NParams::NBeam::FLibrary BeamParamsLibrary;

					check(BeamParamsLibrary::IsValidChecked(Context, BeamParams));

					const FLocationInfo& LocationInfo = BeamParams->GetLocationInfo();
					const ELocation& LocationType	  = LocationInfo.GetType();

					// Self
					if (LocationType == ELocation::Self)
					{
						CS_IS_PTR_NULL_CHECKED(RootComponent)

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
						CS_IS_PTR_NULL_CHECKED(Component)

						return Component->GetComponentLocation();
					}
					// Camera
					if (LocationType == ELocation::Camera)
					{
						// Try to get camera through the owner
						if (Owner)
						{
							typedef NCsCamera::FLibrary CameraLibrary;

							return CameraLibrary::GetLocationChecked(Context, Owner);
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

				FVector FImpl::GetDirection(DataType* Data, const FVector& Start)
				{
					using namespace NCached;

					const FString& ScopeName		   = Str::GetDirection;
					const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponBeam;
					const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponBeamScopedTimerBeamGetDirection;

					CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

					const FString& Context = Str::GetDirection;

					// Get Data Slice
					typedef NCsWeapon::NBeam::NData::IData WeaponDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Data);
	
					// Get Beam Params
					typedef NCsWeapon::NBeam::NParams::NBeam::FLibrary BeamParamsLibrary;
					using namespace NCsWeapon::NBeam::NParams::NBeam;

					const IBeam* BeamParams = WeaponData->GetBeamParams();

					check(BeamParamsLibrary::IsValidChecked(Context, BeamParams));

					const FDirectionInfo& DirectionInfo = BeamParams->GetDirectionInfo();
					const EDirection& DirectionType		= DirectionInfo.GetType();
					const int32& DirectionRules			= DirectionInfo.GetRules();

					checkf(DirectionRules != NCsRotationRules::None, TEXT("%s: No DirectionRules set in BeamParams for Data."), *Context);

					// Self
					if (DirectionType == EDirection::Self)
					{
						CS_IS_PTR_NULL_CHECKED(RootComponent)

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
						CS_IS_PTR_NULL_CHECKED(Component)
		
						const FRotator Rotation = NCsRotationRules::GetRotation(Component, DirectionRules);

						return Rotation.Vector();
					}
					// Camera
					if (DirectionType == EDirection::Camera)
					{
						// Try to get camera through the owner
						if (Owner)
						{
							typedef NCsCamera::FLibrary CameraLibrary;

							return CameraLibrary::GetDirectionChecked(Context, Owner, DirectionRules);
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
							typedef NCsCamera::FLibrary CameraLibrary;

							const FVector CameraStart = CameraLibrary::GetLocationChecked(Context, Owner);
							const FVector Dir		  = CameraLibrary::GetDirectionChecked(Context, Owner, DirectionRules);
							// TODO: Fix
							const FVector End		  = CameraStart + 10000.0f * Dir;
							//const FVector End		  = CameraStart + BeamParams->GetDistance() * Dir;

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

				void FImpl::LineTrace(DataType* Data, const FVector& Start, const FVector& End, FHitResult& OutHit)
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
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					WeaponBeamDataType* WeaponBeamData = WeaponDataLibrary::GetInterfaceChecked<WeaponBeamDataType>(Context, Data);

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

				void FImpl::Emit(DataType* Data)
				{
					CS_SCOPED_TIMER(BeamScopedHandle);

					using namespace NCached;

					const FString& Context = Str::Beam;

					const FVector Location = GetLocation(Data);
					const FVector Direction	= GetDirection(Data, Location);
				}

				#undef DataType

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