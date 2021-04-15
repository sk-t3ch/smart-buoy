const path = require('path');

module.exports = {
  transpileDependencies: [
    'vuetify'
  ],
  assetsDir: "static",
  pages: {
    index: {
      entry: 'src/main.js',
      title: 'SmartBuoy'
    }
  }
}
