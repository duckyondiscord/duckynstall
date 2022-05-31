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
 

void prepareChRoot()
{
    using namespace std;
    
    string diskPath;
    cout << "Type in the full path of the device you'd like to install to(THE SELECTED DRIVE WILL BE ERASED! PROCEED WITH CAUTION!):";
    cin >> diskPath;
    
    cout << "Formatting disk...\n";
    string command = "umount -R /mnt > /dev/null"; // Dirty solutions but system() annoys the hell out of me so deal with it
    system(command.c_str());
    command = "sgdisk -Z " + diskPath;
    system(command.c_str());
    command = "sgdisk -a 2048 -o " + diskPath;
    system(command.c_str());
    command = "sgdisk -n 1::+1M --typecode=1:ef02 --change-name=1:'BIOSBOOT' " + diskPath;
    system(command.c_str());
    command = "sgdisk -n 2::+512M --typecode=2:ef00 --change-name=2:'EFIBOOT' " + diskPath;
    system(command.c_str());
    command = "sgdisk -n 3::-0 --typecode=3:8300 --change-name=3:'ROOT' " + diskPath;
    system(command.c_str());

    cout << "Making filesystems...\n";
    if(isSubstring("nvme", diskPath) != -1 || isSubstring("mmcblk", diskPath) != -1)
    {
        command = "mkfs.vfat -F32 " + diskPath + "p2";
        system(command.c_str());
        command = "mkfs.ext4 " + diskPath + "p3";
        system(command.c_str());
        command = "mount " + diskPath + "p3 " + "/mnt";
        system(command.c_str());
        cout << "System is ready for installation!\n";
    }
    else
    {
        command = "mkfs.vfat -F32 " + diskPath + "2";
        system(command.c_str());
        command = "mkfs.ext4 " + diskPath + "3";
        system(command.c_str());
        command = "mount " + diskPath + "3 " + "/mnt";
        system(command.c_str());
        cout << "System is ready for installation!\n";
    }
    

}

int main()
{
    prepareChRoot();
    char reboot;
        std::cout << "Do you wish to reboot the system? This is necessary for the system to recognize the new partition table. [Y/n]";
        std::cin >> reboot;
        if(reboot == 'Y' || reboot == 'y')
        {
            system("reboot");
        }
        if(reboot == 'N' || reboot == 'n')
        {
            return 0;
        }
}
