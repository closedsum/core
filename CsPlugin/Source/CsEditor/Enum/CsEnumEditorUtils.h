// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Primitive.h"

class UUserDefinedEnum;

class CSEDITOR_API FCsEnumEditorUtils
{
public:

	static UUserDefinedEnum* GetUserDefinedEnum(const FECsUserDefinedEnum& EnumType);
	static void SyncInputAction();
	static void UpdateNames(const FECsUserDefinedEnum& EnumType, const TArray<FName>& Names, const TMap<FName, FText>& DisplayNameMap);
	static void PrepareForChange(UUserDefinedEnum* Enum);
	static void BroadcastChanges(const UUserDefinedEnum* Enum, const TArray<TPair<FName, int64>>& OldNames, bool bResolveData = true);

	/** copy full enumerators names from given enum to OutEnumNames, the last '_MAX' enumerator is skipped */
	static void CopyEnumeratorsWithoutMax(const UEnum* Enum, TArray<TPair<FName, int64>>& OutEnumNames);

	static FName GetNameFromNamespacedName(const FName& Name);
};
