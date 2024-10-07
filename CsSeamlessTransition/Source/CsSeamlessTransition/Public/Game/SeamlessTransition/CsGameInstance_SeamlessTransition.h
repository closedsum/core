// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "CsMacro_Namespace.h"
#include "Game/Types/CsTypes_GameInstance_Transition.h"
#include "Types/CsTypes_SeamlessTransition.h"

#include "CsGameInstance_SeamlessTransition.generated.h"

UINTERFACE(Blueprintable)
class CSSEAMLESSTRANSITION_API UCsGameInstance_SeamlessTransition : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// CsPlayerTransitionCacheType | CacheType (NCsPlayer::NTransition::FCache)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPlayer, NTransition, FCache)

class CSSEAMLESSTRANSITION_API ICsGameInstance_SeamlessTransition
{
	GENERATED_IINTERFACE_BODY()

private:

	typedef NCsGameInstance::NTransition::FParams TransitionParamsType;
	typedef NCsSeamlessTransition::EState StateType;
	typedef NCsPlayer::NTransition::FCache CacheType;

// Transition
public:

	virtual const bool& GetHasPerformedTransition() const = 0;

	virtual void PerformTransition(const TransitionParamsType& Params) = 0;

	virtual CacheType* GetPlayerTransitionCache() const = 0;

// Seamless Transition
public:

	virtual bool IsSeamlessTransitionActive() const = 0;

	virtual void SeamlessTransition_EnableTransitionInProgress() = 0;

	virtual const StateType& GetSeamlessTransitionState() const = 0;

// Player
public:

	virtual const FName& GetPlayerPawnTraveledTag() const = 0;

	virtual void SetPlayerPawnTraveled(const bool& bTraveled) = 0;

	virtual bool HasPlayerPawnTraveled() const = 0;
};