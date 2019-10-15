#include <iostream>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <fstream>
#include <vector>
#include <dirent.h>
using namespace std;

class FileManager{
private:
    const char* fileName;
    string fileType;
    int fileSize;
    int userID;
    string userName;
    int groupID;
    string groupName;
    string permissions;
    string accessTime;
    string modificationTime;
    string changeTime;
    int blockSize;
    std::vector<FileManager> children;
    int errNo;
  public:
    //getter methods
    const char* getFileName() const;
    string getFileType();
    int getFileSize();
    long getUserID();
    string getUserName();
    long getGroupID();
    string getGroupName();
    string getPermissions();
    string getAccessTime();
    string getModificationTime();
    string getChangeTime();
    int getBlockSize();
    int getErrNo();
    //end of getter methods

    FileManager();
    FileManager(const char* newFile);
    ~FileManager();
    int Dump(fstream &stream);
    int Rename(const char* newFileName);
    int Remove();
    int Compare(FileManager otherFile);
    int Expand(const char* fileName);
  };
