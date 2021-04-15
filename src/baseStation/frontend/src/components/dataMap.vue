<template lang="html">
    <v-card
      class="mx-auto"
      color="primary"
      dark
    >
    <v-responsive :aspect-ratio="1/1">
      <GmapMap
        v-if="position"
        :center="position"
        :zoom="12"
        map-type-id="terrain"
        style="height: 100%"
      ></GmapMap>
    </v-responsive>
  </v-card>
</template>

<script>
export default {
  props: ['name'],
  computed:{
    position(){
      const pos = this.$store.getters.mostRecentMeasurement(this.name);
      console.log("pos", pos)
      if (pos.value && pos.value.length > 1){
        return {lat:pos.value[0], lng:pos.value[1]};
      }
      return false
    }
  },
}
</script>
