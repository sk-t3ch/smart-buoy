<template>
  <div>
    <update-feed v-model="drawer"></update-feed>
    <v-toolbar
      color="primary"
      class="centered"
      dark
      tabs
      app
    >
      <v-toolbar-title
      class="display-2 font-weight-black font-italic"
      >
      <v-icon color="secondary">star</v-icon>
      Smart Buoy Dashboard
      <v-icon color="secondary">star</v-icon>
    </v-toolbar-title>

      <v-spacer></v-spacer>

        <span class="group pa-2">
          <v-tooltip bottom>
            <template v-slot:activator="{ on }">
              <v-icon class="pa-1" v-on="on">{{ statusIcon }}</v-icon>
            </template>
            <span>Socket Connection</span>
          </v-tooltip>
          <v-tooltip bottom>
            <template v-slot:activator="{ on }">
              <v-icon @click.stop="drawer_toggle" class="pa-1" v-on="on">message</v-icon>
            </template>
            <span>View Live Feed</span>
          </v-tooltip>

        </span>

      <v-tabs
        slot="extension"
        v-model="active"
        color="primary"
        grow
      >
        <v-tabs-slider color="yellow"></v-tabs-slider>

        <v-tab
          v-for="route in routes"
          :key="route.name"
          :to="route.path"
        >
          {{ route.name }}
        </v-tab>
      </v-tabs>
    </v-toolbar>

  </div>
</template>


<script>
import UpdateFeed from './update_feed.vue'

  export default {
    components:{
      UpdateFeed,
    },
    sockets: {
      connect(){
        this.statusIcon = 'signal_wifi_4_bar';
      },
      disconnect(){
        this.statusIcon = 'error';
      }
    },
    data () {
      return {
        routes: this.$router.options.routes.map(route => ({
                name: route.name,
                path: route.path,
                })),
        active: null,
        text: 'Live updates received',
        statusIcon: 'error',
        drawer: null,
      }
    },
    methods: {
      drawer_toggle: function(){
        this.drawer = !this.drawer
      }
    }
}

</script>
