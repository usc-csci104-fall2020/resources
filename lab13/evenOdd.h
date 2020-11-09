#include <memory>

struct Node 
{
	int val;
	std::shared_ptr<Node> next;
	Node(int x) : val(x), next(nullptr) {}
	Node(int x, std::shared_ptr<Node> nextNode) : val(x), next(nextNode) {}
};


std::shared_ptr<Node> oddEvenList(std::shared_ptr<Node> head);