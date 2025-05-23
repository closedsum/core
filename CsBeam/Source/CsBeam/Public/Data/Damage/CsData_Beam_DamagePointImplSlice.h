// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
// Data
#include "Data/Damage/CsData_Beam_Damage.h"
#include "Managers/Damage/Data/Point/CsData_DamagePointImpl.h"
// Log
#include "Utility/CsBeamLog.h"

#include "CsData_Beam_DamagePointImplSlice.generated.h"

// NCsBeam::NData::NDamage::NPoint::NImplSlice::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsBeam, NData, NDamage, NPoint, NImplSlice, FImplSlice)

/**
* Represents a "slice" of data, BeamDamageDataType (NCsBeam::NDamage::NDamage::IDamage) which is 
* specialized as a Damage Point.
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsData_Beam_DamagePointImplSlice
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data|Damage|Point")
	FCsData_DamagePoint Damage;

public:

	FCsData_Beam_DamagePointImplSlice() :
		Damage()
	{
	}

	using SliceType = NCsBeam::NData::NDamage::NPoint::NImplSlice::FImplSlice;

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

namespace NCsBeam
{
	namespace NData
	{
		namespace NDamage
		{
			namespace NPoint
			{
				namespace NImplSlice
				{
					using BeamDamageDataType = NCsBeam::NData::NDamage::IDamage;

					/**
					* Represents a "slice" of data, BeamDamageDataType (NCsBeam::NDamage::NDamage::IDamage)
					* which is specialized as a Damage Point.
					* 
					* If members are set via points to an "owning" data, then
					* "Emulates" BeamDamageDataType (NCsBeam::NDamage::NDamage::IDamage) by mimicking 
					* the interfaces and having pointers to the appropriate members. 
					* 
					* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
					* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
					*/
					struct CSBEAM_API FImplSlice : public BeamDamageDataType
					{
					public:

						static const FName Name;

					private:

						using DamageDataType = NCsDamage::NData::IData;
						using DamageDataImplType = NCsDamage::NData::NPoint::NImpl::FImpl;

					private:

						// ICsGetInterfaceMap

						/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
						FCsInterfaceMap* InterfaceMap;

						// BeamDamageDataType (NCsBeam::NDamage::NDamage::IDamage)

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

					// BeamDamageDataType (NCsBeam::NDamage::NDamage::IDamage)
					#pragma region
					public:

						FORCEINLINE DamageDataType* GetDamageData() const { return const_cast<DamageDataImplType*>(&DamageData); }

					#pragma endregion BeamDamageDataType (NCsBeam::NDamage::NDamage::IDamage)

					public:

						static void Deconstruct(void* Ptr)
						{
							delete static_cast<NCsBeam::NData::NDamage::NPoint::NImplSlice::FImplSlice*>(Ptr);
						}

						static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
					};
				}
			}
		}
	}
}