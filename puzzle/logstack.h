#include <stack>

template<typename PositionType, typename OperationOrderedType>
class LogStack : public std::stack<OperationOrderedType> {
public:
    // Default constructor.
    LogStack() : std::stack<OperationOrderedType>() {}

    bool isUseless() {
        return (this->size() > 1) && (this->top() != *(--(--(this->c.end()))));
    }

    // Dumping operator 
    template<
        typename PositionTypeT,
        typename OperationOrderedTypeT
    >
    friend std::ostream& operator<< (std::ostream & out, const LogStack<PositionTypeT, OperationOrderedTypeT> & item);

    void makeOn(const PositionType & position) const;
};

template<typename PositionType, typename OperationOrderedType>
std::ostream& operator<< (std::ostream & out, const LogStack<PositionType, OperationOrderedType> & item) {  
    for ( typename LogStack<PositionType, OperationOrderedType>::container_type::const_iterator 
            it = item.c.begin(), end = item.c.end(); it != end; ++it){ 
        out << *it << std::endl;
    }
    out << "Total: " << item.size() << " operations." << std::endl;
    return out;
}

template<typename PositionType, typename OperationOrderedType>
void LogStack<PositionType, OperationOrderedType>::makeOn(const PositionType & position) const {
    PositionType local(position);
    for ( typename LogStack<PositionType, OperationOrderedType>::container_type::const_iterator 
        it = this->c.begin(), end = this->c.end(); it != end; ++it){ 
        std::cout << local;
        std::string s;
        std::cin >> s;
        local.makeOperation(*it);
    }
}
