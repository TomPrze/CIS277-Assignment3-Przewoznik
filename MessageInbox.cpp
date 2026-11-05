#include "MessageInbox.h"

MessageInbox::MessageInbox(std::size_t maxTextBytes)
{
	head = nullptr;
	tail = nullptr;
	count = 0;
	usedBytes = 0;
	maxBytes = maxTextBytes;
}

MessageInbox::~MessageInbox()
{
    clear();
}

bool MessageInbox::receive(std::size_t id,
            const std::string& sender,
            const std::string& text)
{
    if(id == 0 || sender.empty() == true || text.empty() == true)
    {
    	return false;
	}
	
	if(text.size() > maxBytes - usedBytes)
		return false;
		
	Node* current = head;
	while(current != nullptr)
	{
		if(current->message.id == id)
			return false;
		
		else
			current = current->next;
	}
	
	Node* newNode = new Node;
	newNode->message.id = id;
	newNode->message.sender = sender;
	newNode->message.text = text;
	newNode->message.isRead = false;
	newNode->next = nullptr;
	
	if(head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	count++;
	usedBytes += text.size();
	
	return true;
}
	
bool MessageInbox::read(std::size_t id, TextMessage& result)
{
	Node* current = head;
	while(current != nullptr)
	{
		if(current->message.id == id)
			{
				current->message.isRead = true;
				result = current->message;
				return true;
			}
		else
			current = current->next;
	}
	return false;
}

bool MessageInbox::erase(std::size_t id)
{
	if (head == nullptr)
    {
        return false;
    }
	
    if (head->message.id == id)
    {
		Node* delNode = head;
		head = head->next;
		if(head == nullptr)
			tail = nullptr;
		
		--count;
		usedBytes -= delNode->message.text.size();
		
		delete delNode;
		
		return true;
	}
	
	Node* previous = head;
	Node* current = head->next;
	while (current != nullptr)
	{
	    if (current->message.id == id)
	    {
	        previous->next = current->next;
			if(current == tail)
			{
				tail = previous;
			}
			
			--count;
			usedBytes -= current->message.text.size();
			
			delete current;
			
			return true;
	    }
	    else
	    {
	        previous = current;
			current = current->next;
	    }
	}
	
	return false;
}

std::vector<TextMessage> MessageInbox::messages() const
{
	std::vector<TextMessage> result;
	
	Node* current = head;
	while (current != nullptr)
	{
		result.push_back(current->message);
		current = current->next;
	}
	
	return result;
}

void MessageInbox::clear()
{
	while(head != nullptr)
    {
		Node* delNode = head;
		head = head->next;
		delete delNode;
	}
	
	tail = nullptr;
	usedBytes = 0;
	count = 0;
}
	
std::size_t MessageInbox::messageCount() const
{
	return count;
}
	
std::size_t MessageInbox::usedTextBytes() const
{
	return usedBytes;
}
	
std::size_t MessageInbox::remainingTextBytes() const
{
	return maxBytes - usedBytes;
}