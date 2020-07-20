// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Interface
#include "CsStatusEffect.h"
#include "Damage/CsStatusEffect_Damage.h"
// Types
#include "CsTypes_StatusEffect.h"
#include "Managers/Damage/Expression/CsTypes_DamageExpression.h"
#include "CsStatusEffect_DamagePoint.generated.h"

struct FCsInterfaceMap;
class ICsDamageExpression;

UCLASS(BlueprintType, Blueprintable)
class CSSE_API UCsStatusEffect_DamagePoint : public UObject,
											 public ICsStatusEffect,
											 public ICsStatusEffect_Damage
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

	/** * How the status effect will get triggered. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FECsStatusEffectTriggerCondition TriggerCondition;

	/** The frequency the status effect will occur once triggered.
		If ECsStatusEffectTriggerFrequency::Once,
		 Ignore GetCount() and GetInterval().
		If ECsStatusEffectTriggerFrequency::Count,
		 GetCount() should be > 0, if NOT, it will be treated as 
		 ECsStatusEffectTriggerFrequency::Once.
		If ECsStatusEffectTriggerFrequency::Infinite,
		 Ignore GetCount() and GetInterval() should be > 0.0f.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECsStatusEffectTriggerFrequency TriggerFrequency;

	/** Get the number of times to apply the status effect when triggered.
		Only valid if GetTriggerFrequency() == ECsStatusEffectTriggerFrequency::Count.
		Should be > 0. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** Get the delay before applying the status effect when triggered.
		If Delay == 0.0f, the status effect will be applied at a given interval.
		If Delay == 0.0f and Interval == 0.0f, the status will be applied immediately. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	/** Get the time between each status effect being applied when triggered.
		Only valid if,
		ECsStatusEffectTriggerFrequency::Count
		 or
		ECsStatusEffectTriggerFrequency::Infinite */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	TArray<ICsStatusEffect*> Children;

// ICsStatusEffect
#pragma region
public:

	FORCEINLINE const FECsStatusEffectTriggerCondition& GetTriggerCondition() const
	{
		return TriggerCondition;
	}

	FORCEINLINE const ECsStatusEffectTriggerFrequency& GetTriggerFrequency() const
	{
		return TriggerFrequency;
	}

	FORCEINLINE const int32& GetCount() const
	{
		return Count;
	}

	FORCEINLINE const float& GetDelay() const
	{
		return Delay;
	}

	FORCEINLINE const float& GetInterval() const
	{
		return Interval;
	}

	FORCEINLINE const TArray<ICsStatusEffect*>& GetChildren() const
	{
		return Children;
	}

#pragma endregion ICsStatusEffect

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsScriptDamagePoint DamagePoint;

	ICsDamageExpression* DamagePointEmu;

// ICsStatusEffect_Damage
#pragma region
public:

	FORCEINLINE ICsDamageExpression* GetDamageExpression() const
	{
		return DamagePointEmu;
	}

#pragma endregion ICsStatusEffect_Damage
};