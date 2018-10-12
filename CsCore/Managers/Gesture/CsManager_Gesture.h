// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes.h"
#include "Types/CsTypes_Input.h"
#include "CsManager_Gesture.generated.h"

UCLASS(transient)
class CSCORE_API UCsManager_Gesture : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	static UCsManager_Gesture* Get();
	static void Init();
	static void Shutdown();

protected:

	void Initialize();
	void CleanUp();

public:

	void Clear();

	UPROPERTY(BlueprintReadWrite, Category = "Gesture")
	TWeakObjectPtr<UWorld> CurrentWorld;

	UFUNCTION(BlueprintCallable, Category = "Gesture")
	void SetCurrentWorld(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Gesture")
	UWorld* GetCurrentWorld();

	UPROPERTY(BlueprintReadOnly, Category = "Gesture")
	TArray<class UCsGesture*> Gestures;

	UFUNCTION(BlueprintCallable, Category = "Gesture")
	void AddGesture(TSubclassOf<class UCsGesture> GestureClass);

	UFUNCTION(BlueprintCallable, Category = "Gesture")
	UCsGesture* GetGesture(const FECsGestureType &GestureType);
	
	UFUNCTION(BlueprintCallable, Category = "Gesture")
	virtual void ProcessInputs(FCsInputFrame &InputFrame);

private:
	// Singleton data
	static UCsManager_Gesture* s_managerGestureSingleton;
	static bool s_bManagerHasShutdown;
};