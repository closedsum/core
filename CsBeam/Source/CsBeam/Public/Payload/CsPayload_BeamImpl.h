// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
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

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Instigator;

	/** The owner of the Beam. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Owner;

	/** The parent of the Beam. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PreserveChangesFromDefaultMask;

// BeamPayloadType (NCsBeam::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsBeam Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Scale;

	FCsPayload_Beam() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		PreserveChangesFromDefaultMask(0),
		Type(),
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

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			// BeamPayloadType (NCsBeam::NPayload::IPayload)

			FECsBeam Type;

			FVector Location;

			FVector Direction;

			FVector Scale;

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
			FORCEINLINE const FVector& GetLocation() const { return Location; }
			FORCEINLINE const FVector& GetDirection() const { return Direction; }
			FORCEINLINE const FVector& GetScale() const { return Scale; }

		#pragma endregion BeamPayloadType (NCsBeam::NPayload::IPayload)
		};

	#undef PooledPayloadType
	#undef BeamPayloadType
	}
}