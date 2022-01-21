// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/SoftObjectPath.h"

// FCsLibraryLoad_MemberInfo
#pragma region

struct CSCORE_API FCsLibraryLoad_MemberInfo
{
private:

	FName Name;
	FString NameAsString;
	FName Path;
	FString PathAsString;
	FName Type;
	FString TypeAsString;

public:

	FCsLibraryLoad_MemberInfo() :
		Name(NAME_None),
		NameAsString(),
		Path(NAME_None),
		PathAsString(),
		Type(NAME_None),
		TypeAsString()
	{
	}

	FORCEINLINE bool operator==(const FCsLibraryLoad_MemberInfo& B) const
	{
		return Name == B.Name && Path == B.Path && Type == B.Type;
	}

	FORCEINLINE bool operator!=(const FCsLibraryLoad_MemberInfo& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void SetName(const FName& InName)
	{
		Name		 = InName;
		NameAsString = Name.ToString();
	}

	FORCEINLINE void SetName(const FString& InName)
	{
		NameAsString = InName;
		Name		 = FName(*NameAsString);
	}

	FORCEINLINE const FName& GetFName() const
	{
		return Name;
	}

	FORCEINLINE const FString& GetName() const
	{
		return NameAsString;
	}

	FORCEINLINE void SetPath(const FName& InPath)
	{
		Path		 = InPath;
		PathAsString = Path.ToString();
	}

	FORCEINLINE void SetPath(const FString& InPath)
	{
		PathAsString = InPath;
		Path		 = FName(*PathAsString);
	}

	FORCEINLINE const FName& GetFPath() const
	{
		return Path;
	}

	FORCEINLINE const FString& GetPath() const
	{
		return PathAsString;
	}

	FORCEINLINE void SetType(const FName& InType)
	{
		Type		 = InType;
		TypeAsString = Type.ToString();
	}

	FORCEINLINE void SetType(const FString& InType)
	{
		TypeAsString = InType;
		Type		 = FName(*TypeAsString);
	}

	FORCEINLINE const FName& GetFType() const
	{
		return Type;
	}

	FORCEINLINE const FString& GetType() const
	{
		return TypeAsString;
	}

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("%s (%s) @ %s"), *NameAsString, *TypeAsString, *PathAsString);
	}

	FORCEINLINE friend uint32 GetTypeHash(FCsLibraryLoad_MemberInfo const& This)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(This.Name));
		Hash = HashCombine(Hash, GetTypeHash(This.Path));
		Hash = HashCombine(Hash, GetTypeHash(This.Type));
		return Hash;
	}
};

#pragma endregion FCsLibraryLoad_MemberInfo

// LibraryLoad_GetSoftObjectPaths_Code
#pragma region

enum class ECsLibraryLoad_GetSoftObjectPaths_Code : uint8
{
	/** Recursively get class object paths */
	RecursiveGetClass = 1 << 0,
	/** Recursively get object object paths */
	RecursiveGetObject = 1 << 1
};

namespace NCsLibraryLoad_GetSoftObjectPaths_Code
{
	typedef ECsLibraryLoad_GetSoftObjectPaths_Code Type;

	/*
	namespace Ref
	{
		extern CSCORE_API const Type RecursiveGetClass;
		extern CSCORE_API const Type RecursiveGetObject;
	}
	*/

	extern CSCORE_API const int32 None;
	extern CSCORE_API const int32 All;
}

#pragma endregion LibraryLoad_GetSoftObjectPaths_Code

// FCsLibraryLoad_GetSoftObjectPaths
#pragma region

struct CSCORE_API FCsLibraryLoad_GetSoftObjectPaths
{
public:

	int32 Code;

	TSet<FSoftObjectPath> Paths;
	TMap<FCsLibraryLoad_MemberInfo, FSoftObjectPath> PathByMemberInfoMap;
	TMap<FSoftObjectPath, TArray<FCsLibraryLoad_MemberInfo>> MemberInfosByPathMap;

	FCsLibraryLoad_GetSoftObjectPaths() :
		Code(NCsLibraryLoad_GetSoftObjectPaths_Code::None),
		Paths(),
		PathByMemberInfoMap(),
		MemberInfosByPathMap()
	{
	}

	void Reset()
	{
		Code = NCsLibraryLoad_GetSoftObjectPaths_Code::None;
		Paths.Reset();
		PathByMemberInfoMap.Reset();
		MemberInfosByPathMap.Reset();
	}
};

#pragma endregion FCsLibraryLoad_GetSoftObjectPaths


// FCsLibraryLoad_GetObjectPaths
#pragma region

struct CSCORE_API FCsLibraryLoad_GetObjectPaths
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

	FCsLibraryLoad_GetObjectPaths();

	void SetRootName(const FString& Name)
	{
		RootName = Name;
		RootDefaultName = TEXT("Default__") + RootName + TEXT("_C");
	}

	void AddPath(const FSoftObjectPath& SoftPath);

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

#pragma endregion FCsLibraryLoad_GetObjectPaths

// FCsLibraryLoad_GetReferencesReport_Category
#pragma region

struct CSCORE_API FCsLibraryLoad_GetReferencesReport_Category
{
public:

	FString Name;

	TArray<FCsLibraryLoad_MemberInfo> MemberInfos;
	TArray<FSoftObjectPath> ObjectPaths;
	TMap<FSoftObjectPath, int32> CountByObjectPath;
	TMap<FSoftObjectPath, TArray<FCsLibraryLoad_MemberInfo>> MemberInfosByObjectPath;

	TArray<FCsLibraryLoad_MemberInfo> UnusedMemberInfos;

	FCsLibraryLoad_GetReferencesReport_Category() :
		Name(),
		MemberInfos(),
		ObjectPaths(),
		CountByObjectPath(),
		MemberInfosByObjectPath(),
		UnusedMemberInfos()
	{
	}

	void Add(const FCsLibraryLoad_MemberInfo& MemberInfo, const FSoftObjectPath& ObjectPath);
	void AddUnused(const FCsLibraryLoad_MemberInfo& MemberInfo);

	void Print();
};

#pragma endregion FCsLibraryLoad_GetReferencesReport_Category

// FCsLibraryLoad_GetReferencesReport
#pragma region

struct CSCORE_API FCsLibraryLoad_GetReferencesReport
{
public:

	FString Name;
	FString DefaultName;
	FString Path;

	FCsLibraryLoad_GetReferencesReport_Category Hard;
	FCsLibraryLoad_GetReferencesReport_Category Soft;

	TSet<FString> VisitedFunctions;

	TArray<TSet<FSoftObjectPath>> ReferenceDepthList;
	int32 TotalCount;

	FCsLibraryLoad_GetReferencesReport() :
		Name(),
		Path(),
		Hard(),
		Soft(),
		VisitedFunctions(),
		ReferenceDepthList(),
		TotalCount(0)
	{
		Hard.Name = TEXT("Hard");
		Soft.Name = TEXT("Soft");
	}

	void SetName(const FString& InName)
	{
		Name = InName;
		DefaultName = TEXT("Default__") + Name + TEXT("_C");
	}

	void VisitFunction(const FString& FunctionPath)
	{
		VisitedFunctions.Add(FunctionPath);
	}

	FORCEINLINE bool HasVisitedFunction(const FString& FunctionPath)
	{
		return VisitedFunctions.Contains(FunctionPath);
	}

	void AddToDepthList(const FSoftObjectPath& InPath, const int32& Depth);

	void ResolveDepthList();

	void Print();
};

#pragma endregion FCsLibraryLoad_GetReferencesReport