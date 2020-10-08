// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			/**
			* 
			*/
			struct CSCORE_API IPoint : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IPoint(){}

				virtual const float& GetValue() const = 0;
			};
		}
	}
}