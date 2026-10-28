#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t blockSize, size_t blockCount) //constructor
{
    size = blockSize;
    count = blockCount;

    memory = new unsigned char[size * count];

    for (size_t i = 0; i < count; i++)
    {
        freeStack.push(memory + (i * size));
    }
}

MemoryPool::~MemoryPool() //destructor
{
    delete[] memory;
}

void* MemoryPool::allocate() //removes one available block from the free-block stack and returns a pointer to that block
{
    if(freeStack.empty())
    {
        return nullptr; //returns null pointer if empty
    }
    else
    {
        void* block = freeStack.pop();
        allocated.push_back(block); //adds block to allocated to keep track
        return block;
    }
}

bool MemoryPool::deallocate(void* ptr)
{
    for (size_t i = 0; i < allocated.size(); i++)
    {
        if (allocated[i] == ptr) //checks if block is already allocated
        {
            freeStack.push(ptr);
            allocated.erase(allocated.begin() + i);
            return true;
        }
    }

    return false;
}

size_t MemoryPool::availableBlocks() const //returns num of unallocated blocks
{
    return freeStack.size();
}

size_t MemoryPool::allocatedBlocks() const //returns num of allocated blocks
{
    return allocated.size();
}

size_t MemoryPool::blockSize() const //returns one block's capacity in bytes
{
    return size;
}

size_t MemoryPool::capacity() const //returns total capacity of stack in bytes
{
    return size * count;
}