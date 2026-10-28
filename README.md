# CIS-277 Assignment 3: Text Messages and Dynamic Memory
## Student
Tomasz Przewoznik

## Design
I planned to use a singly linked list to store messages dynamically. Each node contains a TextMessage and a pointer to the next node. The MessageInbox owns and manages all nodes, using head and tail pointers to track the beginning and end of the list. The inbox keeps track of the message count, used text bytes, and maximum text capacity. Before adding a message, it checks that the ID is valid and unique, the sender and text are not empty, and enough capacity remains. Adding, reading, deleting, and clearing messages updates the list and counters as needed. The destructor calls clear() to delete all nodes and prevent memory leaks. Only message text counts toward the byte limit.

## How to Compile
A C++23-compatible compiler is required. Compile the program using the following command:

g++ -std=c++23 -Wall -Wextra -pedantic main.cpp MessageInbox.cpp -o message_inbox.exe

## How to Run
On Windows, run the executable from the terminal:

.\message_inbox.exe

## Tests and Results
I tested the program using the demonstration in main.cpp and additional individual checks suggest by AI.

| Test | Expected result | Actual result |
|---|---|---|
| Initialize a 20-byte inbox | 0 messages, 0 bytes used, 20 bytes remaining | Passed |
| Receive `"Hello"` | 1 message, 5 bytes used, 15 bytes remaining | Passed |
| Receive `"Greetings"` after `"Hello"` | 2 messages, 14 bytes used, 6 bytes remaining | Passed |
| Receive `"Hello there"` with only 6 bytes remaining | Message rejected; counters remain unchanged | Passed |
| Read message ID 1 | Correct message returned and marked as read | Passed |
| Erase message ID 1 | Message removed; count becomes 1, used bytes become 9, and 11 bytes remain | Passed |
| Call `messages()` | Remaining messages returned in arrival order | Passed |
| Call `clear()` | 0 messages, 0 bytes used, 20 bytes remaining | Passed |
| Receive a message after clearing | New message accepted; counters update correctly | Passed |
| Receive a duplicate ID | Duplicate message rejected | Passed |
| Receive ID 0 | Message rejected | Passed |
| Receive with an empty sender | Message rejected | Passed |
| Receive with empty text | Message rejected | Passed |
| Read a nonexistent ID | Returns `false` and leaves the result unchanged | Passed |

## Analysis Questions
1.
  First node: The head pointer moves to the second node. 

  Before:

  head
   |
   v
  [A] -> [B] -> [C] -> nullptr
                   ^
                   |
                  tail

  After deleting A:

  head
   |
   v
  [B] -> [C] -> nullptr
          ^
          |
         tail

  Deleting the last node: The previous node's next pointer becomes nullptr, and tail is updated to point to that previous node.

  Before:

  head
   |
   v
  [A] -> [B] -> [C] -> nullptr
                   ^
                   |
                  tail

  After deleting C:

  head
   |
   v
  [A] -> [B] -> nullptr
          ^
          |
        tail

  Deleting the only node: Both head and tail become nullptr, because no nodes remain.

  Before:

  head, tail
      |
      v
     [A] -> nullptr
  
  After:
  head = nullptr
  tail = nullptr


3. Read does not delete or alter anything, while deleting removes the node it's affecting and releases its memory.
4. It measures the sum of the lengths of all stored message texts. It excludes sender strings, TextMessage objects, Node objects, the messages() vector, and pointer fields.
5. In the worst case, receive might have to examine all existing nodes n, making it have O(n) time. Meanwhile, appending is only O(1) because the tail is already known, meaning it doesn't have to go through potentially the whole list.
6. If they remain allocated, the memory will leak. Since there's no longer anything pointing to those nodes, they can no longer be deallocated. If two inbox objects share the same ownership, then both may try to delete the same nodes, causing memory corruption. 

## AI Use
ChatGPT was used for bug finding and fixing along with additional testing and formatting the table for said testing's results.
