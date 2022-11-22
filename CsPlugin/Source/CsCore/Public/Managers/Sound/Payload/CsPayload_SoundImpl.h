// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/Sound/Payload/CsPayload_Sound.h"

#pragma once

class UObject;
struct FCsInterfaceMap;
class USoundBase;

namespace NCsSound
{
	namespace NPayload
	{
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define SoundPayloadType NCsSound::NPayload::IPayload

		/**
		*/
		struct CSCORE_API FImpl final : public PooledPayloadType,
										public SoundPayloadType
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

			bool bAllocated;

		public:

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

			NCsPooledObject::EUpdate UpdateType;

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			// SoundPayloadType (NCsSound::NPayload::IPayload)

			USoundBase* Sound;

			USoundAttenuation* SoundAttenuation;

			EDeallocateMethod DeallocateMethod;

			float LifeTime;
	
			float DurationMultiplier;

			float FadeInTime;

			ECsAttachmentTransformRules AttachmentTransformRules;

			FName Bone;

			int32 TransformRules;

			FTransform Transform;

			float VolumeMultiplier;

			float PitchMultiplier;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }
			FORCEINLINE const NCsPooledObject::EUpdate& GetUpdateType() const { return UpdateType; }
			FORCEINLINE UObject* GetInstigator() const { return Instigator; }
			FORCEINLINE UObject* GetOwner() const { return Owner; }
			FORCEINLINE UObject* GetParent() const { return Parent; }
			FORCEINLINE const FCsTime& GetTime() const { return Time; }
			FORCEINLINE void Allocate(){ bAllocated = true; }

			void Reset();

			FORCEINLINE const uint32& GetPreserveChangesFromDefaultMask() const { return PreserveChangesFromDefaultMask; }

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const { return Cast<T>(GetInstigator()); }

			template<typename T>
			FORCEINLINE T* GetOwner() const { return Cast<T>(GetOwner()); }

			template<typename T>
			FORCEINLINE T* GetParent() const { return Cast<T>(GetParent()); }

		// SoundPayloadType (NCsSound::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE USoundBase* GetSound() const { return Sound; }
			FORCEINLINE USoundAttenuation* GetSoundAttenuation() const { return SoundAttenuation; }
			FORCEINLINE const EDeallocateMethod& GetDeallocateMethod() const { return DeallocateMethod; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const float& GetDurationMultiplier() const { return DurationMultiplier; }
			FORCEINLINE const float& GetFadeInTime() const { return FadeInTime; }
			FORCEINLINE const ECsAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
			FORCEINLINE const FName& GetBone() const { return Bone; }
			FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
			FORCEINLINE const FTransform& GetTransform() const { return Transform; }
			FORCEINLINE const float& GetVolumeMultiplier() const { return VolumeMultiplier; }
			FORCEINLINE const float& GetPitchMultiplier() const { return PitchMultiplier; }

		#pragma endregion SoundPayloadType (NCsSound::NPayload::IPayload)
		};

#undef PooledPayloadType
#undef SoundPayloadType
	}
}