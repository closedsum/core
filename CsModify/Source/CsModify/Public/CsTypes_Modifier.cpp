// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsTypes_Modifier.h"

// NumericValueModifierApplication
#pragma region

namespace NCsNumericValueModifierApplication
{
	namespace Ref
	{
		typedef EMCsNumericValueModifierApplication EnumMapType;

		CSMODIFY_API CS_ADD_TO_ENUM_MAP(Multiply);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP(Add);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP(Replace);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP(PercentAddFirst);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP(PercentAddLast);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsNumericValueModifierApplication_MAX, "MAX");
	}
}

namespace NCsModifier
{
	namespace NValue
	{
		namespace NNumeric
		{
			namespace NApplication
			{
				namespace Ref
				{
					typedef EMApplication EnumMapType;

					CSMODIFY_API CS_ADD_TO_ENUM_MAP(Multiply);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP(Add);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP(Replace);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP(PercentAddFirst);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP(PercentAddLast);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP_CUSTOM(EApplication_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion NumericValueModifierApplication

// NumericValueCreateModifier
#pragma region

namespace NCsNumericValueCreateModifier
{
	namespace Ref
	{
		typedef EMCsNumericValueCreateModifier EnumMapType;

		CSMODIFY_API CS_ADD_TO_ENUM_MAP(Current);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP(CurrentAndMultiplyBy);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP(CurrentAndAddTo);
		CSMODIFY_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsNumericValueCreateModifier_MAX, "MAX");
	}
}

namespace NCsModifier
{
	namespace NValue
	{
		namespace NNumeric
		{
			namespace NCreate
			{
				namespace Ref
				{
					typedef EMCreate EnumMapType;

					CSMODIFY_API CS_ADD_TO_ENUM_MAP(Current);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP(CurrentAndMultiplyBy);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP(CurrentAndAddTo);
					CSMODIFY_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECreate_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion NumericValueCreateModifier