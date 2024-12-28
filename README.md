# Words Counter using TDD

## Author
<p>Lucas Gabriel de Oliveira Lima - 231003406<p>
<table>
  <tr>
    <td align="center"><a href="https://github.com/lucasdbr05" target="_blank"><img style="border-radius: 50%;" src="https://github.com/lucasdbr05.png" width="100px;" alt="Lucas Lima"/><br /><sub><b>Lucas Lima</b></sub></a><br /></td>
</table>

## Setup

```shell
sudo apt-get install g++
sudo apt-get install make
sudo apt-get install valgrind
sudo apt-get install cppcheck
sudo apt-get install clang-format-14
sudo apt-get install doxygen

sudo apt-get install python3-pip
sudo pip install cpplint
```

or

```shell
make setup
```


## Run

To compile the main file, the tests, and run the tests:
```shell
make all
```

To analyse test coverage:
```shell
make gcov
```

To analyze static and dynamic memory leaks:
```shell
make valgrind
make cppcheck
```

To check the code formatting standards:
```shell
make cpplint
```
