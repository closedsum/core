// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Interface
#include "Data/CsData.h"
#include "Data/CsData_StatusEffect.h"
#include "Data/Damage/CsData_StatusEffect_Damage.h"
#include "Data/Trigger/CsData_StatusEffect_Trigger.h"
// Types
#include "CsTypes_StatusEffect.h"
#include "Managers/Damage/Data/Shape/CsTypes_Data_DamageShape.h"
#include "CsData_StatusEffect_DamageSphere.generated.h"

// Proxy
#pragma region

struct FCsInterfaceMap;

// NCsDamage::NData::IData
namespace NCsDamage {
	namespace NData {
		struct IData; } }

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
			* "Emulates" UCsData_StatusEffect_DamageSphere by mimicking the interfaces and having pointers to the appropriate
			* members. The idea behind this struct is to keep the code a cleaner and more readable.
			*/
			struct CSSE_API FSphereProxy : public DataType,
										   public StatusEffectDataType,
										   public StatusEffectDamageDataType
			{
			public:

				static const FName Name;

			private:

				typedef NCsStatusEffect::NTrigger::FFrequencyParams TriggerFrequencyParamsType;
				typedef NCsStatusEffect::NTransfer::FFrequencyParams TransferFrequencyParamsType;
				typedef NCsDamage::NData::IData DamageDataType;

				UObject* Outer;

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				// NCsStatusEffect::NData::IData

				FECsStatusEffectTriggerCondition* TriggerCondition;

				TriggerFrequencyParamsType* TriggerFrequencyParams;

				TransferFrequencyParamsType* TransferFrequencyParams;

				TArray<StatusEffectDataType*>* Children;

				// NCsStatusEffect::NData::NDamage::IDamage

				DamageDataType* DamageData;

			public:

				FSphereProxy();
				~FSphereProxy();

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

			// NCsStatusEffect::NData::IData
			#pragma region
			public:

				FORCEINLINE const FECsStatusEffectTriggerCondition& GetTriggerCondition() const { return *TriggerCondition; }
				FORCEINLINE const TriggerFrequencyParamsType& GetTriggerFrequencyParams() const { return *TriggerFrequencyParams; }
				FORCEINLINE const TransferFrequencyParamsType& GetTransferFrequencyParams() const { return *TransferFrequencyParams; }
				FORCEINLINE const TArray<StatusEffectDataType*>& GetChildren() const { return *Children; }

			#pragma endregion NCsStatusEffect::NData::IData

			public:

				FORCEINLINE void SetDamageData(DamageDataType* Value) { DamageData = Value; }

			// NCsStatusEffect::NData::NDamage::IDamage
			#pragma region
			public:

				FORCEINLINE DamageDataType* GetDamageData() const { return DamageData; }

			#pragma endregion NCsStatusEffect::NData::NDamage::IDamage
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
namespace NCsDamage {
	namespace NData {
		struct IData; } }

UCLASS(BlueprintType, Blueprintable)
class CSSE_API UCsData_StatusEffect_DamageSphere : public UObject,
												   public ICsData,
												   public ICsData_StatusEffect,
												   public ICsData_StatusEffect_Damage
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

private:

	typedef NCsData::IData DataType;
	typedef NCsDamage::NData::IData DamageDataType;

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

	FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

protected:

	bool bLoaded;

// ICsData
#pragma region
public:

	FORCEINLINE DataType* _getIData() const
	{
		return DataProxy;
	}

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

	FORCEINLINE const FECsStatusEffectTriggerCondition& GetTriggerCondition() const
	{
		return TriggerCondition;
	}

	FORCEINLINE const FCsStatusEffectTriggerFrequencyParams& GetTriggerFrequencyParams() const
	{
		return TriggerFrequencyParams;
	}

	FORCEINLINE const FCsStatusEffectTransferFrequencyParams& GetTransferFrequencyParams() const
	{
		return TransferFrequencyParams;
	}

	FORCEINLINE const TArray<ICsData_StatusEffect*>& GetChildren() const
	{
		return Children;
	}

#pragma endregion ICsData_StatusEffect

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsData_DamageSphere DamageSphere;

	DamageDataType* DamageSphereProxy;

// ICsStatusEffect_Damage
#pragma region
public:

	FORCEINLINE DamageDataType* GetDamageData() const
	{
		return DamageSphereProxy;
	}

#pragma endregion ICsStatusEffect_Damage
};