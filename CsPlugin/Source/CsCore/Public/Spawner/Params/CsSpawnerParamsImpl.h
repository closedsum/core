// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsSpawnerParams.h"

#pragma once

struct FCsInterfaceMap;

/**
*/
struct CSCORE_API FCsSpawnerParamsImpl final : public ICsSpawnerParams
{
public:

	static const FName Name;

private:

	FCsInterfaceMap* InterfaceMap;

public:

	// ICsSpawnerParams

	FCsSpawnerCountParams CountParams;

	FCsSpawnerFrequencyParams FrequencyParams;

	float TotalTime;

public:

	FCsSpawnerParamsImpl();
	~FCsSpawnerParamsImpl();

// ICsGetInterfaceMap
#pragma region
public:

	FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
	{
		return InterfaceMap;
	}

#pragma endregion ICsGetInterfaceMap

// ICsSpawnerParams
#pragma region
public:

	FORCEINLINE const FCsSpawnerCountParams& GetCountParams() const
	{
		return CountParams;
	}

	FORCEINLINE const FCsSpawnerFrequencyParams& GetFrequencyParams() const
	{
		return FrequencyParams;
	}

	FORCEINLINE const float& GetTotalTime() const
	{
		return TotalTime;
	}

#pragma endregion ICsSpawnerParams
};