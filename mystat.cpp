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
        cout << n.getFileName() << endl;
        cout << n.getFileType() << endl;
        cout << n.getFileSize() << endl;
        cout << n.getUserID() << endl;
        cout << n.getUserName() << endl;
        cout << n.getGroupID() << endl;
        cout << n.getGroupName() << endl;
        cout << n.getPermissions() << endl;
        cout << n.getAccessTime() << endl;
        cout << n.getModificationTime() << endl;
        cout << n.getChangeTime() << endl;
        cout << n.getBlockSize() << endl;
      }
    }
    }
  }
  return n.getErrNo();
}
