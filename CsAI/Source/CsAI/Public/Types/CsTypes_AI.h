// Copyright Studio Sai. All Rights Reserved.
#pragma once
// Component
#include "Navigation/PathFollowingComponent.h"

#include "CsTypes_AI.generated.h"

// FCsAIMoveRequest
#pragma region

class AActor;
class UNavigationQueryFilter;

USTRUCT(BlueprintType)
struct CSAI_API FCsAIMoveRequest
{
	GENERATED_USTRUCT_BODY()

public:

	/** move goal: actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	AActor* GoalActor;

	/** move goal: location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	FVector GoalLocation;

	/** pathfinding: navigation filter to use */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	TSubclassOf<UNavigationQueryFilter> FilterClass;

	/** move goal is an actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bInitialized;

	/** move goal is an actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bMoveToActor;

	/** pathfinding: if set - regular pathfinding will be used, if not - direct path between two points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bUsePathfinding;

	/** pathfinding: allow using incomplete path going toward goal but not reaching it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bAllowPartialPath;

	/** pathfinding: goal location will be projected on navigation data before use */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bProjectGoalOnNavigation;

	/** pathfollowing: acceptance radius needs to be increased by agent radius (stop on overlap vs exact point) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bReachTestIncludesAgentRadius;

	/** pathfollowing: acceptance radius needs to be increased by goal actor radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bReachTestIncludesGoalRadius;

	/** pathfollowing: keep focal point at move goal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	bool bCanStrafe;

	/** pathfollowing: required distance to goal to complete move */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	float AcceptanceRadius;

	/** custom user data: flags */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	int32 UserFlags;

	FCsAIMoveRequest() :
		GoalActor(nullptr),
		GoalLocation(FLT_MAX),
		FilterClass(nullptr),
		bInitialized(false),
		bMoveToActor(false),
		bUsePathfinding(true),
		bAllowPartialPath(true),
		bProjectGoalOnNavigation(true),
		bReachTestIncludesAgentRadius(true),
		bReachTestIncludesGoalRadius(true),
		bCanStrafe(false),
		AcceptanceRadius(-1.0f),
		UserFlags(0)
	{
	}

	void CopyTo(FAIMoveRequest& Request) const
	{
		if (GoalActor)
			Request.SetGoalActor(GoalActor);
		else
			Request.SetGoalLocation(GoalLocation);

		Request.SetNavigationFilter(FilterClass);
		Request.SetUsePathfinding(bUsePathfinding);
		Request.SetAllowPartialPath(bAllowPartialPath);
		Request.SetProjectGoalLocation(bProjectGoalOnNavigation);
		Request.SetReachTestIncludesAgentRadius(bReachTestIncludesAgentRadius);
		Request.SetReachTestIncludesGoalRadius(bReachTestIncludesGoalRadius);
		Request.SetCanStrafe(bCanStrafe);
		Request.SetAcceptanceRadius(AcceptanceRadius);
		Request.SetUserFlags(UserFlags);
	}
};

#pragma endregion FCsAIMoveRequest

// FCsPathFollowingRequestResult
#pragma region

USTRUCT(BlueprintType)
struct CSAI_API FCsPathFollowingRequestResult
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	FAIRequestID MoveId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsAI|Move")
	TEnumAsByte<EPathFollowingRequestResult::Type> Code;

	FCsPathFollowingRequestResult() :
		MoveId(),
		Code(EPathFollowingRequestResult::Failed)
	{
	}
};

#pragma endregion FCsPathFollowingRequestResult

UENUM(BlueprintType)
enum class ECsPathFollowingVelocityMode : uint8
{
	Reset	UMETA(DisplayName = "Reset"),
	Keep	UMETA(DisplayName = "Keep")
};