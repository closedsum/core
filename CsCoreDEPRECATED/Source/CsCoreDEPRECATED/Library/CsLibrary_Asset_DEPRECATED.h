// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsLibrary_Asset_DEPRECATED.generated.h"

class UCsDataMapping;

UCLASS()
class CSCOREDEPRECATED_API UCsLibrary_Asset_DEPRECATED : public UObject
{
	GENERATED_UCLASS_BODY()
public:

#if WITH_EDITOR

	static UCsDataMapping* GetDataMapping();

	template<typename T>
	static T* GetDataMapping()
	{
		return Cast<T>(GetDataMapping());
	}

#endif // #if WITH_EDITOR
};