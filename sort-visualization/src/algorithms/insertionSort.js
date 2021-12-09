const swap = (arr, i, j) => {
    const temp = arr[i]
    arr[i] = arr[j]
    arr[j] = temp
}

const insertionSort = (block) => {
    const dup = block.slice();
    const order = [];

    let i = 0;
    let j;

    for (; i < dup.length; i++) {
        j = i - 1;
        while (j >= 0 && dup[j] > dup[j + 1]) {
            swap(dup, j, j + 1);
            order.push([j, j + 1, null, null]); // compare
            order.push([j, j + 1, dup.slice(), null]); // swap
            j--;
        }
    }

    for (i = 0; i < dup.length; i++) {
        order.push([null, null, null, i]);
    }

    return order;
}

export default insertionSort;