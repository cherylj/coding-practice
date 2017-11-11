// From: https://www.hackerrank.com/challenges/cut-the-sticks/problem
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

function main() {
    var n = parseInt(readLine());
    arr = readLine().split(' ');
    arr = arr.map(Number);
    let smallest = arr.reduce((sm, cur) => {
        if (cur < sm) {
            return cur;
        }
        return sm;
    });

    while (arr.length > 0) {
        console.log(arr.length);
        let newSmallest = 1000;

        let newArr = [];
        for (let i = 0; i < arr.length; i++) {
            const newVal = arr[i] - smallest;
            if (newVal > 0) {
                newArr.push(newVal);
                if (newVal < newSmallest) {
                    newSmallest = newVal;
                }
            }
        }
        arr = newArr;
        smallest = newSmallest;
    }
}
