// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Data/CsData.h"
#include "Managers/Damage/Data/CsData_Damage.h"
// Damage
#include "Value/Point/CsDamageValuePointImpl.h"
// Log
#include "Utility/CsLog.h"

#include "CsData_DamagePointImpl.generated.h"

// FCsData_DamagePoint
#pragma region

// NCsDamage::NData::NPoint::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NData, NPoint, FImpl)

USTRUCT(BlueprintType)
struct CSDMG_API FCsData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsDamageType Type;

	FCsData_DamagePoint() :
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
		#define DataType NCsData::IData
		#define DamageDataType NCsDamage::NData::IData

			/**
			*
			*/
			struct CSDMG_API FImpl : public DataType,
									 public DamageDataType
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

			// DamageDataType (NCsDamage::NData::IData)
			#pragma region
			public:

				FORCEINLINE const ValueType* GetValue() const { return &Value; }
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageType)

			#pragma endregion DamageDataType (NCsDamage::NData::IData)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			#undef ValueType
			#undef ValueImplType
			};

		#undef DataType
		#undef DamageDataType
		}
	}
}

#pragma endregion FCsData_DamagePoint

struct FCsInterfaceMap;

// NCsDamage::NData::NPoint::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NData, NPoint, FProxy)

/**
* Data for a Damage Point
* 
* Implements the interfaces:
*  ICsData
*  ICsData_Damage
*/
UCLASS(BlueprintType, Blueprintable)
class CSDMG_API UCsData_DamagePointImpl : public UObject,
										  public ICsData,
										  public ICsData_Damage
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

#define DataType NCsData::IData
#define ValueType NCsDamage::NValue::IValue

private:

	DataType* DataProxy;

// UObject Interface
#pragma region
public:

	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

protected:

	bool bLoaded;

private:

	void Init();
	void Reset();

	FCsInterfaceMap* InterfaceMap;

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

#pragma endregion ICsGetInterfaceMap

// ICsData
#pragma region
public:

	FORCEINLINE DataType* _getIData() const { return DataProxy; }

	bool IsValid(const int32& LoadFlags);

	void Load(const int32& LoadFlags);
	
	void Unload();

	bool IsLoaded() const;

#pragma endregion ICsData

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsDamageType Type;

#define DamagePointProxyType NCsDamage::NData::NPoint::FProxy
	DamagePointProxyType* DamageDataPointProxy;
#undef DamagePointProxyType

// ICsData_Damage
#pragma region
public:

	const ValueType* GetValue() const;
	FORCEINLINE const FECsDamageType& GetType() const { return Type; }

#pragma endregion ICsData_Damage

#undef DataType
#undef ValueType
};