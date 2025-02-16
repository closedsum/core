// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
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

// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPayload_Projectile
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** Describes how the pooled object should updated. Usually update for a
		pooled object (implements the interface: ICsPooledObject) is controlled
		by its manager.
		Usually the default value is UpdateType::Manager (NCsPooledObject::EUpdate). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	ECsPooledObjectUpdate UpdateType;

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	UObject* Instigator;

	/** The owner of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	UObject* Owner;

	/** The parent of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	UObject* Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	int32 PreserveChangesFromDefaultMask;

// PrjPayloadType (NCsProjectile::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FECsProjectile Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj", meta = (UIMin = "0", ClampMin = "0"))
	int32 Generation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FVector Direction;

	FCsPayload_Projectile() :
		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		UpdateType(ECsPooledObjectUpdate::Manager),
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		PreserveChangesFromDefaultMask(0),
		// PrjPayloadType (NCsProjectile::Payload::IPayload)
		Type(),
		Generation(0),
		Location(0.0f),
		Direction(0.0f)
	{
	}

	using PayloadType = NCsProjectile::NPayload::IPayload;

	void CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const;

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
		namespace NImpl
		{
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using PayloadType = NCsProjectile::NPayload::IPayload;

			/**
			* Basic implementation of the interfaces: 
			*  PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			*  ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
			*/
			struct CSPRJ_API FImpl : public PooledPayloadType,
									 public PayloadType
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

				// PayloadType (NCsProjectile::NPayload::IPayload)

				FECsProjectile Type;

				int32 Generation;

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

			// PayloadType (NCsProjectile::NPayload::IPayload)
			#pragma region
			public:

				FORCEINLINE const FECsProjectile& GetType() const { return Type; }
				FORCEINLINE const int32& GetGeneration() const { return Generation; }
				FORCEINLINE const FVector& GetDirection() const { return Direction; }
				FORCEINLINE const FVector& GetLocation() const { return Location; }

			#pragma endregion PayloadType (NCsProjectile::NPayload::IPayload)
			};
		}
	}
}

/*
namespace NCsProjectile
{
	namespace NPayload
	{
		struct CSPRJ_API FTestTrait
		{
		private:

			NCsProjectile::NPayload::RPayload __PrjPayloadTrait__;
			NCsProjectile::NPayload::TCheck<FTestTrait> __check__1;

		public:

			FTestTrait() :
				__PrjPayloadTrait__(),
				__check__1()
			{
				__PrjPayloadTrait__.Set__GetType(&FTestTrait::GetType);
				__PrjPayloadTrait__.Set__GetDirection(&FTestTrait::GetDirection);
				__PrjPayloadTrait__.Set__GetLocation(&FTestTrait::GetLocation);
			}

			FORCEINLINE static const FECsProjectile& GetType(const void* __Outer) { return ((*(static_cast<const FTestTrait*>(__Outer))).GetType)(); }
			FORCEINLINE static const FVector3f& GetDirection(const void* __Outer) { return ((*(static_cast<const FTestTrait*>(__Outer))).GetDirection)(); }
			FORCEINLINE static const FVector3f& GetLocation(const void* __Outer) { return ((*(static_cast<const FTestTrait*>(__Outer))).GetLocation)(); }

			FORCEINLINE const FECsProjectile& GetType() const { return EMCsProjectile::Get().GetMAX(); }

			FORCEINLINE const FVector3f& GetDirection() const { return FVector3f::ZeroVector; }

			FORCEINLINE const FVector3f& GetLocation() const { return FVector3f::ZeroVector; }
		};
	}
}
*/