# duckynstall
An Arch Linux install program written in C++ tailored to my needs specifically(feel free to adapt as you see fit, I think I made the code pretty easy-to-read and very customizable)

# Usage
Compile the programs using `g++ installSystem.cpp -o install && g++ installSystem2.cpp -o install2`
After compiling, execute in this order and under these circumstances:
Run the install binary in the Arch Linux live environment, then after that finishes, run the install2 binary in the chroot that the previous script enters for you.
