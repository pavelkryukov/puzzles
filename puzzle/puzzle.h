#include <ctime>
#include <iostream>

#include "solver.h"

template<typename PositionType, typename OperationType>
class Puzzle {
    typedef Solver<PositionType, OperationType> SolverType;
    const PositionType position;
public:
    Puzzle(std::istream & input) : position(input) {}

    void solve(unsigned size = 0) const {
       SolverType* solver1 = new SolverType(position);
       
       const unsigned t0 = std::clock();
       solver1->solve(size);
       const unsigned t = std::clock() - t0;
       
       solver1->getResult(std::cout);

       std::cout << "Time: " << ((float)t / CLOCKS_PER_SEC) << "s" << std::endl;
       delete solver1;
    }

    void fillDeadLocks(unsigned size) const {
        for (unsigned size1 = 1; size1 < size; size1++) {
            SolverType solver(position);
            solver.solve(size1);
        }
    }

    void solveMinimumUp(unsigned size1 = 1) const {
        for (unsigned size = size1; true; size++) {
            SolverType solver(position);

            const unsigned t0 = std::clock();
            solver.solve(size);
            const unsigned t = std::clock() - t0;

            std::cout << size << " operations in " << ((float)t / CLOCKS_PER_SEC) << "s" << std::endl;

            if (solver.getStatus() == SolverType::SOLVED) {
                solver.getResult(std::cout);
                break;
            }
        }
    }

    void solveMinimumDown(unsigned size = 0) const {
        SolverType* previous = 0;
        do {
            SolverType* solver = new SolverType(position);

            const unsigned t0 = std::clock();
            solver->solve(size);
            const unsigned t = std::clock() - t0;

            if (solver->getStatus() != SolverType::SOLVED) {
                if (previous) {
                    previous->getResult(std::cout);
                    delete previous;
                }
                else {
                    solver->getResult(std::cout);
                }
                delete solver;
                break;
            }
            
      //      solver2->optimize();

            size = solver->size();
            std::cout << size << " operations in " << ((float)t / CLOCKS_PER_SEC) << "s" << std::endl;
            
            delete previous;
            previous = solver;
        } while (true);
    }
};
