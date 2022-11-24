

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    //worked vector keeps track of how many times a worker has worked
    vector<size_t> worked(avail[0].size());
    //instantiates empty element, useful for the logic of the helper function later
    sched.emplace_back();

    if(helperSchedule(avail, dailyNeed, maxShifts, sched, worked)) return true;
    else {
        sched.pop_back();
        return false;
    }
}


bool helperSchedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& worked
)
{
    //base case
    //if the built schedule has reached the required num of days 
    //and the last day has been filled, the schedule is valid
    if(sched.size() > avail.size()) {
        sched.pop_back();
        return true;
    }

    int currDay = sched.size() - 1;

    Worker_T i;
    if(sched.back().size() == 0) i = 0;
    else i = sched.back().back() + 1;
    for(; i < avail[currDay].size(); i++) {
        //checks to see if the current worker is available to call,
        //and has not been overworked
        if(avail[currDay][i] == 0) continue;
        if(worked[i] == maxShifts) continue;

        sched[currDay].push_back(i);
        worked[i]++;

        if(sched[currDay].size() == dailyNeed) {
            sched.emplace_back();
        } 

        if(helperSchedule(avail, dailyNeed, maxShifts, sched, worked)) {
            return true;
        }
        
        //undo all changes made if a valid schedule was not returned
        if(sched[currDay].size() == dailyNeed ) {
            sched.pop_back();
        }

        worked[i]--;
        sched[currDay].pop_back();
    }
    
    //if all possible solutions have been checked, no valid schedule exists
    return false;
}
