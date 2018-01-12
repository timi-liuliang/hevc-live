import os
import subprocess

camera_process_0 = subprocess.Popen(['ffmpeg', '-f', 'v4l2', '-framerate', '25', '-video_size', '320x240', '-i', '/dev/video0', '-f', 'mpegts', '-codec:v', 'mpeg1video', '-s', '320x240', '-b:v', '1000k', '-bf', '0', 'http://101.200.222.178:10001/camera_0'])

