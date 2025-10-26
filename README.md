# todo-cli

a command line todo list built with C++, saves to a text file.
(a learning project - building while figuring out cmd line parsing with vectors and file i/o)

## build & run
```bash
g++ -o todo src/main.cpp
./todo add "buy food"
./todo list
./todo complete 1
./todo delete 2
```

## how it works

stores tasks in `tasks.txt`:
```
0|buy food
1|finish project
```

first number: 0 = not done, 1 = done.

## todo

- [ ] add colors
- [ ] add priorities
- [ ] better the file format