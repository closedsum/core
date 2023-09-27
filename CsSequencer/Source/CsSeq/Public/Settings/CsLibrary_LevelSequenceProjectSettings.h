// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

namespace NCsLevelSequence
{
	namespace NProject
	{
		namespace NSettings
		{
			/**
			* Library of functions related to a LevelSequenceProjectSettings
			*/
			struct CSSEQ_API FLibrary final
			{
			public:

				/**
				* Specifies default display frame rate for newly created level sequences
				* also defines frame locked frame rate where sequences are set to be frame locked. 
				* Examples: 30 fps, 120/1 (120 fps), 30000/1001 (29.97), 0.01s (10ms).
				* 
				* return
				*/
				static float GetDefaultDisplayRate();

				/**
				* Specifies default display frame rate for newly created level sequences
				* also defines frame locked frame rate where sequences are set to be frame locked.
				* Examples: 30 fps, 120/1 (120 fps), 30000/1001 (29.97), 0.01s (10ms).
				*  NOTE: This is 1/0f / GetDefaultDisplayRate().
				*
				* return
				*/
				FORCEINLINE static float GetDefaultDisplayDeltaTime()
				{
					return 1.0f / GetDefaultDisplayRate();
				}

				/**
				* Specifies default tick resolution for newly created level sequences. 
				* Examples: 30 fps, 120/1 (120 fps), 30000/1001 (29.97), 0.01s (10ms).
				* 
				* return
				*/
				static int32 GetDefaultTickResolution();
			};
		}
	}
}                                                                                                                                                                                                                                                                                                                                            