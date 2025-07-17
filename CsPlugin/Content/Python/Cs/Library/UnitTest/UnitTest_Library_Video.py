import os
import shutil
from datetime import datetime
import time
from typing import Dict

# IMPORT

# Library
# - Cs/Library/Library_Video.py
import Cs.Library.Library_Video as Cs_Library_Video

# ALIAS

# "alias" - library (py)
FPyVideoLibrary = Cs_Library_Video.NPyVideo.FLibrary

def delete_output_directory(context: str, output_dir: str):
    if os.path.exists(output_dir):
        try:
            shutil.rmtree(output_dir)
            return True
        except Exception as e:
            raise Exception(f"{context}: Failed to delete directory: {output_dir}. Error: {e}")
        return False
    return True

def GetYouTubeURL() -> str:
    return "https://www.youtube.com/watch?v=kPa7bsKwL-c"

def ut_YouTube_GetInfoRaiseError():
    context: str = f"{os.path.basename(__file__)}.ut_YouTube_GetInfoRaiseError"

    url: str = GetYouTubeURL()

    print(f"{context}: Unit Test: YouTube_GetInfoRaiseError")
    print(f"Script File: Cs/Library/Library_Video.py")
    print(f"Class: {FPyVideoLibrary.__class__.__qualname__}")

    # Retrieve YouTube video info
    print(f"{context}: Retrieve YouTube video info - START")

    start_time: datetime = datetime.now()

    info: Dict[str, any] = {}

    try:
        info = FPyVideoLibrary.GetInfoRaiseError(context, url)
    except Exception as e:
        print(f"{context}: Failed to get YouTube video info: {e}")
        print(f"FAIL")
        return

    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")
    print(f"SUCCESS")

def ut_YouTube_DownloadRaiseError():
    context: str = f"{os.path.basename(__file__)}.ut_YouTube_DownloadRaiseError"

    delete_files_at_end: bool = True

    current_time: datetime = datetime.now()
    current_time_str: str  = current_time.strftime("%Y%m%d%H%M%S")

    current_file_path: str = os.path.abspath(__file__)
    output_dir: str        = f"{os.path.dirname(current_file_path)}/Test"

    # Clear existing output directory
    if not delete_output_directory(context, output_dir):
        print(f"FAIL")
        return

    save_path: str = f"{output_dir}/yt_video_{current_time_str}.mp4"

    params: FPyVideoLibrary.FDownload.FParams = FPyVideoLibrary.FDownload.FParams()
    params.URL      = GetYouTubeURL()
    params.SavePath = save_path

    print(f"{context}: Unit Test: YouTube_DownloadRaiseError")
    print(f"Script File: Cs/Library/Library_Video.py")
    print(f"Class: {FPyVideoLibrary.__class__.__qualname__}")

    # Retrieve YouTube video info
    print(f"{context}: Retrieve YouTube video info - START")

    start_time: datetime = datetime.now()

    try:
        params.Info = FPyVideoLibrary.GetInfoRaiseError(context, params.URL)
    except Exception as e:
        print(f"{context}: Failed to get YouTube video info: {e}")
        print(f"FAIL")
        return

    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Download YouTube video
    print(f"{context}: Download YouTube video - START")

    start_time: datetime = datetime.now()

    try:
        FPyVideoLibrary.YouTube_DownloadRaiseError(context, params)
    except Exception as e:
        print(f"{context}: Failed to download YouTube video: {e}")
        print(f"FAIL")
        return
    
    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Delete output directory
    if delete_files_at_end:
        if not delete_output_directory(context, output_dir):
            print(f"FAIL")
            return

    print(f"{context}: Elapsed Time: {datetime.now() - current_time}")

    print(f"SUCCESS")

