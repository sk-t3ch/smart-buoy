<template>
  <v-card color="primary" dark>
    <v-responsive :aspect-ratio="1 / 1">
      <v-card-title>
        <v-toolbar flat dark color="primary">
          <v-icon large left color="secondary" v-if="measurement">
            {{ measurement.icon }}
          </v-icon>
          <v-toolbar-title class="white--text">{{
            name | capitalise
          }}</v-toolbar-title>
          <v-spacer></v-spacer>
          <v-btn @click.stop="toggle" icon color="accent" v-show="visualisation">
            <v-icon>{{ fullscreenIcon }}</v-icon>
          </v-btn>
          <v-switch
            color="accent"
            class="mt-4"
            v-model="visualisation"
          ></v-switch>
        </v-toolbar>
      </v-card-title>
        <v-card-text
          v-if="!visualisation"
          class="text-center align-center"
        >
          <div v-if="measurement" class="display-1 font-weight-black "
            >{{ measurement.value }} {{ measurement.unit }}</div
          >
          <v-progress-circular v-else indeterminate color="accent" />
        </v-card-text>
        <v-card-text v-else class="text-center">
            <div v-if="measurements">
              <fullscreen ref="fullscreen" @change="fullscreenChange">
                <v-btn
                  @click.stop="toggle"
                  v-show="fullscreen"
                  class="fullGraphButton"
                  icon
                >
                  <v-icon large>{{ fullscreenIcon }}</v-icon>
                </v-btn>
                <GChart
                  type="LineChart"
                  :data="[['Time', 'Value']].concat(measurements)"
                  :options="chartOptions"
                  v-bind:style="{ height: '100vh'}"
                  v-if="fullscreen"
                />
              </fullscreen>
              <GChart
                type="LineChart"
                v-if="!fullscreen"
                :data="[['Time', 'Value']].concat(measurements)"
                :options="chartOptions"
                v-bind:style="{ height: '100%'}"
              />
            </div>
            <v-progress-circular v-else indeterminate color="accent" />
        </v-card-text>
    </v-responsive>
  </v-card>
</template>

<script type="text/javascript">
import { GChart } from "vue-google-charts";
import fullscreen from "vue-fullscreen";
import Vue from "vue";
Vue.use(fullscreen);

export default {
  components: {
    GChart,
  },
  props: {
    name: {
      type: String,
      required: true,
      default: "",
    },
  },
  data() {
    return {
      icon: null,
      title: null,
      value: null,
      unit: null,
      visualisation: false,
      gChartData: false,
      chartOptions: {
        hAxis: { title: "Time", titleTextStyle: { color: "#333" } },
        vAxis: { title: this.name },
        colors: [
          this.$vuetify.theme.themes.light.primary.base,
          this.$vuetify.theme.themes.light.secondary,
        ],
        backgroundColor: this.$vuetify.theme.themes.light.accent,
        legend: "none",
      },
      fullscreen: false,
      fullscreenIcon: "mdi-fullscreen"
    };
  },
  computed: {
    measurement (){
      return this.$store.getters.mostRecentMeasurement(this.name);
    },
    measurements() {
      return this.$store.getters.gChartForMeasurements(this.name)
    },
    chartTitle() {
      return `${this.$options.filters.capitalise(this.name)} (${this.unit})`;
    },
  },
  watch: {
    chartTitle() {
      this.chartOptions.vAxis.title = this.chartTitle;
    },
  },
  methods: {
    toggle() {
      this.$refs["fullscreen"].toggle();
    },
    fullscreenChange(fullscreen) {
      this.fullscreenIcon = fullscreen
        ? "mdi-fullscreen-exit"
        : "mdi-fullscreen";
      this.fullscreen = fullscreen;
    },
  },
  filters: {
    capitalise: function (value) {
      if (!value) return "";
      value = value
        .split("_")
        .map((el) => el.charAt(0).toUpperCase() + el.slice(1))
        .join(" ");
      return value;
    },
  },
};
</script>


<style lang="css">
.fullGraphButton {
  z-index: 200;
  float: right;
  padding-right: 20px;
}
</style>
