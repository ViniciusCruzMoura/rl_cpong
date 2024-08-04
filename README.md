# RL_CPong

- This repo contains a classic Pong game developed in C using the raylib library. This project was used as a means of learning.
- Naming and documentation of the source code and data structures are in progress.

## Installation

### Docker
To install build dependencies:
```
docker run -it --rm --network=host -v "$PWD":/usr/src/app -w /usr/src/app ubuntu:22.04 bash
./configure.sh
./build.sh
```
Other examples:
```
docker run -it --rm --network=host -v "$PWD":/usr/src/app -w /usr/src/app ubuntu:22.04 sh -c "./configure.sh && ./build.sh"
```

### Linux

The build system has the following package requirements:
 * raylib 5 (https://github.com/raysan5/raylib)

There are 2 steps to set up a working build.

#### Step 1: Install dependencies

Dependency installation instructions for common Linux distros are provided below:

##### Debian / Ubuntu
To install build dependencies:
```
sudo apt install -y ...
```

##### Arch Linux
To install build dependencies:
```
sudo pacman -S ...
```

#### Step 2: Build
Run `./build.sh` to build the project
Other examples:
```
make
```

Resulting artifacts can be found in the `build` directory.

The full list of configurable variables are listed below, with the default being the first listed:

* ``PLATFORM``: ``PLATFORM_DESKTOP``

### Windows

Install WSL and a distro of your choice following
[Windows Subsystem for Linux Installation Guide for Windows 10.](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
We recommend either Debian or Ubuntu 22.04 Linux distributions under WSL.

Next, clone the repo from within the Linux shell:
`git clone https://github.com/ViniciusCruzMoura/rl_cpong.git`

Then continue following the directions in the [Linux](#linux) installation section below.

## Contribute

Issues and pull requests are welcome.
