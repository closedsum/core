// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Interface
#include "Data/CsData.h"
#include "Data/CsData_StatusEffect.h"
#include "Data/Damage/CsData_StatusEffect_Damage.h"
// Types
#include "CsTypes_StatusEffect.h"
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"

#include "CsData_StatusEffect_DamagePoint.generated.h"

// Proxy
#pragma region

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NDamage
		{
#define DataType NCsData::IData
#define StatusEffectDataType NCsStatusEffect::NData::IData
#define StatusEffectDamageDataType NCsStatusEffect::NData::NDamage::IDamage

			/**
			* "Emulates" UCsData_StatusEffect_DamagePoint by mimicking the interfaces and having pointers to the appropriate
			* members. The idea behind this struct is to keep the code a cleaner and more readable.
			*/
			struct CSSE_API FPointProxy : public DataType,
										public StatusEffectDataType,
										public StatusEffectDamageDataType
			{
			public:

				static const FName Name;

			#define TriggerFrequencyParamsType NCsStatusEffect::NTrigger::FFrequencyParams
			#define TransferFrequencyParamsType NCsStatusEffect::NTransfer::FFrequencyParams
			#define DamageDataType NCsDamage::NData::IData

			private:

				UObject* Outer;

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				// StatusEffectDataType (NCsStatusEffect::NData::IData)

				FECsStatusEffectTriggerCondition* TriggerCondition;

				TriggerFrequencyParamsType* TriggerFrequencyParams;

				TransferFrequencyParamsType* TransferFrequencyParams;

				TArray<StatusEffectDataType*>* Children;

				// StatusEffectDamageDataType (NCsStatusEffect::NData::NDamage::IDamage)

				DamageDataType* DamageData;

			public:

				FPointProxy();
				~FPointProxy();

				FORCEINLINE void SetOuter(UObject* InOuter) { Outer = InOuter; }

				FORCEINLINE UObject* _getUObject() const { return Outer; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				FORCEINLINE void SetTriggerCondition(FECsStatusEffectTriggerCondition* Value) { TriggerCondition = Value; }
				FORCEINLINE void SetTriggerFrequencyParams(TriggerFrequencyParamsType* Value) { TriggerFrequencyParams = Value; }
				FORCEINLINE void SetTransferFrequencyParams(TransferFrequencyParamsType* Value) { TransferFrequencyParams = Value; }
				FORCEINLINE void SetChildren(TArray<StatusEffectDataType*>* Value) { Children = Value; }

			// StatusEffectDataType (NCsStatusEffect::NData::IData)
			#pragma region
			public:

				FORCEINLINE const FECsStatusEffectTriggerCondition& GetTriggerCondition() const { return *TriggerCondition; }
				FORCEINLINE const TriggerFrequencyParamsType& GetTriggerFrequencyParams() const { return *TriggerFrequencyParams; }
				FORCEINLINE const TransferFrequencyParamsType& GetTransferFrequencyParams() const { return *TransferFrequencyParams; }
				FORCEINLINE const TArray<StatusEffectDataType*>& GetChildren() const { return *Children; }

			#pragma endregion StatusEffectDataType (NCsStatusEffect::NData::IData)

			public:

				FORCEINLINE void SetDamageData(DamageDataType* Value) { DamageData = Value; }

			// StatusEffectDamageDataType (NCsStatusEffect::NData::NDamage::IDamage)
			#pragma region
			public:

				FORCEINLINE DamageDataType* GetDamageData() const { return DamageData; }

			#pragma endregion StatusEffectDamageDataType (NCsStatusEffect::NData::NDamage::IDamage)

			#undef TriggerFrequencyParamsType
			#undef TransferFrequencyParamsType
			#undef DamageDataType
			};

#undef DataType
#undef StatusEffectDataType
#undef StatusEffectDamageDataType
		}
	}
}

#pragma endregion Proxy

struct FCsInterfaceMap;

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

UCLASS(BlueprintType, Blueprintable)
class CSSE_API UCsData_StatusEffect_DamagePoint : public UObject,
												  public ICsData,
												  public ICsData_StatusEffect,
												  public ICsData_StatusEffect_Damage
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

#define DataType NCsData::IData
#define DamageDataType NCsDamage::NData::IData

private:

	DataType* DataProxy;

// UObject Interface
#pragma region
public:

	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

private:

	void Init();

	FCsInterfaceMap* InterfaceMap;

// ICsGetInterfaceMap
#pragma region
public:

	FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

#pragma endregion ICsGetInterfaceMap

protected:

	bool bLoaded;

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

	/** How the status effect will get triggered. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FECsStatusEffectTriggerCondition TriggerCondition;

	/** Parameters that describes the frequency the status effect is
		triggered. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsStatusEffectTriggerFrequencyParams TriggerFrequencyParams;

	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsStatusEffectTransferFrequencyParams TransferFrequencyParams;

	TArray<ICsData_StatusEffect*> Children;

// ICsData_StatusEffect
#pragma region
public:

	FORCEINLINE const FECsStatusEffectTriggerCondition& GetTriggerCondition() const { return TriggerCondition; }
	FORCEINLINE const FCsStatusEffectTriggerFrequencyParams& GetTriggerFrequencyParams() const { return TriggerFrequencyParams; }
	FORCEINLINE const FCsStatusEffectTransferFrequencyParams& GetTransferFrequencyParams() const { return TransferFrequencyParams; }
	FORCEINLINE const TArray<ICsData_StatusEffect*>& GetChildren() const { return Children; }

#pragma endregion ICsStatusEffect

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsData_DamagePoint DamagePoint;

	DamageDataType* DamagePointProxy;

// ICsStatusEffect_Damage
#pragma region
public:

	FORCEINLINE DamageDataType* GetDamageData() const { return DamagePointProxy; }

#pragma endregion ICsStatusEffect_Damage

#undef DataType
#undef DamageDataType
};