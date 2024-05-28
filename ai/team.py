CAPACITY = 10
FLOORS_TOTAL = 5 #total number of FLOORS_TOTAL

#WORLD OF PROBLEM:elevator capacity, floors, residents
#CONSTRAINTS:
#1.The elevator has maximum capacity of 10
#2.The total number of FLOORS_TOTAL is 5
#3.In the beginning the elevator is empty in floor 0
#4.Each floor has a specific number of residents in the beginning

# function to point where the elevator goes next
def go_to_floor(state, floor):
    # if the elevator position  is less than its capacity and the elevator
    # is not on the ground then the new state enters the list of states
    if floor == 0:
        new_state = list(state).copy()
        new_state[0] = 0
        new_state[FLOORS_TOTAL] = 0
        return tuple(new_state)
    if state[FLOORS_TOTAL] < CAPACITY and state[floor] > 0:
        new_state = list(state).copy()
        if state[floor] > CAPACITY - state[FLOORS_TOTAL]:
            # we exclude the last floor
            new_state[floor] = state[floor] + state[FLOORS_TOTAL] - CAPACITY
            new_state[0] = floor
            new_state[FLOORS_TOTAL] = CAPACITY
        else:
            new_state[floor] = 0
            new_state[0] = floor
            new_state[FLOORS_TOTAL] = state[floor] + state[FLOORS_TOTAL]
        return tuple(new_state)
    else:
        return None

# state:    ( elevator position={0,1,2,3,4}, floor1, floor2, floor3, floor4, elevator )
# initial:  ( 0, 12, 3, 7, 8, 0 )
# final:    ( 0, 0, 0, 0, 0, 0 )
def bfs(initial_state, final_state):
    visited = {}
    frontier = [initial_state]

    while len(frontier) > 0:
        # print(frontier)
        state = frontier.pop(0)
        print(state)
        # if the elevator has reached the final state all previously visited
        # states are printed
        if state == final_state:
            print(f"\n\nBFS: states visited = {len(visited)}")
            return final_state
        visited[state] = 1
        #the state must be immutable in order to become key to the dict
        # print(state)

        # anakalypsh paidiwn
        current_floor = state[0]
        current_capacity = state[-1]

        if current_capacity == CAPACITY or current_floor == FLOORS_TOTAL - 1:
            new_state = go_to_floor(state, 0)
            #putting the new state to the frontier
            if new_state not in visited:
                frontier.append(new_state)
            continue

        return_to_0 = True

        for floor in range(1, FLOORS_TOTAL):
            # in case the elevator is over the ground and the floor
            # (in frontier) is over the current position of the elevator go up
            if floor <= current_floor:
                continue
            # in case the floor (in frontier) is not the last and the elevator
            # position is on the ground  go up
            elif floor < FLOORS_TOTAL - 1 and state[floor] == 0:
                continue
            # in case the last floor is visited,the next floor in frontier is 4 and
            # the elevator is not in 0 the new state is added to the list
            elif (floor == FLOORS_TOTAL - 1 and state[FLOORS_TOTAL - 1] == 0 and current_floor != 0 and return_to_0):
                new_state = go_to_floor(state, 0)
            # in case the elevator carries less than 10 people and the next floor
            # in frontier  is over the current floor the elevator goes up
            elif current_capacity < CAPACITY and floor > current_floor:
                return_to_0 = False 
                new_state = go_to_floor(state, floor)
                if new_state is None:
                    continue
            # in case there is no new state continue
            else:
                continue

            # BFS: bazw paidia (new states) sto TELOS tou frontier
            if new_state not in visited:
                frontier.append(new_state)
    return None

def heuristic(state):
    return sum(state)

def bestfs(initial_state, final_state):
    visited = {}
    state = initial_state

    while state != final_state:
        print(state)
        # initialize available states
        avail_states = []
        current_floor = state[0]
        current_capacity = state[-1]

        # test all states
        for floor in range(1, FLOORS_TOTAL):
            if floor == current_floor:
                continue
            new_state = go_to_floor(state, floor)
            if new_state == None:
                continue
            # only add states not already visited
            if new_state not in visited:
                avail_states.append(new_state)
                # mark state as visited
                visited[new_state] = 1

        # sort combinations according to heuristic value
        avail_states.sort(key=heuristic)

        if avail_states:
            # get best path
            state = avail_states.pop(0)
            avail_states.clear()

        if current_capacity == CAPACITY or current_floor == FLOORS_TOTAL - 1:
            state = go_to_floor(state, 0)
    
    print(f"\n\nBestFS: states visited: {len(visited)}")
    return final_state 

def main():
    initial = (0, 12, 3, 7, 8, 0)
    final = (0, 0, 0, 0, 0, 0)
    method = "BestFS"

    if method == "BFS":
        state = bfs(initial, final)
    elif method == "BestFS":
        state = bestfs(initial, final)
    print(state)

if __name__ == "__main__":
    main()
