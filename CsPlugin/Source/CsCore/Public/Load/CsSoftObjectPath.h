// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Load/CsObjectPathDependencyGroup.h"
#include "Load/CsResourceSize.h"
// Log
#include "Utility/CsLog.h"

#include "CsSoftObjectPath.generated.h"

// FCsSoftObjectPath
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSoftObjectPath
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FSoftObjectPath Path;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsResourceSize Size;

	FCsSoftObjectPath() :
		Path(),
		Size()
	{
	}

	FORCEINLINE bool operator==(const FCsSoftObjectPath& B) const
	{
		return Path.GetAssetPath() == B.Path.GetAssetPath() && Path.GetSubPathString() == B.Path.GetSubPathString();
	}

	FORCEINLINE bool operator!=(const FCsSoftObjectPath& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("[%s] @ %s"), *(Size.ToString()), *(Path.ToString()));
	}

	FORCEINLINE friend uint32 GetTypeHash(FCsSoftObjectPath const& This)
	{
		return GetTypeHash(This.Path);
	}
};

#pragma endregion FCsSoftObjectPath

// FCsTArraySoftObjectPath
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArraySoftObjectPath
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CsCore|Load")
	TArray<FCsSoftObjectPath> Paths;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	TSet<FCsSoftObjectPath> Set;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	TArray<FSoftObjectPath> Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	TSet<FSoftObjectPath> InternalSet;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsResourceSize Size;

	FCsTArraySoftObjectPath() :
		Paths(),
		Set(),
		Internal(),
		InternalSet(),
		Size()
	{
	}

	void Reset()
	{
		Paths.Reset(Paths.Max());
		Set.Reset();
		Internal.Reset(Internal.Max());
		InternalSet.Reset();
		Size.Reset();
	}

	void BuildFromPaths()
	{
		for (const FCsSoftObjectPath& Path : Paths)
		{
			Set.Add(Path);
			InternalSet.Add(Path.Path);
		}
		
		// Reset Paths since there could be duplicates
		Paths.Reset(Paths.Max());
		Internal.Reset(Paths.Max());

		for (const FCsSoftObjectPath& Path : Set)
		{
			Paths.Add(Path);
			Internal.Add(Path.Path);
		}
		CalculateSize();
	}

#if WITH_EDITOR
	
	void BuildFromSet()
	{
		const int32 Count = Set.Num();

		Paths.Reset(Count);
		Internal.Reset(Count);
		InternalSet.Reset();

		for (const FCsSoftObjectPath& Path : Set)
		{
			Paths.Add(Path);
			Internal.Add(Path.Path);
			InternalSet.Add(Path.Path);
		}
		CalculateSize();
	}

#endif // #if WITH_EDITOR

	FORCEINLINE void CalculateSize()
	{
		Size.Reset();

		for (const FCsSoftObjectPath& Path : Paths)
		{
			Size += Path.Size;
		}
	}

#if WITH_EDITOR

	void Populate(UObject* O, const FSoftObjectPath& Path, bool bLog = true);
	void Populate(const TSet<FSoftObjectPath>& InSet, bool bLog = true);

	void Append(const FCsTArraySoftObjectPath& InPaths)
	{
		Set.Append(InPaths.Set);

		BuildFromSet();
	}

#endif // #if WITH_EDITOR
};

#pragma endregion FCsTArraySoftObjectPath

// FCsTArraySoftObjectPathByGroup
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsTArraySoftObjectPathByGroup
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Load")
	FCsTArraySoftObjectPath PathsByGroup[(uint8)ECsObjectPathDependencyGroup::ECsObjectPathDependencyGroup_MAX];

	FCsTArraySoftObjectPathByGroup()
	{
	}

	void Reset()
	{
		for (FCsTArraySoftObjectPath& Paths : PathsByGroup)
		{
			Paths.Reset();
		}
	}
};

#pragma endregion FCsTArraySoftObjectPathByGroup