// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsManager.h"
#include "CsManager_FX.generated.h"

UCLASS()
class CSCORE_API ACsManager_FX : public ACsManager
{
	GENERATED_UCLASS_BODY()

	virtual void Shutdown() override;
	virtual void Destroyed() override;
	virtual void CreatePool(const int32 &Size) override;
	virtual void PostActorCreated() override;

	virtual void OnTick(const float &DeltaSeconds) override;

	TSubclassOf<class ACsEmitter> EmitterClass;

	TArray<class ACsEmitter*> ActiveEmitters;

	UPROPERTY()
	TArray<class ACsEmitter*> Pool;

	uint8 PoolIndex;

	class ACsEmitter* Allocate();

	virtual void DeAllocate(const int32 &Index) override;

	class ACsEmitter* Play(struct FCsFxElement* InFX, UObject* Owner, UObject* Parent);
	class ACsEmitter* Play(struct FCsFxElement* InFX, UObject* InOwner);
	class ACsEmitter* Play(struct FCsFxElement* InFX);
	class ACsEmitter* Play(struct FCsFxElement* InFX, UObject* InOwner, const FVector &Location);

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, FCsFxElement* InFX, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, struct FCsFxElement* InFX, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, struct FCsFxElement* InFX, T* InObject, void (T::*OnDeAllocate)());

	template<typename T>
	void Play(class ACsEmitter* OutEmitter, struct FCsFxElement* InFX, UObject* InOwner, const FVector &Location, T* InObject, void (T::*OnDeAllocate)());

#if WITH_EDITOR
	void ToggleEmitterEditorIcons(const bool &Toggle);
#endif // #if WITH_EDITOR
};