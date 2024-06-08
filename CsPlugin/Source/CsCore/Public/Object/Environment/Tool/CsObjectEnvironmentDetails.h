// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

class UObject;

namespace NCsObject
{
	enum class EEnvironment : uint8 
	{
		None,
		/** A world being edited in the editor */
		Editor,
		/** A Play In Editor world */
		PIE,
		/** A preview world for an editor tool */
		EditorPreview
	};

	namespace NEnvironment
	{
		struct CSCORE_API FDetails
		{
		public:

			EEnvironment Type;

			bool bSelected;

			FDetails() :
				Type(NCsObject::EEnvironment::None),
				bSelected(false)
			{
			}
		};
	}
}