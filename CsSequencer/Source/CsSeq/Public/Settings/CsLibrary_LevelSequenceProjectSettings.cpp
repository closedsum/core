// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/CsLibrary_LevelSequenceProjectSettings.h"

// Settings
#include "Runtime/LevelSequence/Private/LevelSequenceProjectSettings.h" 

namespace NCsLevelSequence
{
	namespace NProject
	{
		namespace NSettings
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						const FString fps = TEXT("fps");
					}
				}
			}

			float FLibrary::GetDefaultDisplayRate()
			{
				using namespace NCsLevelSequence::NProject::NSettings::NLibrary::NCached;

			#if WITH_EDITOR
				FString DefaultDisplayRate = TEXT("30fps");

				if (IConsoleVariable* ConsoleVariable = IConsoleManager::Get().FindConsoleVariable(TEXT("LevelSequence.DefaultDisplayRate")))
				{
					DefaultDisplayRate = ConsoleVariable->GetString();
				}
			#else
				FString DefaultDisplayRate = GetMutableDefault<ULevelSequenceProjectSettings>()->DefaultDisplayRate;
			#endif // #if WITH_EDITOR

				DefaultDisplayRate.RemoveFromEnd(Str::fps);

				return FCString::Atof(*DefaultDisplayRate);
			
			}

			int32 FLibrary::GetDefaultTickResolution()
			{
				using namespace NCsLevelSequence::NProject::NSettings::NLibrary::NCached;

			#if WITH_EDITOR
				FString DefaultTickResolution = TEXT("24000fps");

				if (IConsoleVariable* ConsoleVariable = IConsoleManager::Get().FindConsoleVariable(TEXT("LevelSequence.DefaultTickResolution")))
				{
					DefaultTickResolution = ConsoleVariable->GetString();
				}
			#else
				FString DefaultTickResolution = GetMutableDefault<ULevelSequenceProjectSettings>()->DefaultTickResolution;
			#endif // #if WITH_EDITOR

				DefaultTickResolution.RemoveFromEnd(Str::fps);

				return FCString::Atoi(*DefaultTickResolution);
			}
		}
	}
}