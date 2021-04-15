<template>
  <div class="dashboard">
     <v-container grid-list-md text-xs-center>
        <v-layout row wrap :v-if="measurements">
          <v-flex v-for="measurement in measurements" :key="measurement" xs12 sm6 md6 lg4>
              <data-card  :name="measurement" v-if="measurement!=='location'"></data-card>
              <data-map :name="measurement" v-else></data-map>
          </v-flex>
        </v-layout>
      </v-container>
  </div>
</template>

<script>
import DataCard from '../components/dataCard.vue'
import DataMap from '../components/dataMap.vue'

export default {
  name: 'dashboard',
  components: {
    DataCard,
    DataMap,
  },
  data(){
    return {
      measurements: this.$store.getters.measurementNames,
    }
  }
}
</script>
