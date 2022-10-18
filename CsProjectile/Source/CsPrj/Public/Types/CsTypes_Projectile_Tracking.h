// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

namespace NCsProjectile
{
	namespace NTracking
	{
		enum class EState : uint8
		{
			Inactive,
			Delay,
			Active
		};
	}
}

namespace NCsProjectile
{
	namespace NTracking
	{
		enum class EObject : uint8
		{
			Component,
			Bone,
			Location,
			ID
		};
	}
}