// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Data/ICsData.h"
#include "Managers/Damage/Data/CsData_Damage.h"
// Damage
#include "Value/Point/CsDamageValuePointImpl.h"
// Log
#include "Utility/CsDmgLog.h"

#include "CsData_DamagePointImpl.generated.h"

// FCsData_DamagePoint
#pragma region

// NCsDamage::NData::NPoint::NImpl::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NData, NPoint, NImpl, FImpl)

USTRUCT(BlueprintType)
struct CSDMG_API FCsData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Data|Point")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Data|Point")
	FECsDamageType Type;

	FCsData_DamagePoint() :
		Value(0.0f),
		Type()
	{
	}

	using PointImplType = NCsDamage::NData::NPoint::NImpl::FImpl;

	void CopyToPoint(PointImplType* Point);
	void CopyToPointAsValue(PointImplType* Point) const;

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			namespace NImpl
			{
				using DamageDataType = NCsDamage::NData::IData;

				/**
				*
				*/
				struct CSDMG_API FImpl : public CsDataType,
										 public DamageDataType
				{
				public:

					static const FName Name;

				private:

					using ValueType = NCsDamage::NValue::IValue;
					using ValueImplType = NCsDamage::NValue::NPoint::FImpl;

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
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
				};
			}
		}
	}
}

#pragma endregion FCsData_DamagePoint

struct FCsInterfaceMap;

// DamagePointProxyType (NCsDamage::NData::NPoint::NProxy::FProxy)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NData, NPoint, NProxy, FProxy)

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

private:

	using ValueType = NCsDamage::NValue::IValue;
	using DamagePointProxyType = NCsDamage::NData::NPoint::NProxy::FProxy;

private:

	CsDataType* DataProxy;

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

	FORCEINLINE CsDataType* _getIData() const { return DataProxy; }

	bool IsValid(const int32& LoadFlags);

	void Load(const int32& LoadFlags);
	
	void TopLoad();

	void Unload();

	bool IsLoaded() const;

#pragma endregion ICsData

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Data|Point", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Data|Point")
	FECsDamageType Type;

	DamagePointProxyType* DamageDataPointProxy;

// ICsData_Damage
#pragma region
public:

	const ValueType* GetValue() const;
	FORCEINLINE const FECsDamageType& GetType() const { return Type; }

#pragma endregion ICsData_Damage
};