def ut_YouTube_DownloadAudioRaiseError():
    context: str = f"{os.path.basename(__file__)}.ut_YouTube_DownloadAudioRaiseError"

    delete_files_at_end: bool = True

    current_time: datetime = datetime.now()
    current_time_str: str  = current_time.strftime("%Y%m%d%H%M%S")
    
    current_file_path: str = os.path.abspath(__file__)
    output_dir: str        = f"{os.path.dirname(current_file_path)}/Test"

    # Clear existing output directory
    if not delete_output_directory(context, output_dir):
        print(f"FAIL")
        return

    save_path: str = f"{output_dir}/yt_video_{current_time_str}.mp3"

    params: FPyVideoLibrary.FDownload.FParams = FPyVideoLibrary.FDownload.FParams()
    params.URL      = GetYouTubeURL()
    params.SavePath = save_path

    print(f"{context}: Unit Test: YouTube_DownloadRaiseError")
    print(f"Script File: Cs/Library/Library_Video.py")
    print(f"Class: {FPyVideoLibrary.__class__.__qualname__}")

    # Retrieve YouTube video info
    print(f"{context}: Retrieve YouTube video info - START")

    start_time: datetime = datetime.now()

    try:
        params.Info = FPyVideoLibrary.GetInfoRaiseError(context, params.URL)
    except Exception as e:
        print(f"{context}: Failed to get YouTube video info: {e}")
        print(f"FAIL")
        return

    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Download YouTube audio
    print(f"{context}: Download YouTube audio - START")

    start_time: datetime = datetime.now()
    result: Dict[str, any] = {}

    try:
        result = FPyVideoLibrary.YouTube_DownloadAudioRaiseError(context, params)
    except Exception as e:
        print(f"{context}: Failed to download YouTube audio: {e}")
        print(f"FAIL")
        return
    
    print(f"{context}: Download Duration: {result['duration']}")
    print(f"{context}: Convert MP3 Duration: {result['convert_mp3_duration']}")
    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Delete output directory
    if delete_files_at_end:
        if not delete_output_directory(context, output_dir):
            print(f"FAIL")
            return

    print(f"{context}: Elapsed Time: {datetime.now() - current_time}")

    print(f"SUCCESS")

def ut_YouTube_DownloadVideoAudioCombine():
    context: str = f"{os.path.basename(__file__)}.ut_YouTube_DownloadVideoAudioCombine"

    delete_files_at_end: bool = True

    current_time: datetime = datetime.now()
    current_time_str: str  = current_time.strftime("%Y%m%d%H%M%S")

    current_file_path: str = os.path.abspath(__file__)
    output_dir: str        = f"{os.path.dirname(current_file_path)}/Test"

    # Clear existing output directory
    if not delete_output_directory(context, output_dir):
        print(f"FAIL")
        return

    video_save_path: str = f"{output_dir}/yt_video_{current_time_str}_video.mp4"

    params: FPyVideoLibrary.FDownload.FParams = FPyVideoLibrary.FDownload.FParams()
    params.URL      = GetYouTubeURL()
    params.SavePath = video_save_path

    print(f"{context}: Unit Test: YouTube_DownloadRaiseError")
    print(f"Script File: Cs/Library/Library_Video.py")
    print(f"Class: {FPyVideoLibrary.__class__.__qualname__}")

    # Retrieve YouTube video info
    print(f"{context}: Retrieve YouTube video info - START")

    start_time: datetime = datetime.now()

    try:
        params.Info = FPyVideoLibrary.GetInfoRaiseError(context, params.URL)
    except Exception as e:
        print(f"{context}: Failed to get YouTube video info: {e}")
        print(f"FAIL")
        return

    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Download YouTube video
    print(f"{context}: Download YouTube video - START")

    start_time: datetime = datetime.now()

    try:
        FPyVideoLibrary.YouTube_DownloadRaiseError(context, params)
    except Exception as e:
        print(f"{context}: Failed to download YouTube video: {e}")
        print(f"FAIL")
        return
    
    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Download YouTube audio
    print(f"{context}: Download YouTube audio - START")

    audio_save_path: str = f"{output_dir}/yt_video_{current_time_str}_audio.mp4"
    params.SavePath = audio_save_path

    start_time: datetime = datetime.now()
    result: Dict[str, any] = {}

    try:
        result = FPyVideoLibrary.YouTube_DownloadAudioRaiseError(context, params)
    except Exception as e:
        print(f"{context}: Failed to download YouTube audio: {e}")
        print(f"FAIL")
        return
    
    audio_save_path = result["audio_path"]

    print(f"{context}: Download Duration: {result['duration']}")
    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Combine video and audio
    print(f"{context}: Combine video and audio - START")

    start_time: datetime = datetime.now()
    save_path: str = f"{output_dir}/yt_video_{current_time_str}.mp4"

    try:
        FPyVideoLibrary.CombineVideoAudioRaiseError(context, video_save_path, audio_save_path, save_path)
    except Exception as e:
        print(f"{context}: Failed to combine video: {video_save_path} and audio: {audio_save_path} to: {save_path}. Error: {e}")
        print(f"FAIL")
        return

    print(f"{context}: COMPLETED: Elapsed Time: {datetime.now() - start_time}")

    # Delete output directory
    if delete_files_at_end:
        if not delete_output_directory(context, output_dir):
            print(f"FAIL")
            return

    print(f"{context}: Elapsed Time: {datetime.now() - current_time}")

    print(f"SUCCESS")

def run():
    #ut_YouTube_GetInfoRaiseError()
    #ut_YouTube_DownloadRaiseError()
    #ut_YouTube_DownloadAudioRaiseError()
    ut_YouTube_DownloadVideoAudioCombine()

def main():
    run()

if __name__ == '__main__':
    main()