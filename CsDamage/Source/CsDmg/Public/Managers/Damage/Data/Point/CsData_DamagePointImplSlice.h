// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsDmgLog.h"
// Data
#include "Managers/Damage/Data/CsData_Damage.h"
// Damage
#include "Value/Point/CsDamageValuePointImpl.h"

#include "CsData_DamagePointImplSlice.generated.h"

// NCsDamage::NData::NPoint::NImplSlice::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NData, NPoint, NImplSlice, FImplSlice)

/**
* Represents a "slice" of data, DamageDataType (NCsDamage::NData::IData).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsData_DamagePointImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// DamageDataType (NCsDamage::NData::IData)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Data|Point")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Data|Point")
	FECsDamageType Type;

	FCsData_DamagePointImplSlice() :
		Value(0.0f),
		Type()
	{
	}

	using SliceType = NCsDamage::NData::NPoint::NImplSlice::FImplSlice;

	SliceType* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);
	SliceType* SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

private:

	SliceType* SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			namespace NImplSlice
			{
				using DataType = NCsDamage::NData::IData;

				/**
				* Represents a "slice" of data, DamageDataType (NCsDamage::NData::IData).
				* 
				* If members are set via points to an "owning" data, then
				* "Emulates" DamageDataType (NCsDamage::NData::IData) by mimicking 
				* the interfaces and having pointers to the appropriate members. 
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSDMG_API FImplSlice final : public DataType
				{
				public:

					static const FName Name;

				private:
			
					using ThisType = NCsDamage::NData::NPoint::NImplSlice::FImplSlice;
					using ValueType = NCsDamage::NValue::IValue;
					using ValueImplType = NCsDamage::NValue::NPoint::FImpl;

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition) 
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// ProjectileDataType (NCsProjectile::NData::IData)

					ValueImplType Value;

					CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageType)

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						Value(),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type)
					{
						CS_CTOR_SET_MEMBER_PROXY(Type);
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

					FORCEINLINE void SetValue(const float& InValue) { Value.SetValue(InValue); }
					FORCEINLINE void SetValue(float* InValue) { Value.SetValue(InValue); }

				// ICsData_Damage
				#pragma region
				public:

					FORCEINLINE const ValueType* GetValue() const { return &Value; }
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageType)

				#pragma endregion ICsData_Damage

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<ThisType*>(Ptr);
					}

					static FImplSlice* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

				private:

					static FImplSlice* SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& DataName, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
				};
			}
		}
	}
}