// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;
class AActor;
class UClass;

namespace NCsLevel
{
	namespace NEditor
	{
		struct CSEDITOR_API FTool
		{
		public:

			//const TArray<UObject*>&(*GetObjectsImpl)();

			//const TArray<UObject*>&(*GetObjectsByClassImpl)(UClass* /*Class*/);

			//const TArray<UObject*>&(*GetSelectedObjectsImpl)();

			static void GetActors(TArray<AActor*>& OutActors);

			static void GetActorsByClass(UClass* Class, TArray<AActor*>& OutActors);

			static void GetActorsByInterface(UClass* Class, TArray<AActor*>& OutActors);

			static void GetSelectedActors(TArray<AActor*>& OutActors);
		};
	}
}