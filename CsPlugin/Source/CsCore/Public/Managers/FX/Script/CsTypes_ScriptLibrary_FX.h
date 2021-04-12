// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Spawner/Params/CsTypes_SpawnerParams.h"
#include "Managers/Time/CsTypes_Update.h"

#include "CsTypes_ScriptLibrary_FX.generated.h"
#pragma once

// NCsFX::NSpawn::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NSpawn, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORE_API FCsScriptLibrary_FX_Spawn_Params
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsFX FX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsSpawnerFrequencyParams FrequencyParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsUpdateGroup Group;

	FCsScriptLibrary_FX_Spawn_Params() :
		FX(),
		Actor(nullptr),
		FrequencyParams(),
		Group()
	{
	}

#define ParamsType NCsFX::NSpawn::NParams::FParams
	void CopyParams(ParamsType* Params) const;
#undef ParamsType

	bool IsValid(const FString& Context) const;
	void Update();
	//void OnPostEditChange();
};