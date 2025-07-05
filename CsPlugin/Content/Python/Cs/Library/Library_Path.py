import os

# IMPORT

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary

# "alias" - functions (py)
    # Common
check                   = FPyCommonLibrary.check
checkf                  = FPyCommonLibrary.checkf
IsStringNotEmptyChecked = FPyCommonLibrary.IsStringNotEmptyChecked
IsStringNotEmptyRaiseError = FPyCommonLibrary.IsStringNotEmptyRaiseError

# Contants

EXTENSIONS = {".mp4"}

class NPyPath:
    class FLibrary:
        @staticmethod
        def DoesExistRaiseError(context: str, path: str) -> bool:
            """
            Get whether or not a path exists.
             Assert if NOT.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context (str): The calling context.
                path:   (str): The path to check.
            Returns:
                bool: True if the path exists, False otherwise.
            """
            try:
                IsStringNotEmptyRaiseError(context, path)
            except Exception as e:
                raise e
            
            if not os.path.exists(path):
                raise Exception(f"{context}: Path does not exist: {path}.") # TODO: Add more information about the path.
            return True

        @staticmethod
        def GetFilenameChecked(context: str, path: str) -> tuple[str, str, str, str]:
            """
            Get the filename from a path.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Example: "D:/some/path/video.mp4" -> ("video.mp4", "video", ".mp4", "D:/some/path")

            Args:
                context (str): The calling context.
                path:   (str): The path to get the filename from.
            Returns:
                tuple[str, str, str, str]: The filename with extension, filename, extension, and directory.
            """

            check(IsStringNotEmptyChecked(context, path))

            filename_with_extension: str = ""

            # Get Filename with Extension
            try:
                filename_with_extension = os.path.basename(path)
            except Exception as e:
                checkf(False, f"{context}: Failed to get filename from path: {path}. Error: {e}")
                return ("", "", "", "")

            # Get Filename andExtension
            filename: str = ""
            extension: str = ""
            try:
                filename, extension = os.path.splitext(filename_with_extension)
            except Exception as e:
                checkf(False, f"{context}: Failed to get extension from filename: {filename_with_extension}. Error: {e}")
                return ("", "", "", "")

            # Get Directory
            directory: str = ""

            try:
                directory = os.path.dirname(path)
            except Exception as e:
                checkf(False, f"{context}: Failed to get directory from path: {path}. Error: {e}")
                return ("", "", "", "")

            return (filename_with_extension, filename, extension, directory)
        
        @staticmethod
        def GetFilenameRaiseError(context: str, path: str) -> tuple[str, str, str, str]:
            """
            Get the filename from a path.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example: "D:/some/path/video.mp4" -> ("video.mp4", "video", ".mp4", "D:/some/path")

            Args:
                context (str): The calling context.
                path:   (str): The path to get the filename from.
            Returns:
                tuple[str, str, str, str]: The filename with extension, filename, extension, and directory.
            """

            try:
                IsStringNotEmptyRaiseError(context, path)
            except Exception as e:
                raise e

            filename_with_extension: str = ""

            # Get Filename with Extension
            try:
                filename_with_extension = os.path.basename(path)
            except Exception as e:
                raise Exception(f"{context}: Failed to get filename from path: {path}. Error: {e}")

            # Get Filename andExtension
            filename: str = ""
            extension: str = ""
            try:
                filename, extension = os.path.splitext(filename_with_extension)
            except Exception as e:
                raise Exception(f"{context}: Failed to get extension from filename: {filename_with_extension}. Error: {e}")

            # Get Directory
            directory: str = ""

            try:
                directory = os.path.dirname(path)
            except Exception as e:
                raise Exception(f"{context}: Failed to get directory from path: {path}. Error: {e}")

            return (filename_with_extension, filename, extension, directory)
        
        @staticmethod
        def GetExtensionRaiseError(context: str, path: str) -> str:
            """
            Get the extension of a path.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example: "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4" -> ".mp4"

            Args:
                context (str): The calling context.
                path:   (str): The path to get the extension from.
            Returns:
                str: The extension of the path.
            """
            try:
                IsStringNotEmptyRaiseError(context, path)
            except Exception as e:
                raise e
            
            extension: str = ""
            
            try:
                extension = os.path.splitext(path)[1]
            except Exception as e:
                raise Exception(f"{context}: Failed to get extension from path: {path}. Error: {e}")

            return extension