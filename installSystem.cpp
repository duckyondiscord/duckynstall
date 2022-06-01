#include <iostream>
#include <stdlib.h>
#include <string>

int isSubstring(std::string s1, std::string s2) // Function I copy-pasted to find if a string is a substring of another, later used in checking of the storage device is NVMe or eMMC
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
    cout << "Type the full path of the device you'd like to install to(THE SELECTED DRIVE WILL BE ERASED! PROCEED WITH CAUTION!):";
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

    if(isSubstring("nvme", diskPath) != -1 || isSubstring("mmcblk", diskPath) != -1) // Check if the storage device is NVMe or eMMC, this is where the isSubstring function comes in
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
    system("cp /bin/duckynstall2 /mnt/bin/duckynstall2");
    system("arch-chroot /mnt");
    

}
 

int main()
{
    prepareChRoot();
}
