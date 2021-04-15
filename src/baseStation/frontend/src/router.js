import Vue from 'vue';
import Router from 'vue-router';


Vue.use(Router);

export default new Router({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
    {
      path: '/',
      name: 'dashboard',
      component: ()=> import('./views/Dashboard.vue'),
    },
    {
      path: '/about',
      name: 'about',
      component: ()=> import('./views/About.vue'),
    },
    {
      path: '/trends',
      name: 'trends',
      component: ()=> import('./views/Trends.vue'),
    }
  ]
})
