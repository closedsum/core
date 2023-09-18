// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_AI.h"

#include "CsScriptLibrary_PathFollowingComponent.generated.h"

class UPathFollowingComponent;

UCLASS()
class CSAI_API UCsScriptLibrary_PathFollowingComponent : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** 
	* aborts following path
	*  Call Component->AbortMove()
	* 
	* @param Context	The calling context.
	* @param Component
	* @param Instigator
	* @param AbortFlags
	* @param RequestID
	* @param VelocityMode
	* return				Whether Component->AbortMove() was called or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsAI|Component|Library", meta = (AutoCreateRefTerm="Context,AbortFlags,RequestID,VelocityMode"))
	static bool AbortMove(const FString& Context, UPathFollowingComponent* Component, UObject* Instigator, const int32& AbortFlags, const FAIRequestID& RequestID, const ECsPathFollowingVelocityMode& VelocityMode = ECsPathFollowingVelocityMode::Reset);

// FPathFollowingResultFlags
#pragma region
public:

	/**
	* (0)
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_None()
	{
		return FPathFollowingResultFlags::None;
	}

	/**
	* EPathFollowingResult::Success (1 << 0)
	*  Reached destination 
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_Success()
	{
		return FPathFollowingResultFlags::Success;
	}

	/**
	* EPathFollowingResult::Blocked (1 << 1)
	*  Movement was blocked
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_Blocked()
	{
		return FPathFollowingResultFlags::Blocked;
	}

	/**
	* EPathFollowingResult::OffPath (1 << 2)
	*  Agent is not on path
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_OffPath()
	{
		return FPathFollowingResultFlags::OffPath;
	}

	/**
	* EPathFollowingResult::Aborted (1 << 3)
	*  Aborted
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_Aborted()
	{
		return FPathFollowingResultFlags::UserAbort;
	}

	/**
	* (1 << 4)
	*  Abort details: owner no longer wants to move
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_OwnerFinished()
	{
		return FPathFollowingResultFlags::OwnerFinished;
	}

	/**
	* (1 << 5)
	*  Abort details: path is no longer valid 
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_InvalidPath()
	{
		return FPathFollowingResultFlags::InvalidPath;
	}

	/**
	* (1 << 6)
	*  Abort details: unable to move
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_MovementStop()
	{
		return FPathFollowingResultFlags::MovementStop;
	}

	/**
	* (1 << 7)
	*  Abort details: new movement request was received
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_NewRequest()
	{
		return FPathFollowingResultFlags::NewRequest;
	}

	/**
	* (1 << 8)
	*  Abort details: blueprint MoveTo function was called
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_ForcedScript()
	{
		return FPathFollowingResultFlags::ForcedScript;
	}

	/**
	* (1 << 9)
	*  Finish details: never started, agent was already at goal
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_AlreadyAtGoal()
	{
		return FPathFollowingResultFlags::AlreadyAtGoal;
	}

	/**
	* (1 << 10)
	*  Can be used to create project specific reasons 
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_FirstGameplayFlagShift()
	{
		return FPathFollowingResultFlags::FirstGameplayFlagShift;
	}

	/**
	* (~(Success | Blocked | OffPath))
	*/
	UFUNCTION(BlueprintPure, Category = "CsAI|Component|Library")
	static int32 GetResultFlags_UserAbortFlagMask()
	{
		return FPathFollowingResultFlags::UserAbortFlagMask;
	}

#pragma endregion FPathFollowingResultFlags
};