SET PATH=E:\ffmpeg-4.2.2-win64-static\bin
rem ffmpeg -encoders
rem pause
ffmpeg -i Project1.exe%%d.bmp -r 10 -c:v libx265 -preset slow output.mp4
pause
