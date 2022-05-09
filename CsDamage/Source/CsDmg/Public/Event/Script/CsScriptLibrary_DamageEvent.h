// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Damage.h"

#include "CsScriptLibrary_DamageEvent.generated.h"

/**
* Script Library to access any information from the current damage event (EventType: NCsDamage::NEvent::IEvent)).
* Assumes Object implements the interfaces:
* - ICsReceiveDamage
* - ICsGetCurrentDamageEvent
* Any functions should be called immediately after the following events:
* - Damage_ScriptEvent gets broadcasted during ICsReceiveDamage->Damage and after current damage event is set.
* - RecieveDamage (bRecieveDamage must be true) is called.
* - OverrideDamage (bOverrideDamage must be true) is called.
*/
UCLASS()
class CSDMG_API UCsScriptLibrary_DamageEvent : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* 
	* 
	* @param Context	The calling context.
	* @param Object
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static float GetDamage(const FString& Context, UObject* Object);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Object
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static UObject* GetInstigator(const FString& Context, UObject* Object);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Object
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static UObject* GetCauser(const FString& Context, UObject* Object);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Object
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static FVector GetDamageDirection(const FString& Context, UObject* Object);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Object
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static FECsHitType GetHitType(const FString& Context, UObject* Object);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Object
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static FHitResult GetOrigin(const FString& Context, UObject* Object);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Object
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static FHitResult GetHitResult(const FString& Context, UObject* Object);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Object
	* @param OutObjects	(out)
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Damage|Event", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetIgnoreObjects(const FString& Context, UObject* Object, TArray<UObject*>& OutObjects);
};