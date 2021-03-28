<template>
  <div>
    <h1>Hi</h1>
    <Keypress
      key-event="keypress"
      :key-code="65"
      @success="directionKeyHandler"
    />
    <Keypress
      key-event="keypress"
      :key-code="87"
      @success="directionKeyHandler"
    />
    <Keypress
      key-event="keypress"
      :key-code="68"
      @success="directionKeyHandler"
    />
    <Keypress key-event="keypress" :key-code="83" @success="someMethod" />
    <!-- <Keypress
      key-event="keypress"
      :key-code="38"
      @success="directionKeyHandler(38)"
    />
    <Keypress
      key-event="keypress"
      :key-code="39"
      @success="directionKeyHandler(39)"
    />
    <Keypress
      key-event="keypress"
      :key-code="40"
      @success="directionKeyHandler(40)"
    /> -->
    <Keypress key-event="keypress" :key-code="13" @success="someMethod" />
  </div>
</template>

<script>
export default {
  name: "CarControlComp",
  components: {
    Keypress: () => import("vue-keypress"),
  },
  data() {
    return {
      isConnected: false,
    };
  },
  methods: {
    someMethod(event, expectedEvent, message) {
      // Do something
      console.log("sth wrong");
      console.log(event, expectedEvent, message);
    },
    directionKeyHandler(event) {
      console.log(event);
      //   switch (keyCode) {
      //     case 37: // Arrow LEFT
      //       console.log("left");
      //       break;
      //     case 38: // Arrow UP
      //       console.log("up");
      //       break;
      //     case 39: // Arrow RIGHT
      //       console.log("right");
      //       break;
      //     case 40: // Arrow DOWN
      //       console.log("down");
      //       break;
      //   }
    },
  },
};
</script>

<style></style>
