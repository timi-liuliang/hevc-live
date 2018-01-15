import os
import platform
import subprocess

if platform.system()=="Linux":
    camera_process_0 = subprocess.Popen(['ffmpeg', '-f', 'v4l2', '-framerate', '25', '-video_size', '640x480', '-i', '/dev/video0', '-f', 'mpegts', "-tune", "zerolatency", '-codec:v', 'mpeg1video', "-x265-params", "bframes=0", "-pix_fmt", "yuv420p", '-s', '640x480', '-b:v', '250k', '-bf', '0', 'http://101.200.222.178:10001/camera_0'])
else:
    camera_process_0 = subprocess.Popen(['ffmpeg', '-f', 'avfoundation', '-framerate', '10', '-video_size', '640x480', '-i', '0', '-f', 'mpegts', "-tune", "zerolatency",'-codec:v', 'hevc', "-x265-params", "bframes=0", "-pix_fmt", "yuv420p", '-s', '640x480', '-b:v', '250k', '-bf', '0', 'http://118.190.156.61:10001/camera_0'])
    #camera_process_0 = subprocess.Popen(['ffmpeg', '-f', 'avfoundation', '-framerate', '10', '-video_size', '640x480', '-i', '0', '-f', 'mpegts', "-tune", "zerolatency",'-codec:v', 'hevc', "-x265-params", "bframes=0", "-pix_fmt", "yuv420p", '-s', '640x480', '-b:v', '250k', '-bf', '0', 'http://localhost:10001/camera_0'])
