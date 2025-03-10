#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>

//Function to create a file
void create_file()
{
  char filename[100];
  int fd;
  printf("Enter the file name to be created :");
  scanf("%s",filename);
  fd=open(filename,O_CREAT,0777);
  if(fd==-1)
  {
    printf("File could not be created\n");
  }
  else
  {
    printf("File created successfully\n");
  }
  close(fd);
}

//Function to read the information in the file
void read_file()
{
  char filename[100],buf1[2];
  int fd;
  printf("Enter the file name to be created :");
  scanf("%s",filename);
  fd=open(filename,O_RDONLY,0777);
  if(fd==-1)
  {
    perror("Error\n");
  }
  while(read(fd,buf1,1)>0)
  	write(1,buf1,1);
  printf("\n");
  close(fd);
}

//Function to write information into the file
void write_file()
{
  char filename[100],buf[1],info[100];
  int fd,n;
  printf("Enter the file name to be written into :");
  scanf("%s",filename);
  fd=open(filename,O_WRONLY|O_CREAT|O_TRUNC,0777);
  if(fd==-1)
  {
    perror("Error\n");
  }
  printf("Enter the information to be written :");
  scanf("%s",info);
  write(fd,info,strlen(info));
  printf("Content written into the file successfully\n");
}

//To Rename File
void rename_file()
{
  char filename[100],newfile[100];
  int fd;
  printf("Enter the filename that has to be renamed :");
  scanf("%s",filename);
  printf("Enter the new name of the file :");
  scanf("%s",newfile);
  fd=link(filename,newfile);
  if(fd==-1)
  {
    printf("Error occurred during renaming\n");
  }
  else
  {
    fd=unlink(filename);
    if(fd==-1)
    {
      printf("Error occurred during renaming\n");
    }
    else
    {
      printf("%s successfully renamed to %s\n",filename,newfile);
    }
  }
}

//Delete file
void delete_file()
{
  char filename[100];
  int fd;
  printf("Enter the filename that has to be deleted :");
  scanf("%s",filename);
  fd=unlink(filename);
  if(fd==-1)
  {
      printf("Error occurred during renaming\n");
  }
  else
  {
    printf("%s file deleted successfully\n",filename);
  }
}

//Append information into the file
void append_file()
{
  char filename[100],buf[1],info[100];
  int fd,n;
  printf("Enter the file name to be append into :");
  scanf("%s",filename);
  fd=open(filename,O_WRONLY|O_APPEND,0777);
  if(fd==-1)
  {
    perror("Error\n");
  }
  printf("Enter the information to be written :");
  scanf("%s",info);
  write(fd,info,strlen(info));
}

//To get file information
void display_file_info()
{
  char filename[100];
  struct stat statv;
  printf("Enter the file name whose details has to be displayed :");
  scanf("%s",filename);
  if(stat(filename,&statv)==-1)
    printf("Error occurred during extracting file information\n");
  else
  {
    printf("File Name :");
    if(S_ISDIR(statv.st_mode))
      printf("Directory file\n");
    if(S_ISCHR(statv.st_mode))
      printf("Character file\n");
    if(S_ISBLK(statv.st_mode))
      printf("Block File\n");
    if(S_ISLNK(statv.st_mode))
      printf("Symbolic Link File\n");
    if(S_ISFIFO(statv.st_mode))
      printf("FIFO or PIPE File\n");
    if(S_ISREG(statv.st_mode))
      printf("Regular File\n");
    printf("Number of linked files : %ld\n",statv.st_nlink);
    printf("Inode Number : %ld\n",statv.st_ino);
  }
}

//Create Directory
void create_directory()
{
  char dirname[100];
  printf("Enter the name of the directory to be created :");
  scanf("%s",dirname);
  if(mkdir(dirname,0755)==0)
  {
    printf("Directory Created Successfully \n");
  }
  else
  {
    printf("Error during directory creation\n");
  }
}

//Delete Directory
void delete_directory()
{
  char dirname[100];
  printf("Enter the name of the directory to be deleted :");
  scanf("%s",dirname);
  if(rmdir(dirname)==0)
  {
    printf("Directory Deleted Successfully \n");
  }
  else
  {
    printf("Error during directory deletion\n");
  }
}

//To list all files in the directory
void list_directory()
{
  char dirname[100];
  printf("Enter the name of the directory name :");
  scanf("%s",dirname);
  DIR *dir;
  struct dirent * entry;
  dir=opendir(dirname);
  if(dir==NULL)
  {
    printf("Error opening directory\n");
  }
  else
  {
    printf("Files in directory %s :",dirname);
    while((entry=readdir(dir))!=NULL)
    {
      printf("%s\n",entry->d_name);
    }
    closedir(dir);
  }
}

int main(int argc,char * argv[])
{
  int choice;
  while(1)
  {
    printf("1.Create File\n");
    printf("2.Delete File\n");
    printf("3.Read File\n");
    printf("4.Write File\n");
    printf("5.Append File\n");
    printf("6.Rename File\n");
    printf("7.Display File Information\n");
    printf("8.Create Directory\n");
    printf("9.Delete Directory\n");
    printf("10.List Content In A Directory\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:create_file();
      break;
      case 2:delete_file();
      break;
      case 3:read_file();
      break;
      case 4:write_file();
      break;
      case 5:append_file();
      break;
      case 6:rename_file();
      break;
      case 7:display_file_info();
      break;
      case 8:create_directory();
      break;
      case 9:delete_directory();
      break;
      case 10:list_directory();
      break;
      default:exit(0);
    }
  }  
  return 0;
}
  
