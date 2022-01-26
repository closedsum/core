// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			/**
			* 
			*/
			struct CSDMG_API IPoint : public ICsGetInterfaceMap
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