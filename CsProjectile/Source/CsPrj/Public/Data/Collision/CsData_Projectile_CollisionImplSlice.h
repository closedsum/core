// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Collision.h"
// Log
#include "Utility/CsPrjLog.h"
// Data
#include "Data/Collision/CsData_Projectile_Collision.h"

#include "CsData_Projectile_CollisionImplSlice.generated.h"
#pragma once

// NCsProjectile::NData::NCollision::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NData, NCollision, FImplSlice)

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsCollisionPreset Preset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	FCsData_Projectile_CollisionImplSlice() :
		Preset(),
		Radius(0.0f)
	{
	}

#define SliceType NCsProjectile::NData::NCollision::FImplSlice

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NData
	{
		namespace NCollision
		{
		#define CollisionDataType NCsProjectile::NData::NCollision::ICollision

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
			
				// ICsGetInterfaceMap

				/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition) 
					that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)

				CS_DECLARE_MEMBER_WITH_EMU(CollisionPreset, FCsCollisionPreset)
				CS_DECLARE_MEMBER_WITH_EMU(CollisionRadius, float)

			public:

				FImplSlice() :
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_EMU(CollisionPreset),
					CS_CTOR_INIT_MEMBER_WITH_EMU(CollisionRadius, 0.0f)
				{
					CS_CTOR_SET_MEMBER_EMU(CollisionPreset);
					CS_CTOR_SET_MEMBER_EMU(CollisionRadius);
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

			// CollisionDataType (NCsProjectile::NData::NCollision::ICollision)
			#pragma region
			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(CollisionPreset, FCsCollisionPreset)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(CollisionRadius, float)

			#pragma endregion CollisionDataType (NCsProjectile::NData::NCollision::ICollision)

			public:

				static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsProjectile::NData::NCollision::FImplSlice*>(Ptr);
				}

				static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
			};

		#undef CollisionDataType
		}
	}
}