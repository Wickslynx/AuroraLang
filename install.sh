#!/bin/bash

if [ $# -gt 0 ]; then # If there are any cmd line arguments
    if [["$1"] == "clean"]; then
        cd src
        make clean
        exit 0
    elif [["$1"] == "--test"]; then
        cd src
        make install
        exit 0
    fi
fi



echo "Installing AuroraLang..."

while true; do
    echo "Do you want to install all additional dependencies? (Y/N)"
    read dependencies

    if [[ "$dependencies" == "Y" ]]; then
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            sudo apt update
            sudo apt-get install nasm g++
            sudo apt upgrade g++ # To prevent C++ 20 not supported.
            break
        elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
            winget install --id=NASM.NASM  -e
            winget install --id=GNU.Mingw-w64   -e
            break
        else
            echo "Automatic dependency installation is not supported on your operating system."
            break
        fi
    elif [[ "$dependencies" == "N" ]]; then
        echo "Continuing without installing dependencies..."
        break
    else 
        echo "Unknown option, try again..."
    fi
done

cd src

echo "Do you want to install the program globaly? (Y/N)"
read install

if [[ "$install" == "Y" ]]; then
    if [ "$(id -u)" -eq 0 ]; then
        make install
    else 
        echo "You need to run this program with root! (sudo)"
    fi
elif [[ "$install" == "N" ]]; then
    make
fi
