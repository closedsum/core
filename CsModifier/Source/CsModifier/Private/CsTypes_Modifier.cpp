// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsTypes_Modifier.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Modifier)

// NumericValueModifierApplication
#pragma region

namespace NCsNumericValueModifierApplication
{
	namespace Ref
	{
		typedef EMCsNumericValueModifierApplication EnumMapType;

		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Multiply);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Add);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Replace);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(PercentAddFirst);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(PercentAddLast);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsNumericValueModifierApplication_MAX, "MAX");
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

					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Multiply);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Add);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Replace);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(PercentAddFirst);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(PercentAddLast);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP_CUSTOM(EApplication_MAX, "MAX");
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

		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Current);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(CurrentAndMultiplyBy);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP(CurrentAndAddTo);
		CSMODIFIER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsNumericValueCreateModifier_MAX, "MAX");
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

					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(Current);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(CurrentAndMultiplyBy);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP(CurrentAndAddTo);
					CSMODIFIER_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECreate_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion NumericValueCreateModifier