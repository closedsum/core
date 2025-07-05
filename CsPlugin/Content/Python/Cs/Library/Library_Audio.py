# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
from pathlib import Path
from mutagen.mp3 import MP3

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Path.py
import Cs.Library.Library_Path as Cs_Library_Path

# "ALIAS"

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
FPyPathLibrary = Cs_Library_Path.NPyPath.FLibrary

# "alias" - functions
IsStringNotEmptyRaiseError = FPyCommonLibrary.IsStringNotEmptyRaiseError
    # Path
DoesExistRaiseError = FPyPathLibrary.DoesExistRaiseError

# Constants

MP3_EXT = ".mp3"

class NPyAudio:
    class FLibrary:
        @staticmethod
        def GetDurationRaiseError(context: str, file_path: str) -> float:
            """
            Get the duration of the audio file.
             Assert if Failed.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context:    (str): The calling context.
                file_path   (str): The path to the audio file.
            Returns:
                float: The duration of the audio file.
            """
            try:
                IsStringNotEmptyRaiseError(context, file_path)
                DoesExistRaiseError(context, file_path)
            except Exception as e:
                raise e

            path = Path(file_path)
            file_ext = path.suffix

            # MP3
            if file_ext == MP3_EXT:
                audio = MP3(file_path)
                return audio.info.length
            else:
                raise Exception(f"{context}: Unsupported file extension: {file_ext}")
            return 0.0