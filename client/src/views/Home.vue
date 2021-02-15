<template>
  <div class="home">
     <v-container grid-list-md text-xs-center>
        <v-layout row wrap :v-if="measurements">
          <v-flex v-for="measurement in measurements" :key="measurement" xs4 sm6>
              <data-card  :name="measurement" v-if="measurement!=='location'"></data-card>
              <data-map :name="measurement" v-else></data-map>
          </v-flex>
        </v-layout>
      </v-container>
  </div>
</template>

<script>
import DataCard from '../components/data_card.vue'
import DataMap from '../components/data_map.vue'

export default {
  name: 'home',
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
