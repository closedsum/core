import unreal as ue
from io import BufferedReader
import os
import shutil
import pyktok as pyk
from moviepy.video.io.VideoFileClip import VideoFileClip
from moviepy.audio.io.AudioFileClip import AudioFileClip
import yt_dlp as yt
import cv2
import ffmpeg
from datetime import datetime
from typing import List, Tuple, Dict

# IMPORT

# Library
# - Cs/Library/Library_Common.py
import Cs.Library.Library_Common as Cs_Library_Common
# - Cs/Library/Library_Math.py
import Cs.Library.Library_Math as Cs_Library_Math
# - Cs/Library/Library_Array.py
import Cs.Library.Library_Array as Cs_Library_Array
# - Cs/Library/Library_Path.py
import Cs.Library.Library_Path as Cs_Library_Path
# - Cs/Library/Library_Audio.py
import Cs.Library.Library_Audio as Cs_Library_Audio

# "alias" - library (py)
FPyCommonLibrary = Cs_Library_Common.NPyCommon.FLibrary
FPyMathLibrary = Cs_Library_Math.NPyMath.FLibrary
FPyArrayLibrary = Cs_Library_Array.NPyArray.FLibrary
FPyPathLibrary = Cs_Library_Path.NPyPath.FLibrary
FPyAudioLibrary = Cs_Library_Audio.NPyAudio.FLibrary

# "alias" - functions (py)
    # Common
check                      = FPyCommonLibrary.check
checkf                     = FPyCommonLibrary.checkf
IsStringNotEmptyChecked    = FPyCommonLibrary.IsStringNotEmptyChecked
IsStringNotEmptyRaiseError = FPyCommonLibrary.IsStringNotEmptyRaiseError
IsValidDictRaiseError      = FPyCommonLibrary.IsValidDictRaiseError
    # Math
IsFloatGreaterThanRaiseError = FPyMathLibrary.IsFloatGreaterThanRaiseError
    # Array
IsNotEmptyRaiseError = FPyArrayLibrary.IsNotEmptyRaiseError
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

def get_ffmpeg_path():
    """Get FFMPEG path"""
    
    project_dir: str = ue.Paths.project_dir()
    project_dir = ue.Paths.convert_relative_path_to_full(project_dir)
    ffmepg_exe: str = f"{project_dir}ThirdParty/ffmpeg/bin/ffmpeg.exe"
    ffmepg_exe = ffmepg_exe.replace("/", "\\\\")
    return ffmepg_exe

def get_ffprobe_path():
    """Get FFProbe path"""
    
    project_dir: str = ue.Paths.project_dir()
    project_dir = ue.Paths.convert_relative_path_to_full(project_dir)
    ffprobe_exe: str = f"{project_dir}ThirdParty/ffmpeg/bin/ffprobe.exe"
    ffprobe_exe = ffprobe_exe.replace("/", "\\\\")
    return ffprobe_exe

