<template lang="html">
  <div class="trends">
     <v-container grid-list-md text-xs-center>
      <v-layout row wrap>
        <v-flex xs12 sm6 md5 ma-1>
          <v-subheader>Measurements</v-subheader>
          <v-select
            v-model="chosenMeasurements"
            :items="measurements"
            attach
            chips
            multiple
          ></v-select>
        </v-flex>

        <v-flex xs12 sm6 md2 ma-1>
          <v-subheader>Start Date</v-subheader>
          <v-menu
            v-model="startDateMenu"
            :close-on-content-click="false"
            :nudge-right="40"
            lazy
            transition="scale-transition"
            offset-y
            full-width
            min-width="290px"
          >
            <template v-slot:activator="{ on }">
              <v-text-field
                v-model="startDate"
                prepend-icon="mdi-calendar-search"
                readonly
                v-on="on"
              ></v-text-field>
            </template>
            <v-date-picker v-model="startDate" @input="startDateMenu = false"></v-date-picker>
          </v-menu>
        </v-flex>

        <v-flex xs12 sm6 md2 ma-1>
          <v-subheader>End Date</v-subheader>
          <v-menu
            v-model="endDateMenu"
            :close-on-content-click="false"
            :nudge-right="40"
            lazy
            transition="scale-transition"
            offset-y
            full-width
            min-width="290px"
          >
            <template v-slot:activator="{ on }">
              <v-text-field
                v-model="endDate"
                prepend-icon="mdi-calendar-search"
                readonly
                v-on="on"
              ></v-text-field>
            </template>
            <v-date-picker v-model="endDate" @input="endDateMenu = false"></v-date-picker>
          </v-menu>
        </v-flex>

        <v-flex md2 ma-1>
          <v-subheader>Granularity</v-subheader>
          <v-slider
           v-model="granularity"
           :tick-labels="ticksLabels"
           :max="2"
           step="1"
           ticks="always"
           tick-size="4"
         ></v-slider>
        </v-flex>


        <v-flex xs12>
          <v-card color="primary" pa-5>
            <v-card-text>
              <GChart
              id="trendsChart"
              :style="{height: '50vh'}"
              type="LineChart"
              :data="chartData"
              :options="chartOptions"
              />
            </v-card-text>
            <v-card-actions>

              <v-btn
                 absolute
                 dark
                 fab
                 bottom
                 right
                 color="pink"
                 @click="downloadCSV"
               >
                 <v-icon>mdi-download</v-icon>
               </v-btn>

            </v-card-actions>
          </v-card>

        </v-flex>


        <v-spacer></v-spacer>
      </v-layout>
    </v-container>
  </div>
</template>

<script>
import { GChart } from 'vue-google-charts'

export default {

  components: {
    GChart,
  },
  data (){
    return {
      chosenMeasurements: [],
      measurements: this.prettifyMeasurementNames(),
      gChartData: [['Time', 'Value'], ['12:00:01', 5]],
      startDate: this.getYesterday(),
      endDate: new Date().toISOString().substr(0, 10),
      startDateMenu: false,
      endDateMenu: false,
      chartOptions: {
        chart: {
          title: this.name,
          subtitle: this.name,

        },
        backgroundColor: this.$vuetify.theme.themes.light.accent,
      },
      chartData: [
        ['Date', 'Value'],
        ['12/01/01', 12],
        ['13/01/01', 13],
      ],
      ticksLabels: ['Min', 'Hours', 'Days'],
      granularity: 2,
    }
  },
  computed: {
  },
  watch: {
    chosenMeasurements(){
      this.getChartData();
    },
    startDate(){
      this.getChartData()
    },
    endDate(){
      this.getChartData()
    },
    granularity(){
      this.getChartData()
    }
  },
  methods: {
    getYesterday(){
      let d = new Date()
      d.setDate(d.getDate() - 1);
      return d.toISOString().substr(0, 10);
    },
    prettifyMeasurementNames(){
      return this.$store.getters.trendMeasurementNames
      .map(
        name => name.split('_')).map(
          name => (name.map(
            el=> (el.charAt(0).toUpperCase() + el.slice(1))
          )).join(' ')
        )
    },
    getChartData(){
      let measurementNames;
      if (this.chosenMeasurements.length == 0) return;
      else {
        measurementNames = this.chosenMeasurements.map(
          name => name.split(' ')).map(
            name => (name.map(
              el=> (el.charAt(0).toLowerCase() + el.slice(1))
            )).join(' ')
          )
      }

      (async () => {
        let payload = {};
        payload.chosenMeasurements = measurementNames;
        payload.startDate = this.startDate;
        payload.endDate = this.endDate;
        payload.granularity = this.granularity;
        const baseURL = this.$store.state.piUrl;
        try{
          const rawResponse = await fetch(`${baseURL}/trends`, {
            method: 'POST',
            headers: {
              'Accept': 'application/json',
              'Content-Type': 'application/json'
            },
            body: JSON.stringify(payload)
          });
          let data = await rawResponse.json();

          console.log(data);
          data = data.map( (el, idx) => {
            if (idx!==0){
              el[0] = new Date(el[0]);
              return el
            }
            else{
              return el
            }
          });
          this.chartData = data;

        }
        catch(err){
          console.log("ERR ", err);
        }

      })();

    },
    downloadCSV(){
      let csv = '';
      for(let i = 0; i < this.chartData.length; i++) {
        for(let j = 0; j < this.chartData[i].length; j++) {
          csv += this.chartData[i][j] + ',';
        }
        csv += '\n';
      }
      const element = document.createElement('a');
      const name = `${this.chosenMeasurements.join(' ')} ${this.startDate}-${this.endDate}.csv`;
      element.setAttribute('download', name);
      element.setAttribute('href', 'data:application/octet-stream,' + encodeURIComponent(csv));
      element.style.display = 'none';
      document.body.appendChild(element);
      element.click();
      document.body.removeChild(element);
    },
  },
}
</script>
