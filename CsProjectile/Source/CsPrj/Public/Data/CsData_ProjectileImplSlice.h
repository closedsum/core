// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsPrjLog.h"
// Data
#include "Data/CsData_Projectile.h"

#include "CsData_ProjectileImplSlice.generated.h"
#pragma once

// NCsProjectile::NData::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, FImplSlice)

/**
* Represents a "slice" of data, ProjectileDataType (NCsProjectile::NData::IData).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_ProjectileImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// ProjectileDataType (NCsProjectile::NData::IData)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float InitialSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float GravityScale;

	FCsData_ProjectileImplSlice() :
		LifeTime(0.0f),
		InitialSpeed(0.0f),
		MaxSpeed(0.0f),
		GravityScale(0.0f)
	{
	}

#define SliceType NCsProjectile::NData::FImplSlice

	SliceType* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);
	SliceType* SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

private:

	SliceType* SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NData
	{
		/**
		* Represents a "slice" of data, ProjectileDataType (NCsProjectile::NData::IData).
		* 
		* If members are set via points to an "owning" data, then
		* "Emulates" ProjectileDataType (NCsProjectile::NData::IData) by mimicking 
		* the interfaces and having pointers to the appropriate members. 
		*
		* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
		* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
		*/
		struct CSPRJ_API FImplSlice final : public IData
		{
		public:

			static const FName Name;

		private:
			
			// ICsGetInterfaceMap

			/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition) 
				that describe the data. */
			FCsInterfaceMap* InterfaceMap;

			// ProjectileDataType (NCsProjectile::NData::IData)

			CS_DECLARE_MEMBER_WITH_PROXY(LifeTime, float)
			CS_DECLARE_MEMBER_WITH_PROXY(InitialSpeed, float)
			CS_DECLARE_MEMBER_WITH_PROXY(MaxSpeed, float)
			CS_DECLARE_MEMBER_WITH_PROXY(GravityScale, float)

		public:

			FImplSlice() :
				InterfaceMap(nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(LifeTime, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(InitialSpeed, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxSpeed, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(GravityScale, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(LifeTime);
				CS_CTOR_SET_MEMBER_PROXY(InitialSpeed);
				CS_CTOR_SET_MEMBER_PROXY(MaxSpeed);
				CS_CTOR_SET_MEMBER_PROXY(GravityScale);
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

		// ICsData_Projectile
		#pragma region
		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LifeTime, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(InitialSpeed, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxSpeed, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(GravityScale, float)

		#pragma endregion ICsData_Projectile

		public:

			static void Deconstruct(void* Ptr)
			{
				delete static_cast<NCsProjectile::NData::FImplSlice*>(Ptr);
			}

			static FImplSlice* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		private:

			static FImplSlice* SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& DataName, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
		};
	}
}