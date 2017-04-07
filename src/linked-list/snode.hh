#pragma once

#include <initializer_list>
#include <set>
#include <stdexcept>
#include <type_traits>


namespace ospp {


template<typename T>
struct Node {
  T data{};
  Node *next{nullptr};

  Node(T &data, Node *next)
  noexcept(std::is_nothrow_copy_constructible<T>::value);
  Node(T &data) noexcept(std::is_nothrow_copy_constructible<T>::value);
  Node() noexcept(std::is_nothrow_constructible<T>::value) = default;
};


template<T>
Node<T>::Node(T &data, Node<T> *next)
  noexcept(std::is_nothrow_copy_constructible<T>::value)
  : data{data}, next{next}
{}


template<T>
Node<T>::Node(T &data) noexcept(std::is_nothrow_copy_constructible<T>::value)
  : data{data}
{}


template<typename T>
void
removeDuplicates(Node<T> *node)
{
  std::set<T> found;
  auto prev = node;
  while (node) {
    auto it = found.insert(node->data);
    if (not it->second) {
      auto tmp = node;
      node = node->next;
      prev->next = node;
      delete tmp;
      continue;
    }
    prev = node;
    node = node->next;
  }
}


template<typename T>
unsigned
length(Node<T> *node) noexcept
{
  auto len = 0u;
  while (node) {
    ++len;
    node = node->next;
  }
  return len;
}


template<typename TData>
TData
getKthFromLast(Node<TData> *node, unsigned k)
{
  auto leading = node;
  while (leading and k) {
    --k;
    leading = leading->next;
  }

  if (k)
    throw std::out_of_range;

  while (leading) {
    leading = leading->next;
    node = node->next;
  }
  return node->data;
}


template<typename TData>
void
removeNode(Node<TData> *node)
{
  if (not node)
    return;

  if (not node->next) {
    delete node;
    return;
  }

  auto tmp = node->next;
  node->data = tmp->data;
  node->next = tmp->next;
  delete tmp;
}


template<typename TData>
Node<TData>* createNodeList(std::initializer_list<TData> dataList)
{
  Node<TData> *head{nullptr}, *next{nullptr};
  for (auto data : dataList)
  {
    if (not head) {
      try {
        head = new Node<TData>(data);
        next = head;
      } catch (...) {
        // delete node list and re-throw
      }
    }
    else {
      try {
        next->next = new Node<TData>(data);
        next = next->next;
      } catch (...) {
        // delete node list and re-throw
      }
    }
  }
}


template<typename TData>
void
deleteNodeList(Node<TData> *node) noexcept
{
  Node<TData> *prev;
  while (node) {
    prev = node;
    node = node->next;
    delete prev;
  }
}


} // namespace ospp
