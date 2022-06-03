#include <iostream>
#include <stdlib.h>
#include <string>

void installSystem2()
{
    using namespace std;
    string input; // String I use throughout my code for inputs since they're not persistent information
    string command;
    cout << "Which timezone are you in? (e.g America/New_York): ";
    cin >> input;
    system("sed -i 's/^#en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen"); // Set locale
    system("locale-gen"); // Generate locale
    command = "timedatectl --no-ask-password set-timezone " + input; // Set the timezone to the user-specified value
    system(command.c_str());
    system("timedatectl --no-ask-password set-ntp 1"); // Enable NTP for automatic time syncing
    system("localectl --no-ask-password set-locale LANG=\"en_US.UTF-8\" LC_TIME=\"en_US.UTF-8\"");
    cout << "Select keymap(e.g us): ";
    cin >> input;
    command = "localectl --no-ask-password set-keymap " + input; // Set the keymap to the user-specified value
    system("sed -i 's/^# %wheel ALL=(ALL:ALL) NOPASSWD: ALL/%wheel ALL=(ALL:ALL) NOPASSWD: ALL/' /etc/sudoers"); // Add sudo perms for group wheel without a password
    system("cd /etc; rm pacman.conf; wget https://duckykutya.cf/pacman.conf"); // Download and apply custom pacman.conf file so I don't need to modify it with code
    system("pacman -Sy --noconfirm"); // Update repos in case of an out-of-date ISO
    system("pacman -S --noconfirm mesa xorg xorg-server xorg-apps xorg-drivers xorg-xkill xorg-xinit plasma-desktop alsa-plugins alsa-utils ark mpv cronie discover dolphin dosfstools ntfs-3g fuse2 fuse3 gcc gparted grub gwenview kate kcodecs kcoreaddons kdeplasma-addons kitty firefox neofetch pacman-contrib p7zip patch sddm sddm-kcm spectacle wine winetricks xdg-desktop-portal-kde xdg-user-dirs zip zsh pipewire pipewire-pulse pipewire-alsa networkmanager intel-ucode amd-ucode xf86-video-nouveau && systemctl enable sddm NetworkManager"); // Install the system
    cout << "\nWould you like to have a root user? [y/n]";
    cin >> input;
    if(input == "y" || input == "Y")
    {
        cout << "Enter the password for root below\n";
        system("passwd root");
    }
    
    string username;
    cout << "\nEnter your username:";
    cin >> username; // Couldn't reuse input for this one for later reasons
    command = "useradd -m -G wheel -s /bin/bash " + username;
    system(command.c_str());
    command = "passwd " + username;
    system(command.c_str());

    cout << "Name him, name your son! (name your PC): ";
    cin >> input;
    command = "echo " + input + " > /etc/hostname";
    system(command.c_str());
    
    string diskPath;
    cout << "I'm gonna need your disk again(last time, I swear): ";
    cin >> diskPath;

    
    command = "grub-install --efi-directory=/boot " + diskPath;         //
    system(command.c_str());                                            //
    command = "grub-install " + diskPath;                               //  Install for both BIOS and UEFI boot since I couldn't be bothered to detect which one the system was booted with
    system(command.c_str());                                            //  and there isn't much overhead to doing this
    system("grub-mkconfig -o /boot/grub/grub.cfg");
    system("notify-send -a \"duckynstall\" \"Installation Finished!\""); // If the user is using a DE in the live environment, notify them that the installation is done!
}                                                             

int main()
{
    installSystem2();
    std::cout << "We should be done!\n" << ":)\n";
    
}
