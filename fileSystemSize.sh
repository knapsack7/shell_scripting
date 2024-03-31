#! /bin/bash
echo "This program get first 10 biggest file in the file system passed via positional argument"
path = "$1"
echo $path
du -ah $path | sort -hr | head -n 5 > /Users/manoj/Documents/shellscripting/fileSize.txt
echo "This is the list of big files in the file System $path "
cat /Users/manoj/Documents/shellscripting/fileSize.txt
