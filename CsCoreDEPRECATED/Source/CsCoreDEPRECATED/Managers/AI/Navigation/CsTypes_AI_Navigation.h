// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/Navigation/NavigationTypes.h"
#include "AI/Navigation/NavQueryFilter.h"
#include "NavigationSystem/Public/NavigationSystemTypes.h"
#include "NavigationSystem/Public/NavigationData.h"

#include "CsTypes_AI_Navigation.generated.h"
#pragma once

// Project Point
#pragma region

	// FCsAINavProjectPointRequest
#pragma region

class UObject;
class APawn;
class AAIController;

#define CS_INVALID_AI_NAV_PROJECT_POINT_REQUEST_ID UINT8_MAX

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsAINavProjectPointRequest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	uint8 Id;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TWeakObjectPtr<UObject> Caller;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TWeakObjectPtr<APawn> Pawn;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TWeakObjectPtr<AAIController> Controller;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	FVector Point;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	FVector Extent;

	FSharedConstNavQueryFilter QueryFilter;

	FCsAINavProjectPointRequest() :
		Id(CS_INVALID_AI_NAV_PROJECT_POINT_REQUEST_ID),
		Caller(nullptr),
		Pawn(nullptr),
		Controller(nullptr),
		Point(FVector::ZeroVector),
		Extent(INVALID_NAVEXTENT),
		QueryFilter(NULL)
	{
	}

	void Reset()
	{
		Caller = nullptr;
		Pawn = nullptr;
		Controller = nullptr;
		Point = FVector::ZeroVector;
		Extent = INVALID_NAVEXTENT;
	}

	UObject* GetCaller() const { return Caller.IsValid() ? Caller.Get() : nullptr; }
	template<typename T>
	T* GetCaller() const { return Cast<T>(GetCaller()); }

	APawn* GetPawn() const { return Pawn.IsValid() ? Pawn.Get() : nullptr; }
	template<typename T>
	T* GetPawn() const { return Cast<T>(GetPawn()); }

	AAIController* GetController() const { return Controller.IsValid() ? Controller.Get() : nullptr; }
	template<typename T>
	T* GetController() const { return Cast<T>(GetController()); }
};

#pragma endregion FCsAINavProjectPointRequest

	// FCsAINavProjectPointResponse
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsAINavProjectPointResponse
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	bool bResult;

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	FVector Location;

	FCsAINavProjectPointResponse()
	{
		Reset();
	}

	void Reset()
	{
		bResult = false;
		Location = FVector::ZeroVector;
	}
};

#pragma endregion FCsAINavProjectPointResponse

#pragma endregion Project Point

// Find Path
#pragma region

	// FCsAINavFindPathRequest
#pragma region

class UObject;
class APawn;
class AAIController;
class ANavigationData;

#define CS_INVALID_AI_NAV_FIND_PATH_REQUEST_ID UINT8_MAX

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsAINavFindPathRequest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	uint8 Id;

	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	bool bAsync;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TWeakObjectPtr<UObject> Caller;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TWeakObjectPtr<APawn> Pawn;

	UPROPERTY(BlueprintReadWrite, Category = "Navigation")
	TWeakObjectPtr<AAIController> Controller;

	FPathFindingQuery Query;

	EPathFindingMode::Type Mode;

	FCsAINavFindPathRequest() :
		Id(CS_INVALID_AI_NAV_FIND_PATH_REQUEST_ID),
		bAsync(false),
		Caller(nullptr),
		Pawn(nullptr),
		Controller(nullptr),
		Query(),
		Mode(EPathFindingMode::Regular)
	{
	}

	FORCEINLINE FCsAINavFindPathRequest& operator=(const FCsAINavFindPathRequest& B)
	{
		bAsync = B.bAsync;
		Caller = B.Caller;
		Pawn = B.Pawn;
		Controller = B.Controller;
		CopyQuery(B.Query);
		Mode = B.Mode;
		return *this;
	}

	void Reset()
	{
		bAsync = false;
		Caller = nullptr;
		Pawn = nullptr;
		Controller = nullptr;
		Mode = EPathFindingMode::Regular;

		Query.Owner = nullptr;
		Query.NavData = nullptr;
		Query.PathInstanceToFill = nullptr;
		CopyNavAgentProperties(FNavAgentProperties::DefaultProperties, Query.NavAgentProperties);
	}

	FORCEINLINE void CopyQuery(const FPathFindingQuery& OtherQuery)
	{
		Query.Owner = OtherQuery.Owner;
		Query.StartLocation = OtherQuery.StartLocation;
		Query.EndLocation = OtherQuery.EndLocation;
		Query.QueryFilter = OtherQuery.QueryFilter;
		Query.NavDataFlags = OtherQuery.NavDataFlags;
		Query.bAllowPartialPaths = OtherQuery.bAllowPartialPaths;
		Query.NavData = OtherQuery.NavData;
		Query.PathInstanceToFill = OtherQuery.PathInstanceToFill;
		// FNavAgentProperties
		CopyNavAgentProperties(OtherQuery.NavAgentProperties, Query.NavAgentProperties);
	}

	FORCEINLINE void CopyNavAgentProperties(const FNavAgentProperties& From, FNavAgentProperties& To)
	{
		To.bCanCrouch = From.bCanCrouch;
		To.bCanJump = From.bCanJump;
		To.bCanWalk = From.bCanWalk;
		To.bCanSwim = From.bCanSwim;
		To.bCanFly = From.bCanFly;
		To.AgentRadius = From.AgentRadius;
		To.AgentHeight = From.AgentHeight;
		To.AgentStepHeight = From.AgentStepHeight;
		To.NavWalkingSearchHeightScale = From.NavWalkingSearchHeightScale;
		To.PreferredNavData = From.PreferredNavData;
	}

	void UpdateQuery(const UObject* InOwner, ANavigationData* InNavData, const FVector& Start, const FVector& End)
	{
		Query.Owner = InOwner;
		Query.NavData = InNavData;
		Query.StartLocation = Start;
		Query.EndLocation = End;
	}

	UObject* GetCaller() const { return Caller.IsValid() ? Caller.Get() : nullptr; }
	template<typename T>
	T* GetCaller() const { return Cast<T>(GetCaller()); }

	APawn* GetPawn() const { return Pawn.IsValid() ? Pawn.Get() : nullptr; }
	template<typename T>
	T* GetPawn() const { return Cast<T>(GetPawn()); }

	AAIController* GetController() const { return Controller.IsValid() ? Controller.Get() : nullptr; }
	template<typename T>
	T* GetController() const { return Cast<T>(GetController()); }
};

#pragma endregion FCsAINavFindPathRequest

	// FCsAINavFindPathResponse
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsAINavFindPathResponse
{
	GENERATED_USTRUCT_BODY()

	FPathFindingResult Result;

	FCsAINavFindPathResponse()
	{
		Reset();
	}

	void Reset()
	{
		Result.Path.Reset();
		Result.Result = ENavigationQueryResult::Invalid;
	}
};

#pragma endregion FCsAINavFindPathResponse

#pragma endregion Find Path