const axios = require('axios')
const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000; 


app.use(bodyParser.json());

let isLedOn = false;

const arduinoURL = 'http://<ip given by esp8266>/'


app.get('/led/status', (req, res) => {
  res.json({ status: isLedOn });
});

app.post('/led', (req, res) => {
  const { action } = req.body; 
  if (action === 'on') {
    isLedOn = true;
    
    console.log('LED turned on');
  } else if (action === 'off') {
    isLedOn = false;
    
    console.log('LED turned off');
  }
  const ledBody = {
    state: isLedOn
  }
  axios.post(arduinoURL + "led", ledBody)
    .then(response => {
      console.log(response.data)
    })
    .catch(error => {
      console.error(error.message);
    })
  res.json({ status: isLedOn });
});


app.get('/temperature', (req, res) => {
  axios.get(arduinoURL + 'temperature')
    .then(response => {
      res.json( response.data );
    })
    .catch(error => {
      console.error(error.message);
      res.status(500).json({ error: 'Failed to retrieve temperature data' });
    });
});

app.get('/humidity', (req, res) => {
  axios.get(arduinoURL + 'humidity')
    .then(response => {
      res.json( response.data );
    })
    .catch(error => {
      console.error(error.message);
      res.status(500).json({ error: 'Failed to retrieve humidity data' });
    });
});



app.listen(port, () => {
  console.log(`Server is listening at http://localhost:${port}`);
});
