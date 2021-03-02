import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    measurements: {
      location:{
        name: 'Location',
        data: [[]],
        unit: '',
        icon: 'mdi-crosshairs-gps',
        trend: false,
      },
      air_pressure: {
        name: 'Air Pressure',
        data: [[]],
        unit: 'KPa',
        icon: 'mdi-weather-windy',
        trend: true
      },
      wave_height:{
        name: 'Wave Height',
        data: [[]],
        unit: 'm',
        icon: 'mdi-current-ac',
        trend: true
      },
      wave_period:{
        name: 'Wave Period',
        data: [[]],
        unit: 's',
        icon: 'mdi-current-ac',
        trend: true
      },
      wave_power:{
        name: 'Wave Power',
        data: [[]],
        unit: 'kW/m',
        icon: 'mdi-current-ac',
        trend: true
      },
      air_temperature: {
        name: 'Air Temperature',
        data: [[]],
        unit: '°C',
        icon: 'mdi-thermometer',
        trend: true
      },
      water_temperature: {
        name: 'Water Temperature',
        data: [[]],
        unit: '°C',
        icon: 'mdi-thermometer',
        trend: true
      },
      voltage: {
        name: 'Voltage',
        data: [[]],
        unit: 'V',
        icon: 'mdi-battery',
        trend: true
      },
      current: {
        name: 'Current',
        data: [[]],
        unit: 'mA',
        icon: 'mdi-power-plug',
        trend: true
      },
    }
  },
  getters: {
    measurementNames: state => {
      return Object.keys(state.measurements);
    },
    trendMeasurementNames: state => {
      return Object.entries(state.measurements).filter(el=>el[1].trend).map(el=>el[0]);
    },
    // gets the side panel showing updates
    recentUpdates: state => {
      let result = [];
      for (const measurement of Object.values(state.measurements)) {
        measurement.data.forEach( dataPoint =>{
          if (dataPoint.length < 1) return;
          try{
            result.push({
              name: measurement.name,
              dtime: dataPoint[0],
              value: dataPoint[1],
              time: `${dataPoint[0].getHours()}:${dataPoint[0].getMinutes()}:${dataPoint[0].getSeconds()}`,
              icon: measurement.icon,
            })
          }
          catch(e){
            dataPoint[0] = new Date(dataPoint[0]);
            result.push({
              name: measurement.name,
              dtime: dataPoint[0],
              value: dataPoint[1],
              time: `${dataPoint[0].getHours()}:${dataPoint[0].getMinutes()}:${dataPoint[0].getSeconds()}`,
              icon: measurement.icon,
            })
          }
        })
      }
      result.sort( (a, b) => {
        return  new Date(b.dtime) - new Date(a.dtime) ;
      });
      return result.slice(0, 20);
    },
    current_value_of_measurement: (state) => (name) =>{
      return state.measurements[name].data.slice(-1)[0][1];
    },
    mostRecentMeasurement: state => (name) => {
      let measurementInfo = state.measurements[name];
      if(measurementInfo.data.length > 1){
        const data_point = measurementInfo.data.slice(-1)[0];
        return {time: data_point[0], value:data_point[1], unit: measurementInfo.unit, icon:measurementInfo.icon };
      }
    },
    gChartForMeasurements: (state) => (name) => {
      if (state.measurements[name].data.length > 1){
        return state.measurements[name].data.slice(1);
      }
    },

  },
  mutations: {
    addDataPoint(state, data){
      let measurementData;
      try {
        measurementData = state.measurements[data.name].data
      } catch (e) {
        return
      }
      while(measurementData.length > 50){
        measurementData.shift();
      }
      measurementData.push(data.dataPoint);
    }
  },
  actions: {
    "SOCKET_buoy_measurement_update"({ commit }, data){
      const update = JSON.parse(data);
      const name = update.name;
      let value;
      if (name !== 'location'){
        value = parseFloat(update.value);
      }
      else{
        value = update.value;
      }
      const time = new Date(update.time);
      const storeMeasurementName = name.replace(' ', '_');
      commit('addDataPoint', {
        name: storeMeasurementName,
        dataPoint: [time, value],
      });
    },

  }
})
