// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Containers/CsGetInterfaceMap.h"

struct FCsInterfaceMap;
class UObject;

namespace NCsUserWidget
{
	namespace NData
	{
		/**
		*/
		struct CSUI_API FInterfaceMap final : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

		public:

			FInterfaceMap();
			~FInterfaceMap();


			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap
		};
	}
}