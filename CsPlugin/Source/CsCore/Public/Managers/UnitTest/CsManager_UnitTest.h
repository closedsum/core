// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Coroutine/CsRoutine.h"
#include "CsManager_UnitTest.generated.h"

class ICsGetManagerUnitTest;
class ICsUnitTestPlan;

UCLASS(transient)
class CSCORE_API UCsManager_UnitTest : public UObject
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;

#pragma endregion UObject Interface

// Singleton
#pragma region
public:

	static UCsManager_UnitTest* Get(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, UObject* InOuter = nullptr);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerUnitTest* Get_GetManagerUnitTest(UObject* InRoot);

#endif // #if WITH_EDITOR

protected:

	void Initialize();
	void CleanUp();

private:
	// Singleton data
	static UCsManager_UnitTest* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
private:

	UObject* MyRoot;

public:

	FORCEINLINE void SetMyRoot(UObject* InRoot)
	{
		MyRoot = InRoot;
	}

	FORCEINLINE const UObject* GetMyRoot() const
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

protected:

	TMap<FName, ICsUnitTestPlan*> PlanMap;
	TArray<ICsUnitTestPlan*> Plans;

// Add
#pragma region
public:

	template<typename UnitTestPlanType>
	void Add()
	{
		static_assert(std::is_base_of<ICsUnitTestPlan, UnitTestPlanType>(), "UCsManager_UnitTest::Add: UnitTestPlayType does NOT implement interface: ICsUnitTestPlan.");

		UnitTestPlanType* Suite = new UnitTestPlanType();

		Add(Suite);
	}

protected:

	void Add(ICsUnitTestPlan* Plan);
	
#pragma endregion Add

// Get
#pragma region
protected:

	ICsUnitTestPlan* CurrentPlan;

public:

	FORCEINLINE const ICsUnitTestPlan* GetCurrentPlan() const
	{
		return CurrentPlan;
	}

#pragma endregion Get

	void Start();
	//void Start(const FName& Name);

protected:

	char Start_Internal(FCsRoutine* R);

// Exec
#pragma region
public:

	UFUNCTION(Exec)
	void StartUnitTestPlans();

#pragma endregion Exec
};