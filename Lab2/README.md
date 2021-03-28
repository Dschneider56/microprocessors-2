# source files for Lab 2

This directory contains a few files for Lab 2

## Folder structure
```
snake.py		modified snake game
snake.ino   Arduino code to communicate data to snake
```

## set up Python3 Environment on your laptop

You can download and install the latest Python3 from https://www.python.org/downloads/

After you have Python3 installed, it is recommended that you create a virtual environment so that you can maintain multiple python environments for different projects. See the instructions here https://docs.python.org/3/tutorial/venv.html

Note that you then need to install pyserial package for your Python environment
```
pip3 install pyserial
```

By now, you should be ready to work on Lab 2.

To run this code the user should connect their arduino board to their laptop
after creating the circuit described in the lab report document.

Once the arduino code is loaded and running, navigate to the directory where
snake.py is located and run `python3 snake.py`.

At this point, the user is free to use the gyroscope or joystick to move the
snake and to trigger the apple to turn golden.
