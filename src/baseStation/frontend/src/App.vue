<template>
  <v-app>
    <nav-bar />
    <v-main class="accent">
      <router-view> </router-view>
    </v-main>
    <v-footer app class="topped">
      <v-spacer />
      <v-col cols="auto" class="text-none white--text">
        <v-btn
          dark
          href="https://t3chflicks.org"
          target="_blank"
          text
          class="text-none px-1 ml-0 mr-1 elevation-0"
        >
          T3chFlicks </v-btn
        >- A tech focused education and services company
      </v-col>
    </v-footer>
  </v-app>
</template>



<script type="text/javascript">
import NavBar from "./components/navBar.vue";

export default {
  components: {
    NavBar,
  },
  created(){
    this.$store.commit('updatePiUrl', location.origin)
  }
};
</script>
<style scoped>
  .topped {
    z-index: 3;
    border-top: 4px solid var(--v-accent-base) !important;
    background-color: var(--v-primary-base)  !important
  }
</style>