import React from 'react';
import './Info.css'

const Info = () => {
    return (
        <div className='info'>
            <div className='key'>
                <span className='block compare'></span>Compare
            </div>
            <div className='key'>
                <span className='block swap'></span>Swap
            </div>
            <div className='key'>
                <span className='block sorted'></span>Sorted
            </div>
        </div>
    );
}

export default Info;