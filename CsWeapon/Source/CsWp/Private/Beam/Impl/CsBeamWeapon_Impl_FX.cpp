// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Impl/CsBeamWeapon_Impl_FX.h"

// Library
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
#include "Data/CsLibrary_Data_Beam.h"
#include "Collision/CsTypes_Collision.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Beam/Data/Visual/CsData_BeamWeapon_VisualFire.h"
#include "Data/Visual/Impact/CsData_Beam_VisualImpact.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Beam/CsBeamWeapon.h"
#include "Beam/Data/Visual/CsParams_BeamWeapon_VisualFire.h"
// Components
#include "Components/SceneComponent.h"

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NImpl
		{
			namespace NFX
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NFX::FImpl, TryFire);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NFX::FImpl, TryImpact);
					}
				}

				using DataType = NCsWeapon::NData::IData;
				using BeamDataType = NCsBeam::NData::IData;

				void FImpl::SetOuter(UObject* InOuter)
				{
					Outer = InOuter;
					Interface = Cast<ICsBeamWeapon>(Outer);
				}

				void FImpl::TryFire(DataType* Data)
				{
					using namespace NCached;

					const FString& Context = Str::TryFire;

					// FireVisualDataType (NCsWeapon::NBeam::NData::NVisual::NFire::IFire)
					if (FireVisualDataType* FXData = CsWeaponDataLibrary::GetSafeInterfaceChecked<FireVisualDataType>(Context, Data))
					{
						typedef NCsWeapon::NBeam::NData::NVisual::NFire::NParams::IParams ParamsType;
						typedef NCsWeapon::NBeam::NData::NVisual::NFire::NParams::EAttach AttachType;

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

				void FImpl::TryImpact(BeamDataType* Data, const FHitResult& Hit)
				{
					using namespace NCached;

					const FString& Context = Str::TryImpact;

					// ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact)
					typedef NCsBeam::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

					if (ImpactVisualDataType* ImpactVisualData = CsBeamDataLibrary::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
					{
						// Get Physics Surface
						EPhysicalSurface SurfaceType = NCsHitResult::GetPhysSurfaceType(Hit);

						const FCsFX& FX = ImpactVisualData->GetImpactFX(SurfaceType);

						FTransform Transform;
						Transform.SetLocation(Hit.Location);
						Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

						// Spawn FX
						CsFXManagerLibrary::SpawnChecked(Context, Outer, FX, Transform);
					}
				}
			}
		}
	}
}