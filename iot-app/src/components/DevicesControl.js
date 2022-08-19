import { Grid, Paper, Alert, Box, Container } from '@mui/material'
import { styled } from '@mui/material/styles'
import React from 'react'
import ReactPlayer from 'react-player/lazy'

const Item = styled(Paper)(({ theme }) => ({
  backgroundColor: theme.palette.mode === 'dark' ? '#1A2027' : '#fff',
  ...theme.typography.body2,
  padding: theme.spacing(1),
  textAlign: 'center',
  color: theme.palette.text.secondary,
}));


export default function DevicesControl() {

  return (
    <Box sx={{ width: '100%', minHeight: '100vh', margin: '0px auto' }}>
      <Container>
        <Box
          sx={{
            maxWidth: '500px',
            margin: '0 auto',
            marginBottom: '20px',
          }}
        >
          <Alert
            sx={{
              fontWeight: 'bold',
              marginTop: '20px',
            }}
            severity="warning"
          >
            Its beta, don't expect too much!
          </Alert>
        </Box>
        <Paper
          sx={{
            p: 1,
            maxWidth: '690px',
            margin: '0 auto',
            marginBottom: '20px',
            flexGrow: 1,
            backgroundColor: (theme) =>
              theme.palette.mode === 'dark' ? '#1A2027' : '#fff',
          }}
        >
          <Grid container spacing={2}>
            <Grid item xs={12} md={12}>
              <Item>
                <ReactPlayer
                  url={'http://localhost:4000/index.m3u8'}
                  controls={true}
                />
              </Item>
            </Grid>
          </Grid>
        </Paper>
      </Container>
    </Box>
  )
}
