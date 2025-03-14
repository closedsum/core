// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Namespace.h"
#include "CsTypes_ConsoleCommand.h"

#include "CsCoordinator_ConsoleCommand.generated.h"

class ICsGetCoordinatorConsoleCommand;

// NCsConsoleCommand::NManager::IManager
CS_FWD_DECLARE_CLASS_NAMESPACE_2(NCsConsoleCommand, NManager, IManager)

UCLASS()
class CSCONSOLECOMMAND_API UCsCoordinator_ConsoleCommand : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	using HandleType = NCsConsoleCommand::NManager::FHandle;
	using ManagerType = NCsConsoleCommand::NManager::IManager;
	using InfoType = NCsConsoleCommand::FInfo;

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsCoordinator_ConsoleCommand* Get(UObject* InRoot = nullptr);
#else
	static UCsCoordinator_ConsoleCommand* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static bool IsValid(UObject* InRoot = nullptr);
#else
	static bool IsValid(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? false : s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetCoordinatorConsoleCommand* Get_GetCoordinatorConsoleCommand(UObject* InRoot);
	static ICsGetCoordinatorConsoleCommand* GetSafe_GetCoordinatorConsoleCommand(UObject* Object);

	static UCsCoordinator_ConsoleCommand* GetSafe(UObject* Object);

public:

	static UCsCoordinator_ConsoleCommand* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	virtual void CleanUp();

private:
	// Singleton data
	static UCsCoordinator_ConsoleCommand* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

public:

	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog);

private:

	TMap<HandleType, ManagerType*> ManagerMap;

public:

	HandleType AddManager(ManagerType* Manager);

	void OnDeconstructManager(ManagerType* Manager, const HandleType& Handle);

	void RemoveManager(const HandleType& Handle);

	void GetCategories(TArray<FString>& OutCategories);

	const TArray<InfoType>* GetConsoleCommandInfos(const FString& Category);
};