# IMPORT

# Library
# - Cs/Library/Library_Path.py
import Cs.Library.Library_Path as Cs_Library_Path
# - Cs/Library/Library_Image.py
import Cs.Library.Library_Image as Cs_Library_Image

# ALIAS

# "alias" - library (py)
FPyPathLibrary = Cs_Library_Path.NPyPath.FLibrary
FPyImageLibrary = Cs_Library_Image.NPyImage.FLibrary

# "alias" - functions (py)
    # Path
GetExtensionRaiseError = FPyPathLibrary.GetExtensionRaiseError

# Contants

class NPyImage:
    class NURI:
        class FLibrary:
            @staticmethod
            def GetAsDataRaiseError(context: str, image_path: str) -> str:
                """
                Get the image as data URI.
                 Assert if Failed.
                    NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

                Args:
                    context:    (str): The calling context.
                    image_path: (str): The path to the image.
                Returns:
                    str: The image as data URI (encoded base64 string).
                """
                # Get extension
                ext: str = ""

                try:
                    ext = GetExtensionRaiseError(context, image_path)
                except Exception as e:
                    raise e

                # Get image as base64
                try:
                    base64_image: str = FPyImageLibrary.GetAsBase64StringRaiseError(context, image_path)
                except Exception as e:
                    raise e
                
                ext = ext.replace(".", "")
                return f"data:image/{ext};base64,{base64_image}"