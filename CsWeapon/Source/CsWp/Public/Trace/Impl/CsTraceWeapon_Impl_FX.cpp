// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Impl/CsTraceWeapon_Impl_FX.h"

// Types

// Library
#include "Data/CsLibrary_Data_Weapon.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Trace/Data/Visual/CsData_TraceWeapon_VisualFire.h"
#include "Managers/Trace/Data/CsData_Trace.h"
#include "Managers/Trace/Data/Visual/CsData_Trace_VisualTracer.h"
#include "Managers/Trace/Data/Visual/CsData_Trace_VisualImpact.h"
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
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NFX::FImpl, SetPayload);
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

						// Get Manager
						UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(Outer->GetWorld()->GetGameState());
						// Allocate payload
						typedef NCsFX::NPayload::IPayload PayloadType;

						const ParamsType* Params = FXData->GetFireFXParams();
						const FCsFX& FX			 = Params->GetFX();

						PayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
						// Set appropriate values on payload
						SetPayload(Payload, FX);
						SetPayload(Payload, FXData);

						Manager_FX->Spawn(FX.Type, Payload);
					}
				}

				#define TraceDataType NCsTrace::NData::IData
				void FImpl::TryTracer(TraceDataType* Data, const FVector& End)
				{
				#undef TraceDataType

					using namespace NCached;

					const FString& Context = Str::TryTracer;

					// TracerVisualDataType (NCsTrace::NData::NVisual::NTracer::ITracer)
					typedef NCsTrace::NData::NVisual::NTracer::ITracer TracerVisualDataType;
					typedef NCsTrace::NData::FLibrary TraceDataLibrary;

					if (TracerVisualDataType* TracerVisualData = TraceDataLibrary::GetSafeInterfaceChecked<TracerVisualDataType>(Context, Data))
					{
						// Get Manager
						UCsManager_FX_Actor* Manager_FX_Actor = UCsManager_FX_Actor::Get(Outer->GetWorld()->GetGameState());
						// Get Payload
						typedef NCsFX::NPayload::FImpl PayloadImplType;

						const FCsFX& FX = TracerVisualData->GetTracerFX();

						PayloadImplType* Payload = Manager_FX_Actor->AllocatePayload<PayloadImplType>(FX.Type);

						SetPayload(Payload, TracerVisualData);

						// Get and Set any Niagara Parameters
						typedef NCsFX::NParameter::NVector::FVectorType ParameterVectorType;

						ParameterVectorType* Parameter = Manager_FX_Actor->AllocateValue<ParameterVectorType>();

						Parameter->Name  = TracerVisualData->GetTracerEndParameterName();
						Parameter->Value = End;

						Payload->Parameters.Reset(FMath::Max(Payload->Parameters.Max(), 1));
						Payload->Parameters.Add(Parameter);

						// Spawn FX
						Manager_FX_Actor->Spawn(FX.Type, Payload);
					}
				}

				#define TraceDataType NCsTrace::NData::IData
				void FImpl::TryImpact(TraceDataType* Data, const FHitResult& Hit)
				{
				#undef TraceDataType

					using namespace NCached;

					const FString& Context = Str::TryImpact;

					// ImpactVisualDataType (NCsTrace::NData::NVisual::NImpact::IImpact)
					typedef NCsTrace::NData::NVisual::NImpact::IImpact ImpactVisualDataType;
					typedef NCsTrace::NData::FLibrary TraceDataLibrary;

					if (ImpactVisualDataType* ImpactVisualData = TraceDataLibrary::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
					{
						// Get Manager
						UCsManager_FX_Actor* Manager_FX_Actor = UCsManager_FX_Actor::Get(Outer->GetWorld()->GetGameState());
						
						// Get Physics Surface
						UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;
						EPhysicalSurface SurfaceType    = PhysMaterial ? PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

						const FCsFX& FX = ImpactVisualData->GetImpactFX(SurfaceType);

						// Get Payload
						// TODO: MAYBE: FUTURE: Add virtual method to set Payload (defaults to PayloadImplType)
						typedef NCsFX::NPayload::FImpl PayloadImplType;

						PayloadImplType* Payload = Manager_FX_Actor->AllocatePayload<PayloadImplType>(FX.Type);
						// Set appropriate data on Payload
						SetPayload(Payload, FX);

						Payload->Transform.SetLocation(Hit.Location);
						Payload->Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

						// Spawn FX
						Manager_FX_Actor->Spawn(FX.Type, Payload);
					}
				}

				#define FXPayloadType NCsFX::NPayload::IPayload
				void FImpl::SetPayload(FXPayloadType* Payload, const FCsFX& FX)
				{
				#undef FXPayloadType

					using namespace NCached;

					const FString& Context = Str::SetPayload;

					typedef NCsFX::NPayload::FImpl PayloadImplType;
					typedef NCsFX::NPayload::FLibrary PayloadLibrary;

					PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

					PayloadImpl->Instigator					= Outer;
					PayloadImpl->Owner						= Owner;
					PayloadImpl->FXSystem					= FX.GetChecked(Context);
					PayloadImpl->DeallocateMethod			= FX.GetDeallocateMethod();
					PayloadImpl->LifeTime					= FX.LifeTime;
					PayloadImpl->AttachmentTransformRules	= FX.AttachmentTransformRules;
					PayloadImpl->Bone						= FX.Bone;
					PayloadImpl->TransformRules				= FX.TransformRules;
					PayloadImpl->Transform					= FX.Transform;
				}

				#define FXPayloadType NCsFX::NPayload::IPayload
				#define FireVisualDataType NCsWeapon::NTrace::NData::NVisual::NFire::IFire
				void FImpl::SetPayload(FXPayloadType* Payload, FireVisualDataType* FireVisualData)
				{
				#undef FXPayloadType
				#undef FireVisualDataType

					using namespace NCached;

					const FString& Context = Str::SetPayload;

					typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams ParamsType;

					const ParamsType* Params = FireVisualData->GetFireFXParams();

					typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::EAttach AttachType;

					const AttachType& Type = Params->GetAttachType();

					typedef NCsFX::NPayload::FImpl PayloadImplType;
					typedef NCsFX::NPayload::FLibrary PayloadLibrary;

					PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

					// None
					if (Type == AttachType::None)
					{
						PayloadImpl->Parent = nullptr;
					}
					// Owner
					else
					if (Type == AttachType::Owner)
					{
						PayloadImpl->Parent = Owner;
					}
					// Component
					else
					if (Type == AttachType::Component)
					{
						checkf(Component, TEXT("%s: Component is NULL."), *Context);

						PayloadImpl->Parent = Component;
					}
					// Custom
					else
					{
						checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."), *Context);
					}
				}

				#define FXPayloadType NCsFX::NPayload::IPayload
				#define TracerVisualDataType NCsTrace::NData::NVisual::NTracer::ITracer
				void FImpl::SetPayload(FXPayloadType* Payload, TracerVisualDataType* TracerVisualData)
				{
				#undef FXPayloadType
				#undef TracerVisualDataType

					const FCsFX& FX = TracerVisualData->GetTracerFX();

					SetPayload(Payload, FX);

					using namespace NCached;

					const FString& Context = Str::SetPayload;

					typedef NCsFX::NPayload::FImpl PayloadImplType;
					typedef NCsFX::NPayload::FLibrary PayloadLibrary;

					PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

					// Set Parent based on AttachType
					typedef NCsTrace::NData::NVisual::NTracer::EAttach AttachType;

					const AttachType& AType = TracerVisualData->GetTracerAttachType();

					// None
					if (AType == AttachType::None)
					{
						PayloadImpl->Parent = nullptr;
					}
					// Owner
					else
					if (AType == AttachType::Owner)
					{
						PayloadImpl->Parent = Owner;
					}
					// Component
					else
					if (AType == AttachType::Component)
					{
						checkf(Component, TEXT("%s: Component is NULL."), *Context);

						PayloadImpl->Parent = Component;
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

					// Set Transform based on TransformType.
					// NOTE: This is only valid if AttachType == None.

					if (AType == AttachType::None)
					{
						typedef NCsTrace::NData::NVisual::NTracer::ETransform TransformType;

						const TransformType& TType = TracerVisualData->GetTracerTransformType();

						FTransform TransformToApply = FTransform::Identity;

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
								TransformToApply = Actor->GetActorTransform();
							else
							if (USceneComponent* C = Cast<USceneComponent>(Owner))
								TransformToApply = C->GetComponentTransform();
						}
						// Component
						else
						if (TType == TransformType::Component)
						{
							checkf(Component, TEXT("%s: Component is NULL."), *Context);

							TransformToApply = Component->GetComponentTransform();
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
		
						// Location - Add each component
						PayloadImpl->Transform.AddToTranslation(TransformToApply.GetTranslation());
						// Rotation - Add each component
						FRotator Rotation = PayloadImpl->Transform.Rotator();
						Rotation += TransformToApply.Rotator();
						PayloadImpl->Transform.SetRotation(Rotation.Quaternion());
						// Scale - Multiply each component
						FVector Scale = PayloadImpl->Transform.GetScale3D();
						Scale *= TransformToApply.GetScale3D();
						PayloadImpl->Transform.SetScale3D(Scale);
					}
				}
			}
		}
	}
}