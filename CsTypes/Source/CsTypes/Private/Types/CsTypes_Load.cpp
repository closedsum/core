// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Load.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Load)

namespace ECsLoadCached
{
	namespace Str
	{
		CSTYPES_API const FString _Path = TEXT("_Path");
		CSTYPES_API const FString _Internal = TEXT("_Internal");
		CSTYPES_API const FString _Class = TEXT("_Class");
		CSTYPES_API const FString _SubclassOf = TEXT("_SubclassOf");
		CSTYPES_API const FString _LoadFlags = TEXT("_LoadFlags");
		CSTYPES_API const FString _1P_LoadFlags = TEXT("1P_LoadFlags");
		CSTYPES_API const FString _3P_LoadFlags = TEXT("3P_LoadFlags");
		CSTYPES_API const FString _3P_Low_LoadFlags = TEXT("3P_Low_LoadFlags");
		CSTYPES_API const FString VR_LoadFlags = TEXT("VR_LoadFlags");
		CSTYPES_API const FString _C = TEXT("_C");
	}
}

// LoadCodes
#pragma region

namespace NCsLoadCodes
{
	/*
	namespace Ref
	{
		CSTYPES_API const Type Game = EMCsLoadFlags::Get().Add(Type::Game, TEXT("Game"));
		CSTYPES_API const Type Game1P = EMCsLoadFlags::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSTYPES_API const Type Game3P = EMCsLoadFlags::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSTYPES_API const Type Game3PLow = EMCsLoadFlags::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
	}
	*/
	CSTYPES_API const int32 None = 0;
	CSTYPES_API const int32 All = 15; // 1 + 2 + 4 + 8
}

#pragma endregion LoadCodes

// LoadFlags
#pragma region

namespace NCsLoadFlags
{
	namespace Ref
	{
		CSTYPES_API const Type Game = EMCsLoadFlags::Get().Add(Type::Game, TEXT("Game"));
		CSTYPES_API const Type Game1P = EMCsLoadFlags::Get().Add(Type::Game1P, TEXT("Game1P"), TEXT("Game 1P"));
		CSTYPES_API const Type Game3P = EMCsLoadFlags::Get().Add(Type::Game3P, TEXT("Game3P"), TEXT("Game 3P"));
		CSTYPES_API const Type Game3PLow = EMCsLoadFlags::Get().Add(Type::Game3PLow, TEXT("Game3PLow"), TEXT("Game 3P Low"));
		CSTYPES_API const Type GameVR = EMCsLoadFlags::Get().Add(Type::GameVR, TEXT("GameVR"), TEXT("Game VR"));
		CSTYPES_API const Type UI = EMCsLoadFlags::Get().Add(Type::UI, TEXT("UI"));
		//CSTYPES_API const Type All = EMCsLoadFlags::Get().Add(Type::All, TEXT("All"));
	}

	CSTYPES_API const int32 None = 0;
	CSTYPES_API const int32 All = 63; // 1 + 2 + 4 + 8 + 16 + 32
}

#pragma endregion LoadFlags

// UnloadCodes
#pragma region

namespace NCsUnloadCodes
{
	/*
	namespace Ref
	{
	}
	*/
	CSTYPES_API const int32 None = 0;
	CSTYPES_API const int32 All = 1;
}

#pragma endregion UnloadCodes

// LoadAsyncOrder
#pragma region

namespace NCsLoadAsyncOrder
{
	namespace Ref
	{
		typedef EMCsLoadAsyncOrder EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(None);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(FirstToLast, "First to Last");
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Bulk);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsLoadAsyncOrder_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsLoadAsyncOrder_MAX;
}

#pragma endregion LoadAsyncOrder