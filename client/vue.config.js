const path = require('path');

module.exports = {
  runtimeCompiler: true,
  css: {
    sourceMap: true
  },
  indexPath: path.resolve(__dirname, '../server/public/index.html'),
  outputDir: path.resolve(__dirname, '../server/public'),
  assetsDir: 'static',
  productionSourceMap: undefined,
  parallel: undefined
}
