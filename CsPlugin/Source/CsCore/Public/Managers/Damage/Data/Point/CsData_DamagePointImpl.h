// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Type
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
// Data
#include "Managers/Damage/Data/CsData_Damage.h"
// Log
#include "Utility/CsLog.h"

#include "CsData_DamagePointImpl.generated.h"
#pragma once

// NCsDamage::NData::NPoint::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NData, NPoint, FImpl)

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_DamagePointImpl
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsDamageType Type;

	FCsData_DamagePointImpl() :
		Value(0.0f),
		Type()
	{
	}

#define PointType NCsDamage::NData::NPoint::FImpl
	void CopyToPoint(PointType* Point);
	void CopyToPointAsValue(PointType* Point) const;
#undef PointType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
		#define DataType NCsDamage::NData::IData

			/**
			*
			*/
			struct CSCORE_API FImpl : public DataType
			{
			public:

				static const FName Name;

			#define ValueType NCsDamage::NValue::IValue
			#define ValueImplType NCsDamage::NValue::NPoint::FImpl

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				// DataType (NCsDamage::NData::IData)

				ValueImplType Value;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageType)

			public:

				FImpl();
				~FImpl();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				FORCEINLINE void SetValue(const float& InValue) { Value.SetValue(InValue); }
				FORCEINLINE void SetValue(float* InValue) { Value.SetValue(InValue); }

			// DataType (NCsDamage::NData::IData)
			#pragma region
			public:

				FORCEINLINE const ValueType* GetValue() const { return &Value; }
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageType)

			#pragma endregion DataType (NCsDamage::NData::IData)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			#undef ValueType
			#undef ValueImplType
			};

		#undef DataType
		}
	}
}