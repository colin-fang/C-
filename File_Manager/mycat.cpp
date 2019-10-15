#include <iostream>
#include "FileManager.h"
using namespace std;

inline bool FileCheck(const string &name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char* argv[]){
  char* name = argv[1];
  FileManager n(name);

  if(argc > 2){
    if(nn.getFileType() == "regular file"){
      if(FileCheck(name)){
        n.Dump(cout);
      }
    }
  }
  return n.getErrNo();
}
