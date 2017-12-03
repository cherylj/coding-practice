// https://www.hackerrank.com/challenges/torque-and-development/problem

process.stdin.resume();
process.stdin.setEncoding('ascii');

var input_stdin = "";
var input_stdin_array = "";
var input_currentline = 0;

process.stdin.on('data', function (data) {
    input_stdin += data;
});

process.stdin.on('end', function () {
    input_stdin_array = input_stdin.split("\n");
    main();
});

function readLine() {
    return input_stdin_array[input_currentline++];
}

/////////////// ignore above this line ////////////////////

/* When calculating the lowest cost option, there are two scenarios:
 * 1 - The cost of building a library is equal to or less than the
 *     cost of repairing a road.
 * 2 - The cost of repairing a road is less than the cost of building
 *     a library.
 *
 * For the first case, we should just build a library in every city.
 *
 * For the second case, we need to determine how many "islands" there are.
 * An "island" is a group of one or more cities that are connected.  islands
 * are not connected to eachother:
 *
 *  1 -- 2           5 -- 6      10      11
 *       |           |           |
 *       3 -- 4      7 -- 8      9
 *
 * In the above example, there are four "islands" (or sets):
 * (1, 2, 3, 4), (5, 6, 7, 8), (9, 10), (11)
 *
 * We will create an object for each city we encounter that contains:
 * 1 - its name (Index, used for logging)
 * 2 - whether or not it's been already visited
 * 3 - a list of cities it has a direct connection to.
 * If we never encounter one of the cities, its entry in the cityArray will
 * be undefined.
 *
 * To find all the sets, we will use graph traversal.  We will iterate through the
 * array of cities:
 *  - If the city has not yet been visited by the traversal, push it onto the stack.
 *  - While the stack is not empty:
 *    - Pop off the first element from the stack
 *    - Mark the element as visited
 *    - For each of the connected cities:
 *        - If the city has not been visited, push it onto the stack.
 *
 * Every time we encounter an element on the cityArray that has not been visited,
 * we increment the number of sets.  If we encounter an element in the cityArray
 * that is undefined, we also increment the number of sets, because this means it
 * is an island itself.
 *
 * The cost calculation puts a library in each island, then counts the number of
 * roads to connect each city within the island.
 *
 * The number of roads to connect the cities within the island is N - 1, where N is
 * the number of cities in the island.
 *
 * I cheat and don't count the number of elements in each set / island.  I know
 * that the number of roads will be:
 *    (total # of cities - 1) - (number of sets - 1)
 * This is true because we can imagine that all the cities are connected (which is
 * where the (total # of cities - 1) comes from), then to create the islands, we
 * remove (number of sets - 1) roads.
 */

const calculateCost = (cityArray, costRoad, costLibrary) => {
    let stack = [];
    let sets = 0;

    for (let i = 0; i < cityArray.length; i++) {
        if (!cityArray[i]) {
            // This city had no roads to another city.  It is its own set.
            sets++;
            continue;
        }
        if (cityArray[i].visited) {
            // Already included in a previous set.  Don't count it.
            continue;
        }

        // Unvisited city, push it into the stack and start traversing its roads.
        stack.push(cityArray[i]);
        sets++;
        while(stack.length != 0) {
            const element = stack.pop()
            //console.log(`visiting: ${element.name}`);
            for (let j = 0; j < element.connectedCities.length; j++) {
                // Push the linked city if it has not yet been visited.
                if (!cityArray[element.connectedCities[j]].visited) {
                    stack.push(cityArray[element.connectedCities[j]]);
                    /* Also mark the connected city as visited so other
                     * cities don't also add it to the stack.
                     */
                    cityArray[element.connectedCities[j]].visited = true;
                }
            }
            element.visited = true;
        }
    }
    //console.log(`Found ${sets} sets in the dataset.`);
    const numRoads = (cityArray.length - 1) - (sets - 1);
    //console.log(`Number of roads: ${numRoads}`);
    console.log((numRoads * costRoad) + (sets * costLibrary));
};

function main() {
    var q = parseInt(readLine());

    for(var a0 = 0; a0 < q; a0++){
        var n_temp = readLine().split(' ');
        var numCities = parseInt(n_temp[0]);
        var numRoads = parseInt(n_temp[1]);
        var costLibrary = parseInt(n_temp[2]);
        var costRoad = parseInt(n_temp[3]);

        /* If the cost of building a library is <= the cost of building roads,
         * the min cost is just building a library in each city.  Read in the
         * roads, but don't allocate the city array (to save some space)
         */
        let cityArray = undefined;
        if (costRoad < costLibrary) {
            cityArray = Array(numCities);
        }

        for(var a1 = 0; a1 < numRoads; a1++){
            var city_1_temp = readLine().split(' ');
            var city_1 = parseInt(city_1_temp[0]);
            var city_2 = parseInt(city_1_temp[1]);

            // Adjust to be zero indexed.
            city_1--;
            city_2--;

            if (cityArray) {
                if (cityArray[city_1]) {
                    cityArray[city_1].connectedCities.push(city_2);
                } else {
                    cityArray[city_1] = {
                        name: city_1,
                        visited: false,
                        connectedCities: [city_2]
                    };
                }
                if (cityArray[city_2]) {
                    cityArray[city_2].connectedCities.push(city_1);
                } else {
                    cityArray[city_2] = {
                        name: city_2,
                        visited: false,
                        connectedCities: [city_1]
                    };
                }
            }
        }

        if (cityArray) {
            calculateCost(cityArray, costRoad, costLibrary);
        } else {
            //console.log(`Cheaper to build a library in each city.  Total cost: ${numCities * costLibrary}`);
            console.log(numCities * costLibrary);
        }
    }
}
