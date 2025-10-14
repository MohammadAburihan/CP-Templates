#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename Key, typename Value>
using ordered_map = tree<Key, Value, less<Key>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    // Declaration of ordered_multiset as 'ss'
    ordered_multiset<int> ss;

    // Inserting elements into 'ss'
    ss.insert(5);
    ss.insert(2);
    ss.insert(7);
    ss.insert(2); // Allows duplicates
    ss.insert(1);

    // Erase element 20
    ss.erase(20);

    if (ss.find(20) != ss.end())
        cout << "20 is found\n";
    else
        cout << "20 is not found\n";

    // Find lower bound of 15
    auto it = ss.lower_bound(15);

    // Displaying elements 
    cout << "Elements in the ordered_multiset: ";
    for (auto it : ss) { // 1 2 2 5 7
        cout << it << " ";
    }
    cout << endl;

    // Counting elements less than 5 using order_of_key
    cout << "Elements less than 5: " << ss.order_of_key(5) << endl; // 3

    // Deleting an element, e.g., deleting value 2
    auto it = ss.find_by_order(ss.order_of_key(2)); // Find iterator to the element 2
    if (it != ss.end()) {
        ss.erase(it); // Erase the found element O(log n)
        cout << "Element 2 removed from the ordered_multiset." << endl;
    } else {
        cout << "Element not found in the ordered_multiset." << endl;
    }

    return 0;
}
