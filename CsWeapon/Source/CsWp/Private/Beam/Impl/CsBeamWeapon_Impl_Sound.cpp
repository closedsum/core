// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Impl/CsBeamWeapon_Impl_Sound.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
	// Data
#include "Data/CsLibrary_Data_Weapon.h"
#include "Data/CsLibrary_Data_Beam.h"
	// Payload
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
	// Common
#include "Collision/CsLibrary_Collision.h"
// Data
#include "Beam/Data/Sound/CsData_BeamWeapon_SoundFire.h"
#include "Data/Sound/CsData_Beam_SoundImpact.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Beam/CsBeamWeapon.h"
#include "Beam/Data/Sound/CsParams_BeamWeapon_SoundFire.h"

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NImpl
		{
			namespace NSound
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NSound::FImpl, TryFire);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NBeam::NImpl::NSound::FImpl, TryImpact);
					}
				}

				void FImpl::SetOuter(UObject* InOuter)
				{
					Outer	  = InOuter;
					Interface = Cast<ICsBeamWeapon>(Outer);
				}

				#define DataType NCsWeapon::NData::IData
				void FImpl::TryFire(DataType* Data)
				{
				#undef DataType

					using namespace NCached;

					const FString& Context = Str::TryFire;

					// SoundDataType (NCsWeapon::NBeam::NData::NSound::NFire::IFire)
					typedef NCsWeapon::NBeam::NData::NSound::NFire::IFire SoundDataType;

					if (SoundDataType* SoundData = CsWeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Data))
					{
						typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

						PooledPayloadType PooledPayload;
						PooledPayload.Instigator = Outer;
						PooledPayload.Owner = Owner;

						// Get Sound
						typedef NCsWeapon::NBeam::NData::NSound::NFire::NParams::IParams ParamsType;

						const ParamsType* Params = SoundData->GetFireSoundParams();
						const FCsSound& Sound    = Params->GetSound();

						// Spawn Sound
						typedef NCsSound::NManager::FLibrary SoundManagerLibrary;

						SoundManagerLibrary::SpawnChecked(Context, Outer, &PooledPayload, Sound);
					}
				}

				#define BeamDataType NCsBeam::NData::IData
				void FImpl::TryImpact(BeamDataType* Data, const FHitResult& Hit)
				{
				#undef BeamDataType

					using namespace NCached;

					const FString& Context = Str::TryImpact;

					// ImpactSoundDataType (NCsBeam::NData::NSound::NImpact::IImpact)
					typedef NCsBeam::NData::NSound::NImpact::IImpact ImpactSoundDataType;
					typedef NCsBeam::NData::FLibrary BeamDataLibrary;
					typedef NCsCollision::FLibrary CollisionLibrary;

					if (ImpactSoundDataType* ImpactSoundData = BeamDataLibrary::GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
					{
						typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

						PooledPayloadType PooledPayload;
						PooledPayload.Instigator = Outer;
						PooledPayload.Owner		 = Owner;

						// Get Impact sound associated with Physics Surface
						EPhysicalSurface SurfaceType = NCsHitResult::GetPhysSurfaceType(Hit);

						const FCsSound& Sound = ImpactSoundData->GetImpactSound(SurfaceType);

						FTransform3f Transform = FTransform3f::Identity;
						Transform.SetLocation(CollisionLibrary::GetLocation(Hit));
						Transform.SetRotation(CollisionLibrary::GetImpactQuat(Hit));

						// Spawn Sound
						typedef NCsSound::NManager::FLibrary SoundManagerLibrary;

						SoundManagerLibrary::SpawnChecked(Context, Outer, &PooledPayload, Sound, Transform);
					}
				}
			}
		}
	}
}