Going back to practice some algorithms in C++ whenever I have some free time. 

Will try to add some small twists and challenges for myself and to structure the software in a more robust way.

Any suggestions on how to improve performance/readability/scalability are more than welcomed.

### Installing GoogleTest as a Shared Library
```
$ sudo apt install libgtest-dev -y

$ cd /usr/src/gtest

$ sudo cmake CMakeLists.txt

$ sudo make all

$ sudo apt install google-mock -y

$ cd /usr/src/gmock

$ sudo cmake CMakeLists.txt

$ sudo make all

$ cd /usr/src/googletest

# create symbolic links to all gtest libraries into the /usr/lib folder 

$ sudo find -name "*.a" -exec ln -vsr "{}" --target-directory="/usr/lib" ';'
```