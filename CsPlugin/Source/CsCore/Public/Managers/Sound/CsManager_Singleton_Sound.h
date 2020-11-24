// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Singleton/CsManager_Singleton.h"
// Get Singleton
#include "Managers/Sound/CsGetManagerSound.h"

#include "CsManager_Singleton_Sound.generated.h"

class UCsManager_Sound;

UCLASS()
class CSCORE_API UCsManager_Singleton_Sound : public UCsManager_Singleton,
											  public ICsGetManagerSound
{
	GENERATED_UCLASS_BODY()

// ICsGetManagerSound
#pragma region
protected:

	UPROPERTY()
	UCsManager_Sound* Manager_Sound;

public:

	FORCEINLINE UCsManager_Sound* GetManager_Sound() const
	{
		return Manager_Sound;
	}

	FORCEINLINE void SetManager_Sound(UCsManager_Sound* InManager)
	{
		Manager_Sound = InManager;
	}

#pragma endregion ICsGetManagerSound
};