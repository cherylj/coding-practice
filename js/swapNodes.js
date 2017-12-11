// Author:  Cheryl Jennings
// From https://www.hackerrank.com/challenges/swap-nodes-algo/problem

function Node(value) {
    this.value = value;
    this.left =  undefined;
    this.right = undefined;
}

function findNode(tree, value) {
    if (!tree) {
        return undefined;
    }

    if (tree.value ===  value) {
        return tree;
    }

    const found = findNode(tree.left, value);
    if (found) {
        return found;
    }

    return findNode(tree.right, value);
}

function printTree(tree) {
    if (!tree) {
        return '';
    }

    let str = '';
    if (tree.left) {
        str += printTree(tree.left) + ' ';
    }

    str += tree.value;

    if (tree.right) {
        str += ' ' + printTree(tree.right);
    }
    return str;
}

function swapNodes(tree, level, constant) {
    if (!tree) {
        return;
    }

    if (level % constant === 0) {
        const tmp = tree.left;
        tree.left = tree.right;
        tree.right = tmp;
    }

    swapNodes(tree.left, level + 1, constant);
    swapNodes(tree.right, level + 1, constant);
}

function processData(input) {
    const lines = input.split('\n');
    if (lines.length < 1) {
        console.log('not enough lines!');
        return;
    }
    let i;
    let head = new Node(1);

    const numNodes = parseInt(lines[0]);
    for (i = 1; i <= numNodes; i++) {
        const nums = lines[i].split(' ');
        if (nums.length != 2) {
            throw 'Wrong input format: ' + lines[i];
        }

        if (nums[0] == -1 && nums[1] == -1) {
            continue;
        }

        const node = findNode(head, i);
        if (!node) {
            throw 'Node not found! ' + i;
        }

        if(nums[0] != -1) {
            node.left = new Node(parseInt(nums[0]));
        }

        if (nums[1] != -1) {
            node.right = new Node(parseInt(nums[1]));
        }
    }

    const numSwaps = parseInt(lines[i]);
    // console.log(`numSwaps is: ${numSwaps}`);
    for (let j = 1; j <= numSwaps; j++) {
        // console.log(`swapping for constant: ${parseInt(lines[i + j])}`);
        swapNodes(head, 1, parseInt(lines[i + j]));
        console.log(printTree(head));
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
