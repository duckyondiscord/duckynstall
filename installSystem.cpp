#include <iostream>
#include <stdlib.h>
#include <string>

int isSubstring(std::string s1, std::string s2)
{
    int M = s1.length();
    int N = s2.length();
 
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;
 
        /* For current index i, check for
 pattern match */
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
 
        if (j == M)
            return i;
    }
 
    return -1;
}
 

void installSystem()
{
    using namespace std;
    string diskPath;
    string command;
    cout << "Enter the disk you used previously(raw disk name, no partition numbers):";
    cin >> diskPath;
    if(isSubstring("nvme", diskPath) != -1 || isSubstring("mmcblk", diskPath) != -1)
    {
        command = "mount " + diskPath + "p3";
        system(command.c_str());
    }
    else
    {
        command = "mount " + diskPath + "3";
        system(command.c_str());
    }

    system("pacstrap /mnt base linux linux-firmware sudo nano archlinux-keyring wget openssh --noconfirm"); // OpenSSH is installed to allow the user to scp the next executable over from another system if needed
    system("genfstab -U /mnt >> /mnt/etc/fstab");
    cout << "\nChanging root into the arch environment, you need to run the next part of installSystem in the chroot environment";
    system("arch-chroot /mnt");
}

int main()
{
    installSystem();
}