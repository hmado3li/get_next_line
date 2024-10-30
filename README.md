# get_next_line
## Overview
The get_next_line project is part of the curriculum at 42, where the objective is to implement a function that reads a line from a file descriptor, one line at a time, until the end of the file. This project highlights important programming concepts related to file handling, memory management, and function usage in C.

## Project Goals
The function `get_next_line` is designed to:

- Read from a file descriptor and return a line each time it’s called.
- Handle various edge cases, such as multiple calls to read from a file and reading from standard input.

## Key Concepts Learned
### Memory Leaks
In this project, I developed a deeper understanding of memory leaks and how to avoid them. Working with dynamic memory allocation (`malloc` and `free`), I learned how memory can be allocated without proper release, leading to memory leaks. Proper memory management is crucial to ensure no allocated memory remains unfreed, especially in a function like `get_next_line`, which is called multiple times in succession.

### File Descriptors (File Table and Node Table)

The project gave me a closer look at file descriptors, which represent open files in a program. Each file descriptor has entries in two tables:

- **File Table**: Stores information about open files, including the file descriptor, offset (position of the read/write pointer), and file status.
- **Node Table**: Stores metadata about the file, like permissions, size, and timestamps. Multiple file descriptors can refer to the same entry in this table, which is useful for managing open files across different parts of a program.

### The `read` and `open` Functions
The `read` function is fundamental to `get_next_line`, as it reads a specified number of bytes from a file descriptor. Similarly, the `open` function is responsible for opening a file and returning a descriptor, which is essential for initializing the file descriptor used by `get_next_line`. Correct handling of these functions allowed me to read from files efficiently and manage errors such as incomplete reads.

### `read` Function Offset
An essential part of this project involved managing the offset within the file. The offset marks the position in the file from which data is `read`. Each call to read advances the file offset based on the number of bytes read, allowing `get_next_line` to continue reading from the correct position on each subsequent call.

Usage
To use `get_next_line`, include the header and call it with a file descriptor as the parameter. Each call to `get_next_line` returns the next line from the file until it reaches the end of the file (EOF).

```c
Copy code
#include "get_next_line.h"

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## Conclusion
The get_next_line project at 42 was an excellent opportunity to learn about file handling, memory management, and efficient reading operations in C. This project built a strong foundation for understanding file I/O in low-level programming.
