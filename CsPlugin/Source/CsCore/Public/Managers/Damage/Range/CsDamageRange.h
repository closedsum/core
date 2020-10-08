// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NRange
	{
		/**
		* 
		*/
		struct CSCORE_API IRange : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IRange(){}

			virtual const float& GetMinRange() const = 0;

			virtual const float& GetMaxRange() const = 0;
		};
	}
}