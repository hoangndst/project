import React, { useState, useEffect } from 'react';
import logo from './logo.svg';
import './App.css';
import Info from './components/Info/Info';
import Tabbar from './components/Tabbar/Tabbar';
import ListBlocks from './components/Blocks/ListBlocks';
import bubbleSort from './algorithms/bubbleSort';
import insertionSort from './algorithms/insertionSort';
import selectionSort from './algorithms/selectionSort';

function App() {

    const [algo, setAlgo] = useState('bubble')
    const [len, setLength] = useState(30)
    const [blocks, setBlocks] = useState([])
    const [sorting, setSorting] = useState(false)
    const [completed, setCompleted] = useState(true)
    const [speed, setSpeed] = useState(400)
    const [compare, setCompare] = useState([])
    const [swap, setSwap] = useState([])
    const [sortedIndex, setSortedIndex] = useState([])

    const generateRandomArray = (len) => {
		setCompleted(false)
		setSorting(false)
		setSortedIndex([])

		const randomArray = Array.from(Array(len + 1).keys()).slice(1)
		
		for (let i = randomArray.length - 1; i > 0; i--) {
			const randomIndex = Math.floor(Math.random() * (i - 1))
			const temp = randomArray[i]
			randomArray[i] = randomArray[randomIndex]
			randomArray[randomIndex] = temp
		}
		setBlocks(randomArray)
	}

    useEffect(() => {
        generateRandomArray(len)
    }, [len, algo])


    const handleAlgo = (event) => {
        setAlgo(event.target.value)
    }

    const handleLength = (event) => {
        setLength(Number(event.target.value))
    }

    const handleSpeed = (event) => {
        setSpeed(Math.ceil(400 / Number(event.target.value)));
    }

    const handleSort = () => {
        const sortOrder = (order) => {
            (function loop(i) {
                setTimeout(() => {
                    const [a, b, arr, index] = order[i];
                    setCompare([a, b]);
                    setSwap([]);
                    if (index !== null) {
                        setSortedIndex((prev) => {
                            return [...prev, index]
                        })
                    }

                    if (arr !== null) {
                        setBlocks(arr);
                        if (a !== null && b !== null) {
                            setSwap([a, b]);
                        }
                    }
                    if (i++ < order.length - 1) {
                        loop(i);
                    } else {
                        setSorting(false);
                        setCompleted(true);
                    }

                }, speed);
            })(0);
        }

        setSorting(true);
        if (algo === 'bubble') {
            sortOrder(bubbleSort(blocks));
        } else if (algo === 'insertion') {
            sortOrder(insertionSort(blocks));
        } else if (algo === 'selection') {
            sortOrder(selectionSort(blocks));
        }
    }

    return (
        <div className="App">
        <Tabbar 
            handleAlgo={handleAlgo} 
            handleLength={handleLength} 
            handleSort={handleSort} 
            handleSpeed={handleSpeed} 
            sorting={sorting}
            completed={completed}
            algo={algo}
            len={len}
            speed={speed}
            generateRandomArray={() => generateRandomArray(len)}
        />
        <Info />
        <ListBlocks 
			blocks={blocks} 
			compare={sorting && compare}
			swap={sorting && swap}
			sorted={sortedIndex} 
		/>
        </div>
    );
}

export default App;
