// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Data
#include "Projectile/Data/Visual/Fire/CsData_ProjectileWeapon_VisualFire.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsData_ProjectileWeapon_VisualFireImplSlice.generated.h"

// NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NData, NVisual, NFire, FImplSlice)

/**
* Represents a "slice" of data, VisualFireDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsData_ProjectileWeapon_VisualFireImplSlice
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsWp|Projectile")
	FCsProjectileWeapon_Fire_VisualParams Params;

public:

	FCsData_ProjectileWeapon_VisualFireImplSlice() :
		Params()
	{
	}

#define SliceType NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
				#define VisualFireDataType NCsWeapon::NProjectile::NData::NVisual::NFire::IFire

					/**
					* Represents a "slice" of data, VisualFireDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire).
					* 
					* If members are set via points to an "owning" data, then
					* "Emulates" VisualFireDataType NCsWeapon::NProjectile::NData::NVisual::NFire::IFire) by mimicking 
					* the interfaces and having pointers to the appropriate members. 
					* 
					* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
					* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
					*/
					struct CSWP_API FImplSlice : public VisualFireDataType
					{
					public:

						static const FName Name;

					#define ParamsType NCsWeapon::NProjectile::NFire::NVisual::FParams

					private:

						// ICsGetInterfaceMap

						/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
						FCsInterfaceMap* InterfaceMap;

					public:

						// VisualFireDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire)

						ParamsType Params;

					public:

						FImplSlice() :
							InterfaceMap(nullptr),
							Params()
						{
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

						FORCEINLINE ParamsType* GetFireVisualParamsPtr() { return &Params; }

					// VisualFireDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire)
					#pragma region
					public:

						FORCEINLINE const ParamsType& GetFireVisualParams() const { return Params; }

					#pragma endregion VisualFireDataType (NCsWeapon::NProjectile::NData::NVisual::NFire::IFire)

					public:

						static void Deconstruct(void* Ptr)
						{
							delete static_cast<NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice*>(Ptr);
						}

						static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef ParamsType
					};

				#undef VisualFireDataType
				}
			}
		}
	}
}