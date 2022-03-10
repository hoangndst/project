import { Grid, Paper, Alert, Typography, FormControlLabel, Skeleton, Button } from '@mui/material'
import Switch from '@mui/material/Switch';
import { styled } from '@mui/material/styles'
import React from 'react'
import { useEffect } from 'react';
import { DatePicker } from '@mui/lab';
import AdapterDateFns from '@mui/lab/AdapterDateFns';
import LocalizationProvider from '@mui/lab/LocalizationProvider';
import CalendarPicker from '@mui/lab/CalendarPicker';
import { getDht11Data } from '../controller/action';
import { Line } from 'react-chartjs-2';
import Chart from 'chart.js/auto'

const Android12Switch = styled(Switch)(({ theme }) => ({
    padding: 8,
    '& .MuiSwitch-track': {
      borderRadius: 22 / 2,
      '&:before, &:after': {
        content: '""',
        position: 'absolute',
        top: '50%',
        transform: 'translateY(-50%)',
        width: 16,
        height: 16,
      },
      '&:before': {
        backgroundImage: `url('data:image/svg+xml;utf8,<svg xmlns="http://www.w3.org/2000/svg" height="16" width="16" viewBox="0 0 24 24"><path fill="${encodeURIComponent(
          theme.palette.getContrastText(theme.palette.primary.main),
        )}" d="M21,7L9,19L3.5,13.5L4.91,12.09L9,16.17L19.59,5.59L21,7Z"/></svg>')`,
        left: 12,
      },
      '&:after': {
        backgroundImage: `url('data:image/svg+xml;utf8,<svg xmlns="http://www.w3.org/2000/svg" height="16" width="16" viewBox="0 0 24 24"><path fill="${encodeURIComponent(
          theme.palette.getContrastText(theme.palette.primary.main),
        )}" d="M19,13H5V11H19V13Z" /></svg>')`,
        right: 12,
      },
    },
    '& .MuiSwitch-thumb': {
      boxShadow: 'none',
      width: 16,
      height: 16,
      margin: 2,
    },
}));

const Item = styled(Paper)(({ theme }) => ({
    backgroundColor: theme.palette.mode === 'dark' ? '#1A2027' : '#fff',
    ...theme.typography.body2,
    padding: theme.spacing(1),
    textAlign: 'center',
    color: theme.palette.text.secondary,
}));


export default function Information() {

    const [data, setData] = React.useState([]);
    const [date, setDate] = React.useState(new Date());

    const [chartData, setChartData] = React.useState({
        labels: data.map(item => item.time),
        datasets: [
            {
                label: "Temperature",
                data: data.map(item => item.temperature),
                backgroundColor: [
                  "rgba(75,192,192,1)",
                  "#ecf0f1",
                  "#50AF95",
                  "#f3ba2f",
                  "#2a71d0",
                ],
                borderColor: "black",
                borderWidth: 2,
            },

            {
                label: "Humidity",
                data: data.map(item => item.humidity),
                backgroundColor: [
                  "rgba(75,192,192,1)",
                  "#ecf0f1",
                  "#50AF95",
                  "#f3ba2f",
                  "#2a71d0",
                ],
                borderColor: "black",
                borderWidth: 2,
            },


        ],
    });

    useEffect(() => {
        const interval = setInterval(() => {
            getDht11Data().then(res => {
                let tmp = {
                    time: new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' }),
                    temperature: res[0].temp,
                    humidity: res[0].humd
                }
                if (data.length >= 10) {
                    data.shift();
                }
                let newData = data;
                newData.push(tmp);
                setData(newData);
                setChartData({
                    labels: data.map(item => item.time),
                    datasets: [
                        {
                            label: "Temperature",
                            data: data.map(item => item.temperature),
                            backgroundColor: [
                            //   "rgba(75,192,192,1)",
                              "#ecf0f1",
                            //   "#50AF95",
                            //   "#f3ba2f",
                            //   "#2a71d0",
                            ],
                            borderColor: "black",
                            borderWidth: 2,
                        },

                        {
                            label: "Humidity",
                            data: data.map(item => item.humidity),
                            backgroundColor: [
                            //   "rgba(75,192,192,1)",
                              "#ecf0f1",
                            //   "#50AF95",
                            //   "#f3ba2f",
                            //   "#2a71d0",
                            ],
                            borderColor: "#3e95cd",
                            borderWidth: 2,
                        },
                    ],
                });
            })
        }, 2000);
        return () => clearInterval(interval);
    }, []);

  return (
    <div style={ { width: '100%', margin: '0 auto', height: '100%' } }>

        <Alert
            style={{ marginBottom: '10px', fontWeight: 'bold' }}
            severity="info">
            It's beta, don't expect too much!
        </Alert>
        <Paper
            sx={{
                p: 1,
                marginBottom: '10px',
                maxWidth: '100%',
                flexGrow: 1,
                backgroundColor: (theme) =>
                theme.palette.mode === 'dark' ? '#1A2027' : '#fff',
            }}
        >
            <Typography sx={{ fontSize: 20, fontWeight: 1000 }} color="text.first" gutterBottom>
                DHT11 Sensor Data
            </Typography>
            <Grid container spacing={2}>
                <Grid item xs={12} md={12}>
                    <Item>
                        <Line data={chartData} />
                    </Item>
                </Grid>
            </Grid>
            <Grid container spacing={2} marginTop={'5px'}>
                <Grid item xs={6} md={6}>
                    <Item>
                        Temperature: {data[data.length - 1] ? data[data.length - 1].temperature : '-'}
                    </Item>
                </Grid>
                <Grid item xs={6} md={6}>
                    <Item>
                        Humidity: {data[data.length - 1] ? data[data.length - 1].humidity : '-'} %
                    </Item>
                </Grid>
            </Grid>
        </Paper>

        <Paper
            sx={{
                p: 1,
                marginBottom: '10px',
                maxWidth: '100%',
                flexGrow: 1,
                backgroundColor: (theme) =>
                theme.palette.mode === 'dark' ? '#1A2027' : '#fff',
            }}
        >
            <Typography sx={{ fontSize: 20, fontWeight: 1000 }} color="text.first" gutterBottom>
                CALENDER
            </Typography>
            <Grid container spacing={2}>
                <Grid item xs={12} md={12}>
                    <LocalizationProvider dateAdapter={AdapterDateFns}>
                        <Item>
                            <CalendarPicker date={date} onChange={(newDate) => setDate(newDate)} />
                        </Item>
                    </LocalizationProvider>
                    
                </Grid>
            </Grid>
        </Paper>
        
    </div>
  )
}
