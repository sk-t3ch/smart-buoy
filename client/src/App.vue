<template>
  <v-app>
    <navbar/>
    <v-content
    class="accent"
    >
      <router-view>
      </router-view>
    </v-content>
  </v-app>

</template>



<script type="text/javascript">
import Navbar from './components/nav_bar.vue'

export default {
  components: {
    Navbar
  }
}

</script>
