// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsTypes_Modifier.h"

// IntegralValueModifierApplication
#pragma region

namespace NCsIntegralValueModifierApplication
{
	namespace Ref
	{
		typedef EMCsIntegralValueModifierApplication EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Multiply);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Add);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Replace);
		CSCORE_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsIntegralValueModifierApplication_MAX, "MAX");
	}
}

namespace NCsModifier
{
	namespace NValue
	{
		namespace NIntegral
		{
			namespace NApplication
			{
				namespace Ref
				{
					typedef EMApplication EnumMapType;

					CSCORE_API CS_ADD_TO_ENUM_MAP(Multiply);
					CSCORE_API CS_ADD_TO_ENUM_MAP(Add);
					CSCORE_API CS_ADD_TO_ENUM_MAP(Replace);
					CSCORE_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EApplication_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion IntegralValueModifierApplication