FFMPEG_PATH = get_ffmpeg_path()
FFPROBE_PATH = get_ffprobe_path()

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
        def GetVideoType(context: str, url: str) -> str:
            """
            Get the type of video.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.GetVideoType(context, "https://www.tiktok.com/@casted.gg/video/7516568773625662763")

            Args:
                context:   (str): The calling context.
                url:       (str): The URL of the video.
            Returns:
                str: The type of video.
            """
            try:
                IsStringNotEmptyRaiseError(context, url)
            except Exception as e:
                raise e
            
            # TikTok
            if url.startswith("https://www.tiktok.com/") or url.startswith("http://wmw.tiktok.com/"):
                return "TikTok"
            # YouTube
            if url.startswith("https://www.youtube.com/") or url.startswith("http://www.youtube.com/"):
                return "YouTube"        
            return ""
            
        @staticmethod
        def IsURL_TikTok_RaiseError(context: str, url: str) -> bool:
            """
            Check if a URL is a valid TikTok URL.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).
            """
            ThisType = __class__

            video_type: str = ThisType.GetVideoType(context, url)
        
            if video_type != "TikTok":
                raise Exception(f"{context}: URL: {url} is NOT a valid TikTok URL.")
            return True

        @staticmethod
        def IsURL_YouTube_RaiseError(context: str, url: str) -> bool:
            """
            Check if a URL is a valid YouTube URL.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).
            """
            ThisType = __class__

            video_type: str = ThisType.GetVideoType(context, url)

            if video_type != "YouTube":
                raise Exception(f"{context}: URL: {url} is NOT a valid YouTube URL.")
            return True

        class FDownload:
            class FParams:
                """
                Params for downloading a video.
                """

                URL: str = ""
                """
                The URL of the video to download.
                """
                SavePath: str = ""
                """
                The path to save the video to.
                """
                MaxTotalPixels: int = 0
                """
                The maximum total number of pixels of the video.
                """
                Info: Dict[str, any] = {}
                """
                The information of the video to download.
                 const | NOT mutable
                """

                def __init__(self):
                    self.URL: str = ""
                    self.SavePath: str = ""
                    self.MaxTotalPixels: int = 1920 * 1080
                    self.Info: Dict[str, any] = {}

                def Reset(self):
                    self.URL = ""
                    self.SavePath = ""
                    self.MaxTotalPixels: int = 1920 * 1080
                    self.Info = {}

                def IsValidChecked(self, context: str) -> bool:
                    check(IsStringNotEmptyChecked(context, self.URL))
                    check(IsStringNotEmptyChecked(context, self.SavePath))
                    return True

                def IsValidRaiseError(self, context: str) -> bool:
                    try:
                        IsStringNotEmptyRaiseError(context, self.URL)
                        IsStringNotEmptyRaiseError(context, self.SavePath)
                    except Exception as e:
                        raise e
                    return True

        @staticmethod
        def TikTok_DownloadRaiseError(context: str, params: FDownload.FParams) -> Dict[str, any]:
            """
            Download a TikTok video.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.TikTok_DownloadRaiseError(context, "https://www.tiktok.com/@casted.gg/video/7516568773625662763", "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4")

            Args:
                context:   (str):               The calling context.
                params:    (FDownload.FParams): The parameters for the download.
            Returns:
                Dict[str, any]: The result of the download.
                 Format:
                  Dict["video_type"]: str
                   - The type of video.
                  Dict["video_has_audio"]: bool
                   - Whether the video has audio.
                  Dict["video_title"]: str | None
                   - The title of the video.
                  Dict["video_file_path"]: str
                   - The path to the downloaded video file.
            """
            ThisType = __class__

            try:
                params.IsValidRaiseError(context)
            except Exception as e:
                raise e

            url: str = params.URL
            save_path: str = params.SavePath

            # Check URL is Valid (TikTok)
            try:
                ThisType.IsURL_TikTok_RaiseError(context, url)
            except Exception as e:
                raise e
            
            # Get Filename
            filename_with_extension: str = ""
            filename: str = ""
            extension: str = ""
            directory: str = ""

            try:
                filename_with_extension, filename, extension, directory = GetFilenameRaiseError(context, save_path)
            except Exception as e:
                raise e

            # Check Extension is Valid / Supported
            try:
                ThisType.IsValidExtensionRaiseError(context, extension)
            except Exception as e:
                raise e

            result: Dict[str, any] = {}

            # TODO: Get relevant info from TikTok
            result["video_type"] = "TikTok"
            result["video_has_audio"] = True

            # TikTok video is only downloaded as .mp4
            ext = ".mp4"

            if extension != ext:
                raise Exception(f"{context}: TikTok video is only downloaded as .mp4. Extension: {extension} is NOT valid.")

            # Change Current Working Directory to save_path's directory
            # NOTE: PyKTok ONLY saves to the current working directory
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

            result["video_file_path"] = save_path

            os.chdir(current_dir)
            return result

        @staticmethod
        def YouTube_DownloadRaiseError(context: str, params: FDownload.FParams) -> Dict[str, any]:
            """
            Download a YouTube video.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:    
                params = FDownload.FParams()
                params.URL            = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
                params.SavePath       = "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4"
                params.MaxTotalPixels = 1920 * 1080
                params.Info           = info

                NPyVideo.FLibrary.YouTube_DownloadRaiseError(context, params)

            Args:
                context:   (str):               The calling context.
                params:    (FDownload.FParams): The parameters for the download.
            Returns:
                Dict[str, any]: The result of the download.
                 Format:
                  Dict["video_type"]: str
                   - The type of video.
                  Dict["video_has_audio"]: bool
                   - Whether the video has audio.
                  Dict["video_title"]: str | None
                   - The title of the video.
                  Dict["video_file_path"]: str
                   - The path to the downloaded video file.
            """
            ThisType = __class__

            try:
                params.IsValidRaiseError(context)
            except Exception as e:
                raise e
            
            url: str = params.URL
            save_path: str = params.SavePath

            # Check URL is Valid (YouTube)
            try:
                ThisType.IsURL_YouTube_RaiseError(context, url)
            except Exception as e:
                raise e
            
            info: Dict[str, any]  = params.Info
            max_total_pixels: int = params.MaxTotalPixels

            result: Dict[str, any] = {}

            # NOTE: For now, download the YouTube audio separately and then combine.
            # TODO: Look into why combining the video and audio with yt_dlp is NOT working.
            result["video_type"] = "YouTube"
            result["video_has_audio"] = False

            formats: List[Dict[str, any]] = info.get('formats', [])

            try:
                IsNotEmptyRaiseError(context, formats)
            except Exception as e:
                raise Exception(f"{context}: Failed to get ANY formats from YouTube video: {url}. Error: {e}")
            
            # Get Video Title
            video_title: str = info.get('title', None)

            if video_title == None:
                raise Exception(f"{context}: Failed to get video title from YouTube video: {url}.")

            result["video_title"] = video_title

            # Get the appropriate format to download
            # ASSUME: Only download .mp4 formats
            video_formats = []

            if max_total_pixels == 0:
                max_total_pixels = 4096 * 2160

            largest_total_pixels: int = 0
            smallest_file_size: int = 0

            for f in formats:
                format_id: str  = f.get('format_id')
                ext: str        = f.get('ext')
                resolution: str = f.get('resolution')
                file_size: int  = f.get('filesize')

                # Only get video formats with .mp4 extension
                if resolution.find('audio') == -1 and ext == 'mp4' and file_size != None:
                    # Filter by total pixels
                    parts: List[str] = resolution.split('x')

                    if len(parts) == 2:
                        width: int        = int(parts[0])
                        height: int       = int(parts[1])
                        total_pixels: int = width * height

                        # Filter by max total pixels
                        if total_pixels <= max_total_pixels:
                            if total_pixels >= largest_total_pixels:
                                if smallest_file_size == 0:
                                    smallest_file_size = file_size
                            
                                if total_pixels > largest_total_pixels or file_size < smallest_file_size:
                                    video_formats.clear()

                                smallest_file_size = file_size
                                largest_total_pixels = total_pixels
                                video_formats.append(f)
            
            try:
                IsNotEmptyRaiseError(context, video_formats)
            except Exception as e:
                raise Exception(f"{context}: Failed to get ANY Valid video formats from YouTube video: {url}. Error: {e}")
            
            # Get the format with the smallest file size
            format_to_download: Dict[str, any] = video_formats[0]
            format_id: str                     = format_to_download.get('format_id')

            # Download Video
            filename_with_extension: str = ""
            filename: str = ""
            extension: str = ""
            directory: str = ""

            try:
                filename_with_extension, filename, extension, directory = GetFilenameRaiseError(context, save_path)
            except Exception as e:
                raise e

            ydl_opts = {
                'format': format_id,
                'outtmpl': f'{directory}/{filename}.%(ext)s',
                'ffmpeg_location': FFMPEG_PATH,
            }

            try:
                with yt.YoutubeDL(ydl_opts) as ydl:
                    ydl.download([url])
            except Exception as e:
                raise Exception(f"{context}: Failed to download YouTube video: {url}. Error: {e}")
    
            # Check YouTube video was downloaded
            if not os.path.exists(save_path):
                raise Exception(f"{context}: Failed to find saved file: {save_path}.")

            result["video_file_path"] = save_path

            return result

        @staticmethod
        def DownloadChecked(context: str, params: FDownload.FParams) -> Dict[str, any]:
            """
            Download a video from a URL and save it to a path.
                NOTE: Allowed ONLY on Main Thread (Game Thread).

            Example:
                params = FDownload.FParams()
                params.URL      = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
                params.SavePath = "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4"

                NPyVideo.FLibrary.DownloadChecked(context, params)

            Args:
                context:   (str):               The calling context.
                params:    (FDownload.FParams): The parameters for the download.
            Returns:
                Dict[str, any]: The result of the download.
            """
            ThisType = __class__

            check(params.IsValidChecked(context))

            url: str = params.URL
            save_path: str = params.SavePath

            filename_with_extension, filename, extension, directory = GetFilenameChecked(context, save_path)

            check(ThisType.IsValidExtensionChecked(context, extension))

            result: Dict[str, any] = {}

            # TikTok
            if url.startswith("https://www.tiktok.com/") or url.startswith("http://wmw.tiktok.com/"):
                result["video_type"] = "TikTok"

                # TikTok video is only downloaded as .mp4
                ext = ".mp4"
                checkf(extension == ext, f"{context}: TikTok video is only downloaded as .mp4.")

                # Create Directory if it does not exist
                if not os.path.exists(directory):
                    os.makedirs(directory)

                # Change to Directory
                # NOTE: pyktok only saves to the current working directory
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
                return result
            # YouTube
            if url.startswith("https://www.youtube.com/") or url.startswith("http://www.youtube.com/"):
                result["video_type"] = "YouTube"

                return result
            
            checkf(False, f"{context}: Unsupported URL: {url}.")
            return result

        @staticmethod
        def DownloadRaiseError(context: str, params: FDownload.FParams) -> Dict[str, any]:
            """
            Download a video from a URL and save it to a path.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                params = FDownload.FParams()
                params.URL            = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
                params.SavePath       = "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp4"
                params.MaxTotalPixels = 1920 * 1080
                params.Info           = info

                NPyVideo.FLibrary.DownloadRaiseError(context, params)

            Args:
                context:   (str):               The calling context.
                params:    (FDownload.FParams): The parameters for the download.
            Returns:
                Dict[str, any]: The result of the download.
                 Format:
                  Dict["video_type"]: str
                   - The type of video.
                  Dict["video_has_audio"]: bool
                   - Whether the video has audio.
                  Dict["video_title"]: str | None
                   - The title of the video.
                  Dict["video_file_path"]: str
                   - The path to the downloaded video file.
            """
            # TODO: FUTURE: change to have params
            ThisType = __class__

            video_type: str = ThisType.GetVideoType(context, params.URL)

            # TikTok
            if video_type == "TikTok":
                return ThisType.TikTok_DownloadRaiseError(context, params)
            # YouTube
            if video_type == "YouTube":
                return ThisType.YouTube_DownloadRaiseError(context, params)
            
            raise Exception(f"{context}: Unsupported URL: {params.URL}.")
            return {}
        
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
                video_clip.close()
                del video_clip
                video_clip = None
                raise Exception(f"{context}: Failed to create video clip: {file_path}. Error: {e}")

            audio_clip: AudioFileClip = video_clip.audio

            video_ext: str = "." + video_clip.filename.split(".")[-1]
            audio_ext: str = ".pcm"

            audio_file_path: str = file_path.replace(video_ext, audio_ext)
 
            # Write Audio to File
            try:
                audio_clip.write_audiofile(audio_file_path, codec='pcm_s16le', ffmpeg_params=['-f', 's16le'])
            except Exception as e:
                video_clip.close()
                del video_clip
                video_clip = None
                audio_clip.close()
                del audio_clip
                audio_clip = None
                raise Exception(f"{context}: Failed to write audio file: {audio_file_path}. Error: {e}")

            video_clip.close()
            del video_clip
            video_clip = None
            audio_clip.close()
            del audio_clip
            audio_clip = None

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
                f.close()
            except Exception as e:
                f.close()
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
        
        @staticmethod
        def GetInfoRaiseError(context: str, url: str) -> Dict[str, any]:
            """
            Get the info of a video from a URL.
             For now, the dictionary information of the video may be formatted differently for different URLs.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.GetInfoRaiseError(context, "https://www.youtube.com/watch?v=dQw4w9WgXcQ")

            Args:
                context: (str): The calling context.
                url:     (str): The URL of the video.
            Returns:
                Dict[str, any]: The info of the video.
            """
            ThisType = __class__

            video_type: str = ""

            try:
                video_type = ThisType.GetVideoType(context, url)
            except Exception as e:
                raise e
        
            info: Dict[str, any] = {}

            # TikTok
            if video_type == "TikTok":
                # NOTE: TODO: Implement TikTok Info later
                return info
            # YouTube
            if video_type == "YouTube":
                ydl_opts = {
                    'download': False,
                    'ffmpeg_location': FFMPEG_PATH,
                }

                try:
                    with yt.YoutubeDL(ydl_opts) as ydl:
                        info = ydl.extract_info(url, download=False)
                except Exception as e:
                    raise Exception(f"{context}: Failed to get Info from URL: {url}. Error: {e}")

            return info
        
        @staticmethod
        def YouTube_DownloadTranscriptRaiseError(context: str, url: str) -> List[Dict[str, any]]:
            """
            Get the transcript of a YouTube video from a URL.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.YouTube_DownloadTranscriptRaiseError(context, "https://www.youtube.com/watch?v=dQw4w9WgXcQ")

            Args:
                context: (str): The calling context.
                url:     (str): The URL of the video.
            Returns:
                List[Dict[str, any]]: The transcript of the video.
            """
            ThisType = __class__

            # Check URL is YouTube
            try:
                ThisType.IsURL_YouTube_RaiseError(context, url)
            except Exception as e:
                raise e
            
            # Create Temp Directory
            current_dir: str           = os.path.dirname(os.path.abspath(__file__))
            current_time_str: str      = datetime.now().strftime("%Y%m%d%H%M%S")
            temp_dir: str              = os.path.join(current_dir, f"_temp_{current_time_str}")
            temp_srt_path_no_ext: str  = os.path.join(temp_dir, f"_sub_{current_time_str}")
            temp_srt_path: str         = f"{temp_srt_path_no_ext}.en.srt"

            # Download Subtitles
            ydl_opts = {
                'download': False,
                'writeautomaticsub': True,
                'subtitlesformat': 'srt',
                'skip_download': True,
                'outtmpl': temp_srt_path_no_ext
            }

            try:
                with yt.YoutubeDL(ydl_opts) as ydl:
                    ydl.download([url])
            except Exception as e:
                raise Exception(f"{context}: Failed to get Info from URL: {url}. Error: {e}")
            
            # Convert SRT to Dictionary
            try:
                subtitles: List[Dict[str, any]] = ThisType.SRTToDictionaryRaiseError(context, temp_srt_path)

                # Delete Temp Directory
                if os.path.exists(temp_dir):
                    try:
                        shutil.rmtree(temp_dir)
                    except Exception as e:
                        raise Exception(f"{context}: Failed to delete directory: {temp_dir}. Error: {e}")
                else:
                    raise Exception(f"{context}: Failed to find temp directory: {temp_dir}.")
                
                return subtitles
            except Exception as e:
                if os.path.exists(temp_dir):
                    try:
                        shutil.rmtree(temp_dir)
                    except Exception as e:
                        raise Exception(f"{context}: Failed to delete directory: {temp_dir}. Error: {e}")
                else:
                    raise Exception(f"{context}: Failed to find temp directory: {temp_dir}. Error: {e}")
                
                raise e
            return []

        @staticmethod
        def DownloadTranscriptRaiseError(context: str, url: str) -> List[Dict[str, any]]:
            """
            Get the transcript of a video from a URL.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.DownloadTranscriptRaiseError(context, "https://www.youtube.com/watch?v=dQw4w9WgXcQ")

            Args:
                context: (str): The calling context.
                url:     (str): The URL of the video.
            Returns:
                List[Dict[str, any]]: The transcript of the video.
            """
            ThisType = __class__

            # Get Video Type
            video_type: str = ""
            
            try:
                video_type = ThisType.GetVideoType(context, url)
            except Exception as e:
                raise e
            
            try:
                # YouTube
                if video_type == "YouTube":
                    return ThisType.YouTube_DownloadTranscriptRaiseError(context, url)
            except Exception as e:
                raise e
            return []

        @staticmethod
        def CanDownloadTranscriptRaiseError(context: str, url: str) -> bool:
            """
            Check if a transcript can be downloaded from a URL.
             Assert if parameters are NOT Valid.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.CanDownloadTranscriptRaiseError(context, "https://www.youtube.com/watch?v=dQw4w9WgXcQ")

            Args:
                context: (str): The calling context.
                url:     (str): The URL of the video.
            Returns:    
                bool: True if a transcript can be downloaded from the URL, False otherwise.
            """
            ThisType = __class__

            # Get Video Type
            video_type: str = ""
            
            try:
                video_type = ThisType.GetVideoType(context, url)
            except Exception as e:
                raise e
            
            # YouTube
            if video_type == "YouTube":
                return True
            return False
            
        @staticmethod
        def SRTToDictionaryRaiseError(context: str, srt_path: str) -> List[Dict[str, any]]:
            """
            Convert an SRT file to a dictionary.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.SRTToDictionaryRaiseError(context, "D://Trees//cs10//Content//Python//Cs//Library//UnitTest//Test//sub.srt")

            Args:
                context:  (str): The calling context.
                srt_path: (str): The path to the SRT file.
            Returns:
                List[Dict[str, any]]: The dictionary of the SRT file.
            """
            ThisType = __class__

            try:
                DoesPathExistRaiseError(context, srt_path)
            except Exception as e:
                raise e

            # Read SRT File
            subtitles: List[Dict[str, any]] = []

            try:
                with open(srt_path, 'r', encoding='utf-8') as f:
                    content = f.read().strip()
                
                # Split the content into individual subtitle blocks
                blocks = content.split('\n\n')

                for block in blocks:
                    lines = block.strip().split('\n')
                    if not lines:
                        continue

                    # Extract index
                    try:
                        index: int = int(lines[0])
                    except ValueError:
                        continue # Skip if the first line is not a valid index

                    # Extract timestamps
                    timestamps                   = lines[1]
                    time_start_str, time_end_str = timestamps.split(' --> ')

                    # Extract subtitle text
                    text: str = '\n'.join(lines[2:])

                    subtitle_entry: Dict[str, any] = {
                        'index': index,
                        'start_time': time_start_str,
                        'end_time': time_end_str,
                        'text': text
                    }
                    subtitles.append(subtitle_entry)          
            except Exception as e:
                raise Exception(f"{context}: Failed to read SRT file: {srt_path}. Error: {e}")         
            return subtitles
        
        @staticmethod
        def NeedDownloadAudioRaiseError(context: str, url: str) -> bool:
            """
            Check if a audio from the video URL needs to be downloaded.
             Assert if parameters are NOT Valid.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.NeedDownloadAudioRaiseError(context, "https://www.youtube.com/watch?v=dQw4w9WgXcQ")

            Args:
                context: (str): The calling context.
                url:     (str): The URL of the video.
            Returns:    
                bool: True if the audio from the video URL needs to be downloaded, False otherwise.
            """
            ThisType = __class__

            try:
                IsStringNotEmptyRaiseError(context, url)
            except Exception as e:
                raise e

            video_type: str = ""
            
            try:
                video_type = ThisType.GetVideoType(context, url)
            except Exception as e:
                raise e
            
            # YouTube
            if video_type == "YouTube":
                return True
            return False

        @staticmethod
        def YouTube_DownloadAudioRaiseError(context: str, params: FDownload.FParams) -> Dict[str, any]:
            """
            Download the audio of a YouTube video.
             Assert if Failed.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).
                      This usually downloads a .mp4 file for audio.

            Example:
                params = FDownload.FParams()
                params.URL      = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
                params.SavePath = "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp3"
                params.Info     = info

                NPyVideo.FLibrary.YouTube_DownloadAudioRaiseError(context, params)

            Args:
                context:   (str):               The calling context.
                params:    (FDownload.FParams): The parameters for the download.
            Returns:
                Dict[str, any]: The info of the video.
                Format:
                  Dict["audio_path"] -> str
                   - The path to the downloaded audio file.
            """      
            ThisType = __class__

            try:
                params.IsValidRaiseError(context)
            except Exception as e:
                raise e
            
            url: str             = params.URL
            save_path: str       = params.SavePath
            info: Dict[str, any] = params.Info

            # Check URL is YouTube
            try:
                ThisType.IsURL_YouTube_RaiseError(context, url)
            except Exception as e:
                raise e

            # Parse save_path
            filename_with_extension: str = ""
            filename: str = ""
            extension: str = ""
            directory: str = ""

            try:
                filename_with_extension, filename, extension, directory = GetFilenameRaiseError(context, save_path)
            except Exception as e:
                raise e
            
            # Get Formats
            formats: List[Dict[str, any]] = info.get('formats', None)

            try:
                IsNotEmptyRaiseError(context, formats)
            except Exception as e:
                raise Exception(f"{context}: Failed to get formats from URL: {url}. Error: {e}")
            
            # Gather Audio formats
            audio_formats: List[Dict[str, any]] = []

            for f in formats:
                # Check formats that have a resolution that contains "audio"
                resolution: str = f.get('resolution')

                if resolution != None:
                    if resolution.find('audio') != -1:
                        audio_formats.append(f)

            # Look for Audio Formats with [default, low], [default], and [low]
            #  Priority: [default, low] > [default] > [low]
            DEFAULT_LOW = "default_low"
            DEFAULT     = "default"
            LOW         = "low"

            default_audio_id: str     = None
            default_low_audio_id: str = None
            low_audio_id: str         = None
            audio_exts: Dict[str, str]= {}
            audio_exts[DEFAULT_LOW]   = None
            audio_exts[DEFAULT]       = None
            audio_exts[LOW]           = None
            audio_ext: str            = None

            for f in audio_formats:
                format_id = f.get('format_id')
                note: str = f.get('format_note')
                ext: str  = f.get('ext')

                # Check for [default, low] or [default]
                if note.find('Default') != -1 or note.find('default') != -1:
                    # Check for [default, low]
                    if note.find('Low') != -1 or note.find('low') != -1:
                        default_low_audio_id = format_id
                        audio_exts[DEFAULT_LOW] = ext
                    # Check for [default]
                    else:
                        default_audio_id = format_id
                        audio_exts[DEFAULT] = ext
                # Check for [low]
                elif note.find('Low') != -1 or note.find('low') != -1:
                    low_audio_id = format_id
                    audio_exts[LOW] = ext

            audio_id  = default_audio_id
            audio_ext = audio_exts[DEFAULT]

            if default_low_audio_id != None:
                audio_id = default_low_audio_id
                audio_ext = audio_exts[DEFAULT_LOW]
            elif low_audio_id != None:
                audio_id = low_audio_id
                audio_ext = audio_exts[LOW]

            if audio_id == None:
                raise Exception(f"{context}: Failed to find audio ID for URL: {url}.")

            if audio_ext == None:
                raise Exception(f"{context}: Failed to find audio extension for URL: {url}.")

            # Delete Existing File
            if os.path.exists(save_path):
                try:
                    os.remove(save_path)
                except OSError as e:
                    raise Exception(f"{context}: Error: {e} - Could not delete file '{save_path}'.")

            # Setup Download Options
            ydl_opts = {
                'format': audio_id,  # Download best video and audio quality
                'outtmpl': f'{directory}/{filename}.%(ext)s',  # Output file name template
                'ffmpeg_location': FFMPEG_PATH,
            }

            # Download Audio
            try:
                with yt.YoutubeDL(ydl_opts) as ydl:
                    ydl.download([url])
            except Exception as e:
                raise Exception(f"{context}: Error downloading audio: {e}")
            
            audio_path: str = f"{directory}/{filename}.{audio_ext}"

            result: Dict[str, any] = {}
            result["audio_path"] = audio_path

            return result
     
        @staticmethod
        def DownloadAudioRaiseError(context: str, params: FDownload.FParams) -> Dict[str, any]:
            """
            Download the audio of a video.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                params = FDownload.FParams()
                params.URL      = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
                params.SavePath = "C:/Users/User/Downloads/Rick_Astley_Never_Gonna_Give_You_Up.mp3"
                params.Info     = info

                NPyVideo.FLibrary.DownloadAudioRaiseError(context, params)

            Args:
                context:   (str):               The calling context.
                params:    (FDownload.FParams): The parameters for the download.
            Returns:
                Dict[str, any]: The info of the audio of the video.
                 Format:
                  Dict["audio_path"] -> str
                   - The path to the downloaded audio file.
            """
            ThisType = __class__
  
            # Get Video Type
            video_type: str = ""
            
            try:
                video_type = ThisType.GetVideoType(context, params.URL)
            except Exception as e:
                raise e

            try:
                # YouTube
                if video_type == "YouTube":
                    return ThisType.YouTube_DownloadAudioRaiseError(context, params)
            except Exception as e:
                raise e
            
            raise Exception(f"{context}: Unsupported video type: {video_type} for URL: {params.URL}.")
            return {}

        @staticmethod
        def CombineVideoAudioRaiseError(context: str, video_path: str, audio_path: str, save_path: str):
            """
            Combine a video and audio into a single file.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                NPyVideo.FLibrary.CombineVideoAudioRaiseError(context, video_path, audio_path)

            Args:
                context:    (str): The calling context.
                video_path: (str): The path to the video file.
                audio_path: (str): The path to the audio file.
                save_path:  (str): The path to save the combined file.
            Returns:
                None
            """
            try:
                DoesPathExistRaiseError(context, video_path)
                DoesPathExistRaiseError(context, audio_path)
            except Exception as e:
                raise e
            
            # Input Video
            input_video = None

            try:
                input_video = ffmpeg.input(video_path)
            except Exception as e:
                raise Exception(f"{context}: Failed to input video: {video_path}. Error: {e}")
            
            # Input Audio
            input_audio = None

            try:
                input_audio = ffmpeg.input(audio_path)
            except Exception as e:
                raise Exception(f"{context}: Failed to input audio: {audio_path}. Error: {e}")

            # Combine Video and Audio
            try:
                ffmpeg.output(input_video, input_audio, save_path, vcodec='copy', acodec='copy').run(cmd=FFMPEG_PATH, capture_stdout=True, capture_stderr=True)
            except ffmpeg.Error as e:
                output: str = f"{context}: FFmpeg error occurred:"
                output     += f"\n  stderr: {e.stderr.decode('utf-8') if e.stderr else 'No stderr'}"
                output     += f"\n  stdout: {e.stdout.decode('utf-8') if e.stdout else 'No stdout'}"
                output     += f"\n  {e}"
                raise Exception(output)
            except Exception as e:
                raise Exception(f"{context}: Unexpected error: {e}")
            