
if [["$1"] == "clean"]; then
    cd src
    make clean
    exit 0
elif [["$1"] == "--test"]; then
    cd src
    make install
    exit 0
fi

echo "Installing AUR..."

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

echo "Do you want to install the program into the system? (Y/N)"
read install

if [[ "$install" == "Y" ]]; then
    make install
elif [[ "$install" == "N" ]]; then
    make
fi
