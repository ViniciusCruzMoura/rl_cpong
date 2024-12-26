#!/bin/sh
case $1 in
    -b|-build|--build|build)
        docker build --network=host -t $(basename $PWD) .
        exit 0
        ;;
    -r|-run|--run|run)
        if docker images --format '{{.Repository}}:{{.Tag}}' | grep -q "^$(basename $PWD):latest$"; then
            echo
        else
            docker build --network=host -t $(basename $PWD) .
        fi
        docker run -it --rm --network=host --name $(basename $PWD) -v "$PWD":/"$(basename $PWD)" -w /"$(basename $PWD)" $(basename $PWD) sh -c "make -B; make clean"
        exit 0
        ;;
    -rmi|--rmi|rmi)
        docker rmi $(basename $PWD) --force
        exit 0
        ;;
    -l|--l|local)
        if [ ! -d "external" ]; then
            mkdir -p external/
            cd external/
            wget https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_linux_amd64.tar.gz
            tar -xf raylib-5.0_linux_amd64.tar.gz
            rm raylib-5.0_linux_amd64.tar.gz
            mv raylib-5.0_linux_amd64/ raylib/
            cd ../
        fi
        if [ "$2" = "compile" ]; then 
            rm -f game
            make -B; make clean
            exit 0
        fi
        if [ "$2" = "run" ]; then 
            LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./external/raylib/lib ./game 
            exit 0
        fi
        exit 0
        ;;
    -h|-help|--help|help|*)
        echo "These are common commands used in various situations:"
        echo
        echo "Uso:"
        echo "  ./build.sh COMMAND"
        echo
        echo "Commands:"
        echo "  help            Display this help information."
        echo "  build           Build a new Docker image."
        echo "  run             Run the Docker image if it exists; otherwise, build the image and then run it."
        echo "  rmi             Remove the Docker image by untagging it."
        echo "  local           Download and configure the dependencies out of the box."
        echo
        echo "./build.sh COMMAND --help to get help on each command"
        echo
        exit 0
        ;;
esac
