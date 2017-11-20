// Author:  Cheryl Jennings
// From: https://www.hackerrank.com/challenges/array-left-rotation/problem

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

function leftRotation(a, d) {
    /* We can cheat and not actually move any numbers around in the array.
     * We will treat the array like a circular buffer, keeping track of
     * the "head".  During the iterations, if we walk off the end of the
     * array, just start back at the beginning.
     */
     let arr = [];
     let count = 0;
     for (let i = d; count < a.length; count++, i++) {
         if (i >= a.length) {
             i = 0;
         }
         arr.push(a[i]);
     }
     return arr;
}

function main() {
    var n_temp = readLine().split(' ');
    var n = parseInt(n_temp[0]);
    var d = parseInt(n_temp[1]);
    a = readLine().split(' ');
    a = a.map(Number);
    var result = leftRotation(a, d);
    console.log(result.join(" "));



}
