#include <iostream>
#include <set>
#include <vector>
#include <string>

#include "order.h"
#include "logstack.h"

template<typename PositionType, typename OperationType>
class Solver {
public:

    // Status type
    enum Status {
        UNSOLVED,
        INCORRECT,
        WASSOLVED,
        UNSOLVABLE,
        SOLVED,
        OPTIMIZED
    };
private:
    typedef Order<OperationType> OperationOrderedType;
    typedef LogStack<PositionType, OperationOrderedType> LogStackType;
    typedef std::vector<OperationType> OperationVectorType;
    // Deck
    PositionType deck;
	
    // LogStack
    LogStackType logStack;
   
    // Current status
    Status status;

public:	
    // Constructors
    Solver() : deck(), status(UNSOLVED) {}
    Solver(std::istream & input) : deck(input), status(UNSOLVED) {}
    Solver(const PositionType & source) : deck(source), status(UNSOLVED) {};

    static std::set<std::string> deadSet;
    
    // Solve
    void solve(unsigned S = 0);

    // Getter of status
    inline Status getStatus() const {
        return status;
    }

    inline unsigned size() const {
        return logStack.size();
    }

    inline void optimize() {
        logStack.optimize();
    }

    void getResult(std::ostream & out) {
        switch (status) {
            case INCORRECT:
                out << "Incorrect input" << std::endl;
                break;
            case UNSOLVABLE:
                out << "Unsolvable puzzle" << std::endl;
                break;
            case SOLVED:
                out << "Solution: " << std::endl << logStack;
                break;
            case WASSOLVED:
                std::cout << "Puzzle has been already solved, look!" << std::endl; 
                break;
            default:
                break;
        }
    }
};

template<typename PositionType, typename OperationType>
std::set<std::string> Solver<PositionType, OperationType>::deadSet;

template<typename PositionType, typename OperationType>
void Solver<PositionType, OperationType>::solve(unsigned S) { 

    // If deck is incorrect, sorry
    if (!deck.isCorrect()) {
        status = INCORRECT;
        return;
    } 

    // Hash set with delay
    std::set<std::string> hashSet;

    // Pushing first operations vector
                            logStack.push(Order<OperationType>());
                            deck.getListOfOperations(logStack.top());
                            logStack.top().Init();

    while (true) {
        // If there're any unused operations on top
        if (!S || (logStack.size() < S )) {
            if (logStack.top().isValid()) {
                if (!logStack.isUseless()) {
                    deck.makeOperation(logStack.top());

                    // Counting hash
                    const std::string newhash = deck.hash();

                    if (!deadSet.size() || (deadSet.find(newhash) == deadSet.end())) {
                        if (hashSet.find(newhash) == hashSet.end()) {
                            // Check for finish
                            if (deck.isFinished()) {
                                status = SOLVED;
                                return;
                            }
                
                            // Getting operation on current position                          
                            logStack.push(Order<OperationType>());
                            deck.getListOfOperations(logStack.top());
                            logStack.top().Init();

                            // Inserting hash
                            hashSet.insert(newhash);
                        // std::cout << deck << std::endl;
                        }
                        else {
                            // If this position was before, undone changes...
                            deck.unmakeOperation(logStack.top());
                            logStack.top().setNext();
                        }
                    }
                    else {
                        deck.unmakeOperation(logStack.top());
                    
                        logStack.top().incDead();
                        logStack.top().setNext();
                    }
                }
                else {
                    logStack.top().incDead();
                    logStack.top().setNext();
                }
            }
            else {

                // Deadlock position.
                // Rollback last movement
                
                bool deadlock = false;

                if (logStack.top().isEmpty()) {
                    deadSet.insert(deck.hash());
                    deadlock = true;
                }
                logStack.pop();            

                // If all movements are deadlock, return
                if (logStack.empty()) {
                    status = UNSOLVABLE;
                    return;
                }

                if (deadlock) {
                    logStack.top().incDead();
                }
                if (logStack.top().isDeadLock()) {
                    deadSet.insert(deck.hash());
                }

                // Current position is useless, and shouldn't be erased from set
                // But it'll cause memory overflow
                hashSet.erase(deck.hash());
                deck.unmakeOperation(logStack.top());
                logStack.top().setNext();
            }
        }
        else {
                // Deadlock position.
                // Rollback last movement
                logStack.pop();

                // If all movements are deadlock, return
                if (logStack.empty()) {
                    status = UNSOLVABLE;
                    return;
                }

                // Current position is useless, and shouldn't be erased from set
                // But it'll cause memory overflow
                hashSet.erase(deck.hash());
                deck.unmakeOperation(logStack.top());
                logStack.top().setNext();
                

  //          std::cout << "ROLLBACK " << S - logStack.size() << std::endl;
        }
    }
}