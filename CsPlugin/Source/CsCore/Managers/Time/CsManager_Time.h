// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Time/CsTypes_Time.h"
#include "CsManager_Time.generated.h"

UCLASS()
class CSCORE_API UCsManager_Time : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region

public:

	static UCsManager_Time* Get();
	static void Init(UCsManager_Time* Manager);
	static void Shutdown();

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Time* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

protected:

	TArray<FCsTimeGroup> TimeGroups;

public:

	void Start(const FECsTimeGroup& Group);

	// Pause
#pragma region
public:

	void Pause(const FECsTimeGroup& Group);
	void Unpause(const FECsTimeGroup& Group);

	FORCEINLINE bool IsPaused(const FECsTimeGroup& Group)
	{
		return TimeGroups[Group.Value].IsPaused();
	}

#pragma endregion Pause

	// Update
#pragma region
public:

	void Update(const FECsTimeGroup& Group, const float& DeltaTime);
	void Update(const FECsTimeGroup& Group, const float& DeltaTime, const float& Time, const float& RealTime);

#pragma endregion Update

	FORCEINLINE const FCsTime& GetTime(const FECsTimeGroup& Group)
	{
		return TimeGroups[Group.Value].GetTime();
	}

	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime(const FECsTimeGroup& Group)
	{
		return TimeGroups[Group.Value].GetScaledDeltaTime();
	}
};