from io import BufferedReader
import os
import pyktok as pyk
from moviepy.video.io.VideoFileClip import VideoFileClip
from moviepy.audio.io.AudioFileClip import AudioFileClip
import cv2
from typing import List, Tuple

# IMPORT

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Math.py
import Cs.Library.Library_Math as Cs_Library_Math
# - Cs/Library/Library_Path.py
import Cs.Library.Library_Path as Cs_Library_Path

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
FPyMathLibrary = Cs_Library_Math.NPyMath.FLibrary
FPyPathLibrary = Cs_Library_Path.NPyPath.FLibrary

# "alias" - functions (py)
    # Common
check                      = FPyCommonLibrary.check
checkf                     = FPyCommonLibrary.checkf
IsStringNotEmptyChecked    = FPyCommonLibrary.IsStringNotEmptyChecked
IsStringNotEmptyRaiseError = FPyCommonLibrary.IsStringNotEmptyRaiseError
    # Math
IsFloatGreaterThanRaiseError = FPyMathLibrary.IsFloatGreaterThanRaiseError
    # Path
DoesPathExistRaiseError = FPyPathLibrary.DoesExistRaiseError
GetFilenameChecked = FPyPathLibrary.GetFilenameChecked
GetFilenameRaiseError = FPyPathLibrary.GetFilenameRaiseError
GetExtensionRaiseError = FPyPathLibrary.GetExtensionRaiseError

# Contants

EXTENSIONS = {".mp4"}
AUDIO_EXTENSIONS = {".pcm", ".mp3"}
AUDIO_CODECS = {
    ".pcm": "pcm_s16le",
    ".mp3": "mp3",
}

