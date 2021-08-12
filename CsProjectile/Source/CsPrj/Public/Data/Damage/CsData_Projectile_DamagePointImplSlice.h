// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"
// Data
#include "Data/Damage/CsData_Projectile_Damage.h"
#include "Managers/Damage/Data/CsData_DamagePointImpl.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsData_Projectile_DamagePointImplSlice.generated.h"
#pragma once

// NCsProjectile::NData::NDamage::NPoint::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NData, NDamage, NPoint, FImplSlice)

/**
* Represents a "slice" of data, PrjDamageDataType (NCsProjectile::NDamage::NDamage::IDamage) which is 
* specialized as a Damage Point.
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsData_Projectile_DamagePointImplSlice
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsData_DamagePointImpl Damage;

public:

	FCsData_Projectile_DamagePointImplSlice() :
		Damage()
	{
	}

#define SliceType NCsProjectile::NData::NDamage::NPoint::FImplSlice

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

namespace NCsProjectile
{
	namespace NData
	{
		namespace NDamage
		{
			namespace NPoint
			{
			#define PrjDamageDataType NCsProjectile::NData::NDamage::IDamage

				/**
				* Represents a "slice" of data, PrjDamageDataType (NCsProjectile::NDamage::NDamage::IDamage)
				* which is specialized as a Damage Point.
				* 
				* If members are set via points to an "owning" data, then
				* "Emulates" PrjDamageDataType (NCsProjectile::NDamage::NDamage::IDamage) by mimicking 
				* the interfaces and having pointers to the appropriate members. 
				* 
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSPRJ_API FImplSlice : public PrjDamageDataType
				{
				public:

					static const FName Name;

				#define DamageDataType NCsDamage::NData::IData
				#define DamageDataImplType NCsDamage::NData::NPoint::FImpl

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
					that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// PrjDamageDataType (NCsProjectile::NDamage::NDamage::IDamage)

					DamageDataImplType DamageData;

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						DamageData()
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

					FORCEINLINE DamageDataImplType* GetDamageDataImpl() const { return const_cast<DamageDataImplType*>(&DamageData); }

				// PrjDamageDataType (NCsProjectile::NDamage::NDamage::IDamage)
				#pragma region
				public:

					FORCEINLINE DamageDataType* GetDamageData() const { return const_cast<DamageDataImplType*>(&DamageData); }

				#pragma endregion PrjDamageDataType (NCsProjectile::NDamage::NDamage::IDamage)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsProjectile::NData::NDamage::NPoint::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

				#undef DamageDataType
				#undef DamageDataImplType
				};

			#undef PrjDamageDataType
			}
		}
	}
}