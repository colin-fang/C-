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
    if(nn.getFileType() == "regular file"){
      if(FileCheck(name)){
        n.Dump(newName);
      }
    }else{
      cout << "the destination file is not a regular file" << endl;
      return 0;
      }
    }
  }
  return n.getErrNo();
}
