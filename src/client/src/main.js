import Vue from 'vue'
import Vuetify from 'vuetify'
import 'vuetify/src/stylus/app.styl'
import '@mdi/font/css/materialdesignicons.css'
import colors from 'vuetify/es5/util/colors'
//
import App from './App.vue'


import VueRouter from 'vue-router'
import router from './router'
import store from './store'
import VueSocketIO from 'vue-socket.io';
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

Vue.use(new VueSocketIO({
    // debug: true,
    connection: `http://${env.ipAddress}:5000`,
    vuex: {
          store,
          actionPrefix: "SOCKET_",
          mutationPrefix: "SOCKET_"
        },
}))

Vue.use(Vuetify, {
  iconfont: 'md' || 'mdi',
  // theme: {
  //   primary: "#ff0000",
  //   secondary: "#ffce00",
  //   accent: "#029900",
  // },
  theme:{
    primary: colors.cyan,
    accent: colors.teal.accent2,
    secondary: colors.lime.accent1,
  }
})


Vue.config.productionTip = false


new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
