/* Given two linked lists, 'list1' and 'list2', and two indices, 'a' and 'b',
replace the nodes of 'list1' from index 'a' to 'b' with the nodes of 'list2'. */

#include <iostream>
#include <vector>

struct Node
{
    int m_data;
    Node *m_next = nullptr;

    Node(int val = -1, Node *next = nullptr)
        : m_data(val), m_next(next) {}

    // Insert a node at the end of the list.
    void append(Node *node)
    {
        auto *iter = this;
        while (iter && iter->m_next)
            iter = iter->m_next;

        iter->m_next = node;
    }
}; // Node of the linkList.

void deleteList(Node *root)
{
    Node *temp = nullptr;
    while (root)
    {
        temp = root;
        root = root->m_next;
        delete temp;
        temp = nullptr;
    }
}

void PrintList(Node *root)
{
    if (!root)
        return;

    Node *iter = root;
    while (iter)
    {
        std::cout << iter->m_data << " ";
        iter = iter->m_next;
    }
    // std::cout << "):";
}

/**
 * Space: Needs extra space of size m and n, where m and n are lengths of list1 and list2 respectively.
 * Time: O(m+n) Iterates through list1 and list2.
 * Stores both lists in containers, then directly, using the indexes given (idx_a and idxb), 
 * change the next pointers of the required nodes.*/
Node *Solution(Node *list1, Node *list2, int idx_a, int idx_b)
{
    if (!list1 || !list2)
        return nullptr;

    std::vector<Node *> vec1;
    std::vector<Node *> vec2;

    while (list1)
    {
        vec1.emplace_back(list1);
        list1 = list1->m_next;
    } // storing the list1.

    while (list2)
    {
        vec2.emplace_back(list2);
        list2 = list2->m_next;
    } // storing the list2.

    if ((idx_a > 0) && (idx_b < vec1.size() - 1) && (vec2.empty() == false /* list2 is not null */))
    {
        // Nodes in list1 before and after the replacement range.
        auto nodeBefore_Idx_a = vec1[idx_a - 1];
        auto nodeAfter_Idx_b = vec1[idx_b + 1];

        // Nodes at the start and end of list2.
        auto startNode_list2 = vec2[0];
        auto endNode_list2 = vec2[vec2.size() - 1];

        if (startNode_list2 && startNode_list2)
        {
            nodeBefore_Idx_a->m_next = startNode_list2;
            endNode_list2->m_next = nodeAfter_Idx_b;
        }

        for (int idx = idx_a; (idx <= idx_b && idx < vec1.size()); ++idx)
        {
            delete vec1[idx];
            vec1[idx] = nullptr;
        } // Delete the nodes from list1 that are being replaced.
    }

    return vec1.front();
}

int main()
{
    // Create list1
    Node *root_list1 = new Node(1);
    root_list1->append(new Node(2));
    root_list1->append(new Node(3));
    root_list1->append(new Node(4));

    // Create list2
    Node *root_list2 = new Node(1002);
    root_list2->append(new Node(1003));

    std::cout << "list1: ";
    PrintList(root_list1);
    std::cout << "\nlist2: ";
    PrintList(root_list2);

/**
 * list1 :  1->2->3->4
 * list2 :   1002 -> 1003
 *  a = 1, b = 2
 *  output : 1 -> 1002 -> 1003 -> 4  
 */

    Node *mergedList = Solution(root_list1, root_list2, 1, 2);
    std::cout << "\noutput: ";
    PrintList(mergedList);

    // Cleanup remaining nodes to prevent memory leaks
    deleteList(root_list1);

    return 0;
}
