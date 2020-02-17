// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/SoftObjectPath.h"

// FCsLibraryLoad_GetReferencesReport_MemberInfo
#pragma region

struct CSCORE_API FCsLibraryLoad_GetReferencesReport_MemberInfo
{
public:

	FString Name;
	FString Path;
	FString Type;

	FCsLibraryLoad_GetReferencesReport_MemberInfo() :
		Name(),
		Path(),
		Type()
	{
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("%s (%s) @ %s"), *Name, *Type, *Path);
	}
};

#pragma endregion FCsLibraryLoad_GetReferencesReport_MemberInfo

// FCsLibraryLoad_GetReferencesReport_Category
#pragma region

struct CSCORE_API FCsLibraryLoad_GetReferencesReport_Category
{
public:

	FString Name;

	TArray<FCsLibraryLoad_GetReferencesReport_MemberInfo> MemberInfos;
	TArray<FSoftObjectPath> ObjectPaths;
	TMap<FSoftObjectPath, int32> CountByObjectPath;
	TMap<FSoftObjectPath, TArray<FCsLibraryLoad_GetReferencesReport_MemberInfo>> MemberInfosByObjectPath;

	TArray<FCsLibraryLoad_GetReferencesReport_MemberInfo> UnusedMemberInfos;

	FCsLibraryLoad_GetReferencesReport_Category() :
		Name(),
		MemberInfos(),
		ObjectPaths(),
		CountByObjectPath(),
		MemberInfosByObjectPath(),
		UnusedMemberInfos()
	{
	}

	void Add(const FCsLibraryLoad_GetReferencesReport_MemberInfo& MemberInfo, const FSoftObjectPath& ObjectPath);
	void AddUnused(const FCsLibraryLoad_GetReferencesReport_MemberInfo& MemberInfo);

	void Print();
};

#pragma endregion FCsLibraryLoad_GetReferencesReport_Category

// FCsLibraryLoad_GetReferencesReport
#pragma region

struct CSCORE_API FCsLibraryLoad_GetReferencesReport
{
public:

	FString Name;
	FString Path;

	FCsLibraryLoad_GetReferencesReport_Category Hard;
	FCsLibraryLoad_GetReferencesReport_Category Soft;

	FCsLibraryLoad_GetReferencesReport() :
		Name(),
		Path(),
		Hard(),
		Soft()
	{
		Hard.Name = TEXT("Hard");
		Soft.Name = TEXT("Soft");
	}

	void Print();
};

#pragma endregion FCsLibraryLoad_GetReferencesReport