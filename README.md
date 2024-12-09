Login and Registration System

Description

This program is a GUI-based Login and Registration System implemented in C++ using the FLTK library. It allows users to:
Register a new account with secure password requirements.
Login with an existing account.
Display error messages for invalid inputs and credentials.
Automatically validate username and password fields for completeness and correctness.

Requirements
FLTK Library (Fast Light Toolkit)
    Install FLTK via Homebrew on macOS:
         brew install fltk
         Install FLTK on Windows:
             Download FLTK from FLTK.org.
             Follow installation instructions provided in the documentation.
C++ Compiler
    Recommended: clang++ or g++.
    
Features
Main Menu:
    Options to log in or register.
Login Window:
    Prompts the user for a username and password.
    Displays error banners if fields are left empty or credentials are invalid.
Registration Window:
    Requires the user to create a new account with password requirements:
        Minimum 8 characters.
        At least one uppercase letter, one lowercase letter, one digit, and one special character.
    Displays error banners if requirements are not met or username is already taken.
    
File Storage:
    User data is stored in a local text file named users.txt.
    
Compilation Instructions
For macOS
    Use the following command to compile the program:
    clang++ -o main my.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lfltk -lfltk_images
Run the compiled program:
    ./main
    
For Windows
    Ensure FLTK is installed and properly linked with your compiler.
    Use the following command in a terminal or command prompt (adjust paths if necessary):
    g++ -o main.exe my.cpp -I<path_to_fltk_include> -L<path_to_fltk_lib> -lfltk -lfltk_images
    Replace <path_to_fltk_include> and <path_to_fltk_lib> with the actual paths to FLTK's include and lib directories.
    
Run the program:
    main.exe
    
How to Use
Run the program:
    On macOS: ./main
    On Windows: main.exe
Choose an option:
    Click "Login" to log in with an existing account.
    Click "Register New Account" to create a new account.
Follow the prompts:
    For login: Enter your username and password. If fields are empty or credentials are incorrect, error messages will be displayed.
    For registration: Enter a username and a strong password. If requirements are not met, follow the instructions in the error banners.
Program File
    The source code for this program is located in my.cpp. Ensure this file is in the same directory where the compilation commands are executed.

Additional Notes
    This program uses FLTK for GUI rendering, so make sure FLTK is installed correctly on your system.
    
