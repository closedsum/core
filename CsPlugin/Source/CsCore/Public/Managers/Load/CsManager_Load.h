// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Managers
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
#include "Managers/Load/CsManagerLoad_Task_LoadObjects.h"
#include "CsManager_Load.generated.h"

// Structs
#pragma region

	// Memory Resource
#pragma region

struct CSCORE_API FCsResource_ManagerLoad_Task_LoadObjects : public TCsResourceContainer<UCsManagerLoad_Task_LoadObjects>
{
};

struct CSCORE_API FCsManager_ManagerLoad_Task_LoadObjects : public TCsManager_ResourcePointerType_Fixed<UCsManagerLoad_Task_LoadObjects, FCsResource_ManagerLoad_Task_LoadObjects, 0>
{
};

#pragma endregion Memory Resource

#pragma endregion Structs

class ICsGetManagerLoad;
class UWorld;

UCLASS(transient)
class CSCORE_API UCsManager_Load : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Load* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Load* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static UCsManager_Load* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Load* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot);

	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerLoad* Get_GetManagerLoad(const UObject* InRoot);
	static ICsGetManagerLoad* GetSafe_GetManagerLoad(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	void Initialize();

public:

	static bool HasInitialized(const UObject* InRoot);

protected:

	void CleanUp();

private:
	// Singleton data
	static UCsManager_Load* s_Instance;
	static bool s_bShutdown;                                      

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Update
#pragma region
public:

	FECsUpdateGroup UpdateGroup;

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion Update

// Tasks
#pragma region
protected:

	FCsManager_ManagerLoad_Task_LoadObjects Manager_Tasks;

	UPROPERTY()
	TArray<UObject*> Tasks;

#pragma endregion Tasks

public:

	FStreamableManager StreamableManager;

	FCsLoadHandle LoadObjectPaths(const FCsManagerLoad_LoadObjectPathsPayload& Payload);
};