import axios from 'axios';

axios.defaults.headers.get['Content-Type'] = 'application/json';

const server = "https://script.google.com/macros/s/AKfycby_YZQHUYRO62Q2oKOEmMU5ypHoDemqHbphfTDzG1yo/dev?"

export const updateData = (param) => axios.get(server + param).then(res => res.message);
