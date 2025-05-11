// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsAILog.h"

#include "CsTypes_BehaviorTree.generated.h"

// FCsBehaviorTree
#pragma region

class UBehaviorTree;

USTRUCT(BlueprintType)
struct CSAI_API FCsBehaviorTree
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsAI|Behavior Tree")
	TSoftObjectPtr<UBehaviorTree> Tree;

	UPROPERTY(BlueprintReadOnly, Category = "CsAI|Behavior Tree", meta = (Bitmask, BitmaskEnum = "/Script/CsCore.ECsLoadFlags"))
	int32 Tree_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsAI|Behavior Tree")
	UBehaviorTree* Tree_Internal;

public:

	FCsBehaviorTree() :
		Tree(nullptr),
		Tree_LoadFlags(0),
		Tree_Internal(nullptr)
	{
	}

	/**
	* Get the Hard reference to the UBehaviorTree asset.
	*
	* return Behavior Tree
	*/
	FORCEINLINE UBehaviorTree* Get() const { return Tree_Internal; }

	/**
	* Get the pointer to the Hard reference to the UBehaviorTree asset.
	*
	* return Behavior Tree
	*/
	FORCEINLINE UBehaviorTree** GetPtr() { return &Tree_Internal; }

	/**
	* Get the Hard reference to the UBehaviorTree asset.
	*
	* @param Context	The calling context.
	* return			Behavior Tree
	*/
	FORCEINLINE UBehaviorTree* GetChecked(const FString& Context) const
	{
		checkf(Tree.ToSoftObjectPath().IsValid(), TEXT("%s: Tree is NULL."), *Context);
		checkf(Tree_Internal, TEXT("%s: Tree has NOT been loaded from Path @ %s."), *Context, *(Tree.ToSoftObjectPath().ToString()));

		return Tree_Internal;
	}

	/**
	* Get the Hard reference to the UBehaviorTree asset.
	*
	* return Behavior Tree
	*/
	FORCEINLINE UBehaviorTree* GetChecked() const
	{
		checkf(Tree.ToSoftObjectPath().IsValid(), TEXT("FCsBehaviorTree::GetChecked: Tree is NULL."));
		checkf(Tree_Internal, TEXT("FCsBehaviorTree::GetChecked: Tree has NOT been loaded from Path @ %s."), *(Tree.ToSoftObjectPath().ToString()));

		return Tree_Internal;
	}

	/**
	* Safely get the Hard reference to the UBehaviorTree asset.
	*
	* @param Context	The calling context.
	* @param Log		(optional)
	* return			Behavior Tree
	*/
	UBehaviorTree* GetSafe(const FString& Context, void(*Log)(const FString&) = &NCsAI::FLog::Warning) const
	{
		if (!Tree.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Tree is NULL."), *Context));
			return nullptr;
		}

		if (!Tree_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Tree has NOT been loaded from Path @ %s."), *Context, *(Tree.ToSoftObjectPath().ToString())));
		}
		return Tree_Internal;
	}

	/**
	* Safely get the Hard reference to the UBehaviorTree asset.
	*
	* return Behavior Tree
	*/
	UBehaviorTree* GetSafe()
	{
		if (!Tree.ToSoftObjectPath().IsValid())
			return nullptr;
		return Tree_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsAI::FLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsBehaviorTree