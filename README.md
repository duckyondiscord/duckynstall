# duckynstall
An Arch Linux install program written in C++ tailored to my needs specifically(feel free to adapt as you see fit, I think I made the code pretty easy-to-read and very customizable)

# Usage
Compile the programs using `g++ installSystem.cpp -o install && g++ installSystem2.cpp -o install2 && g++ prepareSystem.cpp -o prepare`
After compiling, execute in this order and under these circumstances:
Execute the prepare binary after booting into an Arch Linux ISO, then after that finishes, run the install binary right after it, that will place you in a chroot environment where you can either use `wget` or `scp` to get the install2 binary which you can execute in the chroot.
