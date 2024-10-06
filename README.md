# README   -  Documentation does not exist! 
## 1. What is this?
This program should display photos from the **./Fotos** folder onto a website.

This is some kind of *Google Photos Project* (open source, without Google) meant for home servers as photo database.

## 2. How to use?
i. compile with **./run.bat** on windows (no linux support yet) and go to any address of your computer on port 6001 (changable with a #define).

ii. step i will already start ./main.exe so you don't have to do anything else EXCEPT: You need to have a **./Fotos** directory with subfolders (best is to name them with dates) and insert some photos into them.
Supported image extensions can be found in **IMAGE_EXTENSIONS** in **./utils/checkWhatItIs.hpp**.

## 3. Contribution
We have a e.html format which you are able to render variables into html files. A variable looks like this `{{variable}}`.

Have a look at the **./server/prepareResponse.hpp** > `renderEHTML` function.

e.html files are in the **./pages** folder (set in **./server/prepareResponse.hpp** > PAGES_FOLDER_PATH definition).