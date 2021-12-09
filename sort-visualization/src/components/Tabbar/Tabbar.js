import React from "react";
import './Tabbar.css'

const Tabbar = ( {handleLength, handleSpeed, handleAlgo, generateRandomArray, handleSort, sorting, completed, len, speed, algo}) => {
    return (
        <nav>
            <div className="name">Sorting Visualization</div>
            <div className="options">
                <div className='group speed'>
                    <label>Speed</label>
                    <input type='range' onChange={handleSpeed} min='1' max='10' value={Math.ceil(400 / speed)} disabled={sorting}></input>
                </div>

                <div className='group length'>
                    <label>Length</label>
                    <input type='range' onChange={handleLength} min='5' max={30} step='1' disabled={sorting} value={len}></input>
                </div>
                <select onChange={handleAlgo} disabled={sorting} value={algo}>
                    <option value="bubble">Bubble Sort</option>
                    <option value="selection">Selection Sort</option>
                    <option value="insertion">Insertion Sort</option>
                </select>
                <div>
                    <button onClick={generateRandomArray} disabled={sorting}>Generate Random Array</button>
                    <button onClick={handleSort} disabled={sorting || completed}>Sort</button>
                </div>

            </div>
        </nav>
    )
}

export default Tabbar;