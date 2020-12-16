// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

namespace NCsViewport
{
	class CSCORE_API FLibrary
	{
	public:

		static bool CanProjectWorldToScreenChecked(const FString& Context, UObject* WorldContext);
	};
}