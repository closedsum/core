// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Impl/CsTraceWeapon_Impl_Sound.h"

// Library
#include "Data/CsLibrary_Data_Weapon.h"
#include "Managers/Trace/Data/CsLibrary_Data_Trace.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"
// Data
#include "Trace/Data/Sound/CsData_TraceWeapon_SoundFire.h"
#include "Managers/Trace/Data/CsData_Trace.h"
#include "Managers/Trace/Data/Sound/CsData_Trace_SoundImpact.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
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
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NTrace::NImpl::NSound::FImpl, SetPayload);
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

					// SoundDataType (NCsWeapon::NTrace::NData::NSound::NFire::IFire)
					typedef NCsWeapon::NTrace::NData::NSound::NFire::IFire SoundDataType;
					typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

					if (SoundDataType* SoundData = WeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Data))
					{
						typedef NCsWeapon::NTrace::NData::NSound::NFire::NParams::IParams ParamsType;

						// Get Manager
						UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(Outer->GetWorld()->GetGameState());
						// Allocate payload
						typedef NCsSound::NPayload::IPayload PayloadType;

						const ParamsType* Params = SoundData->GetFireSoundParams();
						const FCsSound& Sound	 = Params->GetSound();
						PayloadType* Payload	 = Manager_Sound->AllocatePayload(Sound.Type);
						// Set appropriate values on payload
						SetPayload(Payload, Sound);

						Manager_Sound->Spawn(Sound.Type, Payload);
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
						// Get Physics Surface
						UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.IsValid() ? Hit.PhysMaterial.Get() : nullptr;
						EPhysicalSurface SurfaceType	= PhysMaterial ? PhysMaterial->SurfaceType : EPhysicalSurface::SurfaceType_Default;

						const FCsSound& Sound = ImpactSoundData->GetImpactSound(SurfaceType);

						// Get Manager
						UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(Outer->GetWorld()->GetGameState());
						// Get Payload
						// TODO: MAYBE: FUTURE: Add virtual method to set Payload (defaults to PayloadImplType)
						typedef NCsSound::NPayload::FImpl PayloadImplType;

						PayloadImplType* Payload = Manager_Sound->AllocatePayload<PayloadImplType>(Sound.Type);
						// Set appropriate data on Payload
						SetPayload(Payload, Sound);

						Payload->Transform.SetLocation(Hit.Location);
						Payload->Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

						// Spawn FX
						Manager_Sound->Spawn(Sound.Type, Payload);
					}
				}

				#define SoundPayloadType NCsSound::NPayload::IPayload
				void FImpl::SetPayload(SoundPayloadType* Payload, const FCsSound& Sound)
				{
				#undef SoundPayloadType

					using namespace NCached;

					const FString& Context = Str::SetPayload;

					typedef NCsSound::NPayload::FImpl PayloadImplType;
					typedef NCsSound::NPayload::FLibrary PayloadLibrary;

					PayloadImplType* PayloadImpl = PayloadLibrary::PureStaticCastChecked<PayloadImplType>(Context, Payload);

					PayloadImpl->Instigator					= Outer;
					PayloadImpl->Owner						= Owner;
					// TODO: Need an Attach Type for Sound
					//PayloadImpl->Parent						= Outer->GetRootComponent();
					PayloadImpl->Sound						= Sound.GetChecked(Context);
					PayloadImpl->SoundAttenuation			= Sound.GetAttenuation();
					PayloadImpl->DeallocateMethod			= Sound.GetDeallocateMethod();
					PayloadImpl->LifeTime					= Sound.LifeTime;
					PayloadImpl->AttachmentTransformRules	= Sound.AttachmentTransformRules;
					PayloadImpl->Bone						= Sound.Bone;
					PayloadImpl->TransformRules				= Sound.TransformRules;
					PayloadImpl->Transform					= Sound.Transform;
				}
			}
		}
	}
}