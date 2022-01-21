// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Save/CsTypes_Save.h"

// SaveStorage
#pragma region

namespace NCsSaveStorage
{
	namespace Ref
	{
		typedef EMCsSaveStorage EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Local);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Cloud);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSaveStorage_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsSaveStorage_MAX;
}

#pragma endregion SaveStorage

// Save
#pragma region

namespace NCsSave
{
	namespace Ref
	{
		typedef EMCsSave EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save1, "Save 1");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save2, "Save 2");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save3, "Save 3");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save4, "Save 4");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save5, "Save 5");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save6, "Save 6");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save7, "Save 7");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(Save8, "Save 8");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSave_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsSave_MAX;
}

#pragma endregion Save

namespace NCsSave
{
	namespace NFile
	{
		const FInfo FInfo::Invalid;
	}
}

// SaveAction
#pragma region

namespace NCsSaveAction
{
	namespace Ref
	{
		typedef EMCsSaveAction EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Enumerate);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Read);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ReadAll, "Read All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Write);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(WriteAll, "Write All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Delete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(DeleteAll, "Delete All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSaveAction_MAX, "MAX");
	}
}

namespace NCsSave
{
	namespace NAction
	{
		namespace Ref
		{
			typedef EMAction EnumMapType;

			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Enumerate);
			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Read);
			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ReadAll, "Read All");
			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Write);
			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(WriteAll, "Write All");
			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Delete);
			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(DeleteAll, "Delete All");
			CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EAction_MAX, "MAX");
		}
	}
}

#pragma endregion SaveAction

// SaveActionState
#pragma region

namespace NCsSaveActionState
{
	namespace Ref
	{
		typedef EMCsSaveActionState EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(None);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(InProgress, "In Progress");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Complete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSaveActionState_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsSaveActionState_MAX;
}

namespace NCsSave
{
	namespace NAction
	{
		namespace NState
		{
			namespace Ref
			{
				typedef EMState EnumMapType;

				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(None);
				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(InProgress, "In Progress");
				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Complete);
				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EState_MAX, "MAX");
			}
		}
	}
}

#pragma endregion SaveActionState