import { Grid, Dialog, Chip, Stack, Avatar, ListItem, DialogTitle, DialogActions, DialogContentText, DialogContent, Paper, Alert, Typography, FormControlLabel, Checkbox, Button, FormControl, OutlinedInput, Select, MenuItem, FormGroup, InputAdornment } from '@mui/material'
import Switch from '@mui/material/Switch';
import { styled } from '@mui/material/styles'
import React from 'react'
import { useEffect } from 'react';
import AddTaskIcon from '@mui/icons-material/AddTask';
import FaceIcon from '@mui/icons-material/Face';
import List from '@mui/material/List';
import Card from '@mui/material/Card';
import CardHeader from '@mui/material/CardHeader';
import ListItemText from '@mui/material/ListItemText';
import ListItemIcon from '@mui/material/ListItemIcon';
import Divider from '@mui/material/Divider';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemAvatar from '@mui/material/ListItemAvatar';
import { updateData } from '../api/ApiServer';
const Item = styled(Paper)(({ theme }) => ({
    backgroundColor: theme.palette.mode === 'dark' ? '#1A2027' : '#fff',
    ...theme.typography.body2,
    padding: theme.spacing(1),
    textAlign: 'center',
    color: theme.palette.text.secondary,
}));

export default function ToDo() {

  const members = ['Hoàng', 'Hiên', 'Hiếu', 'Hưng', 'Tiến'];
  const [memPay, setMemPay] = React.useState('');
  const [listMemEat, setListMemEat] = React.useState([]);
  const [todayMoney, setTodayMoney] = React.useState();
 

  const [open, setOpen] = React.useState(false);

  const handleClickOpen = () => {
    var param = "todayMoney=" + todayMoney + "&";
    for (var i = 0; i < listMemEat.length; i++) {
      param += "l=" + listMemEat[i] + "&";
    }
    param += "memPay=" + memPay;
    updateData(param).then(res => {
      console.log(res);
    });
    setOpen(true);
  };

  const handleClose = () => {
    setOpen(false);
  };


  const handleMemPay = (event) => {
    setMemPay(event.target.value);
  };

  const handleMoneyInput = (event) => {
    setTodayMoney(event.target.value);
    console.log(todayMoney);
  };


  const handleToggle = (value) => () => {
    const currentIndex = listMemEat.indexOf(value);
    const newListMemEat = [...listMemEat];

    if (currentIndex === -1) {
      newListMemEat.push(value);
    } else {
      newListMemEat.splice(currentIndex, 1);
    }

    setListMemEat(newListMemEat);

  };

  return (
    <div style={ { width: '100%', margin: '0 auto' } }>
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
            <Item>
              <Typography sx={{ fontSize: 20, fontWeight: 1000 }} color="text.first" gutterBottom>
                  510GANGZ - TO PAY
              </Typography>
            </Item>
            <Grid container spacing={1} marginTop={1}>
              <Grid item xs={12} md={12}>
                  <Typography sx={{ fontSize: 15, fontWeight: 1000 }} color="text.first" gutterBottom>
                    Participants List
                  </Typography>

                  <List dense sx={{ width: '25ch', bgcolor: 'background.paper', margin: '0 auto' }}>
                    {members.map((value) => {
                      const labelId = `checkbox-list-secondary-label-${value}`;
                      return (
                        <ListItem
                          key={value}
                          secondaryAction={
                            <Checkbox
                              edge="end"
                              onChange={handleToggle(value)}
                              checked={listMemEat.indexOf(value) !== -1}
                              inputProps={{ 'aria-labelledby': labelId }}
                            />
                          }
                          disablePadding
                        >
                          <ListItemButton>
                            <ListItemAvatar>
                              <Avatar
                                alt={`Avatar n°${value + 1}`}
                                // src={`%PUBLIC_URL%/img/avatar/${members.indexOf(value) + 1}.png`}
                              />
                            </ListItemAvatar>
                            <ListItemText id={labelId} primary={`${value}`} />
                          </ListItemButton>
                        </ListItem>
                      );
                    })}
                  </List>

              </Grid>
              <Grid item xs={12} md={12}>
                <Typography sx={{ fontSize: 15, fontWeight: 1000 }} color="text.first" gutterBottom>
                    Payer
                </Typography>
                <FormControl  sx={{ m: 1, width: '25ch' }}>
                    <Select
                    displayEmpty
                    inputProps={{ 'aria-label': 'Without label' }}
                    value={memPay}
                    onChange={handleMemPay}
                    >
                      <MenuItem value="">
                        <em>None</em>
                      </MenuItem>
                      <MenuItem value={"Hoàng"}>Hoàng</MenuItem>
                      <MenuItem value={"Hiên"}>Hiên</MenuItem>
                      <MenuItem value={"Hiếu"}>Hiếu</MenuItem>
                      <MenuItem value={"Hưng"}>Hưng</MenuItem>
                      <MenuItem value={"Tiến"}>Tiến</MenuItem>
                    </Select>
                </FormControl>
              </Grid>
              <Grid item xs={12} md={12}>
                <Typography sx={{ fontSize: 15, fontWeight: 1000 }} color="text.first" gutterBottom>
                  Amount
                </Typography>
                <FormControl sx={{ m: 1, width: '25ch' }} variant="outlined">
                  <OutlinedInput
                    type='number'
                    id="outlined-adornment-weight"
                    value={todayMoney}
                    endAdornment={<InputAdornment position="end">VND</InputAdornment>}
                    aria-describedby="outlined-weight-helper-text"
                    inputProps={{
                      'aria-label': 'weight',
                    }}
                    onChange={handleMoneyInput}
                  />
                </FormControl>
              </Grid>
              <Grid item xs={12} md={12}>
                <Button variant="contained" startIcon={<AddTaskIcon />} onClick={handleClickOpen} >
                  ADD TO TODAY LIST
                </Button>
                <Dialog
                  open={open}
                  onClose={handleClose}
                  aria-labelledby="alert-dialog-title"
                  aria-describedby="alert-dialog-description"
                >
                  <DialogTitle id="alert-dialog-title">
                    {"Notification from 510Gangz"}
                  </DialogTitle>
                  <DialogContent>
                    <DialogContentText id="alert-dialog-description">
                      Update Successfully!
                    </DialogContentText>
                  </DialogContent>
                  <DialogActions>
                    <Button onClick={handleClose} autoFocus>
                      OK
                    </Button>
                  </DialogActions>
                </Dialog>
              </Grid>
            </Grid> 
        </Paper>
    </div>
  )
}
