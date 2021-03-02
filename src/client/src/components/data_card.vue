<template>
  <v-card
    class="mx-auto"
    color="primary"
    dark
    max-width="450"
    min-height="320"
  >
    <v-card-title>
      <v-toolbar dark flat color="primary">
        <v-icon
          large
          left
          >
          {{ icon }}
        </v-icon>
        <v-toolbar-title class="white--text">{{ name | capitalise }}</v-toolbar-title>
        <v-spacer></v-spacer>
        <v-btn @click.stop="toggle" icon>
          <v-icon v-if="visualisation">{{ fullscreen_icon }}</v-icon>
        </v-btn>
        <v-btn icon>
          <v-switch
          v-model="visualisation"
          ></v-switch>
        </v-btn>

      </v-toolbar>
    </v-card-title>

    <v-card-text class="headline font-weight-bold" v-if="!visualisation" >
      <v-container grid-list-md align-center justify-space-around column fill-height>
        <v-flex xs12>
          <span v-if="value" class="display-1 font-weight-black" >{{ value }} {{ unit }}</span>
          <v-progress-circular
          v-else
          indeterminate
          color="accent"
          />
        </v-flex>
      </v-container>


    </v-card-text>

    <v-card-text   v-else>

      <fullscreen ref="fullscreen" @change="fullscreenChange">
        <v-btn @click.stop="toggle" v-show="fullscreen" class="fullGraphButton" icon>
          <v-icon large>{{ fullscreen_icon }}</v-icon>
        </v-btn>

        <GChart
        type="LineChart"
        :data="gChartData"
        :options="chartOptions"
        v-if="gChartData"
        v-bind:style="{ height: graphHeight}"
        />

        <v-progress-circular
        v-else
         indeterminate
         color="accent"
         />
       </fullscreen>

    </v-card-text>




  </v-card>
</template>

<script type="text/javascript">
import { GChart } from 'vue-google-charts'
import fullscreen from 'vue-fullscreen'
import Vue from 'vue'
Vue.use(fullscreen)

export default{
  components: {
    GChart
  },
  props: {
    name: {
      type: String,
      required: true,
      default: ''
      }
    },
  data(){
    return {
      icon: null,
      title: null,
      value: null,
      unit: null,
      visualisation: false,
      gChartData: false,
      chartOptions: {
        hAxis: {title: 'Time',  titleTextStyle: {color: '#333'}},
        vAxis: {title: this.name},
        colors: [this.$vuetify.theme.primary.base, this.$vuetify.theme.secondary],
        backgroundColor: this.$vuetify.theme.accent,
        legend: 'none'
      },
      graphHeight: '30vh',
      fullscreen: false,
      fullscreen_icon: 'fullscreen',
    }
  },
  computed: {
    measurementData(){
      if (!this.visualisation){
         return this.$store.getters.mostRecentMeasurement(this.name);
      }
      else{
        return [['Time', 'Value']].concat(this.$store.getters.gChartForMeasurements(this.name));
      }
    },
    chartTitle(){
      return `${this.$options.filters.capitalise(this.name)} (${this.unit})`
    }
  },
  watch: {
    measurementData(){
      if (!this.visualisation){
        let r = this.measurementData;
        this.icon = r.icon;
        this.value = r.value;
        this.unit = r.unit;
      }
      else{
        this.gChartData = this.measurementData;
      }
    },
    chartTitle(){
      this.chartOptions.vAxis.title = this.chartTitle;
    }
  },
  methods:{
    toggle () {
      this.$refs['fullscreen'].toggle()
    },
    fullscreenChange (fullscreen) {
      this.graphHeight = fullscreen ? '100vh': '30vh';
      this.fullscreen_icon = fullscreen? 'fullscreen_exit': 'fullscreen';
      this.fullscreen = fullscreen
    }
  },
  filters: {
    capitalise: function (value) {
      if (!value) return ''
      value = value.split('_').map(el=>el.charAt(0).toUpperCase() + el.slice(1)).join(' ')
      return value
    },
  }
}


</script>


<style lang="css">
  .fullGraphButton{
    z-index: 200;
    float: right;
    padding-right: 20px;
  }
</style>
