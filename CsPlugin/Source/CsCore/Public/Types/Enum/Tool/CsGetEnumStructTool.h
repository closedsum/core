// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetEnumStructTool.generated.h"

class UObject;
class UStruct;

namespace NCsEnum
{
	namespace NStruct
	{
		namespace NTool
		{
			struct CSCORE_API FPropertyChange
			{
			public:

				FName Name;

				UStruct* Struct;

				FPropertyChange() :
					Name(NAME_None),
					Struct(nullptr)
				{
				}
			};

			struct CSCORE_API FImpl
			{
			private:
				
				UObject* Outer;

				TArray<FPropertyChange> PropertyChanges;

			public:

				void(*ResolveLayoutChangesImpl)(bool /*bForce*/);

				FImpl() : 
					Outer(nullptr),
					PropertyChanges(),
					ResolveLayoutChangesImpl(nullptr)
				{
				}

				void Init(UObject* InOuter);

				void AddPropertyChange(const FName& Name, UStruct* Struct);

				void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);
			};
		}
	}
}

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetEnumStructTool : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetEnumStructTool
{
	GENERATED_IINTERFACE_BODY()

public:

#define EnumStructToolType NCsEnum::NStruct::NTool::FImpl

	virtual EnumStructToolType& GetEnumStructTool() = 0;

#undef EnumStructToolType
};