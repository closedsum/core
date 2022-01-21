// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Impl/CsTraceWeapon_Impl_Sound.h"

// Types
#include "Collision/CsTypes_Collision.h"
// Library
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
// Data
#include "Trace/Data/Sound/CsData_TraceWeapon_SoundFire.h"
#include "Managers/Trace/Data/CsData_Trace.h"
#include "Managers/Trace/Data/Sound/CsData_Trace_SoundImpact.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Weapon
#include "Trace/CsTraceWeapon.h"
#include "Trace/Data/Sound/CsParams_TraceWeapon_SoundFire.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NImpl
		{
			namespace NSound
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NSound::FImpl, TryFire);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NSound::FImpl, TryImpact);
					}
				}

				void FImpl::SetOuter(UObject* InOuter)
				{
					Outer	  = InOuter;
					Interface = Cast<ICsTraceWeapon>(Outer);
				}

				#define DataType NCsWeapon::NData::IData
				void FImpl::TryFire(DataType* Data)
				{
				#undef DataType

					using namespace NCached;

					const FString& Context = Str::TryFire;

					// SoundDataType (NCsWeapon::NTrace::NData::NSound::NFire::IFire)
					typedef NCsWeapon::NTrace::NData::NSound::NFire::IFire SoundDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					if (SoundDataType* SoundData = WeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Data))
					{
						typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

						PooledPayloadType PooledPayload;
						PooledPayload.Instigator = Outer;
						PooledPayload.Owner = Owner;

						// Get Sound
						typedef NCsWeapon::NTrace::NData::NSound::NFire::NParams::IParams ParamsType;

						const ParamsType* Params = SoundData->GetFireSoundParams();
						const FCsSound& Sound    = Params->GetSound();

						// Spawn Sound
						typedef NCsSound::NManager::FLibrary SoundManagerLibrary;

						SoundManagerLibrary::SpawnChecked(Context, Outer, &PooledPayload, Sound);
					}
				}

				#define TraceDataType NCsTrace::NData::IData
				void FImpl::TryImpact(TraceDataType* Data, const FHitResult& Hit)
				{
				#undef TraceDataType

					using namespace NCached;

					const FString& Context = Str::TryImpact;

					// ImpactSoundDataType (NCsTrace::NData::NSound::NImpact::IImpact)
					typedef NCsTrace::NData::NSound::NImpact::IImpact ImpactSoundDataType;
					typedef NCsTrace::NData::FLibrary TraceDataLibrary;

					if (ImpactSoundDataType* ImpactSoundData = TraceDataLibrary::GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
					{
						typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

						PooledPayloadType PooledPayload;
						PooledPayload.Instigator = Outer;
						PooledPayload.Owner		 = Owner;

						// Get Impact sound associated with Physics Surface
						EPhysicalSurface SurfaceType = NCsHitResult::GetPhysSurfaceType(Hit);

						const FCsSound& Sound = ImpactSoundData->GetImpactSound(SurfaceType);

						FTransform Transform = FTransform::Identity;
						Transform.SetLocation(Hit.Location);
						Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

						// Spawn Sound
						typedef NCsSound::NManager::FLibrary SoundManagerLibrary;

						SoundManagerLibrary::SpawnChecked(Context, Outer, &PooledPayload, Sound, Transform);
					}
				}
			}
		}
	}
}