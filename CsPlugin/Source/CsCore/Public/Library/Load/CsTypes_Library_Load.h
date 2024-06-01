// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/SoftObjectPath.h"

// GetObjectPaths
#pragma region

namespace NCsLoad
{
	struct CSCORE_API FGetObjectPaths
	{
	public:

		FString RootName;
		FString RootDefaultName;

		TArray<FSoftObjectPath> Paths;
		TArray<TArray<FSoftObjectPath>> PathGroups;
		TArray<TSet<FSoftObjectPath>> PathSets;

		TSet<FString> VisitedFunctions;

		TMap<FName, TArray<void*>> VisitedPointers;

		int32 TotalCount;

		FGetObjectPaths();

		void SetRootName(const FString& Name)
		{
			RootName = Name;
			RootDefaultName = TEXT("Default__") + RootName + TEXT("_C");
		}

		void AddPath(const FName& Path)
		{
			AddPath(FSoftObjectPath(Path.ToString()));
		}

		void AddPath(const FSoftObjectPath& SoftPath);

		void AddPaths(const TArray<FName>& Dependencies)
		{
			for (const FName& Path : Dependencies)
			{
				AddPath(Path);
			}
		}

		void Resolve();

		void VisitFunction(const FString& FunctionPath)
		{
			VisitedFunctions.Add(FunctionPath);
		}

		FORCEINLINE bool HasVisitedFunction(const FString& FunctionPath)
		{
			return VisitedFunctions.Contains(FunctionPath);
		}

		void VisitPointer(const FName& StructName, const void* Ptr)
		{
			TArray<void*>& Ptrs = VisitedPointers.FindOrAdd(StructName);
			Ptrs.Add(const_cast<void*>(Ptr));
		}

		FORCEINLINE bool HasVisitedPointer(const FName& StructName, const void* Ptr)
		{
			if (TArray<void*>* Ptrs = VisitedPointers.Find(StructName))
			{
				return Ptrs->Contains(Ptr);
			}
			return false;
		}

		void Print();

		void Reset()
		{
			RootName.Empty();
			RootDefaultName.Empty();
			Paths.Reset(Paths.Max());
			PathGroups.Reset(PathGroups.Max());
		
			for (TSet<FSoftObjectPath>& Set : PathSets)
			{
				Set.Reset();
			}

			VisitedFunctions.Reset();
			VisitedPointers.Reset();
			TotalCount = 0;
		}
	};
}

#pragma endregion GetObjectPaths