// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// Projectile
#include "Payload/CsPayload_Projectile.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsPayload_ProjectileImpl.generated.h"

// FCsPayload_Projectile
#pragma region

class UObject;

// NCsProjectile::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, FImpl)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPayload_Projectile
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Instigator;

	/** The owner of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Owner;

	/** The parent of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PreserveChangesFromDefaultMask;

// PrjPayloadType (NCsProjectile::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsProjectile Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;

	FCsPayload_Projectile() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		PreserveChangesFromDefaultMask(0),
		Type(),
		Location(0.0f),
		Direction(0.0f)
	{
	}

#define PayloadType NCsProjectile::NPayload::FImpl
	void CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

#pragma endregion FCsPayload_Projectile

class UObject;
struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NPayload
	{
	#define PooledPayloadType NCsPooledObject::NPayload::IPayload
	#define ProjectilePayloadType NCsProjectile::NPayload::IPayload

		/**
		* Basic implementation of the interfaces: 
		*  PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		*  ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
		*/
		struct CSPRJ_API FImpl : public PooledPayloadType,
								 public ProjectilePayloadType
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

			// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)

			FECsProjectile Type;

			FVector Direction;

			FVector Location;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

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

		// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const FECsProjectile& GetType() const { return Type; }
			FORCEINLINE const FVector& GetDirection() const { return Direction; }
			FORCEINLINE const FVector& GetLocation() const { return Location; }

		#pragma endregion ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
		};

	#undef PooledPayloadType
	#undef ProjectilePayloadType
	}
}