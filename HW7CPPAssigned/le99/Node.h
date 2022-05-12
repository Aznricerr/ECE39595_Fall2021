#include <iostream>
#include <string>

template <class data_t>
class Node
{
private:
   data_t data;
   Node *left = nullptr;
   Node *right = nullptr;

public:
   Node();
   Node(const data_t &val);
   void print() const;
   Node *insertNode(const data_t &n);
};

template <class data_t>
Node<data_t>::Node() {}

template <class data_t>
Node<data_t>::Node(const data_t &val)
{
   data = val;
}

template <class data_t>
void Node<data_t>::print() const
{
   if (this->left != nullptr)
   {
      this->left->print();
   }
   std::cout << data << " ";
   if (this->right != nullptr)
   {
      this->right->print();
   }
}

template <class data_t>
Node<data_t> *Node<data_t>::insertNode(const data_t &n)
{
   if (this->data == n)
      return this;
   if (n < this->data)
   {
      if (left != nullptr)
         return left->insertNode(n);
      else
      {
         left = new Node(n);
         return (left);
      }
   }
   if (n > this->data)
   {
      if (right != nullptr)
         return right->insertNode(n);
      else
      {
         right = new Node(n);
         return (left);
      }
   }
   return (nullptr);
}
