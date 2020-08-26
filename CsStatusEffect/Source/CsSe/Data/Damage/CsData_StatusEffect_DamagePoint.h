// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Interface
#include "Data/CsData_StatusEffect.h"
#include "Data/Damage/CsData_StatusEffect_Damage.h"
// Types
#include "CsTypes_StatusEffect.h"
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"
#include "CsData_StatusEffect_DamagePoint.generated.h"

struct FCsInterfaceMap;
class ICsData_Damage;

UCLASS(BlueprintType, Blueprintable)
class CSSE_API UCsData_StatusEffect_DamagePoint : public UObject,
												  public ICsData_StatusEffect,
												  public ICsData_StatusEffect_Damage
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

// UObject Interface
#pragma region
public:

	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

private:

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

#pragma endregion ICsStatusEffect

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsScriptData_DamagePoint DamagePoint;

	ICsData_Damage* DamagePointEmu;

// ICsStatusEffect_Damage
#pragma region
public:

	FORCEINLINE ICsData_Damage* GetDamageData() const
	{
		return DamagePointEmu;
	}

#pragma endregion ICsStatusEffect_Damage
};