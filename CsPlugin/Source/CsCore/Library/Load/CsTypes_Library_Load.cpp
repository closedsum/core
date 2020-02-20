// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Load/CsTypes_Library_Load.h"
#include "CsCore.h"

// LoadCodes
#pragma region

namespace NCsLibraryLoad_GetSoftObjectPaths_Code
{
	/*
	namespace Ref
	{
	}
	*/
	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 1;
}

#pragma endregion LoadCodes

// FCsLibraryLoad_GetReferencesReport_Category
#pragma region

void FCsLibraryLoad_GetReferencesReport_Category::Add(const FCsLibraryLoad_MemberInfo& MemberInfo, const FSoftObjectPath& ObjectPath)
{
	MemberInfos.Add(MemberInfo);

	FString& SubPathString = const_cast<FString&>(ObjectPath.GetSubPathString());
	SubPathString.Empty();

	ObjectPaths.Add(ObjectPath);

	if (int32* CountPtr = CountByObjectPath.Find(ObjectPath))
	{
		++(*CountPtr);
	}
	else
	{
		CountByObjectPath.Add(ObjectPath, 1);
	}

	if (TArray<FCsLibraryLoad_MemberInfo>* PathsPtr = MemberInfosByObjectPath.Find(ObjectPath))
	{
		PathsPtr->Add(MemberInfo);
	}
	else
	{
		TArray<FCsLibraryLoad_MemberInfo> Paths;
		Paths.Add(MemberInfo);
		MemberInfosByObjectPath.Add(ObjectPath, Paths);
	}
}

void FCsLibraryLoad_GetReferencesReport_Category::AddUnused(const FCsLibraryLoad_MemberInfo& MemberInfo)
{
	UnusedMemberInfos.Add(MemberInfo);
}

void FCsLibraryLoad_GetReferencesReport_Category::Print()
{
	// "Category Name"
	UE_LOG(LogCs, Warning, TEXT("- %s"), *Name);
		// Used
	UE_LOG(LogCs, Warning, TEXT("--"));
	UE_LOG(LogCs, Warning, TEXT("-- Used: %d Members %d Paths (%d Unique)"), MemberInfos.Num(), ObjectPaths.Num(), CountByObjectPath.Num());
	{
		const int32 Count = MemberInfos.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FCsLibraryLoad_MemberInfo& MemberInfo	= MemberInfos[I];
			const FString Info							= MemberInfo.ToString();

			const FSoftObjectPath& ObjectPath = ObjectPaths[I];
			const FString& ObjectName		  = ObjectPath.GetAssetName();
			const FString& Path				  = ObjectPath.GetAssetPathString();

			UE_LOG(LogCs, Warning, TEXT("--- %s"), *Info);
			UE_LOG(LogCs, Warning, TEXT("     = %s @ %s"), *ObjectName, *Path);
		}

		// Count
		UE_LOG(LogCs, Warning, TEXT("---"));
		UE_LOG(LogCs, Warning, TEXT("--- Count: %d Unique Paths"), CountByObjectPath.Num());

		for (TPair<FSoftObjectPath, int32>& Pair : CountByObjectPath)
		{
			const FSoftObjectPath& ObjectPath = Pair.Key;
			const FString& ObjectName		  = ObjectPath.GetAssetName();
			const FString& Path				  = ObjectPath.GetAssetPathString();

			UE_LOG(LogCs, Warning, TEXT("---- %d for %s @ %s"), Pair.Value, *ObjectName, *Path);
		}

		// Members
		UE_LOG(LogCs, Warning, TEXT("---"));
		UE_LOG(LogCs, Warning, TEXT("--- Member: %d Unique Paths"), CountByObjectPath.Num());

		for (TPair<FSoftObjectPath, TArray<FCsLibraryLoad_MemberInfo>>& Pair : MemberInfosByObjectPath)
		{
			const FSoftObjectPath& ObjectPath = Pair.Key;
			const FString& ObjectName		  = ObjectPath.GetAssetName();
			const FString& Path				  = ObjectPath.GetAssetPathString();

			const TArray<FCsLibraryLoad_MemberInfo>& Infos = Pair.Value;

			UE_LOG(LogCs, Warning, TEXT("---- %s @ %s"), *ObjectName, *Path);

			UE_LOG(LogCs, Warning, TEXT("----- %d Members"), Infos.Num());

			for (const FCsLibraryLoad_MemberInfo& Info : Infos)
			{
				UE_LOG(LogCs, Warning, TEXT("------ %s"), *(Info.ToString()));
			}
		}
	}
		// Unused
	UE_LOG(LogCs, Warning, TEXT("--"));
	UE_LOG(LogCs, Warning, TEXT("-- Unused: %d Members"), UnusedMemberInfos.Num());
	{
		for (const FCsLibraryLoad_MemberInfo& Info : UnusedMemberInfos)
		{
			UE_LOG(LogCs, Warning, TEXT("--- %s"), *(Info.ToString()));
		}
	}
}

#pragma endregion FCsLibraryLoad_GetReferencesReport_Category

// FCsLibraryLoad_GetReferencesReport
#pragma region

void FCsLibraryLoad_GetReferencesReport::Print()
{
	UE_LOG(LogCs, Warning, TEXT("GetReferencesReport: %s @ %s"), *Name, *Path);

	Hard.Print();

	UE_LOG(LogCs, Warning, TEXT("-"));

	Soft.Print();
}

#pragma endregion FCsLibraryLoad_GetReferencesReport