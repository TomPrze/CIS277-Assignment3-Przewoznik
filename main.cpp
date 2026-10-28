#include "MessageInbox.h"
#include <iostream>
#include <vector>

int main()
{
    MessageInbox inbox(20);
    std::cout << "=== Receive Messages ===\n";
	
	std::cout << "Message 1 accepted: "
	          << inbox.receive(1, "John", "Hello") << '\n';
	
	std::cout << "Message 2 accepted: "
	          << inbox.receive(2, "Winston", "Greetings") << '\n';
	
	std::cout << "Message 3 accepted: "
	          << inbox.receive(3, "Alina", "Hello there") << '\n';
	
	std::cout << "\n=== Inbox Status ===\n";
	std::cout << "Message count: " << inbox.messageCount() << '\n';
	std::cout << "Used bytes: " << inbox.usedTextBytes() << '\n';
	std::cout << "Remaining bytes: " << inbox.remainingTextBytes() << '\n';
	
	std::cout << "\n=== Read Message ===\n";
	
	TextMessage result;
	
	if (inbox.read(1, result))
	{
	    std::cout << "Sender: " << result.sender << '\n';
	    std::cout << "Text: " << result.text << '\n';
	    std::cout << "Is read: " << result.isRead << '\n';
	}
	else
	{
	    std::cout << "Message not found.\n";
	}
	
	std::cout << "\n=== Delete Message ===\n";
	std::cout << "Message 1 erased: " << inbox.erase(1) << '\n';
	
	std::cout << "\n=== Remaining Messages ===\n";
	
	std::vector<TextMessage> allMessages = inbox.messages();
	
	for (const TextMessage& msg : allMessages)
	{
	    std::cout << "ID: " << msg.id
	              << ", Sender: " << msg.sender
	              << ", Text: " << msg.text
	              << ", Is read: " << msg.isRead << '\n';
	}
	
	std::cout << "\n=== Clear Inbox ===\n";
	inbox.clear();
	
	std::cout << "Message count: " << inbox.messageCount() << '\n';
	std::cout << "Used bytes: " << inbox.usedTextBytes() << '\n';
	std::cout << "Remaining bytes: " << inbox.remainingTextBytes() << '\n';
	
	return 0;
}