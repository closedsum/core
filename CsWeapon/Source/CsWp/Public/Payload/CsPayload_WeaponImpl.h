// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Payload/CsPayload_Weapon.h"
// Types
#include "CsMacro_Namespace.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsPayload_WeaponImpl.generated.h"

// FCsPayload_Weapon
#pragma region

class UObject;

// PayloadType (NCsWeapon::NPayload::IPayload)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NPayload, IPayload)

USTRUCT(BlueprintType)
struct CSWP_API FCsPayload_Weapon
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** Describes how the pooled object should updated. Usually update for a
		pooled object (implements the interface: ICsPooledObject) is controlled
		by its manager.
		Usually the default value is UpdateType::Manager (NCsPooledObject::EUpdate). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp")
	ECsPooledObjectUpdate UpdateType;

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp")
	UObject* Instigator;

	/** The owner of the Weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp")
	UObject* Owner;

	/** The parent of the Weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp")
	UObject* Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp")
	int32 PreserveChangesFromDefaultMask;

// PayloadType (NCsWeapon::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FECsWeapon Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FECsUpdateGroup UpdateGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FTransform Transform;

	FCsPayload_Weapon() :
		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		UpdateType(ECsPooledObjectUpdate::Manager),
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		PreserveChangesFromDefaultMask(0),
		// PayloadType (NCsWeapon::Payload::IPayload)
		Type(),
		UpdateGroup(),
		Transform()
	{
	}

	using PayloadType = NCsWeapon::NPayload::IPayload;

	void CopyToPayloadAsValueChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsPayload_Weapon

class UObject;
struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NPayload
	{
		namespace NImpl
		{
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using PayloadType = NCsWeapon::NPayload::IPayload;

			struct CSWP_API FImpl : public PooledPayloadType,
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

				// PayloadType (NCsWeapon::NPayload::IPayload)

				FECsWeapon Type;

				FECsUpdateGroup UpdateGroup;

				FTransform Transform;

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
				FORCEINLINE T* GetInstigator() const
				{
					return Cast<T>(GetInstigator());
				}

				template<typename T>
				FORCEINLINE T* GetOwner() const
				{
					return Cast<T>(GetOwner());
				}

				template<typename T>
				FORCEINLINE T* GetParent() const
				{
					return Cast<T>(GetParent());
				}

			// PayloadType (NCsWeapon::NPayload::IPayload)
			#pragma region
			public:

				FORCEINLINE const FECsWeapon& GetType() const { return Type; }
				FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const { return UpdateGroup; }
				FORCEINLINE const FTransform& GetTransform() const { return Transform; }

			#pragma endregion PayloadType (NCsWeapon::NPayload::IPayload)
			};
		}
	}
}