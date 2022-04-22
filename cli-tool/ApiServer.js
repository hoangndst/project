import axios from 'axios';

// axios.defaults.headers.get['Content-Type'] = 'application/json';

const server = "https://script.google.com/macros/s/AKfycbxZgjsM7yM1och7yOLzdo9QqNEcwfS8x7lFCXiyFMB4ByYmmyeBOJiSz7B8m3nCXeJJ/exec?";

export const updateData = (param) => axios.post(server + param).then(res => res.data.message);

export const getData = (param) => axios.get(server + param).then(res => res.data);
