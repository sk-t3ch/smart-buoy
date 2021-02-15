<template>
  <div class="about">
    <br/>
    <br/>
    <v-container grid-list-md text-xs-center>
        <v-timeline>
          <v-timeline-item
            v-for="entry in entries"
            :key="entry.id"
            color="red lighten-2"
            large
          >
            <template v-slot:opposite>
              <v-parallax :src="'https://s3.eu-west-2.amazonaws.com/t3chflicks.storage/' + entry.image" height=400></v-parallax>
            </template>
            <v-card class="elevation-2">
              <v-card-title class="headline">{{ entry.title }} : {{ entry.date }}</v-card-title>
              <v-card-text>
                <div v-html="entry.summary"> </div>
              </v-card-text>
            </v-card>
          </v-timeline-item>
        </v-timeline>

    </v-container>
  </div>

</template>


<script >

export default{
    data(){
      return{
        entries: [
          {
            id: 1,
            date:'September 2017',
            title: 'Research Trip to Grenada no.1',
            summary: `
            After countless applications for funding, months of preparation, a last minute passport drama and an eight hour flight, we land in Grenada with a large case of surveying equipment in tow. We’re here to carry out research for my undergraduate dissertation which explores how and why Grenada’s beaches are changing. Over the four weeks we’re in the country, we survey 11 beaches around the island, bask in the glorious weather and thoroughly embrace the Caribbean culture.
            <br></br>
            During our research trip, we have the opportunity to meet with stakeholders from the Government, non-governmental organisations (NGOs) and talk informally with countless business owners and residents. On such a small island, the coast is undeniably an important resource, but balancing economic development with sustainable coastal resource use is a challenge.
            <br></br>
            After four amazing weeks, we head back to the UK, notepads full of scribbles and heads full of ideas. Somehow, we’re both hoping our Grendian adventure doesn’t end here…

                      `,
            image: 'trip_1.JPG',
          },
          {
            id: 2,
            date:'April 2018',
            title: 'Dissertation Hand-in',
            summary: `
            It’s been a massive struggle and taken countless hours/days (and years off my life…) but my dissertation is finally complete. I hand it into my University department on a cloudy Monday morning.
            <br></br>
            Something particularly challenging was finding secondary weather data on a fine enough spatial and temporal scale to be useful and meaningful. That got us thinking...

                    `,
            image: 'finished_dissertation.jpg',
          },
          {
            id: 3,
            date:'October 2018',
            title: 'Collecting Data',
            summary: `
            A few months after graduating, we’re getting stuck into our first jobs. It’s not that my dissertation is keeping me up at night (not any more, at least), but we begin to think about better ways to take measurements of water and air characteristics which would be helpful in monitoring coastal change. For my dissertation, I used data taken from the ERA-Interim database, which are satellite measurements. Like all data, there is a trade-off between spatial footprint and measurement frequency. If I were to do my dissertation again, it would be preferable to have data on a beach-specific rather than island-wide spatial resolution.
            <br></br>
            So...why not make something which can do that? We create a pretty lengthy list of things we would like to measure, loosely grouped by air and water characteristics. Basically, the list is stuff that would help you establish wave regime at any given point in time (including anomalous, short-duration, high impact events like hurricanes and storm surges; and long-period seasonal swells). This is also helpful to be able to link to atmospheric characteristics. Wave regime determines how much energy is received at a beach, therefore what a beach looks like.
            <br></br>
            Collecting the data is only half the battle, displaying it in a usable format which is easy to access is just as important as having it in the first place! This threw up a couple of problems: how to transfer the data from sensors to somewhere accessible and how to display it. Conventional remote data-gathering technology uses phone networks to send data - a bit pricey for our project range.
                      `,
            image: 'ring-binders-aligned-2654130_1920.jpg',
          },
          {
            id: 4,
            date:'December 2018',
            title: 'Idea',
            summary: `
            After a great deal of thinking and deliberating and procrastinating, we think it would be a good idea to make a
            buoy capable of taking air/water measurements. If you stick an aerial on the buoy, it can send data to a remote receiver.
            Data can be viewed on a user-friendly, interactive dashboard. Well, that’s the dream...`,
            image: 'brain.jpg',
          },
          {
            id: 5,
            date:'May 2019',
            title: 'Version 1',
            summary: `
            We built the first version whilst on a 3 week trip to Grenada. You can see how we built it
            at <a href="https://t3chflicks.com/shop/kit/smart-buoy">T3chFlicks</a>, or
            <a href="https://t3chflicks.com/shop/kit/smart-buoy">Instructables</a>.
            We are pretty happy with the outcome, but are of course left with regrets of design
            decisions of a project that you only give yourselves 3 weeks to create!
            `,
            image: 'inthesea.png',
          },
          {
            id: 6,
            date:'Future',
            title: 'Version 2',
            summary: `
            This was definitely our most exciting project so far and we’d love to take it further. But we think that doing so effectively, requires a community. Let’s do it!
            `,
            image: 'sunrise.jpg',
          },
        ]
      }
    },
    methods: {

    }
}
</script>
