// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UCsPhysicsSettings;
class UObject;

namespace NCsPhysics
{
	namespace NSettings
	{
		/**
		*/
		class CSPHYSICS_API FLibrary
		{
		public:
			
			static UCsPhysicsSettings* Get();	
		};
	}
}