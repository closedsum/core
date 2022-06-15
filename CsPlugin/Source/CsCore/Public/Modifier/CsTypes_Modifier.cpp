// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsTypes_Modifier.h"

// NumericValueModifierApplication
#pragma region

namespace NCsNumericValueModifierApplication
{
	namespace Ref
	{
		typedef EMCsNumericValueModifierApplication EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Multiply);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Add);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Replace);
		CSCORE_API CS_ADD_TO_ENUM_MAP(ReplaceOnlyIfGreater);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsNumericValueModifierApplication_MAX, "MAX");
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

#pragma endregion NumericValueModifierApplication

// NumericValueCreateModifier
#pragma region

namespace NCsNumericValueCreateModifier
{
	namespace Ref
	{
		typedef EMCsNumericValueCreateModifier EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Current);
		CSCORE_API CS_ADD_TO_ENUM_MAP(CurrentAndMultiplyBy);
		CSCORE_API CS_ADD_TO_ENUM_MAP(CurrentAndAddTo);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsNumericValueCreateModifier_MAX, "MAX");
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

					CSCORE_API CS_ADD_TO_ENUM_MAP(Current);
					CSCORE_API CS_ADD_TO_ENUM_MAP(CurrentAndMultiplyBy);
					CSCORE_API CS_ADD_TO_ENUM_MAP(CurrentAndAddTo);
					CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECreate_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion NumericValueCreateModifier