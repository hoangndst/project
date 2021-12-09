const swap = (arr, i, j) => {
    const temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


const selectionSort = (blocks) => {
    const dup = blocks.slice();
    const order = [];
    for (let i = 0; i < dup.length; i++) {
        for (let j = i + 1; j < dup.length; j++) {
            order.push([i, j, null, null]);
            if (dup[i] > dup[j]) {
                swap(dup, i, j);
                order.push([i, j, dup.slice(), null]);
            }
        }
        order.push([null, null, null, i])
    }
    return order;
}

export default selectionSort;