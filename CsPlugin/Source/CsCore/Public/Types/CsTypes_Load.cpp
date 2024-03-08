// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Load.h"
#include "CsCore.h"

// Library
#include "Library/Load/CsLibrary_Load.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Utility
#include "Utility/CsPopulateEnumMapFromSettings.h"

namespace ECsLoadCached
{
	namespace Str
	{
		CSCORE_API const FString _Path = TEXT("_Path");
		CSCORE_API const FString _Internal = TEXT("_Internal");
		CSCORE_API const FString _Class = TEXT("_Class");
		CSCORE_API const FString _SubclassOf = TEXT("_SubclassOf");
		CSCORE_API const FString _LoadFlags = TEXT("_LoadFlags");
		CSCORE_API const FString _1P_LoadFlags = TEXT("1P_LoadFlags");
		CSCORE_API const FString _3P_LoadFlags = TEXT("3P_LoadFlags");
		CSCORE_API const FString _3P_Low_LoadFlags = TEXT("3P_Low_LoadFlags");
		CSCORE_API const FString VR_LoadFlags = TEXT("VR_LoadFlags");
		CSCORE_API const FString _C = TEXT("_C");
	}
}

// LoadCodes
#pragma region

namespace NCsLoadCodes
{
	/*
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
	}
	*/
	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 15; // 1 + 2 + 4 + 8
}

#pragma endregion LoadCodes

// LoadFlags
#pragma region

namespace NCsLoadFlags
{
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
		CSCORE_API const Type GameVR = EMCsLoadFlags::Get().Add(Type::GameVR, TEXT("GameVR"), TEXT("Game VR"));
		CSCORE_API const Type UI = EMCsLoadFlags::Get().Add(Type::UI, TEXT("UI"));
		//CSCORE_API const Type All = EMCsLoadFlags::Get().Add(Type::All, TEXT("All"));
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 63; // 1 + 2 + 4 + 8 + 16 + 32
}

#pragma endregion LoadFlags

// LoadFlags_Editor
#pragma region

namespace NCsLoadFlags_Editor
{
	namespace Ref
	{
		CSCORE_API const Type Game = EMCsLoadFlags_Editor::Get().Add(Type::Game, TEXT("Game"));
		CSCORE_API const Type Game1P = EMCsLoadFlags_Editor::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSCORE_API const Type Game3P = EMCsLoadFlags_Editor::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSCORE_API const Type Game3PLow = EMCsLoadFlags_Editor::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
		CSCORE_API const Type GameVR = EMCsLoadFlags_Editor::Get().Add(Type::GameVR, TEXT("GameVR"), TEXT("Game VR"));
		CSCORE_API const Type UI = EMCsLoadFlags_Editor::Get().Add(Type::UI, TEXT("UI"));
		CSCORE_API const Type All = EMCsLoadFlags_Editor::Get().Add(Type::All, TEXT("All"));
		CSCORE_API const Type ECsLoadFlags_Editor_MAX = EMCsLoadFlags_Editor::Get().Add(Type::ECsLoadFlags_Editor_MAX, TEXT("ECsLoadFlags_Editor_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsLoadFlags_Editor_MAX;
}

#pragma endregion LoadFlags_Editor

// UnloadCodes
#pragma region

namespace NCsUnloadCodes
{
	/*
	namespace Ref
	{
	}
	*/
	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 1;
}

#pragma endregion UnloadCodes

// LoadAsyncOrder
#pragma region

namespace NCsLoadAsyncOrder
{
	namespace Ref
	{
		typedef EMCsLoadAsyncOrder EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Bulk);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsLoadAsyncOrder_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsLoadAsyncOrder_MAX;
}

#pragma endregion LoadAsyncOrder