// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Managers
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
#include "Managers/Load/CsManagerLoad_Task_LoadObjects.h"

#include "CsManager_Load.generated.h"

// Structs
#pragma region

	// Memory Resource
#pragma region

namespace NCsLoad
{
	namespace NManager
	{
		namespace NTask
		{
			namespace NLoadObjects
			{
			#define TaskType UCsManagerLoad_Task_LoadObjects

				struct CSCORE_API FResource : public TCsResourceContainer<TaskType>
				{
				};

				struct CSCORE_API FManager : public NCsResource::NManager::NPointer::TFixed<TaskType, FResource, 0>
				{
				};

			#undef TaskType
			}
		}
	}
}

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

#define TaskManagerType NCsLoad::NManager::NTask::NLoadObjects::FManager
	TaskManagerType Manager_Tasks;
#undef TaskManagerType

	UPROPERTY()
	TArray<UObject*> Tasks;

#pragma endregion Tasks

public:

	FStreamableManager StreamableManager;

#define PayloadType NCsLoad::NManager::NLoadObjectPaths::FPayload
	FCsLoadHandle LoadObjectPaths(const PayloadType& Payload);
#undef PayloadType
};