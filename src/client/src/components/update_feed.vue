<template>
    <v-navigation-drawer
      :value="value"
      @input="$emit('input', $event)"
      fixed
      right
      app
      class="primary"
    >
    <v-card-title primary-title centered class="display-1 white--text font-weight-black font-italic">
      Updates
    </v-card-title>
      <v-list>
        <v-list-tile v-for="update in $store.getters.recentUpdates"
        :key="update.time"
                  >

          <v-list-tile-content>
            <div class="text-xs-center">
              <v-chip close @input="remove_update(update.time)"
              class="secondary"
              >
                <v-avatar>

                  <v-icon>{{ update.icon }}</v-icon>
                </v-avatar>
                {{ update.value }}{{ update.unit }}  @ {{ update.time }}
              </v-chip>
            </div>
          </v-list-tile-content>
        </v-list-tile>
      </v-list>
    </v-navigation-drawer>
</template>


<script type="text/javascript">

export default{
  props: ['value'],
  methods:{
    remove_update: function(time){
      const index_to_remove = this.updates.findIndex(el=>el.time===time)
      this.updates.splice(index_to_remove, 1)
    }
  },
  data(){
    return {}
  },
}
</script>
