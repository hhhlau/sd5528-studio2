<template>
  <div class="control-container">
    <div class="left-container">
      <div class="liveview-block">
        <img
          src="http://192.168.0.9:8080/stream.mjpg"
          class="car-live-view"
          alt=""
        />
      </div>
      <div class="scene-selection-block">
        <CarControl></CarControl>
        <v-btn color="success" @click="testFunc">Text</v-btn>
      </div>
    </div>
    <div class="right-container">
      <div class="chart-block">
        <svg
          id="chart"
          ref="chart"
          viewBox="0 0 200 200"
          xmlns="http://www.w3.org/2000/svg"
        >
          <path
            fill="#FF0066"
            d="M37.3,-26.4C51.2,-12.4,67.3,3.3,64.3,14C61.3,24.6,39.3,30.3,19.2,40C-0.9,49.8,-19.2,63.7,-32.3,60.1C-45.3,56.4,-53.3,35.2,-49.5,20.3C-45.8,5.3,-30.4,-3.3,-20.2,-16.6C-10,-29.8,-5,-47.7,3.4,-50.3C11.7,-53,23.4,-40.5,37.3,-26.4Z"
            transform="translate(100 100)"
          />
        </svg>
      </div>
      <div class="msg-block"></div>
    </div>
  </div>
</template>

<script>
import CarControl from "@/components/CarControl";
import anime from "animejs";

const isReachable = require("is-reachable");

// function delay(ms) {
//   return new Promise(function (resolve) {
//     setTimeout(function () {
//       resolve();
//     }, ms);
//   });
// }

export default {
  name: "Control",
  components: { CarControl },

  data() {
    return {
      isCarViewOnline: false,
      paths: [
        "M37.3,-26.4C51.2,-12.4,67.3,3.3,64.3,14C61.3,24.6,39.3,30.3,19.2,40C-0.9,49.8,-19.2,63.7,-32.3,60.1C-45.3,56.4,-53.3,35.2,-49.5,20.3C-45.8,5.3,-30.4,-3.3,-20.2,-16.6C-10,-29.8,-5,-47.7,3.4,-50.3C11.7,-53,23.4,-40.5,37.3,-26.4Z",
        "M41.9,-32.7C55.7,-16.2,69,1.3,63,9C56.9,16.8,31.5,14.7,14.3,18.8C-2.9,22.9,-11.9,33.2,-20.3,32.7C-28.6,32.3,-36.4,21.2,-41.3,7.2C-46.3,-6.8,-48.4,-23.6,-41.1,-38.6C-33.8,-53.6,-16.9,-66.8,-1.4,-65.7C14.1,-64.6,28.2,-49.2,41.9,-32.7Z",
      ],
    };
  },
  mounted() {
    // anime({
    //   targets: "div",
    //   translateX: 250,
    //   rotate: "1turn",
    //   backgroundColor: "#FFF",
    //   duration: 800,
    // });
  },
  methods: {
    testFunc: function () {
      anime({
        targets: this.$refs.chart,
        // translateX: 250, // -> '250px'
        // rotate: 540, // -> '540deg'
        points: [
          {
            value: this.paths[0],
          },
          {
            value: this.paths[1],
          },
        ],
        easing: "easeOutQuad",
        duration: 2000,
        loop: true,
      });
    },
    testCarStream: async function () {
      this.isCarViewOnline = await isReachable("192.168.0.9:8080");
      if (this.isCarViewOnline) {
        console.log("the car is online now");
      } else {
        console.log("the car is offline");
      }
    },
  },
};
</script>

<style>
.control-container {
  width: 100vw;
  height: 100%;
  background-color: #fefefe;
  display: flex;
}
.left-container {
  width: 60vw;
  background-color: red;
}
.liveview-block {
  width: 100%;
  background-color: pink;
  aspect-ratio: 16 / 9;
}
.right-container {
  width: 40vw;
  background-color: blue;
}
.chart-block,
.msg-block {
  width: 100%;
  height: 50%;
}
.car-live-view {
  width: 100%;
}
</style>
