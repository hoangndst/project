import './App.css';
import DevicesControl from './components/DevicesControl';
import * as React from 'react';
import { Paper } from '@mui/material';
function App() {

  return (
    <div className="App">
      <header className="App-header">
        <Paper
          sx={{
            // p: 2,
            minWidth: '100%',
            flexGrow: 1,
            backgroundColor: (theme) =>
              theme.palette.mode === 'dark' ? '#1A2027' : '#fff',
          }}
        >
          <DevicesControl />
        </Paper>
      </header>
    </div>
  );
}

export default App;
