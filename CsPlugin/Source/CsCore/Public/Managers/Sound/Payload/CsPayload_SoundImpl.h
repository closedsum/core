// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/Sound/Payload/CsPayload_Sound.h"

#include "CsPayload_SoundImpl.generated.h"

// NCsSound::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, FImpl)

USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_Sound
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound|Payload")
	UObject* Instigator;

	/** The owner of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound|Payload")
	UObject* Owner;

	/** The parent of the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound|Payload")
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound|Payload")
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound|Payload", meta = (Bitmask, BitmaskEnum = "ECsSoundPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// SoundPayloadType (NCsSound::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound|Payload")
	FCsSound Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound|Payload", meta = (UIMin = "0.001", ClampMin = "0.001"))
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound|Payload", meta = (UIMin = "0.001", ClampMin = "0.001"))
	float PitchMultiplier;

	FCsPayload_Sound() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		Sound(),
		VolumeMultiplier(1.0f),
		PitchMultiplier(1.0f)
	{
	}

#define PayloadType NCsSound::NPayload::FImpl
	void CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadType* Payload) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

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

			FAttachmentTransformRules AttachmentTransformRules;

			FName Bone;

			int32 TransformRules;

			FTransform3f Transform;

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
			FORCEINLINE const FAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
			FORCEINLINE const FName& GetBone() const { return Bone; }
			FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
			FORCEINLINE const FTransform3f& GetTransform() const { return Transform; }
			FORCEINLINE const float& GetVolumeMultiplier() const { return VolumeMultiplier; }
			FORCEINLINE const float& GetPitchMultiplier() const { return PitchMultiplier; }

		#pragma endregion SoundPayloadType (NCsSound::NPayload::IPayload)
		};

#undef PooledPayloadType
#undef SoundPayloadType
	}
}