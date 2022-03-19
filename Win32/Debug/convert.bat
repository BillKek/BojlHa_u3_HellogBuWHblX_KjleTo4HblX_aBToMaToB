SET PATH=E:\ffmpeg-4.2.2-win64-static\bin
rem ffmpeg -encoders > list.txt
rem pause
ffmpeg -i Project1.exe%%d.bmp -r 10 -c:v libx264 -profile:v main -level "3.0" -an -s 320x180 -pix_fmt yuv420p output.mp4
pause
