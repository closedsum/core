// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Interface
#include "Data/CsData.h"
#include "Data/CsData_StatusEffect.h"
#include "Data/Damage/CsData_StatusEffect_Damage.h"
#include "Data/Trigger/CsData_StatusEffect_Trigger.h"
// Types
#include "Types/CsTypes_StatusEffect.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
// Damage
#include "Managers/Damage/Data/Point/CsData_DamagePointImpl.h"

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
		#define SeDataType NCsStatusEffect::NData::IData
		#define DamageSeDataType NCsStatusEffect::NData::NDamage::IDamage

			/**
			* "Emulates" UCsData_StatusEffect_DamagePoint by mimicking the interfaces and having pointers to the appropriate
			* members. The idea behind this struct is to keep the code a cleaner and more readable.
			*/
			struct CSSE_API FPointProxy : public DataType,
									      public SeDataType,
										  public DamageSeDataType
			{
			public:

				static const FName Name;

			#define TriggerFrequencyParamsType NCsStatusEffect::NTrigger::NFrequency::FParams
			#define TransferFrequencyParamsType NCsStatusEffect::NTransfer::NFrequency::FParams
			#define DamageDataType NCsDamage::NData::IData

			private:

				UObject* Outer;

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				// SeDataType (NCsStatusEffect::NData::IData)

				bool* bPersistent;

				TArray<FECsStatusEffect>* Children;

				TArray<FECsStatusEffect>* StatusEffectsToRemove;

				FECsStatusEffectTriggerCondition* TriggerCondition;

				TriggerFrequencyParamsType* TriggerFrequencyParams;

				TransferFrequencyParamsType* TransferFrequencyParams;

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

				FORCEINLINE void SetIsPersistent(bool* Value) { bPersistent = Value; }
				FORCEINLINE void SetChildren(TArray<FECsStatusEffect>* Value) { Children = Value; }
				FORCEINLINE void SetStatusEffectsToRemove(TArray<FECsStatusEffect>* Value) { StatusEffectsToRemove = Value; }

				FORCEINLINE void SetTriggerCondition(FECsStatusEffectTriggerCondition* Value) { TriggerCondition = Value; }
				FORCEINLINE void SetTriggerFrequencyParams(TriggerFrequencyParamsType* Value) { TriggerFrequencyParams = Value; }
				FORCEINLINE void SetTransferFrequencyParams(TransferFrequencyParamsType* Value) { TransferFrequencyParams = Value; }
				
			// SeDataType (NCsStatusEffect::NData::IData)
			#pragma region
			public:

				FORCEINLINE const bool& IsPersistent() const { return *bPersistent; }
				FORCEINLINE const TArray<FECsStatusEffect>& GetChildren() const { return *Children; }
				FORCEINLINE const TArray<FECsStatusEffect>& GetStatusEffectsToRemove() const { return *StatusEffectsToRemove; }

				FORCEINLINE const FECsStatusEffectTriggerCondition& GetTriggerCondition() const { return *TriggerCondition; }
				FORCEINLINE const TriggerFrequencyParamsType& GetTriggerFrequencyParams() const { return *TriggerFrequencyParams; }
				FORCEINLINE const TransferFrequencyParamsType& GetTransferFrequencyParams() const { return *TransferFrequencyParams; }
				
			#pragma endregion SeDataType (NCsStatusEffect::NData::IData)

			public:

				FORCEINLINE void SetDamageData(DamageDataType* Value) { DamageData = Value; }

			// DamageSeDataType (NCsStatusEffect::NData::NDamage::IDamage)
			#pragma region
			public:

				FORCEINLINE DamageDataType* GetDamageData() const { return DamageData; }

			#pragma endregion DamageSeDataType (NCsStatusEffect::NData::NDamage::IDamage)

			#undef TriggerFrequencyParamsType
			#undef TransferFrequencyParamsType
			#undef DamageDataType
			};

		#undef DataType
		#undef SeDataType
		#undef DamageSeDataType
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

	/** Whether the Status EFfect should remain on the object or in the world. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPersistent;

	/** Additional Status Effects to apply when the current Status Effect based on this
		data is applied. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FECsStatusEffect> Children;

	/** Status Effects to remove when the current Status Effect based on this data is applied. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FECsStatusEffect> StatusEffectsToRemove;

	/** How the status effect will get triggered. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FECsStatusEffectTriggerCondition TriggerCondition;

	/** Parameters that describes the frequency the status effect is
		triggered. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsStatusEffect_TriggerFrequencyParams TriggerFrequencyParams;

	/**  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsStatusEffect_TransferFrequencyParams TransferFrequencyParams;

// ICsData_StatusEffect
#pragma region
public:

	FORCEINLINE const bool& IsPersistent() const { return bPersistent; }
	FORCEINLINE const TArray<FECsStatusEffect>& GetChildren() const { return Children; }
	FORCEINLINE const TArray<FECsStatusEffect>& GetStatusEffectsToRemove() const { return StatusEffectsToRemove; }

	FORCEINLINE const FECsStatusEffectTriggerCondition& GetTriggerCondition() const { return TriggerCondition; }
	FORCEINLINE const FCsStatusEffect_TriggerFrequencyParams& GetTriggerFrequencyParams() const { return TriggerFrequencyParams; }
	FORCEINLINE const FCsStatusEffect_TransferFrequencyParams& GetTransferFrequencyParams() const { return TransferFrequencyParams; }

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