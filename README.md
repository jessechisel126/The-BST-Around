The-BST-Around
==============
My program can take in multiple files through command line arguments. So, if using cmd, you must first change your directory to the folder containing the .exe for this program and any test case .txt files. Then, you will need to type the name of the .exe of this program and all .txt files you wish to test separated by spaces, keeping in mind that if any of these file names contains spaces, the file name must be encapsulated by double-quotes.

Ex: ...\Desktop> program.exe "test 1.txt" test2.txt "t e s t 3 .txt"

If using Visual Studio to directly pass the command line arguments to the program, you will need to navigate to the "Solution Explorer" tab and right-click on the project "Chisholm - Homework 4", and click on "Properties". In the "Debugging" section, you will find the "Command Arguments" field. In this, you will type the name of all .txt files you wish to test separated by spaces, keeping in mind that if any of these file names contains spaces, the file name 
must be encapsulated by double-quotes.

Ex: | Command Arguments | "test 1.txt" test2.txt "t e s t 3 .txt"
