<template>
    <v-navigation-drawer
      :value="value"
      @input="$emit('input', $event)"
      fixed
      right
      app
      class="primary"
    >
    <v-card-title primary-title centered class="text-xl-h4 text-sm-h3 white--text font-weight-black font-italic">
      Updates
    </v-card-title>
      <v-list class="ma-3">
        <v-list-item v-for="update in recentUpdates"
        :key="update.icon + update.time + Math.random()"
        class="ma-1"
                  >

          <v-list-item-content>
            <div class="text-xs-center">
              <v-chip
              color="secondary"
              class="black--text"
              >
                <v-avatar>

                  <v-icon>{{ update.icon }}</v-icon>
                </v-avatar>
                {{ update.value }}{{ update.unit }}  @ {{ update.time }}
              </v-chip>
            </div>
          </v-list-item-content>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>
</template>


<script type="text/javascript">

export default{
  props: ['value'],
  computed: {
    recentUpdates(){
      return this.$store.getters.recentUpdates;
    }
  }
}
</script>
