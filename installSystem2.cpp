#include <iostream>
#include <stdlib.h>
#include <string>

void installSystem2()
{
    using namespace std;
    string input;
    string command;
    cout << "Which locale are you in? (e.g America/New_York): ";
    cin >> input;
    system("sed -i 's/^#en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen");
    system("locale-gen");
    command = "timedatectl --no-ask-password set-timezone " + input;
    system(command.c_str());
    system("timedatectl --no-ask-password set-ntp 1");
    system("localectl --no-ask-password set-locale LANG=\"en_US.UTF-8\" LC_TIME=\"en_US.UTF-8\"");
    cout << "Select keymap(e.g us): ";
    cin >> input;
    command = "localectl --no-ask-password set-keymap " + input;
    system("sed -i 's/^# %wheel ALL=(ALL) NOPASSWD: ALL/%wheel ALL=(ALL) NOPASSWD: ALL/' /etc/sudoers"); // Add sudo perms for group wheel without a password
    system("cd /etc; rm pacman.conf; wget https://duckykutya.cf/pacman.conf");
    system("pacman -Sy --noconfirm");

    cout << "\nInstalling system...";
    system("pacman -S --noconfirm mesa xorg xorg-server xorg-apps xorg-drivers xorg-xkill xorg-xinit plasma-desktop alsa-plugins alsa-utils ark mpv cronie discover dolphin dosfstools ntfs-3g fuse2 fuse3 gcc gparted grub gwenview kate kcodecs kcoreaddons kdeplasma-addons kitty firefox neofetch pacman-contrib p7zip patch sddm sddm-kcm spectacle wine winetricks xdg-desktop-portal-kde xdg-user-dirs zip zsh pipewire pipewire-pulse pipewire-alsa networkmanager && systemctl enable sddm NetworkManager");
    system("pacman -S intel-ucode amd-ucode");
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

    
    command = "grub-install --efi-directory=/boot " + diskPath;
    system(command.c_str());
    command = "grub-install " + diskPath;
    system(command.c_str());
    system("grub-mkconfig -o /boot/grub/grub.cfg");
}

int main()
{
    installSystem2();
    std::cout << "We should be done!\n";
}
