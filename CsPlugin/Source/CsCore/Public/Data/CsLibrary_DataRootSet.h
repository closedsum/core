// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// NOTE: Should only be included in .h files

class UObject;

namespace NCsDataRootSet
{
	/**
	*/
	class CSCORE_API FLibrary
	{
	public:

		static UObject* GetImplChecked(const FString& Context, UObject* ContextRoot);

		template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType&(GetDataRootSetType::*GetDataRootSetFn)() const>
		static const DataRootSetType& GetChecked(const FString& Context, UObject* ContextRoot)
		{
			// Get DataRootSetImpl
			UObject* DataRootSetImpl = GetImplChecked(Context, ContextRoot);

			// Get DataRootSet for this Module
			GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(DataRootSetImpl);

			checkf(GetDataRootSet, TEXT("%s: DataRootSet: %s with Class: %s does NOT implement interface: GetDataRootSetType."), *Context, *(DataRootSetImpl->GetName()), *(DataRootSetImpl->GetClass()->GetName()));

			return (GetDataRootSet->*GetDataRootSetFn)();
		}

		static UDataTable* GetSafeDataTable(const FString& Context, UObject* Object, const FString& InterfaceGetName, TSoftObjectPtr<UDataTable> DataTableSoftPath, const FString& DataTableName);
	};
}