// Author:  Cheryl Jennings
// From: https://www.hackerrank.com/challenges/icecream-parlor/problem

function processData(input) {
    inputs = input.split('\n');

    const iterations = inputs[0];

    for (let i = 0; i < iterations; i++) {
        const amount = parseInt(inputs[(i * 3) + 1]);
        const numFlavors = parseInt(inputs[(i * 3) + 2]);
        const flavors = inputs[(i * 3) + 3].split(' ');

        let flavorInts = [];
        for (let j = 0; j < numFlavors; j++) {
            flavorInts.push(parseInt(flavors[j]));
        }
        findMatch(amount, flavorInts);
    }
}

function findMatch(target, values) {
    for (let i = 0; i < (values.length - 1); i++) {
        if (values[i] >= target) {
            continue;
        }
        for (let j = (i + 1); j < values.length; j++) {
            if (values[i] + values[j] === target) {
                console.log(`${i + 1} ${j + 1}`);
                return;
            }
        }
    }
}

process.stdin.resume();
process.stdin.setEncoding("ascii");
_input = "";
process.stdin.on("data", function (input) {
    _input += input;
});

process.stdin.on("end", function () {
   processData(_input);
});
