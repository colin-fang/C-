#include <iostream>
#include "FileManager.h"
using namespace std;

inline bool FileCheck(const string &name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char* argv[]){
  char* name = argv[1];
  char* newName = argv[2];
  FileManager n(name);
  FileManager nn(newName);

  if(argc > 2){
    if(nn.getFileType() == "directory"){
      if(FileCheck(name)){
        char buf[100];
        strcpy(buf, newName);
        strcat(buf, "/");
        strcat(buf, name);
        n.Rename(buf);
      }
    }else{
      if(FileCheck(name)){
        n.Rename(newName);
      }
    }
  }
  return n.getErrNo();
}