class NPyVideo:
    class FLibrary:
        @staticmethod
        def IsValidExtensionChecked(context: str, extension: str) -> bool:
            """
            Check if a given extension is a valid video extension.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Example:
                NPyVideo.FLibrary.IsValidExtensionChecked(context, ".mp4")

            Args:
                context:   (str): The calling context.
                extension: (str): The extension to check.
            Returns:
                bool: True if the extension is a valid video extension, False otherwise.
            """
            check(IsStringNotEmptyChecked(context, extension))
            checkf(extension in EXTENSIONS, f"{context}: extension: {extension} is NOT a valid video extension.")
            return True

        @staticmethod
        def IsValidExtensionRaiseError(context: str, extension: str) -> bool:
            """
            Check if a given extension is a valid video extension.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.IsValidExtensionChecked(context, ".mp4")

            Args:
                context:   (str): The calling context.
                extension: (str): The extension to check.
            Returns:
                bool: True if the extension is a valid video extension, False otherwise.
            """
            try:
                IsStringNotEmptyRaiseError(context, extension)
            except Exception as e:
                raise e
            
            if extension not in EXTENSIONS:
                raise Exception(f"{context}: extension: {extension} is NOT a valid video extension.")
            return True

        @staticmethod
        def GetDurationRaiseError(context: str, file_path: str) -> float:
            """
            Get the duration of a video.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).
            """
            ThisType = __class__

            try:
                DoesPathExistRaiseError(context, file_path)
            except Exception as e:
                raise e
            
            # Open Video
            cap: cv2.VideoCapture = None

            try:
                cap = cv2.VideoCapture(file_path)
            except Exception as e:
                raise Exception(f"{context}: Failed to open video file: {file_path}. Error: {e}")
            
            if not cap.isOpened():
                raise Exception(f"{context}: Failed to open video file: {file_path}.")
            
            # Get Frame Count
            frame_count: int = int((cap.get(cv2.CAP_PROP_FRAME_COUNT)))

            if frame_count <= 0:
                cap.release()
                raise Exception(f"{context}: Failed to get frame count from video file: {file_path}.")

            # Get FPS
            fps: float = cap.get(cv2.CAP_PROP_FPS)

            if fps <= 0:
                cap.release()
                raise Exception(f"{context}: Failed to get FPS from video file: {file_path}.")
            
            duration: float = float(frame_count) / float(fps)
            return duration

        @staticmethod
        def DownloadChecked(context: str, url: str, save_path: str):
            """
            Download a video from a URL and save it to a path.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Example:
                NPyVideo.FLibrary.DownloadChecked(context, "https://www.youtube.com/watch?v=dQw4w9WgXcQ", "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4")

            Args:
                context:   (str): The calling context.
                url:       (str): The URL of the video to download.
                save_path: (str): The path to save the video to.
            """
            ThisType = __class__

            check(IsStringNotEmptyChecked(context, url))
            check(IsStringNotEmptyChecked(context, save_path))

            filename_with_extension, filename, extension, directory = GetFilenameChecked(context, save_path)

            check(ThisType.IsValidExtensionChecked(context, extension))

            # Determine Video Type

            # TikTok
            if url.startswith("https://www.tiktok.com/") or url.startswith("http://wmw.tiktok.com/"):
                # TikTok video is only downloaded as .mp4
                ext = ".mp4"
                checkf(extension == ext, f"{context}: TikTok video is only downloaded as .mp4.")

                os.chdir(directory)

                # Example URL:
                #   url = "https://www.tiktok.com/@casted.gg/video/7516568773625662763?_r=1&_t=ZT-8xG0CXCyrIU

                video_url_part: str = url.split("?", 1)[0]
                video_url_part      = video_url_part.replace("/", "_")
                saved_filename: str = f"{video_url_part}{ext}"

                # NOTE: Setting browser may not be required.
                #pyk.specify_browser("chrome")

                # FUTURE: See if option for .cvs is useful.
                pyk.save_tiktok(f'{url}?is_copy_url=1&is_from_webapp=v1', True, '')

                # Search for saved_filename
                saved_file_path: str = os.path.join(directory, saved_filename)

                checkf(os.path.isfile(saved_file_path), f"{context}: Failed to find saved file: {saved_file_path}.")

                # Rename saved_file_path to save_path
                try:
                    os.rename(saved_file_path, save_path)
                except Exception as e:
                    checkf(False, f"{context}: Failed to rename saved file: {saved_file_path} to {save_path}. Error: {e}")

        @staticmethod
        def DownloadRaiseError(context: str, url: str, save_path: str) -> bool:
            """
            Download a video from a URL and save it to a path.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.DownloadChecked(context, "https://www.youtube.com/watch?v=dQw4w9WgXcQ", "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4")

            Args:
                context:   (str): The calling context.
                url:       (str): The URL of the video to download.
                save_path: (str): The path to save the video to.
            Returns:
                bool: True if the video was downloaded successfully, False otherwise.
            """
            ThisType = __class__

            try:
                IsStringNotEmptyRaiseError(context, url)
                IsStringNotEmptyRaiseError(context, save_path)
            except Exception as e:
                raise e

            filename_with_extension: str = ""
            filename: str = ""
            extension: str = ""
            directory: str = ""

            try:
                filename_with_extension, filename, extension, directory = GetFilenameRaiseError(context, save_path)
            except Exception as e:
                raise e

            try:
                ThisType.IsValidExtensionRaiseError(context, extension)
            except Exception as e:
                raise e

            # Determine Video Type

            # TikTok
            if url.startswith("https://www.tiktok.com/") or url.startswith("http://wmw.tiktok.com/"):
                # TikTok video is only downloaded as .mp4
                ext = ".mp4"

                if extension != ext:
                    raise Exception(f"{context}: TikTok video is only downloaded as .mp4. Extension: {extension} is NOT valid.")

                current_dir: str = os.getcwd()

                if current_dir != directory:
                    os.chdir(directory)

                # Example URL:
                #   url = "https://www.tiktok.com/@casted.gg/video/7516568773625662763?_r=1&_t=ZT-8xG0CXCyrIU"
                
                video_url_part: str = url.removeprefix("https://www.tiktok.com/")
                video_url_part      = video_url_part.removeprefix("http://wmw.tiktok.com/")
                video_url_part      = video_url_part.split("?", 1)[0]
                video_url_part      = video_url_part.replace("/", "_")
                saved_filename: str = f"{video_url_part}{ext}"

                # NOTE: Setting browser may not be required.
                #pyk.specify_browser("chrome")

                # FUTURE: See if option for .cvs is useful.

                try:
                    pyk.save_tiktok(f'{url}?is_copy_url=1&is_from_webapp=v1', True, '')
                except Exception as e:
                    os.chdir(current_dir)
                    raise Exception(f"{context}: Failed to download TikTok video: {url}. Error: {e}")

                # Search for saved_filename
                saved_file_path: str = os.path.join(directory, saved_filename)

                if not os.path.isfile(saved_file_path):
                    os.chdir(current_dir)
                    raise Exception(f"{context}: Failed to find saved file: {saved_file_path}.")

                # Rename saved_file_path to save_path
                try:
                    os.rename(saved_file_path, save_path)
                except Exception as e:
                    os.chdir(current_dir)
                    raise Exception(f"{context}: Failed to rename saved file: {saved_file_path} to {save_path}. Error: {e}")

                os.chdir(current_dir)
                return True
        
        @staticmethod
        def GetAudioAsBufferedReader(context: str, file_path: str) -> BufferedReader:
            """
            Get the audio of a video as a buffered reader.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).
            """       
            # Get Video Extension
            video_ext: str = ""
            
            try:
                video_ext = GetExtensionRaiseError(context, file_path)
            except Exception as e:
                raise e

            video_clip: VideoFileClip = None

            try:
                video_clip = VideoFileClip(file_path)
            except Exception as e:
                raise Exception(f"{context}: Failed to create video clip: {file_path}. Error: {e}")

            audio_clip: AudioFileClip = video_clip.audio

            video_ext: str = "." + video_clip.filename.split(".")[-1]
            audio_ext: str = ".pcm"

            audio_file_path: str = file_path.replace(video_ext, audio_ext)
 
            # Write Audio to File
            try:
                audio_clip.write_audiofile(audio_file_path, codec='pcm_s16le', ffmpeg_params=['-f', 's16le'])
            except Exception as e:
                raise Exception(f"{context}: Failed to write audio file: {audio_file_path}. Error: {e}")

            # Read Audio from File
            f: BufferedReader = None
            
            try:
                f = open(audio_file_path, "rb")
            except Exception as e:
                raise Exception(f"{context}: Failed to read audio file: {audio_file_path}. Error: {e}")

            return f

        @staticmethod
        def GetAudioAsString(context: str, file_path: str) -> str:
            """
            Get the audio of a video as a utf-8 string.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.GetAudioAsString(context, "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4")

            Args:
                context:   (str): The calling context.
                file_path: (str): The path to the video file.
            Returns:
                str: The audio of the video as a utf-8 string.
            """
            ThisType = __class__

            f: BufferedReader = None
            
            try:
                f = ThisType.GetAudioAsBufferedReader(context, file_path)
            except Exception as e:
                raise Exception(f"{context}: Failed to read audio file generated from video: {file_path}. Error: {e}")

            audio_data: bytes = None

            try:
                audio_data = f.read()
            except Exception as e:
                raise Exception(f"{context}: Failed to read audio data from buffered reader. Error: {e}")
            
            # Convert Audio to String
            data_str: str = ""
            
            try:
                data_str = audio_data.decode("utf-8")
            except Exception as e:
                raise Exception(f"{context}: Failed to convert audio data to string. Error: {e}")

            return data_str

        @staticmethod
        def SaveAudio(context: str, file_path: str, save_path: str) -> bool:
            """
            Save the audio of a video to a file.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.SaveAudio(context, "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4", "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp3")

            Args:
                context:   (str): The calling context.
                file_path: (str): The path to the video file.
                save_path: (str): The path to save the audio to.
            Returns:
                bool: True if the audio was saved successfully, False otherwise.
            """
            # Get Video Extension
            video_ext: str = ""
            
            try:
                video_ext = GetExtensionRaiseError(context, file_path)
            except Exception as e:
                raise e
            
            # Read Video
            video_clip: VideoFileClip = None

            try:
                with VideoFileClip(file_path) as video_clip:
                    audio_clip: AudioFileClip = video_clip.audio
                    
                    # Save Audio
                    # NOTE: Assume mp3
                    # TODO: Get codec based on extension
                    # TODO: Check valid audio extension
                    try:
                        audio_clip.write_audiofile(save_path, codec='mp3')         
                    except Exception as e:
                        audio_clip.close()
                        video_clip.close()
                        raise Exception(f"{context}: Failed to write audio file: {save_path}. Error: {e}")

                    audio_clip.close()
                    video_clip.close()

            except Exception as e:
                raise Exception(f"{context}: Failed to create video clip: {file_path}. Error: {e}")

            return True
        
        @staticmethod
        def SaveFramesAtInterval(context: str, file_path: str, save_path: str, save_extension: str, interval: float) -> List[str]:
            """
            Save frames of a video at a given interval.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.SaveFramesAtInterval(context, "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4", "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up", ".jpg", 1.0)

            Args:
                context:        (str):   The calling context.
                file_path:      (str):   The path to the video file.
                save_path:      (str):   The path to save the frames to.
                save_extension: (str):   The extension to save the frames as.
                interval:       (float): The interval in seconds to save the frames at.
            Returns:
                List[Tuple[int, float, str]]: A list of tuples containing the frame index, timestamp, and path to the saved frame.
            """
            ThisType = __class__

            # Check Parameters are Valid
            try:
                DoesPathExistRaiseError(context, file_path)
                IsStringNotEmptyRaiseError(context, save_path)
                IsStringNotEmptyRaiseError(context, save_extension)
                IsFloatGreaterThanRaiseError(context, interval, 0.0)
            except Exception as e:
                raise e

            filename_with_extension: str = ""
            filename: str = ""
            extension: str = ""
            directory: str = ""

            try:
                filename_with_extension, filename, extension, directory = GetFilenameRaiseError(context, save_path)
            except Exception as e:
                raise e

            if not os.path.exists(save_path):
                os.makedirs(save_path)

            # Open Video
            cap: cv2.VideoCapture = None

            try:
                cap = cv2.VideoCapture(file_path)
            except Exception as e:
                raise Exception(f"{context}: Failed to open video file: {file_path}. Error: {e}")
            
            if not cap.isOpened():
                raise Exception(f"{context}: Failed to open video file: {file_path}.")
            
            # Get Frame Count
            frame_count: int = int((cap.get(cv2.CAP_PROP_FRAME_COUNT)))

            if frame_count <= 0:
                cap.release()
                raise Exception(f"{context}: Failed to get frame count from video file: {file_path}.")

            # Get FPS
            fps: float = cap.get(cv2.CAP_PROP_FPS)

            if fps <= 0:
                cap.release()
                raise Exception(f"{context}: Failed to get FPS from video file: {file_path}.")
            
            # Read Frames
            output: List[Tuple[int, float, str]] = []
            
            frame_interval: int = int(fps * interval)

            frame_index: int = 0
            frame_target_index: int = 0
            frame_last = None

            INDEX = 0
            TIMESTAMP = 1
            PATH = 2

            while True:
                ret, frame = cap.read()

                # End of video
                if not ret:
                    # Save Last Frame it was NOT already Saved
                    if frame_index < frame_target_index:
                        entry: Tuple[int, float, str] = (frame_index, float(frame_index) / float(frame_count), os.path.join(save_path, f"{filename}_{frame_index}{save_extension}"))

                        try:
                            cv2.imwrite(entry[PATH], frame_last)
                        except Exception as e:
                            cap.release()
                            raise Exception(f"{context}: Failed to save frame: {entry[PATH]}. Error: {e}")
                        
                        output.append(entry)
                    break

                if frame_index == frame_target_index:
                    entry: Tuple[int, float, str] = (frame_index, float(frame_index) / float(frame_count), os.path.join(save_path, f"{filename}_{frame_index}{save_extension}"))

                    try:
                        cv2.imwrite(entry[PATH], frame)
                    except Exception as e:
                        cap.release()
                        raise Exception(f"{context}: Failed to save frame: {entry[PATH]}. Error: {e}")
                    
                    output.append(entry)
                    
                    frame_target_index += frame_interval

                frame_index += 1
                frame_last = frame

            cap.release()

            return output
        
        @staticmethod
        def GetTitleRaiseError(context: str, url: str) -> str:
            """
            Get the title of a video from a URL.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).
            """
            ThisType = __class__

            try:
                IsStringNotEmptyRaiseError(context, url)
            except Exception as e:
                raise e
            
            # Determine Video Type

            # TikTok
            if url.startswith("https://www.tiktok.com/") or url.startswith("http://wmw.tiktok.com/"):
                json_data: str = pyk.alt_get_tiktok_json(f'{url}?is_copy_url=1&is_from_webapp=v1')

                if not "__DEFAULT_SCOPE__" in json_data:
                    raise Exception(f"{context}: Failed to get TikTok video title: {url}.")
                
                if not "webapp.video-detail" in json_data["__DEFAULT_SCOPE__"]:
                    raise Exception(f"{context}: Failed to get TikTok video title: {url}.")
                
                if not "itemInfo" in json_data["__DEFAULT_SCOPE__"]["webapp.video-detail"]:
                    raise Exception(f"{context}: Failed to get TikTok video title: {url}.")
                
                if not "itemStruct" in json_data["__DEFAULT_SCOPE__"]["webapp.video-detail"]["itemInfo"]:
                    raise Exception(f"{context}: Failed to get TikTok video title: {url}.")
                
                if "stickersOnItem" in json_data["__DEFAULT_SCOPE__"]["webapp.video-detail"]["itemInfo"]["itemStruct"]:
                    title: str = ""

                    for item in json_data["__DEFAULT_SCOPE__"]["webapp.video-detail"]["itemInfo"]["itemStruct"]["stickersOnItem"]:
                        title += f"{item}\n"
                    title.removesuffix("\n")
                    return title
                
                # "desc"
                if not "desc" in json_data["__DEFAULT_SCOPE__"]["webapp.video-detail"]["itemInfo"]["itemStruct"]:
                    raise Exception(f"{context}: Failed to get TikTok video title: {url}.")

                return json_data["__DEFAULT_SCOPE__"]["webapp.video-detail"]["itemInfo"]["itemStruct"]["desc"]
            else:
                raise Exception(f"{context}: Unsupported video type: {url}.")         
            return ""