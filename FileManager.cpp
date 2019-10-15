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

#include "FileManager.h"



//getter methods
const char* FileManager::getFileName() const{
  return fileName;
}
string FileManager::getFileType(){
  return fileType;
}
int FileManager::getFileSize(){
  return fileSize;
}
long FileManager::getUserID(){
  return userID;
}
string FileManager::getUserName(){
  return userName;
}
long FileManager::getGroupID(){
  return groupID;
}
string FileManager::getGroupName(){
  return userName;
}
string FileManager::getPermissions(){
  return permissions;
}
string FileManager::getAccessTime(){
  return accessTime;
}
string FileManager::getModificationTime(){
  return modificationTime;
}
string FileManager::getChangeTime(){
  return changeTime;
}
int FileManager::getBlockSize(){
  return blockSize;
}
int FileManager::getErrNo(){
  return errNo;
}
//end of getter methods

// default constructor
FileManager::FileManager(){
  FileManager::fileName = "";
  FileManager::fileType = "";
  FileManager::fileSize = 0;
  FileManager::userID = 0;
  FileManager::userName = "";
  FileManager::groupID = 0;
  FileManager::groupName = "";
  FileManager::permissions = "";
  FileManager::accessTime = "";
  FileManager::modificationTime = "";
  FileManager::changeTime = "";
  FileManager::blockSize = 0;
  //use function to create vector
  FileManager::errNo = 0;
}
//this is the constructor
  FileManager::FileManager(const char* newFile){
  struct stat buf;
  stat(newFile, &buf);


  FileManager::fileName = newFile;
  FileManager::fileType = buf.st_mode;
  switch (buf.st_mode & S_IFMT) {
    case S_IFBLK:  FileManager::fileType ="block device";      break;
    case S_IFCHR:  FileManager::fileType ="character device";  break;
    case S_IFDIR:  FileManager::fileType ="directory";         break;
    case S_IFIFO:  FileManager::fileType ="FIFO/pipe";         break;
    case S_IFLNK:  FileManager::fileType ="symlink";           break;
    case S_IFREG:  FileManager::fileType ="regular file";      break;
    case S_IFSOCK: FileManager::fileType ="socket";            break;
    default:       FileManager::fileType ="unknown";           break;
    }
  FileManager::fileSize = buf.st_size;
  FileManager::userID = buf.st_uid;
  FileManager::userName = getpwuid(buf.st_uid)->pw_name;
  FileManager::groupID = buf.st_gid;
  FileManager::groupName = getgrgid(buf.st_gid)->gr_name;

  switch (buf.st_mode & S_IFMT) {
    case S_IRWXU:  FileManager::permissions ="rwx --- ---";  break;
    case S_IRUSR:  FileManager::permissions ="r-- --- ---";  break;
    case S_IWUSR:  FileManager::permissions ="-w- --- ---";  break;
    case S_IXUSR:  FileManager::permissions ="--x --- ---";  break;
    case S_IRWXG:  FileManager::permissions ="--- rwx ---";  break;
    case S_IRGRP:  FileManager::permissions ="--- r-- ---";  break;
    case S_IWGRP:  FileManager::permissions ="--- -w- ---";  break;
    case S_IXGRP:  FileManager::permissions ="--- --x ---";  break;
    case S_IRWXO:  FileManager::permissions ="--- --- rwx";  break;
    case S_IROTH:  FileManager::permissions ="--- --- r--";  break;
    case S_IWOTH:  FileManager::permissions ="--- --- -w-";  break;
    case S_IXOTH:  FileManager::permissions ="--- --- --x";  break;
    default:       FileManager::permissions ="unknown";      break;
    }

  FileManager::permissions = buf.st_mode;
  FileManager::accessTime = ctime(&buf.st_atime);
  FileManager::modificationTime = ctime(&buf.st_mtime);
  FileManager::changeTime = ctime(&buf.st_ctime);
  FileManager::blockSize = buf.st_blksize;
  //vector children not initialized in this constructor
  FileManager::errNo = 0;
  }

  //this is the destructor
  FileManager::~FileManager(){

  }

//this is the dump
  int FileManager::Dump(std::fstream &stream){
          if(fileType != "regular file"){
              errNo = ENOTSUP;
              return n.getErrNo();
          }
          std::ifstream infile; //create new stream
          if (!infile){
              std::cerr<< "Unable to open file!";
              return n.getErrNo();
          }
          infile.open(getFileName());//open the file to be read
          char* buffer = new char [getBlockSize()];//get the buffer of size blocksize
          while(true){
              infile.read(buffer, getBlockSize());//but blocksize amount of content from file to be read into buffer
              stream << buffer <<std::endl;//write from buffer into stream
              if(infile.eof()) {//when you reach the end of file, break
                  break;
              }
          }
          infile.close();
          return n.getErrNo();
      }


  //this is the rename()
  int FileManager::Rename(const char* newFileName){
    rename(fileName, newFileName);
    fileName = newFileName;
    return n.getErrNo();
  }
  //this is the Remove()
  int FileManager::Remove(){
    unlink(fileName);
    return n.getErrNo();
  }
  //this is the compare()
  int FileManager::Compare(FileManager otherFile){
    if(fileType.compare("REG") == 0 || otherFile.fileType.compare("REG") == 0){//both files must be regular
      errNo = ENOTSUP;
      return n.getErrNo();
    }
    if(fileSize != otherFile.fileSize){//if they are different sizes they are different files
      return 0;
    }
    //read and compare the two files until eof or until a difference is found
    fstream firstFile;
    fstream secondFile;

    firstFile.open(fileName);
    secondFile.open(otherFile.fileName);

    char firstBuffer[FileManager::blockSize];
    char secondBuffer[otherFile.blockSize];

    while(firstFile.eof() != true){
      firstFile.read(firstBuffer, blockSize);
      secondFile.read(secondBuffer, blockSize);
      if (strcmp(firstBuffer, secondBuffer) != 0){
        break;
      }
    }
    firstFile.close();
    secondFile.close();
    cout << "they are the same"<< "/n";
    return n.getErrNo();

  }
  //this is the expand
  int FileManager::Expand(const char* fileName){
    if (fileType != "DIR"){
      errNo = ENOTSUP;
      return n.getErrNo();
    }
    DIR *dirPointer = NULL;//create a directory pointer
    struct dirent *parent;//create a directory
    dirPointer = opendir(fileName);//open the file
    if(dirPointer == NULL){
      cout << "dirPointer cannot be initialized correctly"<< "/n";
      return n.getErrNo();
    }
    while(parent == readdir(dirPointer)){//countinue to read the children of the dir
      if(parent == NULL)
      {
        cout <<"parent cannot be initialized correctly"<< "/n";
        return n.getErrNo();
      }
      children.emplace(children.end(), parent->d_name);//append each file to the children vector
    }
    closedir (dirPointer);
    return n.getErrNo();
  }
