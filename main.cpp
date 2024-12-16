#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>

using namespace std;

void permissions(const string path){

    string chmod = "chmod +x " + path;

    if (std::system(chmod.c_str()) != 0) {
        std::cerr << "Error turning script on executable" << std::endl;
        return;
    }
}

void createCommand(const string path, 
                   const string name, 
                   const string command){

    filesystem::create_directories(path);

    string scriptpath = path + name + ".sh";
    ofstream scriptf(scriptpath);

    if (!scriptf){
        cerr << "error creating file " + scriptpath << endl;
        return;
    }

    scriptf << "#!/bin/bash\n";
    scriptf << command << "\n";
    scriptf.close();

    permissions(scriptpath);
}

void createLauncher(const string path,
                    const string name, 
                    const string exec, 
                    const string icon){

    string desktoppath = path + name + ".desktop";                   
    ofstream desktopf(desktoppath);

    if (!desktopf){
        cerr << "error creating .desktop file " + desktoppath << endl;
        return;
    }

    desktopf << "[Desktop Entry]\n";
    desktopf << "Type=Application\n";
    desktopf << "Name=" << name << "\n";
    desktopf << "Exec=" << exec << "\n";
    desktopf << "Icon=" << icon << "\n";
    desktopf << "Terminal=false\n";
    
    desktopf.close();

    permissions(desktoppath);  
}

int main(int argc, char const *argv[]){

    if (argc < 4 || argc > 5) {
        cerr << "Erro: Número inválido de argumentos.\n";
        cerr << "Usage: programName -a|-c <command> <name> <icon (opcional it needs to be svg image)>\n";
        return 1;
    }

    string pathlauncher = string(getenv("HOME")) + "/.local/share/applications/";
    string pathscripts = "/mnt/nvme/MeuDir/launchercreator/testes/"; 

    cout << pathlauncher << endl;



    string mode = argv[1];
    string exec = argv[2];
    string name = argv[3];
    string icon = (argc == 5) ? argv[4] : "utilities-terminal";
    
    if (mode == "-c"){
        createCommand(pathscripts ,name, exec);
        createLauncher(pathlauncher, name, pathscripts + name + ".sh", icon);
    }

    if (mode == "-a"){
        createLauncher(pathlauncher, name, exec, icon);
    }

    else{
        cerr << "invalid params\n";
        cerr << "Usage: programName -a|-c <command> <name> <icon (opcional)>\n";
        return 1;
    }


    return 0;
}





