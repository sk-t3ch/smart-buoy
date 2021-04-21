<template>
  <div>
    <update-feed v-model="drawer"></update-feed>
    <v-app-bar color="primary" class="centered" dark app tabs prominent>
      <v-container class="mx-0 px-0" fluid>
        <v-row class="mx-0 px-0">
          <v-col cols="8" xs="8" sm="9" md="10">
            <v-row justify="space-between" class="mx-0 px-0" >
              <v-col cols="4" xs="12" sm="12" md="5" lg="5" xl="3">
                <div
                  class="text-xl-h4 text-sm-h3 font-weight-black font-italic pr-2 mr-2 text-no-wrap"
                >
                  Smart Buoy 
                  <v-btn class="pl-0 ml-0" color="white" target="_blank" icon href="https://github.com/sk-t3ch/smart-buoy">
                    <v-icon>mdi-github</v-icon>
                  </v-btn>
                </div>
              </v-col>
              <v-col cols="12" sm="12" md="6" lg="6">
                <v-text-field
                  color="accent"
                  dark
                  label="Enter your Smart Buoy URL"
                  ref="addressbar"
                  dense
                  v-model="piUrl"
                  rounded
                  outlined
                  :append-icon="piUrlSet ? 'mdi-pencil' : 'mdi-check'"
                  @click:append="piUrlSet ? editUrl() : setUrl()"
                  @click="editUrl"
                  @keyup.enter="setUrl"
                  :readonly="piUrlSet"
                  placeholder="http://raspberrypi.local:5000"
                >
                </v-text-field>
              </v-col>
              <v-spacer/>
            </v-row>
          </v-col>
          <v-spacer/>
          <v-col cols="4" xs="4" sm="3" md="2">
            <div class="float-right">
              <v-tooltip bottom>
                <template v-slot:activator="{ on }">
                  <v-icon class="pa-1" v-on="on" :color="statusColor">{{
                    statusIcon
                  }}</v-icon>
                </template>
                <span>Socket Connection</span>
              </v-tooltip>
              <v-tooltip bottom>
                <template v-slot:activator="{ on }">
                  <v-icon @click.stop="drawerToggle" class="pa-1" v-on="on"
                    >mdi-message</v-icon
                  >
                </template>
                <span>View Live Feed</span>
              </v-tooltip>
            </div>
          </v-col>
        </v-row>
      </v-container>

      <v-tabs slot="extension" v-model="active" grow>
        <v-tabs-slider color="accent"></v-tabs-slider>

        <v-tab v-for="route in routes" :key="route.name" :to="route.path">
          {{ route.name }}
        </v-tab>
      </v-tabs>
    </v-app-bar>
  </div>
</template>


<script>
// import SocketIO from "socket.io-client";
import UpdateFeed from "./updateFeed.vue";

export default {
  components: {
    UpdateFeed,
  },
  sockets: {
    connect() {
      this.statusColor = "secondary";
      this.statusIcon = "mdi-wifi-strength-4";
    },
    disconnect() {
      this.statusColor = "red";
      this.statusIcon = "mdi-alert-circle";
    },
  },
  data() {
    return {
      piUrl: this.$store.state.piUrl,
      piUrlSet: true,
      routes: this.$router.options.routes.map((route) => ({
        name: route.name,
        path: route.path,
      })),
      active: null,
      text: "Live updates received",
      statusIcon: "mdi-alert-circle",
      statusColor: "red",
      drawer: null,
    };
  },
  methods: {
    drawerToggle: function () {
      this.drawer = !this.drawer;
    },
    setUrl() {
      this.piUrlSet = true;
      this.$refs.addressbar.blur();
      const urlObj = new URL(this.piUrl);
      console.log("urlObj", urlObj);
      this.$store.commit('updatePiUrl', this.piUrl)
    },
    editUrl() {
      this.piUrlSet = false
    },
  },
};
</script>