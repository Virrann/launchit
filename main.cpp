#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>

#define PATHLAUNCHER "/home/$USER/.local/share/applications/"
#define PATHSCRIPTS "../testes"


#define NAME "WhatsApp"
#define APP "/mnt/nvme/WhatsAppWeb-linux-x64/WhatsAppWeb"
#define ICONTEST "/mnt/nvme/WhatsAppWeb-linux-x64/resources/app/icon.png"


using namespace std;

void createCommand(const string name, const string path, const string command){

    string scriptpath = path + "/" + name + ".sh";
    ofstream scriptf;

    scriptf.open(scriptpath);

    if (!scriptf){
        cerr << "error creating file " + scriptpath << endl;
        return;
    }

    scriptf << "#!/bin/bash\n";
    scriptf << command << "\n";
    scriptf.close();

    string chmod = "chmod +x " + scriptpath;

    if (std::system(chmod.c_str()) != 0) {
        std::cerr << "Error turning script on executable" << std::endl;
        return;
    }
}

void createLauncher(){

    string header = "[Desktop Entry]\n";

}

int main(/*int argc, char const *argv[]*/){
    /*
    string name = "Name=";
    string type = "Type=Application";
    string exec = "EXEC=";
    string icon = "Icon=";

    /* code */
    createCommand("name", PATHSCRIPTS, "flatpak run com.valvesoftware.Steam");

    return 0;
}





