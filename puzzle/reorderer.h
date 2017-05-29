#include <list>
#include <map>
#include <vector>

template<typename OperationType, typename PriorityType>
class OperationOrderList {
    struct OperationOrderListItem : private std::pair<OperationType, PriorityType> {    
        // Constructor
        OperationOrderListItem(const OperationType & type, const PriorityType delta) : std::pair<OperationType, PriorityType>(type, delta) {}

        const OperationType & getOperation() {
            return this->first;
        }

        // Comparsion for sorting
        inline const bool operator< (const OperationOrderListItem & secondObj) {
            return (this->second > secondObj.second);
        }
    }; 

    std::list<OperationOrderListItem> list;
public:
    void push_back(const OperationType & operation, const PriorityType & priority) {
        list.push_back(OperationOrderListItem(operation, priority));
    }

    void clear() {
        list.clear();
    }

    void getVector(std::vector<OperationType> & vector) {
        // Sorting
        list.sort();

        // Filling vector
        vector.resize(list.size());
        unsigned i = 0;
        const typename std::list<OperationOrderListItem>::iterator end = list.end();
        for ( typename std::list<OperationOrderListItem>::iterator it = list.begin(); 
                it != end; ++it, ++i) {
            vector[i].copy(it->getOperation());
        }
    }
};