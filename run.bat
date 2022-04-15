@echo off
wsl "/mnt/d/osdevelopment/build.sh"
echo If there are no errors above this line, the build was successful.
bochs -q