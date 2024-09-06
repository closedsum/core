// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Impl/CsTraceWeapon_Impl_FX.h"

// Library
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
	// Data
#include "Data/CsLibrary_Data_Weapon.h"
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"
	// Payload
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
	// Common
#include "Collision/CsTypes_Collision.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Trace/Data/Visual/CsData_TraceWeapon_VisualFire.h"
#include "Managers/Trace/Data/CsData_Trace.h"
#include "Trace/Data/Visual/CsData_Trace_VisualTracer.h"
#include "Trace/Data/Visual/CsData_Trace_VisualImpact.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Trace/CsTraceWeapon.h"
#include "Trace/Data/Visual/CsParams_TraceWeapon_VisualFire.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
#include "Managers/FX/Params/CsParams_FX.h"
// Components
#include "Components/SceneComponent.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NImpl
		{
			namespace NFX
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NFX::FImpl, TryFire);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NFX::FImpl, TryTracer);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NFX::FImpl, TryImpact);
					}
				}

				void FImpl::SetOuter(UObject* InOuter)
				{
					Outer = InOuter;
					Interface = Cast<ICsTraceWeapon>(Outer);
				}

				#define DataType NCsWeapon::NData::IData
				void FImpl::TryFire(DataType* Data)
				{
				#undef DataType

					using namespace NCached;

					const FString& Context = Str::TryFire;

					// FXDataType (NCsWeapon::NTrace::NData::NVisual::NFire::IFire)
					typedef NCsWeapon::NTrace::NData::NVisual::NFire::IFire FXDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					if (FXDataType* FXData = WeaponDataLibrary::GetSafeInterfaceChecked<FXDataType>(Context, Data))
					{
						typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams ParamsType;
						typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::EAttach AttachType;

						const ParamsType* Params = FXData->GetFireFXParams();
						const AttachType& Type   = Params->GetAttachType();

						typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

						PooledPayloadType PooledPayload;

						// None
						if (Type == AttachType::None)
						{
							PooledPayload.Parent = nullptr;
						}
						// Owner
						else
						if (Type == AttachType::Owner)
						{
							PooledPayload.Parent = Owner;
						}
						// Component
						else
						if (Type == AttachType::Component)
						{
							CS_IS_PTR_NULL_CHECKED(Component)

							PooledPayload.Parent = Component;
						}
						// Custom
						else
						{
							checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."), *Context);
						}

						// FX
						const FCsFX& FX = Params->GetFX();

						// Spawn
						CsFXManagerLibrary::SpawnChecked(Context, Outer, &PooledPayload, FX);
					}
				}

				#define TraceDataType NCsTrace::NData::IData

				void FImpl::TryTracer(TraceDataType* Data, const FVector3f& End)
				{
					using namespace NCached;

					const FString& Context = Str::TryTracer;

					// TracerVisualDataType (NCsTrace::NData::NVisual::NTracer::ITracer)
					typedef NCsTrace::NData::NVisual::NTracer::ITracer TracerVisualDataType;
					typedef NCsTrace::NData::FLibrary TraceDataLibrary;

					if (TracerVisualDataType* TracerVisualData = TraceDataLibrary::GetSafeInterfaceChecked<TracerVisualDataType>(Context, Data))
					{
						typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

						PooledPayloadType PooledPayload;

						// Set Parent based on AttachType
						typedef NCsTrace::NData::NVisual::NTracer::EAttach AttachType;

						const AttachType& AType = TracerVisualData->GetTracerAttachType();

						// None
						if (AType == AttachType::None)
						{
							PooledPayload.Parent = nullptr;
						}
						// Owner
						else
						if (AType == AttachType::Owner)
						{
							PooledPayload.Parent = Owner;
						}
						// Component
						else
						if (AType == AttachType::Component)
						{
							CS_IS_PTR_NULL_CHECKED(Component)

							PooledPayload.Parent = Component;
						}
						// Custom
						else
						if (AType == AttachType::Custom)
						{
							checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."), *Context);
						}
						else
						{
							checkf(0, TEXT("%s: AttachType: is NOT Valid."), *Context);
						}

						// Get FX
						const FCsFX& FX = TracerVisualData->GetTracerFX();

						// Set Transform based on TransformType.
						// NOTE: This is only valid if AttachType == None.
						FTransform3f Transform = FTransform3f::Identity;

						if (AType == AttachType::None)
						{
							typedef NCsTrace::NData::NVisual::NTracer::ETransform TransformType;

							const TransformType& TType = TracerVisualData->GetTracerTransformType();

							// None
							if (TType == TransformType::None)
							{
								// Do Nothing
							}
							// Owner
							else
							if (TType == TransformType::Owner)
							{
								if (AActor* Actor = Cast<AActor>(Owner))
									Transform = CsMathLibrary::Convert(Actor->GetActorTransform());
								else
								if (USceneComponent* C = Cast<USceneComponent>(Owner))
									Transform = CsMathLibrary::Convert(C->GetComponentTransform());
							}
							// Component
							else
							if (TType == TransformType::Component)
							{
								CS_IS_PTR_NULL_CHECKED(Component)

								Transform = CsMathLibrary::Convert(Component->GetComponentTransform());
							}
							// Custom
							else
							if (TType == TransformType::Custom)
							{
								checkf(0, TEXT("%s: TransformType::Custom is NOT implemented."), *Context);
							}
							else
							{
								checkf(0, TEXT("%s: TransformType: is NOT Valid."), *Context);
							}
						}

						// Allocate Payload
						typedef NCsFX::NPayload::FImpl PayloadImplType;

						PayloadImplType* Payload  = CsFXManagerLibrary::AllocatePayloadImplChecked(Context, Outer, &PooledPayload, FX, Transform);
						UCsManager_FX* Manager_FX = CsFXManagerLibrary::GetChecked(Context, Outer);

						// Get and Set any Niagara Parameters
						typedef NCsFX::NParameter::NVector::FVectorType ParameterVectorType;

						ParameterVectorType* Parameter = Manager_FX->AllocateValue<ParameterVectorType>();

						Parameter->SetName(TracerVisualData->GetTracerEndParameterName());
						Parameter->SetValue(End);

						Payload->Parameters.Reset(FMath::Max(Payload->Parameters.Max(), 1));
						Payload->Parameters.Add(Parameter);

						// Spawn FX
						Manager_FX->Spawn(FX.Type, Payload);
					}
				}

				void FImpl::TryImpact(TraceDataType* Data, const FHitResult& Hit)
				{
					using namespace NCached;

					const FString& Context = Str::TryImpact;

					// ImpactVisualDataType (NCsTrace::NData::NVisual::NImpact::IImpact)
					typedef NCsTrace::NData::NVisual::NImpact::IImpact ImpactVisualDataType;
					typedef NCsTrace::NData::FLibrary TraceDataLibrary;

					if (ImpactVisualDataType* ImpactVisualData = TraceDataLibrary::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
					{
						// Get Physics Surface
						EPhysicalSurface SurfaceType = NCsHitResult::GetPhysSurfaceType(Hit);

						const FCsFX& FX = ImpactVisualData->GetImpactFX(SurfaceType);

						FTransform3f Transform;
						Transform.SetLocation(CsMathLibrary::Convert(Hit.Location));
						Transform.SetRotation(CsMathLibrary::Convert(Hit.ImpactNormal.Rotation().Quaternion()));

						// Spawn FX
						CsFXManagerLibrary::SpawnChecked(Context, Outer, FX, Transform);
					}
				}

				#undef TraceDataType
			}
		}
	}
}