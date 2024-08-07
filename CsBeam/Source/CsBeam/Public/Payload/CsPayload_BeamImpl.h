// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Misc.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Beam
#include "Payload/CsPayload_Beam.h"
// Log
#include "Utility/CsBeamLog.h"

#include "CsPayload_BeamImpl.generated.h"

// FCsPayload_Beam
#pragma region

class UObject;

// NCsBeam::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NPayload, FImpl)

USTRUCT(BlueprintType)
struct CSBEAM_API FCsPayload_Beam
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** Describes how the pooled object should updated. Usually update for a
		pooled object (implements the interface: ICsPooledObject) is controlled
		by its manager.
		Usually the default value is UpdateType::Manager (NCsPooledObject::EUpdate). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	ECsPooledObjectUpdate UpdateType;

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	UObject* Instigator;

	/** The owner of the Beam. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	UObject* Owner;

	/** The parent of the Beam. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	UObject* Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	int32 PreserveChangesFromDefaultMask;

// BeamPayloadType (NCsBeam::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	FECsBeam Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	FCsAttachmentTransformRules AttachRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	FVector3f Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	FVector3f Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Payload")
	FVector3f Scale;

	FCsPayload_Beam() :
		UpdateType(ECsPooledObjectUpdate::Manager),
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		PreserveChangesFromDefaultMask(0),
		Type(),
		AttachRules(FCsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Location(0.0f),
		Direction(0.0f),
		Scale(0.0f)
	{
	}

#define PayloadType NCsBeam::NPayload::FImpl
	void CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

#pragma endregion FCsPayload_Beam

class UObject;
struct FCsInterfaceMap;

namespace NCsBeam
{
	namespace NPayload
	{
	#define PooledPayloadType NCsPooledObject::NPayload::IPayload
	#define BeamPayloadType NCsBeam::NPayload::IPayload

		/**
		* Basic implementation of the interfaces: 
		*  PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		*  BeamPayloadType (NCsBeam::NPayload::IPayload)
		*/
		struct CSBEAM_API FImpl : public PooledPayloadType,
								  public BeamPayloadType
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

			bool bAllocated;

		public:

			NCsPooledObject::EUpdate UpdateType;

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			// BeamPayloadType (NCsBeam::NPayload::IPayload)

			FECsBeam Type;

			FAttachmentTransformRules AttachRules;

			FVector3f Location;

			FVector3f Direction;

			FVector3f Scale;

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
			FORCEINLINE void Allocate() { bAllocated = true; }

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

		// BeamPayloadType (NCsBeam::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const FECsBeam& GetType() const { return Type; }
			FORCEINLINE const FAttachmentTransformRules& GetAttachRules() const { return AttachRules; }
			FORCEINLINE const FVector3f& GetLocation() const { return Location; }
			FORCEINLINE const FVector3f& GetDirection() const { return Direction; }
			FORCEINLINE const FVector3f& GetScale() const { return Scale; }

		#pragma endregion BeamPayloadType (NCsBeam::NPayload::IPayload)
		};

	#undef PooledPayloadType
	#undef BeamPayloadType
	}
}