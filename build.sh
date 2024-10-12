#!/bin/sh
case $1 in
    -b|-build|--build|build)
        docker build --network=host -t $(basename $PWD) .
        exit 0
        ;;
    -r|-run|--run|run)
        docker run -it --rm --network=host --name $(basename $PWD) -v "$PWD":/"$(basename $PWD)" -w /"$(basename $PWD)" $(basename $PWD) sh -c "make -B; make clean"
        exit 0
        ;;
    -rmi|--rmi|rmi)
        docker rmi $(basename $PWD) --force
        exit 0
        ;;
    -h|-help|--help|help|*)
        echo "These are common commands used in various situations:"
        echo
        echo "Uso:"
        echo "  ./build.sh COMMAND"
        echo
        echo "Commands:"
        echo "  help            Shows this information"
        echo "  build           Make docker image"
        echo "  run             Run docker image"
        echo "  rmi             Remove docker image"
        echo
        echo "./build.sh COMMAND --help to get help on each command"
        echo
        exit 0
        ;;
esac
