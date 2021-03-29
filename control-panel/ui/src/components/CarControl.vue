<template>
  <div>
    <h1>Hi</h1>
    <Keypress
      key-event="keydown"
      :key-code="38"
      @success="directionKeyHandler(38)"
    />
    <Keypress
      key-event="keydown"
      :key-code="40"
      @success="directionKeyHandler(40)"
    />
    <Keypress
      key-event="keydown"
      :key-code="37"
      @success="directionKeyHandler(37)"
    />
    <Keypress
      key-event="keydown"
      :key-code="39"
      @success="directionKeyHandler(39)"
    />
    <Keypress key-event="keyup" :key-code="38" @success="stopTheCar" />
    <Keypress key-event="keyup" :key-code="40" @success="stopTheCar" />
    <Keypress key-event="keyup" :key-code="37" @success="stopTheCar" />
    <Keypress key-event="keyup" :key-code="39" @success="stopTheCar" />

    <Keypress key-event="keydown" :key-code="32" @success="captureImg" />
    <Keypress key-event="keydown" :key-code="84" @success="toggleDrivingMode" />
  </div>
</template>

<script>
// const socket = new WebSocket("ws://158.132.55.98:81");
const socket = new WebSocket("ws://158.132.55.92:82/client");
socket.addEventListener("open", function () {
  socket.send("Hello Server!");
});

// Listen for messages
socket.addEventListener("message", function (event) {
  console.log("Message from server ", event.data);
});
export default {
  name: "CarControlComp",
  components: {
    Keypress: () => import("vue-keypress"),
  },
  data() {
    return {
      isConnected: false,
      isManual: true,
    };
  },
  mounted() {},
  methods: {
    captureImg() {
      // Do something
      console.log("Image captured");
    },
    toggleDrivingMode() {
      console.log("hi");
      this.isManual = !this.isManual;
    },
    stopTheCar() {
      socket.send(`STOP`); //0
    },
    directionKeyHandler(keyCode) {
      switch (keyCode) {
        case 37: // Arrow LEFT
          console.log("left"); //4
          socket.send(`LEFT`);
          break;
        case 38: // Arrow UP
          console.log("up"); //1
          socket.send(`UP`);

          break;
        case 39: // Arrow RIGHT
          console.log("right"); //3
          socket.send(`RIGHT`);
          break;
        case 40: // Arrow DOWN
          console.log("back"); //2
          socket.send(`BACK`);
          break;
      }
    },
  },
};
</script>

<style></style>
