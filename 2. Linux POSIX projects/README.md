# Projects in Linux
These projects were made in Linux using POSIX and implement the following:
```
-Listing directory contents;
-Identifying and parsing section files;
-Working with sections;
-Sections filtering;
-Create a Process Hierarchy;
-Synchronizing threads from the same process;
-Create a Threads Barrier;
-Synchronizing threads from different processes;
-Pipe Based Connection;
-Ping Request;
-Request to Create a SHM: Shared Memory Region;
-Write to Shared Memory Request;
-Memory-Map File Request;
-Read From File Offset Request;
-Read From File Section Request;
-Read From Logical Memory Space Offset Request.
```

## Getting Started
You can find each project's description and requirements in the .pdf file attached to it. Also, you should take a quick look over the code written in the .c file.<br/>
In order to test any project you need to:
```
1) Download .c and tester.py files in the same directory;
2) Open a new terminal in that directory and write: "gcc -Wall 'Project Name.c' -o 'Project Name'" (Chapter 2.1);
3) In order to test it write: "python tester.py" (Chapter 3.1);
4) If you want more details while testing, open tester.py and change verbose to true before step3.
```
When submitted, our implementation was tested with one more python file. Below I attached photos with the testing results for each(which is a little lower compared to the tester scores I had).

## Python Tests Score
![alt text](https://github.com/DanutGavrus/Photos/blob/master/1.%20File%20System%20Module.png)<br/><br/><br/>
![alt text](https://github.com/DanutGavrus/Photos/blob/master/2.%20Inter-Process%20Communication.png)<br/><br/><br/>
![alt text](https://github.com/DanutGavrus/Photos/blob/master/3.%20File%20System%20Module.png)

### Built With
* [Code::Blocks](http://www.codeblocks.org/) - The C IDE used
* [Lubuntu](https://lubuntu.net/) - The OS used