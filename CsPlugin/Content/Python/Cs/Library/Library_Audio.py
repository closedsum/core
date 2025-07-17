# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import os
from pathlib import Path
from mutagen.mp3 import MP3
from moviepy.audio.io.AudioFileClip import AudioFileClip

# IMPORT

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Path.py
import Cs.Library.Library_Path as Cs_Library_Path
# - Cs/Library/Library_Process.py
import Cs.Library.Library_Process as Cs_Library_Process

# "ALIAS"

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
FPyPathLibrary = Cs_Library_Path.NPyPath.FLibrary
FPyProcessLibrary = Cs_Library_Process.NPyProcess.FLibrary

# "alias" - functions (py)
IsStringNotEmptyRaiseError = FPyCommonLibrary.IsStringNotEmptyRaiseError
    # Path
DoesExistRaiseError = FPyPathLibrary.DoesExistRaiseError
GetFilenameRaiseError = FPyPathLibrary.GetFilenameRaiseError

# Constants

MP3_EXTS = [".mp3", "mp3"]

class NPyAudio:
    class FLibrary:
        @staticmethod
        def GetCodecRaiseError(context: str, ext: str) -> str:
            """
            Get the codec of the audio file.
             Assert if Failed.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                GetCodecRaiseError("some_function",".mp3") -> "mp3"
            
            Args:
                context: (str): The calling context.
                ext:     (str): The extension of the audio file.
            Returns:
                str: The codec of the audio file.
            """
            if ext in MP3_EXTS:
                return "mp3"
            else:
                raise Exception(f"{context}: Unsupported file extension: {ext}")

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

            # Check if file_path exists
            if not os.path.exists(file_path):
                raise Exception(f"{context}: Audio file does not exist: {file_path}")
            
            path = Path(file_path)
            file_ext = path.suffix

            # MP3
            if file_ext in MP3_EXTS:
                audio = MP3(file_path)
                return audio.info.length
            else:
                raise Exception(f"{context}: Unsupported file extension: {file_ext}")
            return 0.0
        
        @staticmethod
        def ConvertRaiseError(context: str, file_path: str, ext: str):
            """
            Convert an audio file to a different format.
             Assert if Failed.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context:    (str): The calling context.
                file_path   (str): The path to the audio file.
                ext         (str): The extension to convert the audio file to.
            """
            ThisType = __class__
            
            filename_with_extension: str = ""
            filename: str = ""
            extension: str = ""
            directory: str = ""

            try:
                filename_with_extension, filename, extension, directory = GetFilenameRaiseError(context, file_path)
            except Exception as e:
                raise e

            # Check if file_path exists
            if not os.path.exists(file_path):
                raise Exception(f"{context}: Audio file does not exist: {file_path}")

            # Open Audio File
            audio_clip: AudioFileClip = None
            
            try:
                audio_clip = AudioFileClip(file_path)
            except Exception as e:
                audio_clip.close()
                del audio_clip
                audio_clip = None
                raise Exception(f"{context}: Failed to open audio file: {file_path} - {e}")

            # Get Codec
            codec: str = ""

            try:
                codec = ThisType.GetCodecRaiseError(context, ext)
            except Exception as e:
                audio_clip.close()
                del audio_clip
                audio_clip = None
                raise Exception(f"{context}: Failed to export audio file: {output_file} - {e}")

            # Write Audio File
            ext              = ext.removeprefix(".")
            output_file: str = f"{directory}/{filename}.{ext}"
    
            try:
                audio_clip.write_audiofile(output_file, codec=codec)
            except Exception as e:
                audio_clip.close()
                del audio_clip
                audio_clip = None
                raise Exception(f"{context}: Failed to export audio file: {output_file} - {e}")
            
            audio_clip.close()
            del audio_clip
            audio_clip = None