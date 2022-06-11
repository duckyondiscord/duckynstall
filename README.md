# duckynstall
An Arch Linux install program written in C++ tailored to my needs specifically(feel free to adapt as you see fit, I think I made the code pretty easy-to-read and very customizable)
Currently installs KDE Plasma with its default configuration using SDDM as its display manager.

# Usage
Compile the programs using `g++ installSystem.cpp -o duckynstall && g++ installSystem2.cpp -o duckynstall2`
After compiling, execute in this order and under these circumstances:
Run the install binary in the Arch Linux live environment, then after that finishes, run the install2 binary in the chroot that the previous script enters for you.
