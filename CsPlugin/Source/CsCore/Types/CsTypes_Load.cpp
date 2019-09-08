// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Load.h"

namespace ECsLoadCached
{
	namespace Str
	{
		CSCORE_API const FString _Internal = TEXT("_Internal");
		CSCORE_API const FString _LoadFlags = TEXT("_LoadFlags");
		CSCORE_API const FString _1P_LoadFlags = TEXT("1P_LoadFlags");
		CSCORE_API const FString _3P_LoadFlags = TEXT("3P_LoadFlags");
		CSCORE_API const FString _3P_Low_LoadFlags = TEXT("3P_Low_LoadFlags");
		CSCORE_API const FString VR_LoadFlags = TEXT("VR_LoadFlags");
		CSCORE_API const FString _C = TEXT("_C");
	}
}

// LoadFlags
EMCsLoadFlags* EMCsLoadFlags::Instance;

EMCsLoadFlags& EMCsLoadFlags::Get()
{
	if (!Instance)
		Instance = new EMCsLoadFlags();
	return *Instance;
}

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
		CSCORE_API const Type All = EMCsLoadFlags::Get().Add(Type::All, TEXT("All"));
	}
}

// LoadFlags_Editor
EMCsLoadFlags_Editor* EMCsLoadFlags_Editor::Instance;

EMCsLoadFlags_Editor& EMCsLoadFlags_Editor::Get()
{
	if (!Instance)
		Instance = new EMCsLoadFlags_Editor();
	return *Instance;
}

namespace ECsLoadFlags_Editor
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
}

// AssetType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsAssetType)

// LoadAssetsType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsLoadAssetsType)

// LoadAsyncOrder
CS_DEFINE_ENUM_MAP_BODY(EMCsLoadAsyncOrder)

namespace ECsLoadAsyncOrder
{
	namespace Ref
	{
		CSCORE_API const Type None = EMCsLoadAsyncOrder::Get().Add(Type::None, TEXT("None"));
		CSCORE_API const Type FirstToLast = EMCsLoadAsyncOrder::Get().Add(Type::FirstToLast, TEXT("FirstToLast"), TEXT("First to Last"));
		CSCORE_API const Type Bulk = EMCsLoadAsyncOrder::Get().Add(Type::Bulk, TEXT("Bulk"));
		CSCORE_API const Type ECsLoadAsyncOrder_MAX = EMCsLoadAsyncOrder::Get().Add(Type::ECsLoadAsyncOrder_MAX, TEXT("ECsLoadAsyncOrder_MAX"), TEXT("MAX"));
	}
}