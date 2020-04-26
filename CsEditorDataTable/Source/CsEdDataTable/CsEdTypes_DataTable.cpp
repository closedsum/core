// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsEdTypes_DataTable.h"

// BlackboardKeyType
#pragma region

namespace NCsDataTableFileType
{
	namespace Ref
	{
		CSEDDATATABLE_API CS_ADD_TO_ENUM_MAP(EMCsDataTableFileType, json);
		CSEDDATATABLE_API CS_ADD_TO_ENUM_MAP(EMCsDataTableFileType, csv);
		CSEDDATATABLE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDataTableFileType, ECsDataTableFileType_MAX, "MAX");
	}

	CSEDDATATABLE_API const uint8 MAX = (uint8)Type::ECsDataTableFileType_MAX;
}

#pragma endregion BlackboardKeyType