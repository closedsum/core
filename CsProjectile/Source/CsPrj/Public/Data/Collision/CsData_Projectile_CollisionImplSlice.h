// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Collision/CsTypes_Collision.h"
// Log
#include "Utility/CsPrjLog.h"
// Data
#include "Data/Collision/CsData_Projectile_Collision.h"

#include "CsData_Projectile_CollisionImplSlice.generated.h"
#pragma once

class UObject;

// NCsProjectile::NData::NCollision::NImplSlice::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NData, NCollision, NImplSlice, FImplSlice)

/**
* Represents a "slice" of data, CollisionDataType (NCsProjectile::NData::NCollision::ICollision).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_Projectile_CollisionImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// CollisionDataType (NCsProjectile::NData::NCollision::IData)

	/** Collision information (i.e. response, overlap, hit events, ... etc) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data")
	FCsCollisionPreset Preset;

	/** Radius of the collision sphere */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	/** Number of hits before the projectile is stopped (and / or deallocated if pooled).
		NOTE:
			- Collision detection is captured via CollisionComponent->OnComponentHit.
			- GetCollisionPreset().bSimulationGeneratesHitEvents MUST be true for the count to be meaningful. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data", meta = (UIMin = "0", ClampMin = "0"))
	int32 HitCount;

	/** Whether to ignore an object (AActor or UPrimitiveComponent) the projectile has collided with after
		the first collision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data")
	bool bIgnoreHitObjectAfterHit;

	/** List of classes to ignore for colliding objects. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Projectile|Data")
	TArray<TSubclassOf<UObject>> IgnoreHitObjectClasses;

	FCsData_Projectile_CollisionImplSlice() :
		Preset(),
		Radius(0.0f),
		HitCount(0),
		bIgnoreHitObjectAfterHit(false),
		IgnoreHitObjectClasses()
	{
	}

	using SliceType = NCsProjectile::NData::NCollision::NImplSlice::FImplSlice;

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NData
	{
		namespace NCollision
		{
			namespace NImplSlice
			{
				using CollisionDataType = NCsProjectile::NData::NCollision::ICollision;

				/**
				* Represents a "slice" of data, CollisionDataType (NCsProjectile::NData::NCollision::ICollision).
				* 
				* If members are set via points to an "owning" data, then
				* "Emulates" CollisionDataType (NCsProjectile::NData::NCollision::ICollision) by mimicking 
				* the interfaces and having pointers to the appropriate members. 
				* 
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSPRJ_API FImplSlice final : public CollisionDataType
				{
				public:

					static const FName Name;

				private:

					using ThisType = NCsProjectile::NData::NCollision::NImplSlice::FImplSlice;

				private:
			
					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition) 
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)

					CS_DECLARE_MEMBER_WITH_PROXY(CollisionPreset, FCsCollisionPreset)
					CS_DECLARE_MEMBER_WITH_PROXY(CollisionRadius, float)
					CS_DECLARE_MEMBER_WITH_PROXY(HitCount, int32)
					CS_DECLARE_MEMBER_WITH_PROXY(bIgnoreHitObjectAfterHit, bool)
					CS_DECLARE_MEMBER_WITH_PROXY(IgnoreHitObjectClasses, TArray<TSubclassOf<UObject>>)

				public:

					FImplSlice() :
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(CollisionPreset),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(CollisionRadius, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(HitCount, 0),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bIgnoreHitObjectAfterHit, false),
						CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(IgnoreHitObjectClasses)
					{
						CS_CTOR_SET_MEMBER_PROXY(CollisionPreset);
						CS_CTOR_SET_MEMBER_PROXY(CollisionRadius);
						CS_CTOR_SET_MEMBER_PROXY(HitCount);
						CS_CTOR_SET_MEMBER_PROXY(bIgnoreHitObjectAfterHit);
						CS_CTOR_SET_MEMBER_PROXY(IgnoreHitObjectClasses);
					}

					~FImplSlice(){}

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				public:

					FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE void SetIgnoreHitObjectAfterHit(const bool& Value)
					{
						bIgnoreHitObjectAfterHit = Value;
						bIgnoreHitObjectAfterHit_Proxy = &bIgnoreHitObjectAfterHit;
					}
					FORCEINLINE void SetIgnoreHitObjectAfterHit(bool* Value) { check(Value); bIgnoreHitObjectAfterHit_Proxy = Value; }

				// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
				#pragma region
				public:

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CollisionPreset, FCsCollisionPreset)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CollisionRadius, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(HitCount, int32)

					FORCEINLINE const bool& IgnoreHitObjectAfterHit() const { return *bIgnoreHitObjectAfterHit_Proxy; }

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(IgnoreHitObjectClasses, TArray<TSubclassOf<UObject>>)

				#pragma endregion CollisionDataType (NCsProjectile::NData::NCollision::ICollision)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<ThisType*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
				};
			}
		}
	}
}