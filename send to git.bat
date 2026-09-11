@echo off
echo Sending latest files to GitHub...
git add .
git commit -m "Updated project files"
git push
echo Upload Complete!
pause