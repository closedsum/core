// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsManager.h"
#include "Types/CsTypes_FX.h"
#include "CsManager_FX.generated.h"

UCLASS()
class CSCORE_API ACsManager_FX : public ACsManager
{
	GENERATED_UCLASS_BODY()

	static ACsManager_FX* Get(UWorld* InWorld);

	virtual void Clear() override;
	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const int32 &Size) override;
	virtual void OnTick(const float &DeltaSeconds) override;

	TSubclassOf<class ACsEmitter> EmitterClass;

	TArray<class ACsEmitter*> ActiveEmitters;

	UPROPERTY()
	TArray<class ACsEmitter*> Pool;

	uint8 PoolIndex;

	virtual void LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, class UObject* InObject) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	class ACsEmitter* Allocate();

	virtual void DeAllocate(const int32 &Index) override;

	class ACsEmitter* Play(FCsFxElement* InFX, UObject* InOwner, UObject* InParent);
	class ACsEmitter* Play(FCsFxElement* InFX, UObject* InOwner);
	class ACsEmitter* Play(FCsFxElement* InFX);
	class ACsEmitter* Play(FCsFxElement* InFX, UObject* InOwner, const FVector &Location, const FRotator &Rotation);

	class ACsEmitter* Play(FCsFxElement* InFX, UObject* InOwner, UObject* InParent, const FRotator &Rotation);

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, FCsFxElement* InFX, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, const FVector &Location, const FRotator &Rotation, T* InObject, void (T::*OnDeAllocate)());

	UFUNCTION(BlueprintCallable, Category = "Pool")
	class ACsEmitter* Play_Script(FCsFxElement& InFX, UObject* InOwner, UObject* InParent);
	UFUNCTION(BlueprintCallable, Category = "Pool")
	class ACsEmitter* Play_ScriptEX(FCsFxElement& InFX, UObject* InOwner, const FVector &Location, const FRotator &Rotation);

#if WITH_EDITOR
	void ToggleEmitterEditorIcons(const bool &Toggle);
#endif // #if WITH_EDITOR
};