import React, { useState, useEffect } from "react";

function ListBlocks( {blocks, compare, sorted, swap}) {
    const [width, setWidth] = useState(Math.min(20, Math.ceil(window.innerWidth / blocks.length) - 5));
    const color = blocks.length <= 50 && width > 14 ? 'black' : 'transparent';

    useEffect(() => {
        const handleResize = () => {
            setWidth(Math.min(20, Math.ceil(window.innerWidth / blocks.length) - 8));
        };

        window.addEventListener('resize', handleResize);

        setWidth(Math.min(20, Math.ceil(window.innerWidth / blocks.length) - 8));
    }, [blocks.length]);
    
    return (
        <div className="listBlocks">
            {blocks.map((block, index) => {
                const height = block * 500 / blocks.length;
                let background = '#7ED5EA';

                if (compare && (index === compare[0] || index === compare[1])) {
                    background = '#fff461'; // compare color
                }

                if (swap && (index === swap[0] || index === swap[1])) {
                    background = '#ff9f9f'; // swap color
                }
                if (sorted && sorted.includes(index)) {
                    background = '#9fff9f'; // sorted color
                }

                const style = {
                    'backgroundColor': background,
                    'color': color, 
                    'height': height, 
                    'width': width
                }
                return (<div key={index} className='block' style={style}>{block}</div>)
            })}
        </div>
    )   
}

export default ListBlocks;