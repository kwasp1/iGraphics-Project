@echo off
setlocal

:: Loop through all JPG files in the current folder
for %%f in (*.jpg) do (
    :: Convert each JPG to BMP format
    ffmpeg -i "%%f" "%%~nf.bmp"
)

echo Conversion complete.
endlocal
