// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Managers/CsManager.h"
#include "Managers/Process/CsProcess.h"
#include "CsManager_Process.generated.h"

class FCsManager_Process : public TCsManager_PooledObjects_TMap<FECsProcess, UCsProcess, FCsProcessPayload, 16>
{
private:
	typedef TCsManager_PooledObjects_TMap<FECsProcess, UCsProcess, FCsProcessPayload, 16> Super;

public:
	~FCsManager_Process();

// Interface
#pragma region

	virtual void DeconstructObject(UCsProcess* p) override;
	virtual UCsProcess* ConstructObject(const FECsProcess& e) override;
	virtual FString GetObjectName(UCsProcess* p) override;
	virtual const FString& EnumTypeToString(const FECsProcess &e) override;
	virtual const FString& EnumTypeToString(const int32 &index) override;
	virtual void Log(const FString& log) override;

#pragma endregion Interface
};

UCLASS(transient)
class CSCORE_API UICsManager_Process : public UObject
{
	GENERATED_UCLASS_BODY()

protected:

	FCsManager_Process* Internal;

public:

	static UICsManager_Process* Get();
	template<typename T>
	static T* Get()
	{
		return Cast<T>(Get());
	}

	static void Init();
	static void Shutdown();

protected:

	virtual void Initialize();
	virtual void CleanUp();

public:

	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	void Clear();

	virtual UCsProcess* ConstructObject(const FECsProcess &Type);

	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	void CreatePool(const FECsProcess &Type, const int32 &Size);
	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	void AddToPool(const FECsProcess &Type, UCsProcess* Process);
	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	void AddToActivePool(const FECsProcess &Type, UCsProcess* Process);
	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	void OnTick(const float &DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	int32 GetActivePoolSize(const FECsProcess &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	bool IsExhausted(const FECsProcess &Type);
	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	bool DeAllocate(const FECsProcess &Type, const int32 &Index);
	UFUNCTION(BlueprintCallable, Category = "Manager Process")
	void DeAllocateAll();

	FCsProcessPayload* AllocatePayload();

	//UFUNCTION(BlueprintCallable, Category = "Manager Process")
	virtual UCsProcess* Spawn(const FECsProcess &Type, FCsProcessPayload &Payload);
	virtual UCsProcess* Spawn(const FECsProcess &Type, FCsProcessPayload* Payload);

private:
	// Singleton data
	static UICsManager_Process* s_managerProcessSingleton;
	static bool s_bManagerProcessHasShutdown;
};