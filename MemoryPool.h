#include <iostream>
#include <vector>
#include "Stack.h"
using namespace std;

class MemoryPool
{
public:
    MemoryPool(size_t blockSize, size_t blockCount); //constructor

    ~MemoryPool(); //destructor

    void* allocate(); //removes one available block from the free-block stack and returns a pointer to that block

    bool deallocate(void* ptr);

    size_t availableBlocks() const; //returns num of unallocated blocks

    size_t allocatedBlocks() const; //returns num of allocated blocks

    size_t blockSize() const; //returns one block's capacity in bytes

    size_t capacity() const; //returns total capacity of stack in bytes

private:
    Stack<void*> freeStack;
    unsigned char* memory;
    size_t size; //size of each block
    size_t count; //num of blocks

    vector<void*> allocated; //to keep track of allocated blocks
};