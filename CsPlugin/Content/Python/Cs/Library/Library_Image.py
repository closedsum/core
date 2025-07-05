import base64

# IMPORT

# Library
# - Cs/Library/Library_Path.py
import Cs.Library.Library_Path as Cs_Library_Path

# ALIAS

# "alias" - library (py)
FPyPathLibrary = Cs_Library_Path.NPyPath.FLibrary

class NPyImage:
    class FLibrary:
        @staticmethod
        def GetAsBytesRaiseError(context: str, image_path: str) -> bytes:
            """
            Get the image as bytes.
             Assert if Failed.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context     (str): The calling context.
                image_path  (str): The path to the image.
            Returns:
                bytes: The image as bytes.
            """
            # Check image_path exits
            try:
                FPyPathLibrary.DoesExistRaiseError(context, image_path)
            except Exception as e:
                raise e

            # Read image as bytes
            image_data: bytes = None

            try:
                with open(image_path, "rb") as image_file:
                    image_data = image_file.read()
            except Exception as e:
                raise Exception(f"{context}: Failed to get image as bytes: {image_path}. Error: {e}")
            return image_data
        
        @staticmethod
        def GetAsBase64RaiseError(context: str, image_path: str) -> str:
            """
            Get the image as base64.
             Assert if Failed.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context     (str): The calling context.
                image_path  (str): The path to the image.
            Returns:
                str: The image as base64.
            """
            ThisType = __class__

            # Read image as bytes
            image_data: bytes = None

            try:
                image_data = ThisType.GetAsBytesRaiseError(context, image_path)
            except Exception as e:
                raise e
            
            # Encode Image as base64
            encoded_bytes: bytes = None
                  
            try:
                encoded_bytes = base64.b64encode(image_data)
            except Exception as e:
                raise Exception(f"{context}: Failed to encode image as base64: {image_path}. Error: {e}")
            return encoded_bytes
        
        def GetAsBase64StringRaiseError(context: str, image_path: str) -> str:
            """
            Get the image as base64 string.
             Assert if Failed.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Args:
                context     (str): The calling context.
                image_path  (str): The path to the image.
            Returns:
                str: The image as base64 string.
            """
            ThisType = __class__
            
            # Get Image as base64
            encoded_bytes: bytes = None

            try:
                encoded_bytes = ThisType.GetAsBase64RaiseError(context, image_path)
            except Exception as e:
                raise e
            
            # Return encoded bytes as string
            return encoded_bytes.decode('utf-8')