#include <vector>

// Operation with internal vector of next/prev operations

template<typename OperationType>
class Order : public OperationType, public std::vector<OperationType> {
    // Number of current operations
    unsigned current;
    unsigned deadcauses;
public:
    // Constructors
    Order();
    Order(const Order<OperationType> & source);
 
    // Set next operation
    void setNext();

    void Init();
    void incDead() {
        deadcauses++;
    }

    bool isDeadLock() {
        return deadcauses == this->size();
    }

    // Check if there any unused operations
    bool isValid() const;

    bool isEmpty() const {
        return (this->size() == 0);
    }
};

template<typename OperationType>
Order<OperationType>::Order()
    : OperationType()
    , std::vector<OperationType>()
    , current(0)
    , deadcauses(0)
{ }

template<typename OperationType>
Order<OperationType>::Order(const Order<OperationType> & source)
    : OperationType(source)
    , std::vector<OperationType>(source)
    , current(0)
    , deadcauses(0)
{ }

template<typename OperationType>
void Order<OperationType>::Init() {
    if (this->size()) {
        this->copy((*this)[current]);
    }
}

template<typename OperationType>
void Order<OperationType>::setNext() {
    ++current;
    if (current == this->size())
        return;
    this->copy((*this)[current]);
}

template<typename OperationType>
bool Order<OperationType>::isValid() const {
    return current < this->size();
}