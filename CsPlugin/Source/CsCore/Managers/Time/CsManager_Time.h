// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsUpdateGroup.h"
#include "CsManager_Time.generated.h"

class ICsGetManagerTime;

UCLASS()
class CSCORE_API UCsManager_Time : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_Time* Get();
	static void Init();
	static void Shutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerTime* Get_GetManagerTime(UObject* InOwner);

public:

	static UCsManager_Time* Get(UObject* InOwner);
	static void Init(UObject* InOwner);
	static void Shutdown(UObject* InOwner);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Time* s_Instance;
	static bool s_bShutdown;

#pragma endregion Singleton

protected:

	TArray<FCsUpdateGroup> UpdateGroups;

public:

	void Start(const FECsUpdateGroup& Group);

	// Pause
#pragma region
public:

	void Pause(const FECsUpdateGroup& Group);
	void Unpause(const FECsUpdateGroup& Group);

	FORCEINLINE bool IsPaused(const FECsUpdateGroup& Group)
	{
		return UpdateGroups[Group.Value].IsPaused();
	}

#pragma endregion Pause

	// Update
#pragma region
public:

	void Update(const FECsUpdateGroup& Group, const float& DeltaTime);
	void Update(const FECsUpdateGroup& Group, const float& DeltaTime, const float& Time, const float& RealTime);

#pragma endregion Update

	FORCEINLINE const FCsTime& GetTime(const FECsUpdateGroup& Group)
	{
		return UpdateGroups[Group.Value].GetTime();
	}

	FORCEINLINE const FCsDeltaTime& GetScaledDeltaTime(const FECsUpdateGroup& Group)
	{
		return UpdateGroups[Group.Value].GetScaledDeltaTime();
	}
};