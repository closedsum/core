# Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
# MIT License: https://opensource.org/license/mit/
# Free for use and distribution: https://github.com/closedsum/core
import unreal as ue
import subprocess
import re

def get_handle_path():
    """Get handle.exe path"""
    
    project_dir: str = ue.Paths.project_dir()
    project_dir = ue.Paths.convert_relative_path_to_full(project_dir)
    handle_exe: str = f"{project_dir}ThirdParty/handle/handle.exe"
    handle_exe = handle_exe.replace("/", "\\\\")
    return handle_exe

HANDLE_PATH = get_handle_path()

# TODO: check os type (Windows, Linux, Mac)

class NPyProcess:
    class FLibrary:
        @staticmethod
        def KillByFileRaiseError(context: str, file_path: str):
            """
            Kill a process by file path.
                NOTE: Should ONLY be called on Non-Main Thread (NOT Game Thread).

            Example:
                KillByFileRaiseError("some_function", "C:/path/to/file.txt")

            Args:
                context:    (str): The calling context.
                file_path   (str): The path to the file to kill.
            """
            try:
                handle_output = subprocess.check_output([HANDLE_PATH, file_path]).decode('utf-16')
                print(f"{context}: handle_output: {handle_output}")
                # Extract PIDs from handle output (adjust regex based on actual handle.exe output)
                # This regex is a simplified example; you may need to refine it.
                pids = re.findall(r'pid:(\\d+)', handle_output) 

                if not pids:
                    return

                # Attempt to kill each process using taskkill
                for pid in pids:
                    try:
                        subprocess.run(['taskkill', '/F', '/PID', pid], check=True) # /F for forceful kill
                        print(f"{context}: Successfully killed process {pid}")
                    except subprocess.CalledProcessError as e:
                        raise Exception(f"{context}: Error killing process {pid}: {e}")

            except FileNotFoundError:
                raise Exception(f"{context}: handle.exe or taskkill command not found.")
            except Exception as e:
                raise Exception(f"{context}: Error running handle or taskkill: {e}")