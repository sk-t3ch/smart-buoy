<template lang="html">
    <v-card
      class="mx-auto"
      color="primary"
      dark
      max-width="450"
      min-height="320"
    >
    <GmapMap
      v-if="position"
      :center="position"
      :zoom="12"
      map-type-id="terrain"
      style="max-width: 450px; height: 320px"
    >
  </GmapMap>
  </v-card>
</template>

<script>
export default {
  props: ['name'],
  data(){
    return {
      position: false
    }
  },
  computed:{
    positionData(){
      return this.$store.getters.mostRecentMeasurement(this.name);
    }
  },
  watch: {
    positionData(){
      this.position = {lat:this.positionData.value[0], lng:this.positionData.value[1]};
    }
  },
}
</script>
