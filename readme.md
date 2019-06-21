# WIllD

A 40% keyboard kit based on Daisy (https://github.com/qmk/qmk_firmware/tree/master/keyboards/daisy)

Make example for this keyboard (after setting up your build environment):

    make willd:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.


# Keymap

The "default" keymap included is the same as the Planck keyboard. Keys not present are mapped as KC_NO, while unused keys are KC_TLNS.

A printable picture showing this layout is available here: https://imgur.com/9mSF0yf


```
$ make willd:[default|<name>]
```

# Features

I personally do not like to use the TAPPING_TERM timer to ignore a layer activation in a double function key, so I prgrammed the layers to be activated if the key is held and any other key is tapped. If the layer key is released without tappping any other key, the primary keycode is released. Right space key works like this. The QMK RETRO TAPPING feature do not activate the layer if the combination is made before the TAPPING_TERM time runs out, while my implementation activates the layer immediately.

I also wanted to use a key to toggle a layer, but I wanted it act different in both layers. So I reprogrammed the key to activate a layer when tap, and, in this new layer, the toggle only returns if the key is held more than a defined time.

The keyboard has an encoder, that I use to increase and decrease sound.

The keyboard also have indicator leds, that I use to identify in which layer the keyboard is.
