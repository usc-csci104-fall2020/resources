#include <memory>

struct Node 
{
	int val;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	Node(int x, std::shared_ptr<Node> left, std::shared_ptr<Node> right) : val(x), left(left), right(right) {}
};

int numLeaves(std::shared_ptr<Node> root);
