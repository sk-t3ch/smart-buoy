import Vue from 'vue'
import App from './App.vue'
import vuetify from './plugins/vuetify';


import VueRouter from 'vue-router'
import router from './router'
import store from './store'
import VueSocketIO from 'vue-socket.io';
import SocketIO from 'socket.io-client'

import VueGoogleCharts from 'vue-google-charts'
import * as VueGoogleMaps from 'vue2-google-maps'
const env = require("./env.json");

Vue.use(VueGoogleCharts)
Vue.use(VueRouter)


Vue.use(VueGoogleMaps, {
  load: {
    key: env.googleMapsKey,
    libraries: 'places',
  },
});


export let SocketInstance = SocketIO(null,{
  autoConnect: false,
  transports: ['polling'],
  host: '0.0.0.0',
  port: 5000
});

Vue.use(new VueSocketIO({
    debug: true,
    connection: SocketInstance,
    vuex: {
          store,
          actionPrefix: "SOCKET_",
          mutationPrefix: "SOCKET_"
        },
}))

Vue.config.productionTip = false

new Vue({
  vuetify,
  router,
  store,
  render: h => h(App)
}).$mount('#app')
