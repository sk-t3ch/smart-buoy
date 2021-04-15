import Vue from 'vue';
import Vuetify from 'vuetify/lib/framework';
import colors from 'vuetify/lib/util/colors'
// import '@mdi/font/css/materialdesignicons.css'

Vue.use(Vuetify);

export default new Vuetify({
  theme: {
      dark: false,
      options: { customProperties: true },
      themes: {
        light: {
          primary: colors.cyan,
          secondary: colors.lime.accent1,
          accent: colors.teal.accent2
        },
      },
    },
});